#include "LightBase.h"

LightBase::LightBase(glm::vec3 position)
	:position(position)
{
}

void LightBase::Send(Program * program)
{
	program->Send("lightPosition", position);
}

inline glm::vec3 LightBase::GetPosition()
{
	return position;
}

inline void LightBase::SetPosition(glm::vec3 value)
{
	position = value;
}
