#pragma once

class IRenderable
{
protected:
	IRenderable() = default;

public:
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	inline void RenderAll()
	{
		PreRender();
		Render();
		PostRender();
	}
};