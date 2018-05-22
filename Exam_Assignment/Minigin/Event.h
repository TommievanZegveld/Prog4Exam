#pragma once
#include <vector>
#include <memory>

class Observer;

class Event
{
public:
	void AddObserver(std::shared_ptr<Observer> observer);
protected:
	void Notify(Events event);
private:
	const static int maxObservers = 5;
	std::vector<std::shared_ptr<Observer>> m_Observers;
};

inline void Event::AddObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.push_back(observer);
}

inline void Event::Notify(Events event)
{
	for (size_t i = 0; i < m_Observers.size(); i++)
	{
		m_Observers[i]->onNotify( event);
	}
}
