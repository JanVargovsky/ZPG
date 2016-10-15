#pragma once

#include <unordered_map>
#include <memory>

template <typename TKey, typename TValue, typename Factory>
class ManagerBase
{
private:
	static std::unordered_map<TKey, std::shared_ptr<TValue>> items;
	static Factory factory;

protected:
	ManagerBase() = default;

public:
	static std::shared_ptr<TValue> Get(TKey key);
};

template<typename TKey, typename TValue, typename Factory>
std::shared_ptr<TValue> ManagerBase<TKey, TValue, Factory>::Get(TKey key)
{
	shared_ptr<TValue> result;
	auto valueIt = items.find(key);
	if (valueIt == items.end())
	{
		result = factory.Create(key);
		items.insert({ key, result });
	}
	else
		result = valueIt->second;

	return result;
}
