#pragma once
#include "BaseComponent.h"
#pragma warning (disable:4201)
#include <glm/detail/type_vec2.hpp>


class TransformComponent;

enum class ColliderType
{
	STATIC,
	DYNAMIC,
	TRIGGER
};
class ColliderComponent final : public BaseComponent
{
public:

	ColliderComponent(glm::vec2 pos,float width, float height,ColliderType t);
	~ColliderComponent();

	void Update(float deltaTime);
	bool isColliding(ColliderComponent& other);

protected:
	friend class GameObject;
	ColliderType mType;

private:
	float mWidth, mHeight;
	glm::vec2 mPosition;
};

