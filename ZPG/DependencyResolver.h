#pragma once
#include <boost/any.hpp>

#include <unordered_map>
#include <typeindex>
#include <typeinfo>

// God class...
class DependencyResolver
{
#pragma region Singleton
public:
	static DependencyResolver& GetInstance();

private:
	DependencyResolver(const DependencyResolver&) = delete;
	DependencyResolver& operator=(const DependencyResolver&) = delete;
	DependencyResolver();
#pragma endregion

public:
	std::unordered_map<std::type_index, boost::any> container;

	void Register();
public:
	template <typename T>
	T Resolve();
};

template<typename T>
inline T DependencyResolver::Resolve()
{
	auto item = container[typeid(T)];
	return boost::any_cast<T>(item);
}
