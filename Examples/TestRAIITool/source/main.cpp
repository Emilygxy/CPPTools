#include <iostream>
#include "IntArray.h"
#include "Ptr_RAII.h"
#include "CPMath.h"


int main()
{
#ifdef _IntArray_
	IntArray myArray;

	myArray.PushData(2,25);

	for (size_t i = 0; i < myArray.Size(); i++)
	{
		std::cout << "["<<i<<"] = " << myArray.PopData(i) << std::endl;
	}

	IntArray yourArray(10);
	yourArray.PushData(1, 23);
	yourArray.PushData(7, 13);
	yourArray.PushData(9,56);
	for (size_t i = 0; i < yourArray.Size(); i++)
	{
		std::cout << "[" << i << "] = " << yourArray.PopData(i) << std::endl;
	}
#endif


	//demoUniquePtr();
	demoSharedPtr();

	std::vector<int> numList = { 5,6,7,8,3,4,6,2,3,5,6,8,7 };

	std::cout << "Sorted Before: \n";
	int nsize = int(numList.size());
	for (size_t i = 0; i < numList.size(); i++)
	{
		std::cout << numList[i] << " ";
	}

	cp::math::CMathManager::getInstance().QuickSort_Normal(numList, 0, nsize-1);

	std::cout << "Sorted After: \n";
	for (size_t i = 0; i < numList.size(); i++)
	{
		std::cout << numList[i] << " ";
	}

	return 0;
}





