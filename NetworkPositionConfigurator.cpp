//	-----------------------------------------------------------------------------
//	  Copyright (C) Siemens AG 2005  All Rights Reserved.
//	-----------------------------------------------------------------------------
//
//	 Project: NUMARIS/4
//	    File: \n4\pkg\MrServers\MrVista\Ice\IceIdeaFunctors\IceNetworkPosition\NetworkPositionConfigurator.cpp
//	 Version:
//	  Author: BV_ICE
//	    Date: n.a.
//
//	    Lang: C++
//
//	 Descrip: Special Configurator ("IceProgramNetworkPosition") for NetworkPositionFunctor; 
//            Inserts NetworkPositionFunctor into default Functor chain assembled by IceDefaultConfigurator.
//
//	 Classes:
//
//	-----------------------------------------------------------------------------


// NetworkPositionConfigurator:
#include "MrServers/MrVista/Ice/IceIdeaFunctors/IceNetworkPosition/NetworkPositionConfigurator.h"
// ICE_OUT, ICE_ERR
#include "MrServers/MrVista/include/Parc/Trace/IceTrace.h"

using namespace MED_MRES_XProtocol;  //namespace of everything exported by XProtocol component

IResult NetworkPositionConfigurator::Compose( ProtocolComposer::Toolbox& toolbox )
{
    using namespace ProtocolComposer;

    toolbox.Init( "IRIS" );

    // -------------------------------
    // Insert Functor in Functor chain
    // -------------------------------
    // retrieve name of corresponding pipeService for a particular Functor (named 'combineMAG'):
//    MrFunctor successor = toolbox.FindFunctor("imafinish");
//    std::string pipeName = successor.PipeServiceName();
//    MrPipeService pipeService = toolbox.FindPipeService(pipeName.c_str());
    MrFunctor successor = toolbox.FindFunctor("imagesend");
    std::string pipeName = successor.PipeServiceName();
    MrPipeService pipeService = toolbox.FindPipeService(pipeName.c_str());
    //                                                    <FunctorIdName>, <FunctorClassName>@<DllName>
    MrFunctor NetworkPositionFunctor = pipeService.CreateFunctor("NetworkPosition",      "NetworkPositionFunctor@IceNetworkPosition");

    // Insert NetworkPositionFunctor (named 'NetworkPosition') into pre-configured default Functor chain after CombineFunctor (named 'combineMAG'):
    //  ______________________________________            __________________________________            ___________________
    // |                                      |          |                                  |          |                   |
    // | predecesssor Functor <IdNameOfAnchor>|          | inserted Functor <FunctorIdName> |          | successor Functor |
    // |_                                     |_         |_                                 |_         |_                  |_
    //  _|                        <AnchorEvent>_|-->-->-->_| <EventSink>        <EventSource>_|-->-->-->_| <Method>         _|
    // |______________________________________|          |__________________________________|          |___________________|
    //
    if( failed( toolbox.InsertBefore("NetworkPosition",         // <FunctorIdName> to be inserted
                                    "ComputeImage",     // <EventSink> method is called if predecessor fires <anchorsEvent>
                                    "ImageReady",       // <EventSource> is the event the Functor to be inserted fires to its sucessor
//                                    "imafinish",   // <IdNameOfAnchor> Functor serves as origin of the insert action
                                    "imagesend",   // <IdNameOfAnchor> Functor serves as origin of the insert action
                                    "ComputeImage") ) ) // <AnchorMethod> specifies the method of the inserted Functor, and the successor of the inserted Functor
    {
        ICE_ERR("Failed during call of InsertBefore(ImaFinishFunctor->'imafinish'), aborting...\n");
        return I_FAIL;
    }

    // ----------------------------------
    // Set properties of inserted Functor
    // ----------------------------------
    XProtocol& prot = toolbox.Protocol();

    const bool is3DSequence = (prot["YAPS.iNoOfFourierPartitions"].ToLong() > 1) ? true : false;  // nParMeas > 1 ==> 3D sequence
    NetworkPositionFunctor.SetProperty("Is3D", is3DSequence);
    
    // Note: flBolusVolumeDoubled acts as an example how to retrieve an float parameter from YAPS as well as an example
    //       that the default Functor Property setting is overwritten by configuration here:
    const float flBolusVolumeDoubled = (float)( 2.0 * prot["YAPS.flContrastBolusVolume"].ToDouble() );
    NetworkPositionFunctor.SetProperty("CmBolusVolume", flBolusVolumeDoubled); 

//    ICE_OUT( "NetworkPositionFunctor created and inserted into Functor chain!\n" << 
//             "NetworkPositionConfigurator set the following NetworkPositionFunctor's Properties:\n" <<
//             "- Is3D........... " << is3DSequence << "\n"
//             "- CmBolusVolume.. " << flBolusVolumeDoubled << "\n");
    
    return I_OK;
}

// Note: For available conversion methods of prot["..."].ToXXX() see file \n4\pkg\MrServers\MrVista\include\Parc\XNode.h

// Note: Code example for throwing an exception 'Functor myFunctor not found' in the Configurator if searched Functor doesn't exist:
//           toolbox.FindFunctor("myFunctor").SetProperty("myProperty", myValue);
//       Code example for catching a non-existent Functor with a specific error message:
//           MrFunctor  predecessor = toolbox.FindFunctor("myFunctor", false);
//           if(predecessor.IsBad())
//           {
//               ICE_ERROR("xxx");
//           }
//               else
//           {
//               predecessor.SetProperty("myProperty", myValue); 
//           }
