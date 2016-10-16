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
	virtual Camera* Create(CameraType cameraType) override;
};
