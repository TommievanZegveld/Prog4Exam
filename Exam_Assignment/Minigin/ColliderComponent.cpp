#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"



ColliderComponent::ColliderComponent(glm::vec2 pos, float width, float height, ColliderType t) : mPosition(pos),mWidth(width),mHeight(height),mType(t)
{

}


ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	mPosition = mGameObject->GetTransform()->GetPosition();

	//std::cout << mPosition.x << ", " << mPosition.y << std::endl;
}

bool ColliderComponent::isColliding(ColliderComponent& other)
{
	// Our Collider
	auto center = mPosition;
	auto w = mWidth;
	auto h = mHeight;
	float left, right, top, bottom;

	left = center.x - (w * 0.5f);
	right = center.x + (w * 0.5f);

	top = center.y - (h * 0.5f);
	bottom = center.y + (h * 0.5f);

	//	Other Collider
	center = other.mPosition;
	w = other.mWidth;
	h = other.mHeight;

	float leftO, rightO, topO, bottomO;

	leftO = center.x - (w * 0.5f);
	rightO = center.x + (w * 0.5f);
	
	topO = center.y - (h * 0.5f);
	bottomO = center.y + (h * 0.5f);

	return(left < rightO &&
		right > leftO &&
		top < bottomO &&
		bottom > topO);
}
