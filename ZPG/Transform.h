#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <boost/optional.hpp>

class Transform
{
private:
	glm::vec3 position;
	float angle;
	glm::vec3 axis;
	float scale;
	boost::optional<glm::mat4> matrix;

public:
	Transform(glm::vec3 position = glm::vec3(0), float angle = 0, glm::vec3 axis = glm::vec3(0, 1, 0), float scale = 1);

	glm::mat4 Get();

#pragma region Position

	inline glm::vec3 GetPosition() const
	{
		return position;
	}

	inline void SetPosition(glm::vec3 &value)
	{
		matrix.reset();
		position = value;
	}

	inline void AddPosition(glm::vec3 &value)
	{
		matrix.reset();
		position += value;
	}

#pragma endregion

#pragma region Angle

	inline float GetAngle() const
	{
		return angle;
	}

	inline void SetAngle(float value)
	{
		matrix.reset();
		angle = value;
	}

	inline void AddAngle(float value)
	{
		matrix.reset();
		angle += value;
	}

#pragma endregion

#pragma region Axis

	inline glm::vec3 GetAxis() const
	{
		return axis;
	}

	inline void SetAxis(glm::vec3 &value)
	{
		matrix.reset();
		axis = value;
	}

#pragma endregion

#pragma region Scale

	inline float GetScale() const
	{
		return scale;
	}

	void SetScale(float value)
	{
		matrix.reset();
		scale = value;
	}

	inline void AddScale(float value)
	{
		matrix.reset();
		scale += value;
	}

#pragma endregion

private:
	void CalculateMatrix();
};

