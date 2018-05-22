#pragma once

class GameObject;
class TransformComponent;

class BaseComponent
{
public:
	BaseComponent();
	~BaseComponent();

	GameObject* GetGameObject() const;

	virtual void Update(float deltaTime) = 0;

protected:
	friend class GameObject;
	GameObject* mGameObject;

private:

	//BaseComponent(const BaseComponent &obj);
	BaseComponent& operator=(const BaseComponent& obj);
};