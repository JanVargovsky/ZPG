#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <boost/optional.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
	boost::optional<glm::mat4> matrix;

public:
	Transform(glm::vec3 position = glm::vec3(0), glm::vec3 scale = glm::vec3(1), glm::vec3 rotation = glm::vec3(0));

	glm::mat4 Get();

#pragma region Position

	inline glm::vec3 GetPosition() const
	{
		return position;
	}

	inline void SetPosition(const glm::vec3 &value)
	{
		position = value;
		matrix.reset();
	}

	inline void AddPosition(const glm::vec3 &value)
	{
		position += value;
		matrix.reset();
	}

	// Rotate around point by angle and axis
	void AddPosition(const glm::vec3 &point, const float angle, const glm::vec3 &axis);

#pragma endregion

#pragma region Rotation

	inline glm::quat GetRotation() const
	{
		return rotation;
	}

	inline void SetRotation(const glm::quat &value)
	{
		rotation = value;
		matrix.reset();
	}

	inline void SetRotation(float angle, const glm::vec3 &axis)
	{
		rotation = glm::rotate(glm::quat(), glm::radians(angle), axis);
		matrix.reset();
	}

	inline void AddRotation(float angle, const glm::vec3 &axis)
	{
		rotation = glm::rotate(rotation, glm::radians(angle), axis);
		matrix.reset();
	}

#pragma endregion

#pragma region Scale

	inline glm::vec3 GetScale() const
	{
		return scale;
	}

	void SetScale(const glm::vec3 value)
	{
		scale = value;
		matrix.reset();
	}

	void SetScale(const float value)
	{
		SetScale(glm::vec3(value, value, value));
	}

	inline void AddScale(const glm::vec3 value)
	{
		scale += value;
		matrix.reset();
	}

#pragma endregion

private:
	void CalculateMatrix();
};

