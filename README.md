# Currying & Partial Application in C++17

'''cpp:
    template <typename Function>
    auto curry(Function&& function)
    {
        return [=](auto&&... args1)
        {
            if constexpr (std::is_invocable<decltype(function), decltype(args1)...>::value)
            {
                return std::move(function)(std::forward<decltype(args1)>(args1)...);
            }
            else
            {
                return curry([=](auto&&... args2) -> decltype(function(args1..., std::forward<decltype(args2)>(args2)...))
                {
                    return std::move(function)(std::move(args1)..., std::forward<decltype(args2)>(args2)...);
                });
            }
        };
    }
'''

