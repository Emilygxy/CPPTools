#pragma once
#include <vector>
#include <iostream>

namespace cp::math
{
	/** 
	* Meyers' Singleton(C++11 up)
	*/
	class CMathManager
	{
	public:
		// only one instance can be created
		static CMathManager& getInstance() {
			static CMathManager instance;  // 
			return instance;
		}

		// quick sort algorithm(normal version)
		void QuickSort_Normal(std::vector<int>& nums, int low, int high);

	private:
		// constructor and destructor
		CMathManager() {
			std::cout << "Singleton instance created." << std::endl;
		}

		// private destructor(optional, for resource cleanup)
		~CMathManager() {
			std::cout << "Singleton instance destroyed." << std::endl;
		}

		// disable copy and move constructors and operators
		CMathManager(const CMathManager&) = delete;
		CMathManager& operator=(const CMathManager&) = delete;

		// disable move constructors and operators(c++11 up)
		CMathManager(CMathManager&&) = delete;
		CMathManager& operator=(CMathManager&&) = delete;

		// helper methods
		/**
		 * @brief partition the array into two parts, the left part is less than the pivot, the right part is greater than the pivot
		 * @param nums the array to be partitioned
		 * @param low the low index of the array
		 * @param high the high index of the array
		 * @return the index of the pivot
		 */
		int partition(std::vector<int>& nums, int low, int high);
	};

}


