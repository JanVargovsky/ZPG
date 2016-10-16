#pragma once
#include <boost/any.hpp>

#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <memory>

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

public:
	~DependencyResolver();

	std::unordered_map<std::type_index, boost::any> container;

	void Initialize();
public:
	template <typename T>
	T Resolve();
};

template<typename T>
inline T DependencyResolver::Resolve()
{
	auto item = container[typeid(T)];

	if (item.empty())
	{
		std::string message = "not defined type: " + string(typeid(T).name());
		throw exception(message.c_str());
	}

	return boost::any_cast<T>(item);
}
