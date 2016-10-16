#pragma once

#include <unordered_map>
#include <memory>

template <typename TKey, typename TValue, typename Factory>
class ManagerBase
{
private:
	std::unordered_map<TKey, std::shared_ptr<TValue>> items;
	Factory factory;

public:
	ManagerBase(Factory factory);
	std::shared_ptr<TValue> Get(TKey key);
};

template<typename TKey, typename TValue, typename Factory>
inline ManagerBase<TKey, TValue, Factory>::ManagerBase(Factory factory)
	:factory(factory)
{
}

template<typename TKey, typename TValue, typename Factory>
std::shared_ptr<TValue> ManagerBase<TKey, TValue, Factory>::Get(TKey key)
{
	shared_ptr<TValue> result;
	auto valueIt = items.find(key);
	if (valueIt == items.end())
	{
		result = factory->Create(key);
		items.insert({ key, result });
	}
	else
		result = valueIt->second;

	return result;
}
