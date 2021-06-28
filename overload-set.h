#ifndef OVERLOAD_SET_H
#define OVERLOAD_SET_H

#include <utility>

template <typename ...H> class OverloadSet;

template <typename T>
class OverloadSet<T> : public T // inherit from the lamda type and terminate recursive inheritance
{
public:
	OverloadSet(T && t)
	:
		T(std::forward<T>(t))  // call the ctor of the lamda type
	{ }

	using T::operator();  // pull the lambda call operator into overload resolution for this class
};

template <typename T, typename ...Types>
class OverloadSet<T, Types...> : public T, public OverloadSet<Types...>    // inherit from one lamda type and recurse over the lamda type list
{
public:
	OverloadSet(T && t, Types && ...ts)
	:
		T(std::forward<T>(t)),                              // call the ctor of the lamda type
		OverloadSet<Types...>(std::forward<Types>(ts)...)   // call the ctor of the base class
	{}

	using T::operator();                         // pull the lambda call operator into overload resolution for this class
	using OverloadSet<Types...>::operator();     // pull the call operator(s) of the base class(es) into overload resolution for this class
};


// deduce the lambda types with this helper function
template <typename ...F>
auto overload(F && ...f) -> decltype(OverloadSet<F...>(std::forward<F>(f)...))
{
	return OverloadSet<F...>(std::forward<F>(f)...);
}

#endif // OVERLOAD_SET_H
