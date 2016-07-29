//	-----------------------------------------------------------------------------
//	  Copyright (C) Siemens AG 2005  All Rights Reserved.
//	-----------------------------------------------------------------------------
//
//	 Project: NUMARIS/4
//	    File: \n4_servers3\pkg\MrServers\MrVista\Ice\IceIdeaFunctors\IceNetworkPosition\NetworkPositionObjectMap.cpp
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
// NetworkPositionFunctor:
#include "MrServers/MrVista/Ice/IceIdeaFunctors/IceNetworkPosition/NetworkPositionFunctor.h"

// OBJECT_MAP macro definitions
#include "MrServers/MrVista/include/Parc/Reflection/ObjectMap.h"

// Export of classes outside of this Dll (needed once per Dll):
BEGIN_OBJECT_MAP()
    OBJECT_ENTRY(NetworkPositionFunctor)
    OBJECT_ENTRY(NetworkPositionConfigurator)
END_OBJECT_MAP()
