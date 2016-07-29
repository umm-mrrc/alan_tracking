#ifndef __NetworkFeedbackData_H        
#define __NetworkFeedbackData_H   

#include "MrServers/MrVista/include/pack.h"

struct NetPosData
{
	PACKED_MEMBER(int32_t, status);
	PACKED_MEMBER(double, dXPos);
	PACKED_MEMBER(double, dYPos);
	PACKED_MEMBER(double, dZPos);
	PACKED_MEMBER(double, dXRot);
	PACKED_MEMBER(double, dYRot);
	PACKED_MEMBER(double, dZRot);
};

#include "MrServers/MrVista/include/unpack.h"

#endif // __NetworkFeedbackData_H
