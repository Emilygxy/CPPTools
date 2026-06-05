#include "Ptr_RAII.h"
#include <iostream>

MyClass::MyClass(const std::string& name)
	:mName(name)
{
	std::cout << "Construct Class: " << mName << std::endl;
}

MyClass::~MyClass()
{
	std::cout << "Destruct Class: " << mName << std::endl;
}

void demoUniquePtr()
{
	std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>("up1");
	std::cout << "ptr1: " << (ptr1.get()) << std::endl;
	std::unique_ptr<MyClass> ptr2 = std::move(ptr1);
	std::cout << "ptr2: " << (ptr2.get()) << std::endl;
}

void demoSharedPtr()
{
	std::shared_ptr<MyClass> sptr1 = std::make_shared<MyClass>("sp1");
	std::cout << "sptr1's name is " << sptr1->GetName() <<", ref count: " << sptr1.use_count() << std::endl;
	{
		std::shared_ptr<MyClass> sptr2 = sptr1; // copy, ref count +1; sptr1 and sptr2 share common object
		std::cout<<"sptr2's name is " << sptr2->GetName() << ", ref count: " << sptr1.use_count() << std::endl;
		sptr2->SetName("sp2");
		std::cout << "sptr2's name is " << sptr2->GetName() << ", ref count: " << sptr1.use_count() << std::endl;
	}
	std::cout << "sptr1's name is " << sptr1->GetName() << ", ref count: " << sptr1.use_count() << std::endl;
}

Person::~Person()
{
	mPhoneNumbers.clear();
}
