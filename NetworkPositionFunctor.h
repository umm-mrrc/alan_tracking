//-----------------------------------------------------------------------------
//  Copyright (C) Siemens AG 2005  All Rights Reserved.
//-----------------------------------------------------------------------------
//
//     Project: IDEA
//        File: \n4\pkg\MrServers\MrVista\Ice\IceIdeaFunctors\IceNetworkPosition\NetworkPositionFunctor.h
//     Version: 2.0
//      Author: BV_ICE
//        Date: n.a.
//    Language: C++
// Description: <IceFunctor to send additionally inverted greyscale image to database.>
//
//-----------------------------------------------------------------------------
#ifndef NetworkPositionFunctor_h
#define NetworkPositionFunctor_h 1


// Import/Export DLL macro:
#include "MrServers/MrVista/Ice/IceIdeaFunctors/dllInterface.h"
// Base class:
#include "MrServers/MrVista/include/Ice/IceUtils/IceImageReconFunctors.h"


class ICEIDEAFUNCTORS_API NetworkPositionFunctor : public IceImageReconFunctors
{
        public:
                ICE_IMAGE_RECON_FUNCTOR(NetworkPositionFunctor)

        // needed macros to declare class members for IRIS environment:
        BEGIN_PROPERTY_MAP( NetworkPositionFunctor)
            PROPERTY_ENTRY   ( Is3D )
            PROPERTY_DEFAULT ( IsEllipFilter, "MEAS.sEllipticalFilter.ucOn")
            PROPERTY_DEFAULT ( CmBolusVolume, "YAPS.flContrastBolusVolume")
        END_PROPERTY_MAP()

        // macro to declare get/set methods and attribute in Hungarian Notation;
        // (parameter name in this macro must match with name in PROPERTY_MAP macro)
        DECL_GET_SET_PROPERTY(bool,  b,  Is3D)          // --> private: m_bIs3D;           public: getIs3d(), setIs3D(...)
        DECL_GET_SET_PROPERTY(bool,  b,  IsEllipFilter) // --> private: m_bIsEllipFilter;  public: getIsEllipFilter(), setIsEllipFilter(...)
        DECL_GET_SET_PROPERTY(float, fl, CmBolusVolume) // --> private: m_flCmBolusVolume; public: getCmBolusVolume(), setCmBolusVolume(...)

        // -----------------------------
        // - constructor / destructor -
        // -----------------------------
        NetworkPositionFunctor();
        virtual ~NetworkPositionFunctor();

        // -------------
        // - callbacks -
        // -------------
        // Called once at first call of ComputeImage(...):
        virtual IResult FirstCall(IceAs& srcAs, MiniHeader::Pointer& dataHeader, ImageControl& ctrl);

        // Application of functor functionality:
        IResult ComputeImage(IceAs& srcAs, MiniHeader::Pointer& dataHeader, ImageControl& controlData);
		
		// deliver feedback to the MPCU
		bool DeliverFeedback();

    protected:
        // Configuration of Functor (applied after PROPERTY_MAP is set):
        IResult EndInit( IParcEnvironment* env );

         // Finalize (triggered by ACQ_END flag from acquisition):
        virtual IResult endOfJob(IResult reason);

    private:
        // Number of image columns:
        int m_nImageCols;

        // Number of image lines:
        int m_nImageLins;

        // Number of slices:
        int m_nImageSlcs;

        // indicates condition for not inverting pixel data:
        bool m_bNoInversion;
        
        // SeriesInstanceUID for inverted images
        std::string m_sInvertedSeriesUID;

        // ----------------------------------------------------------------------------------------
        // Notice: In general, instanciate an IceObject pointer as class member only if it isn't
        //         forwarded to the successor Functor! Otherwise IceObject's data might be
        //         overwritten by a multithreaded task. Use 'IceObj::Pointer m_p...Obj' here only
        //         for local useage in a Functor.
        //         If there is a need to use a member IceObject pointer which should be forwarded
        //         to the successor Functor (e. g. requiring an IceObject pointer in several
        //         Functor methods) then initialize it with NULL pointer in constructor
        //         (m_p...Obj(NULL)) and create it in every call of ComputeImage
        //         (m_p...Obj = Parc::HeapObject<IceObj>::Create()
        //          m_p...Obj->create(...))
        //         Parc::HeapObject<IceObj>::Create() is like
        //             if(m_p...Obj) delete m_p...Obj;
        //             m_p...Obj = new IceObj;
        // ----------------------------------------------------------------------------------------

        NetworkPositionFunctor(const NetworkPositionFunctor &right);
        NetworkPositionFunctor & operator=(const NetworkPositionFunctor &right);
};

#endif
