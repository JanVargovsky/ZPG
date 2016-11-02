#pragma once
template<typename T>
class Size
{
private:
	T width, height;
public:
	Size() = default;
	Size(T width, T height);

	auto SetWidth(T value);
	auto GetWidth();

	auto SetHeight(T value);
	auto GetHeight();
};

template<typename T>
inline Size<T>::Size(T width, T height)
	:width(width), height(height)
{
}

template<typename T>
inline auto Size<T>::SetWidth(T value)
{
	width = value;
}

template<typename T>
inline auto Size<T>::GetWidth()
{
	return width;
}

template<typename T>
inline auto Size<T>::SetHeight(T value)
{
	height = value;
}

template<typename T>
inline auto Size<T>::GetHeight()
{
	return height;
}
