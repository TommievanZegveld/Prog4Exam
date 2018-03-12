#pragma once

class GameObject;

class BaseComponent
{
public:
	BaseComponent();
	~BaseComponent();

	GameObject* getGameObject() const { return m_GameObject; }
	virtual void Update() {};
protected:
	GameObject* m_GameObject;
};

