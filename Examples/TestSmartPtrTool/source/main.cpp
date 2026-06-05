#include "Smart_Ptr.h"
#include <iostream>

int main()
{
#ifdef WRONGE_CASE
	{
		auto aCamera = std::make_shared<Camera>();
		auto bView = std::make_shared<RenderView>();
		std::cout << "Camera ref count: "<< aCamera.use_count() << std::endl;
		std::cout << "RenderView ref count:" << bView.use_count() << std::endl;
		aCamera->mpRenderView = bView;
		std::cout << "Camera ref count: " << aCamera.use_count() << std::endl;
		std::cout << "RenderView ref count:" << bView.use_count() << std::endl;
		bView->mpCamera = aCamera;

		std::cout << "Camera ref count: " << aCamera.use_count() << std::endl;
		std::cout << "RenderView ref count:" << bView.use_count() << std::endl;
	}

	// not invoke deconstructing functions in the end.
#else
	{
		auto aCamera = std::make_shared<Camera>();
		auto bView = std::make_shared<RenderView>();
		std::cout << "Camera ref count: " << aCamera.use_count() << std::endl;
		std::cout << "RenderView ref count:" << bView.use_count() << std::endl;
		aCamera->mpRenderView = bView;
		std::cout << "Camera ref count: " << aCamera.use_count() << std::endl;
		std::cout << "RenderView ref count:" << bView.use_count() << std::endl;
		bView->mwpCamera = aCamera;

		std::cout << "Camera ref count: " << aCamera.use_count() << std::endl;
		std::cout << "RenderView ref count:" << bView.use_count() << std::endl;
	}

	// invoking deconstructing functions in the end.
#endif

	std::cout << "============= Observer Design Mode with Weak_ptr ===================" << std::endl;
	// create subject
    auto subject = std::make_shared<ConcreteSubject>(0);
    
    // create observers
    auto observer1 = std::make_shared<ConcreteObserver>("Observer1");
    auto observer2 = std::make_shared<ConcreteObserver>("Observer2");
    auto observer3 = std::make_shared<ConcreteObserver>("Observer3");
    
    // register observers
    subject->attach(observer1);
    subject->attach(observer2);
    subject->attach(observer3);
    
    // change state - all observers will be notified
    std::cout << "Setting state to 10:" << std::endl;
    subject->set_state(10);
    
    // remove one observer
    std::cout << "\nDetaching Observer2:" << std::endl;
    subject->detach(observer2);
    
    // change state again
    std::cout << "\nSetting state to 20:" << std::endl;
    subject->set_state(20);
    
    // simulate observer lifecycle end
    std::cout << "\nDestroying Observer3..." << std::endl;
    observer3.reset();  // explicitly destroy observer3

	// change state again - only observer1 will be notified
    std::cout << "\nSetting state to 30:" << std::endl;
    subject->set_state(30);
    
    // automatically clean up expired observers
    std::cout << "\nAutomatic cleanup of expired observers..." << std::endl;
    subject->notify();  // this will clean up expired observers

	return 0;
}
