//-----------------------------------------------------------------------------
//  Copyright (C) Siemens AG 2005  All Rights Reserved.
//-----------------------------------------------------------------------------
//
//     Project: IDEA
//        File: \n4\pkg\MrServers\MrVista\Ice\IceIdeaFunctors\IceNetworkPosition\NetworkPositionFunctor.cpp
//     Version: 2.0
//      Author: BV_ICE
//        Date: n.a.
//    Language: C++
// Description: <IceFunctor to send additionally inverted greyscale image to database.>
//
//-----------------------------------------------------------------------------

// NetworkPositionFunctor:
#include "MrServers/MrVista/Ice/IceIdeaFunctors/IceNetworkPosition/NetworkPositionFunctor.h"
// GetSeriesInstanceUID
#include "MrServers/MrVista/include/Ice/IceUtils/IceUtils.h"

//Feedback Service
#include "MrServers/MrVista/include/Iris/Services/IFeedback.h"
//SEQData
#include "MrServers/MrMeasSrv/SeqIF/libMES/SEQData.h"
//Interventional FB Data
#include "NetworkPositionData.h" 
//Reference to feedback service object
IFeedback::Pointer m_pFeedbackSvc;
NetPosData m_NetPosData; //Feedback buffer local
SEQData m_SeqData; //Feedback buffer to send

//Network communication
#include "ace/SOCK_Connector.h"
#include "ace/SOCK_Stream.h"
#include "ace/Barrier.h"
#include "ace/Time_Value.h"
#include "ace/OS_main.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_sys_socket.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_stdlib.h"
#include "ace/OS_NS_stdio.h"
#include "ace/OS_NS_netdb.h"
#include "ace/Default_Constants.h"

ACE_SOCK_Stream client_stream; 
ACE_SOCK_Connector client_connector;
ACE_Time_Value connTimeout(5); // allow 5 seconds to connect
ACE_Time_Value netTimeout(1000); // allow 1 second during tracking
char request[] = "FEEDME\n";
ACE_INET_Addr addr(21201, "192.168.2.6");

// the rotation and position parameters
double adRotParams[6];

NetworkPositionFunctor::NetworkPositionFunctor()
: m_bIs3D(false)
, m_bIsEllipFilter(false)
, m_flCmBolusVolume(0.0)
, m_nImageCols(0)
, m_nImageLins(0)
, m_nImageSlcs(0)
, m_bNoInversion(true)
{
	// register callback for FirstCall in Functor base class
	// (otherwise method FirtsCall(...) won't be called):
	addCB(IFirstCall);
}


NetworkPositionFunctor::~NetworkPositionFunctor()
{}


IResult NetworkPositionFunctor::EndInit(IParcEnvironment* env)
{
	int iConResult;
	ICE_SET_FN("NetworkPositionFunctor::EndInit(env)")

	// always call base class:
	IResult res = IceImageReconFunctors::EndInit(env);
	if (failed(res))
	ICE_RET_ERR("Error calling IceImageReconFunctors::EndInit(), aborting...", res)

	//Retrieve instance of feedback svc to send feedback
	m_pFeedbackSvc=Parc::cast<IFeedback>(env->Item("FeedbackSvc"));
	if(!m_pFeedbackSvc)
	ICE_RET_ERR("Could not get feedback svc in IceImageReconFunctors::EndInit(), aborting...", I_FAIL)
	
	// connect to TCP position server
	iConResult = client_connector.connect(client_stream, addr, &connTimeout);
	if (iConResult == -1 ) {
		ACE_ERROR_RETURN((LM_ERROR, ACE_TEXT ("%p\n"), ACE_TEXT ("status")), 100);
		ICE_RET_ERR("Failure to establish connection in IceImageReconFunctors::EndInit(), aborting...", I_FAIL)
	}
//	ICE_OUT("Configured NetworkPositionFunctor." <<
//	"\n  m_bIs3D............. = " << ((m_bIs3D == true) ? "true" : "false") <<
//	"\n  m_bIsEllipFilter.... = " << ((m_bIsEllipFilter == true) ? "true" : "false") <<
//	"\n  m_flCmBolusVolume... = " << m_flCmBolusVolume <<
//	"\n  m_nImageCols........ = " << m_nImageCols <<
//	"\n  m_nImageLins........ = " << m_nImageLins <<
//	"\n  m_nImageSlcs........ = " << m_nImageSlcs <<
//	"\n  m_bNoInversion...... = " << ((m_bNoInversion == true) ? "true" : "false") <<
//	"\n  m_sInvertedSeriesUID = " << m_sInvertedSeriesUID);
	return I_OK;
}


