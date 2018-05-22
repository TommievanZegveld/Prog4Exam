#pragma once
#include <memory>

class TransformComponent;
class BaseComponent;

class GameObject
{
public:
	void Update(float deltaTime);

	std::shared_ptr<TransformComponent> GetTransform() const { return mTransform; }

	void SetPosition(float x, float y);

	void AddComponent(std::shared_ptr<BaseComponent> component);
	template<class T> std::shared_ptr<T> GetComponent();

	GameObject();
	virtual ~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

private:
	std::shared_ptr<TransformComponent> mTransform;
	std::vector<std::shared_ptr<BaseComponent>> mComponents;
};

template <class T>
std::shared_ptr<T> GameObject::GetComponent()
{
	const type_info& ti = typeid(T);
	for (auto component : mComponents)
	{
		if (component && typeid(*component) == ti)
			return std::dynamic_pointer_cast<T>(component);
	}
	return nullptr;
}