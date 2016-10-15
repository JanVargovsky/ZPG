#pragma once
#include "FactoryBase.h"
#include "Camera.h"

enum CameraType
{
	Normal,
};

class CameraFactory : public FactoryBase<CameraType, std::shared_ptr<Camera>>
{
public:
	std::shared_ptr<Camera> Create(CameraType cameraType) override;
};

