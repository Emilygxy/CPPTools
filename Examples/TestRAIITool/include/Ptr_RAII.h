#ifndef _PTR_ARRAY_H_
#include <memory>
#include <string>
#include <vector>

class MyClass
{
public:
	MyClass() = delete;
	MyClass(const std::string& name = "empty");
	~MyClass();

	void SetName(const std::string& name)
	{
		mName = name;
	}

	std::string GetName() const noexcept
	{
		return mName;
	}

private:
	std::string mName;
};

void demoUniquePtr();
void demoSharedPtr();

struct Node
{
	// std::shared_ptr<Node> msptr_Node{ nullptr }; // here will accur circle ref, leading to memory leaking
	std::weak_ptr<Node> mwptr_Node; // right, won't accur circle ref
};

class IDCard
{
private:
	std::string mName = "";
	int mAge = 0;
};

//case for 'Rule of Zero'
class Person
{
public:
	~Person();
	enum class GengerType
	{
		Male,
		Female
	};

private:
	GengerType mGenger = GengerType::Male;

	std::unique_ptr<IDCard> mpIDCard{ nullptr }; // push resource management to smart_ptr
	std::vector<std::string> mPhoneNumbers; // push resource management to vector
	std::string mAddress = ""; // push resource management to string
};
#endif // !_PTR_ARRAY_H_
