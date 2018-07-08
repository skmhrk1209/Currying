## Currying & Partial Application in C++17
```cpp
template <typename Function>
constexpr auto curry(Function&& function)
{
    return [=](auto&&... args1)
    {
        if constexpr (std::is_invocable<decltype(function), decltype(args1)...>::value)
        {
            return function(std::forward<decltype(args1)>(args1)...);
        }
        else
        {
            return curry([=](auto&&... args2) -> decltype(function(args1..., std::forward<decltype(args2)>(args2)...))
            {
                return function(args1..., std::forward<decltype(args2)>(args2)...);
            });
        }
    };
}

int main()
{
    // partial application
    std::cout << curry([](auto x, auto y, auto z) { return x + y + z; })(0)(1)(2) << std::endl;

    return 0;
}
```
```shell-session
3
```

## Fixed Point Combinator for anonymous recursive function
```cpp
template <typename Function>
constexpr auto fix(Function&& function)
{
    return curry(function)(function);
}

int main()
{
    // one-line fuctorial!
    std::cout << fix([](auto f, auto n) -> int { return n ? n * f(f, n - 1) : 1; })(10) << std::endl;

    return 0;
}
```
```shell-session
3628800
```

## "for_each" for tuple
```cpp
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

int main()
{
    // print tuple!
    std::cout << "( ";

    forEach(std::forward_as_tuple(0, 0.0, "zero"), [](const auto& elem) { std::cout << elem << " "; });

    std::cout << ")" << std::endl;

    return 0;
}
```
```shell-session
( 0 0 zero )
```

## "stream" for tuple
```cpp
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
```
```shell-session
( 0 0 zero )
```

