#pragma once
#include "FactoryBase.h"
#include "Camera.h"

enum CameraType
{
	Normal,
};

class CameraFactory : public FactoryBase<CameraType, Camera*>
{
public:
	Camera* Create(CameraType cameraType);
};

