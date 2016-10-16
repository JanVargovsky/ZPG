#pragma once

#include <unordered_map>
#include <memory>

template <typename TKey, typename TValue, typename Factory>
class ManagerBase
{
private:
	std::unordered_map<TKey, TValue*> items;
	Factory *factory;

public:
	ManagerBase(Factory *factory);
	virtual ~ManagerBase();

	TValue* Get(TKey key);
};

template<typename TKey, typename TValue, typename Factory>
inline ManagerBase<TKey, TValue, Factory>::ManagerBase(Factory *factory)
	:factory(factory)
{
	for (auto &item : items)
		delete item.second;
	items.clear();
}

template<typename TKey, typename TValue, typename Factory>
inline ManagerBase<TKey, TValue, Factory>::~ManagerBase()
{
}

template<typename TKey, typename TValue, typename Factory>
TValue* ManagerBase<TKey, TValue, Factory>::Get(TKey key)
{
	TValue *result;
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
