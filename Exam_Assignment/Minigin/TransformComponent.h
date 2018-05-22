#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/detail/type_vec3.hpp>
#pragma warning(pop)

class TransformComponent : public BaseComponent
{
public:
	TransformComponent();
	~TransformComponent();

	void Update(float deltaTime);

	const glm::vec3& GetPosition() const { return mPosition; }
	void SetPosition(float x, float y, float z);
	void Move(float x, float y, float z);

private:
	glm::vec3 mPosition;
};