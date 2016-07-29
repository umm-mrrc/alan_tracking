//	-----------------------------------------------------------------------------
//	  Copyright (C) Siemens AG 2005  All Rights Reserved.
//	-----------------------------------------------------------------------------
//
//	 Project: NUMARIS/4
//	    File: \n4\pkg\MrServers\MrVista\Ice\IceIdeaFunctors\IceNetworkPosition\NetworkPositionConfigurator.h
//	 Version:
//	  Author: BV_ICE
//	    Date: n.a.
//
//	    Lang: C++
//
//	 Descrip: Special Configurator for NetworkPositionFunctor; inserts NetworkPositionFunctor into default
//            Functor chain assembled by IceDefaultConfigurator.
//
//	 Classes:
//
//	-----------------------------------------------------------------------------
#ifndef NetworkPositionConfigurator_h
#define NetworkPositionConfigurator_h 1


#include "MrServers/MrVista/include/Parc/ProtocolComposer.h"

class NetworkPositionConfigurator : public Parc::Component, public ProtocolComposer::IComposer
{
public:
    DECLARE_PARC_COMPONENT(NetworkPositionConfigurator);

    virtual IResult Compose( ProtocolComposer::Toolbox& toolbox );
};

#endif