IResult NetworkPositionFunctor::FirstCall(IceAs&, MiniHeader::Pointer&, ImageControl&)
{
	ICE_SET_FN("NetworkPositionFunctor::FirstCall(...)")

//	ICE_OUT("FirstCall NetworkPositionFunctor." <<
//	"\n  m_bIs3D.......... = " << ((m_bIs3D == true) ? "true" : "false") <<
//	"\n  m_bIsEllipFilter. = " << ((m_bIsEllipFilter == true) ? "true" : "false") <<
//	"\n  m_flCmBolusVolume = " << m_flCmBolusVolume <<
//	"\n  m_nImageCols..... = " << m_nImageCols <<
//	"\n  m_nImageLins..... = " << m_nImageLins <<
//	"\n  m_nImageSlcs..... = " << m_nImageSlcs <<
//	"\n  m_bNoInversion... = " << ((m_bNoInversion == true) ? "true" : "false") <<
//	"\n  m_sInvertedSeriesUID = " << m_sInvertedSeriesUID);

	return I_OK;
}


IResult NetworkPositionFunctor::endOfJob(IResult irReason)
{
	ICE_SET_FN("NetworkPositionFunctor::endOfJob(irReason)")

	// close network connection
	client_stream.close();
	
	// irReason :   I_ACQ_END: acquisition finished
	//              I_USER: acquisition cancelled by user
	//              I_FAIL: error
	if (irReason == I_USER)
	{
		ICE_OUT("endOfJob called due to user stop!");
	}

	ICE_OUT("Cleaned up NetworkPositionFunctor.");

	return I_OK;
}

bool NetworkPositionFunctor::DeliverFeedback()
{
	m_NetPosData.status = 1;
	m_NetPosData.dXPos = (double) adRotParams[0];
	m_NetPosData.dYPos = (double) adRotParams[1];
	m_NetPosData.dZPos = (double) adRotParams[2];
	m_NetPosData.dXRot = (double) adRotParams[3];
	m_NetPosData.dYRot = (double) adRotParams[4];
	m_NetPosData.dZRot = (double) adRotParams[5];
	
	//Prepare m_SeqData
	if(!m_SeqData.setData(&m_NetPosData, sizeof(m_NetPosData))) {
		client_stream.close();
		ICE_OUT("NetworkPositionFunctor deliverFeedback setData failure\n" );
		ICE_RET_ERR("m_SeqData.setData() FAILED", false)
	}

	m_SeqData.setID("IFD");

	//Send feedback data to MPCU
	if (failed(m_pFeedbackSvc->Send(&m_SeqData))) {
		client_stream.close();
		ICE_OUT("NetworkPositionFunctor deliverFeedback feedbacksvc send failure\n" );
		ICE_RET_ERR("m_pFeedbackSvc->Send() FAILED", false)
	}

	return true;
}

IResult NetworkPositionFunctor::ComputeImage(IceAs& srcAs, MiniHeader::Pointer& dataHeader, ImageControl& ctrl)
{
	ICE_SET_FN("NetworkPositionFunctor::ComputeImage(srcAs, dataHeader, ctrl)")

	// send request to server
	if (-1 == client_stream.send_n(request,7,&netTimeout)) {
		// ignore connection errors here, if we wanted to fail, we could use the error message below.
		//ICE_RET_ERR("Could not reach server in IceImageReconFunctors::ComputeImage(), aborting...", I_FAIL)
		// set status to indicate we have an outgoing connection problem
		ICE_OUT("NetworkPositionFunctor send fail: Receive status = -2!!!\n" );
		m_NetPosData.status = -2;
	}
	
	// get response from server
	if (-1 == client_stream.recv_n(adRotParams,48,&netTimeout)) {
		// ignore connection errors here, if we wanted to fail, we could use the error message below.
		//ICE_RET_ERR("No response from server in IceImageReconFunctors::ComputeImage(), aborting...", I_FAIL)
		// set status to indicate we have an incoming connection problem
		ICE_OUT("NetworkPositionFunctor  recv fail: Receive status = -3!!!\n" );
		m_NetPosData.status = -3;		
	}
//	ICE_OUT("#####################################################Server response:" <<
//	"\n  arp[0-5]............. = " << adRotParams[0] <<
//	"\n  .........= " << adRotParams[1] <<
//	"\n  .........= " << adRotParams[2] <<
//	"\n  ........ = " << adRotParams[3] <<
//	"\n  ........ = " << adRotParams[4] <<
//	"\n  ........ = " << adRotParams[5]);
	

	// deliver feedback
	if ( !DeliverFeedback() ) {
		ICE_OUT("NetworkPositionFunctor feedback failure\n" );
		client_stream.close();
		ICE_RET_ERR("Unable to deliver feedback to the IceImageReconFunctors::ComputeImage(), aborting...", I_FAIL)
	}
	
	//Insert CheckAndDisplay method to display each image passing through functor
	//IceUtils::CheckAndDisplay(srcAs, IceDisplayData::DISPLAY);

	//Do nothing but pass on image to next functor
	IResult res = ImageReady(srcAs, dataHeader, ctrl);

	if( failed(res) ) {
		ICE_OUT("NetworkPositionFunctor imageready failure\n" );
		client_stream.close();
		ICE_RET_ERR("ERROR calling remaining functor chain, aborting...", res)
	}

	return I_OK;
}
