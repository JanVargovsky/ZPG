#pragma once
#include <boost/any.hpp>

#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <functional>

using deleter_t = std::function<void(void *)>;
using unique_void_ptr = std::unique_ptr<void, deleter_t>;

class DependencyResolver
{
#pragma region Singleton
public:
	static DependencyResolver& GetInstance();

private:
	DependencyResolver(const DependencyResolver&) = delete;
	DependencyResolver& operator=(const DependencyResolver&) = delete;
	DependencyResolver() = default;
#pragma endregion

private:
	std::unordered_map<std::type_index, unique_void_ptr> container;

public:
	~DependencyResolver();

	void Initialize();

	template<typename T>
	auto Register(T *t) -> void;

	template <typename T>
	auto Resolve() -> T;
};

template<typename T>
auto deleter(void const * data) -> void
{
	T const * p = static_cast<T const*>(data);
	printf("deleting %s\n", typeid(T).name());
	delete p;
}

template<typename T>
inline auto DependencyResolver::Register(T * t) -> void
{
	container[typeid(t)] = unique_void_ptr(t, &deleter<T>);
}

template<typename T>
inline auto DependencyResolver::Resolve() -> T
{
	auto item = container.find(typeid(T));

	if (item == container.end())
	{
		std::string message = "not defined type: " + string(typeid(T).name());
		throw exception(message.c_str());
	}

	return static_cast<T>(item->second.get());
}
