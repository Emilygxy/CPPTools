#include "Smart_Ptr.h"
#include <iostream>

#ifdef WRONGE_CASE
Camera::Camera()
{
}

Camera::~Camera()
{
	std::cout << "Camera destroyed\n";
}


RenderView::RenderView()
{
}

RenderView::~RenderView()
{
	std::cout << "RenderView destroyed\n";
}

#else
Camera::Camera()
{
}

Camera::~Camera()
{
	std::cout << "Camera destroyed\n";
}


RenderView::RenderView()
{
}

RenderView::~RenderView()
{
	std::cout << "RenderView destroyed\n";
}
#endif // WRONGE_CASE


void Subject::attach(const std::shared_ptr<Observer>& observer)
{
	observers.insert(observer);
}

void Subject::detach(const std::shared_ptr<Observer>& observer)
{
	observers.erase(observer);
}

void Subject::notify()
{
	// create a temporary list to avoid modifying the collection during notification
    std::vector<std::shared_ptr<Observer>> activeObservers;
    
    for (auto it = observers.begin(); it != observers.end(); ) {
        // try to promote weak_ptr to shared_ptr
        if (auto observer = it->lock()) {
            activeObservers.push_back(observer);
            ++it;
        } else {
            // observer has been destroyed, remove it from the collection
            it = observers.erase(it);
        }
    }
    
    // notify all active observers
    for (const auto& obs : activeObservers) {
        obs->update(shared_from_this());
    }
}

void ConcreteObserver::update(const std::shared_ptr<Subject>& subject)
{
    if (auto subj = std::dynamic_pointer_cast<ConcreteSubject>(subject))
    {
        last_state_ = subj->get_state();
        std::cout << name_ << " received update: State changed to " << last_state_ << std::endl;
    }
}
