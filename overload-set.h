#ifndef OVERLOAD_SET_H
#define OVERLOAD_SET_H

#include <utility>

template <typename ...H> class OverloadSet;

template <typename T>
class OverloadSet<T> : public T
{
public:
	OverloadSet(T && t)
	:
		T(std::forward<T>(t))
	{ }

	using T::operator();
};

template <typename T, typename ...Types>
class OverloadSet<T, Types...> : public T, public OverloadSet<Types...>
{
public:
	OverloadSet(T && t, Types && ...ts)
	:
		T(std::forward<T>(t)),
		OverloadSet<Types...>(std::forward<Types>(ts)...)
	{}

	using T::operator();
	using OverloadSet<Types...>::operator();
};

template <typename ...F>
auto overload(F && ...f) -> decltype(OverloadSet<F...>(std::forward<F>(f)...))
{
	return OverloadSet<F...>(std::forward<F>(f)...);
}

#endif // OVERLOAD_SET_H
