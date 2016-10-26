#include "Updatable.h"

void Updatable::RegisterOnUpdate(UpdateCallback onUpdate)
{
	this->onUpdate.push_back(onUpdate);
}

void Updatable::Update()
{
	for (auto &callback : onUpdate)
		callback();
}
