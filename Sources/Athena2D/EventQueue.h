#pragma once

#include "Event.h"
#include <map>
#include <typeindex>
#include <vector>

class HandlerFunctionBase {
public:
	// Call the member function
	void exec(Event* evnt) {
		call(evnt);
	}
private:
	// Implemented by MemberFunctionHandler
	virtual void call(Event* evnt) = 0;
};

template<class T, class EventType>
class MemberFunctionHandler : public HandlerFunctionBase
{
public:
	typedef void (T::* MemberFunction)(EventType*);

	MemberFunctionHandler(T* instance, MemberFunction memberFunction) : instance{ instance }, memberFunction{ memberFunction } {};

	void call(Event* evnt) {
		// Cast event to the correct type and call member function
		(instance->*memberFunction)(static_cast<EventType*>(evnt));
	}
private:
	// Pointer to class instance
	T* instance;

	// Pointer to member function
	MemberFunction memberFunction;
};

typedef std::vector<HandlerFunctionBase*> Handlers;

class EventQueue
{
public:
	static EventQueue& getInstance()
	{
		static EventQueue instance;
		return instance;
	}
	
	~EventQueue() = default;
	
	template<class T, class EventType>
	void subscribe(T* instance, void (T::*memberFunction)(EventType *))
	{
		Handlers* handlers = eventHandlers[typeid(EventType)];

		if (handlers == nullptr)
		{
			handlers = new Handlers();
			eventHandlers[typeid(EventType)] = handlers;
		}

		handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
	}

	template<typename EventType>
	void publish(EventType* evnt) {
		Handlers* handlers = eventHandlers[typeid(EventType)];

		if (handlers == nullptr) {
			return;
		}

		for (auto& handler : *handlers) {
			if (handler != nullptr) {
				handler->exec(evnt);
			}
		}
	}

	void shutdown()
	{
		for (auto ehPair : eventHandlers)
		{
			for (auto handler : *ehPair.second)
			{
				delete handler;
			}

			delete ehPair.second;
		}
	}
	
private:
	std::map<std::type_index, std::vector<HandlerFunctionBase*>*> eventHandlers;
};

