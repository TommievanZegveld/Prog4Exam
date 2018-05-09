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
	virtual void Render() = 0;

protected:
	GameObject* mGameObject;

private:

	//BaseComponent(const BaseComponent &obj);
	BaseComponent& operator=(const BaseComponent& obj);
};