#pragma once

template<typename TKey, typename TValue>
class FactoryBase
{
public:
	virtual TValue Create(TKey key) = 0;
};

