#pragma once

class GameObject;
class TransformComponent;

class BaseComponent
{
public:
	BaseComponent();
	~BaseComponent();

	std::weak_ptr<GameObject> GetGameObject() const;

	virtual void Update(float deltaTime) = 0;

protected:
	friend class GameObject;
	std::weak_ptr<GameObject> mGameObject;

private:

	//BaseComponent(const BaseComponent &obj);
	BaseComponent& operator=(const BaseComponent& obj);
};