#include "CPMath.h"

namespace cp::math
{
	int CMathManager::partition(std::vector<int>& nums, int low, int high) 
	{
		int pivot = nums[low];  //  the first element as the pivot
        int i = low;
        int j = high;
        
        while (i < j) {
            //  find the first element less than the pivot from right to left
            while (i < j && nums[j] >= pivot) {
                j--;
            }
            if (i < j) {
                nums[i] = nums[j];  //  move the element less than the pivot to the left
                i++;
            }
            
            //  find the first element greater than the pivot from left to right
            while (i < j && nums[i] <= pivot) {
                i++;
            }
            if (i < j) {
                nums[j] = nums[i];  //  move the element greater than the pivot to the right
                j--;
            }
        }
        
        nums[i] = pivot;  //  put the pivot to the final position
        return i;        //  return the index of the pivot
    }

	void CMathManager::QuickSort_Normal(std::vector<int>& nums, int low, int high)
	{
		if (low < high)
		{
			int pivot = partition(nums, low, high);
			QuickSort_Normal(nums, low, pivot - 1);
			QuickSort_Normal(nums, pivot + 1, high);
		}
	}
}
