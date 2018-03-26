#pragma once
#include <memory>
#include "BaseComponent.h"

namespace dae
{
	class TransformComponent;

	class GameObject
	{
	public:
		void Update(float deltaTime);
		void Render() const;

		TransformComponent* GetTransform() const { return mTransform; }
		void SetPosition(float x, float y);

		void AddComponent(BaseComponent* component);
		template<class T> T* GetComponent();

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		TransformComponent* mTransform;
		std::vector<BaseComponent*> mComponents;
	};

	template <class T>
	T* GameObject::GetComponent()
	{
		const type_info& ti = typeid(T);
		for (auto *component : mComponents)
		{
			if (component && typeid(*component) == ti)
				return static_cast<T*>(component);
		}
		return nullptr;
	}
}
