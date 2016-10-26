#pragma once
#include <functional>
#include <vector>

class Updatable
{
private:
	typedef std::function<void()> UpdateCallback;
	
	std::vector<UpdateCallback> onUpdate;

public:
	void RegisterOnUpdate(UpdateCallback onUpdate);
	void Update();
};