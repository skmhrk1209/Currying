#include <iostream>
#include <utility>
#include <tuple>

// Apply a function to each element of a tuple.
template <typename Tuple, typename Function, std::size_t... Indices>
constexpr auto forEachImpl(Tuple&& tuple, Function&& function, std::index_sequence<Indices...>)
{
	// Don't unpack in function parameters because it's not guaranteed each parameter is evaluated from left to right.
	// [](auto&&...) {}((function(std::get<Indices>(std::forward<Tuple>(tuple))), 0)...);

	// So, unpack in initializer list.
	static_cast<void>(std::initializer_list<int>{ (function(std::get<Indices>(std::forward<Tuple>(tuple))), 0)... });
}

// Apply a function to each element of a tuple.
template <typename Tuple, typename Function>
constexpr auto forEach(Tuple&& tuple, Function&& function)
{
	constexpr std::size_t Size(std::tuple_size<typename std::remove_reference<Tuple>::type>::value);
	forEachImpl(std::forward<Tuple>(tuple), std::forward<Function>(function), std::make_index_sequence<Size>());
}

template <typename... Types>
decltype(auto) operator>>(std::istream& is, std::tuple<Types...>& tuple)
{
	forEach(tuple, [&is](auto& element) { is >> element; });

	return is;
}

template <typename... Types>
decltype(auto) operator<<(std::ostream& os, const std::tuple<Types...>& tuple)
{
	os << "( ";

	forEach(tuple, [&os](const auto& element) { os << element << " "; });

	os << ")";

	return os;
}

int main()
{
    // ostream for tuple
    std::cout << std::forward_as_tuple(0, 0.0, "zero") << std::endl; 

    return 0;
}