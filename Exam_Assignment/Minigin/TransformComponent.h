#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/detail/type_vec2.hpp>
#pragma warning(pop)

class TransformComponent : public BaseComponent
{
public:
	TransformComponent();
	~TransformComponent();

	void Update(float deltaTime);

	const glm::vec2& GetPosition() const { return mPosition; }
	void SetPosition(float x, float y);
	void Move(float x, float y);

private:
	glm::vec2 mPosition;
};