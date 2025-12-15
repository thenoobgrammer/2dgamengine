#ifndef INC_2DGAMEENGINE_EVENTBUS_H
#define INC_2DGAMEENGINE_EVENTBUS_H

#include "../Logger/Logger.h"
#include "Event.h"
#include <map>
#include <typeindex>
#include <functional>
#include <list>

class IEventCallback {
    private:
        virtual void Call(Event& e) = 0;
    public:
        virtual ~IEventCallback() = default;
        void Execute(Event& e) {
            Call(e);
        }
};

template <typename TOwner, typename TEvent>
class EventCallback: public IEventCallback {
    private:
        typedef void (TOwner::*CallbackFunction)(TEvent& e);

        TOwner* ownerInstance;
        CallbackFunction callbackFunction;

        virtual void Call(Event& e) override {
            std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
        }
    public:
        EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction) {
            this->ownerInstance = ownerInstance;
            this->callbackFunction = callbackFunction;
        }

        virtual ~EventCallback() override = default;
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventBus {
    private:
        std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;
    public:
        EventBus() {
            Logger::Log("EventBus constructor initialized");
        }

        ~EventBus() {
            Logger::Log("EventBus destructor initialized");
        }

    void Reset() {
        subscribers.clear();
    }

    template <typename TEvent, typename... TArgs>
    void Emit(TArgs&& ...args) {
        auto handlers = subscribers[typeid(TEvent)].get();
        if (handlers) {
            for (auto it = handlers->begin(); it != handlers->end(); it++) {
                auto handler = it->get();
                TEvent event(std::forward<TArgs>(args)...);
                handler->Execute(event);
            }
        }
    }

    template <typename TEvent, typename TOwner>
    void Subscribe(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&)) {
        if (!subscribers[typeid(TEvent)].get()) {
            subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
        }
        auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
        subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    }
};

#endif //INC_2DGAMEENGINE_EVENTBUS_H