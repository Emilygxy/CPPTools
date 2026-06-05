#pragma once
#include <memory>
#include <vector>
#include <set>
#include <string>
// #define WRONGE_CASE

#ifdef WRONGE_CASE
class RenderView; // forward declearation

class Camera
{
public:
	Camera();
	~Camera();

	std::shared_ptr<RenderView> mpRenderView{ nullptr }; // Camera strong-ref RenderView
};

class RenderView
{
public:
	RenderView();
	~RenderView();

	std::shared_ptr<Camera> mpCamera{ nullptr }; // RenderView strong-ref Camera -> circle ref
};

#else
	class RenderView; // forward declearation

	class Camera
	{
	public:
		Camera();
		~Camera();

		std::shared_ptr<RenderView> mpRenderView{ nullptr }; // Camera strong-ref RenderView
	};

	class RenderView
	{
	public:
		RenderView();
		~RenderView();

		std::weak_ptr<Camera> mwpCamera; // RenderView weak-ref Camera -> no circle ref
	};

#endif // WRONGE_CASE

/** 
* @brief Observer Design Mode with Weak_ptr
*/
class Observer; // forward declearation
class Subject : public std::enable_shared_from_this<Subject>
{
public:
	virtual ~Subject() = default;

	void attach(const std::shared_ptr<Observer>& observer);
	void detach(const std::shared_ptr<Observer>& observer);
	void notify();

	virtual int get_state() const = 0;
	virtual void set_state(int state) = 0;
private:
	std::set<std::weak_ptr<Observer>, std::owner_less<std::weak_ptr<Observer>>> observers;
};

class Observer : public std::enable_shared_from_this<Observer>
{
public:
	virtual ~Observer() = default;
	virtual void update(const std::shared_ptr<Subject>&subject) = 0;
};

// specific subject
class ConcreteSubject : public Subject
{
public:
	explicit ConcreteSubject(int state = 0) : state_(state) {}

	int get_state() const override { return state_; }
	void set_state(int state) override {
		if (state != state_) {
			state_ = state;
			notify();
		}
	}

private:
	int state_;
};

// specific Observer
class ConcreteObserver : public Observer
{
public:
	explicit ConcreteObserver(const std::string& name)
		: name_(name), last_state_(-1) {}

	void update(const std::shared_ptr<Subject>& subject) override;

	int get_last_state() const { return last_state_; }

private:
	std::string name_;
	int last_state_;
};



