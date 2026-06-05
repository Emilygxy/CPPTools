#include "IntArray.h"
#include <iostream>

void riskyFunction()
{
	int* _array = new int[100]; // aqquire resource

	bool some_condition = true;
	if (some_condition)
	{
		throw std::runtime_error("something went wrong!"); // get exacption: skip delete[], accuring memory leaking!
	}

	delete[] _array; //release resource(may fail)
}

IntArray::IntArray()
	: m_data(new int[100])
	, m_size(100)
{
	for (size_t i = 0; i < m_size; i++)
	{
		m_data[i] = 0;
	}
}

IntArray::~IntArray()
{
	if (m_data)
	{
		delete[] m_data;
		m_data = nullptr;
	}

	m_size = 0;
}

IntArray::IntArray(size_t _size)
	: m_data(new int[_size])
	, m_size(_size)
{
	for (size_t i = 0; i < m_size; i++)
	{
		m_data[i] = 0;
	}
}

void IntArray::PushData(int index, int val)
{
	if (index >= m_size)
	{
		return;
	}

	m_data[index] = val;
}

int IntArray::PopData(int index)
{
	if (index >= m_size)
	{
		return -1;
	}

	return m_data[index];
}

int* IntArray::Data() const noexcept
{
	return m_data;
}

size_t IntArray::Size() const noexcept
{
	return m_size;
}
