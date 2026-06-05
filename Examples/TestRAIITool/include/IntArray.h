#ifndef _INTARRAY_H_
#include <cmath>
#include <algorithm>

/**
 * @brief non RAII, will get wrong easily.
 */
void riskyFunction();

/**
* @brief RAII, it's a safe way.
*/
class IntArray
{
public:
	IntArray();
	~IntArray();

	IntArray(size_t _size);

	void PushData(int index, int val);

	int PopData(int index);

	int* Data() const noexcept;

	size_t Size() const noexcept;

private:
	int* m_data{ nullptr };
	size_t m_size;
};



#endif // !_INTARRAY_H_
