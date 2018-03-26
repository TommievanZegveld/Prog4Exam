#pragma once

namespace dae
{
	class GameObject;
	class TransformComponent;

	class BaseComponent
	{
	public:
		BaseComponent();
		~BaseComponent();

		GameObject* GetGameObject() const { return mGameObject; }
		TransformComponent* GetTransform() const;

		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

	protected:
		GameObject* mGameObject;

	private:
		friend class GameObject;

		//BaseComponent(const BaseComponent &obj);
		BaseComponent& operator=(const BaseComponent& obj);
	};
}
