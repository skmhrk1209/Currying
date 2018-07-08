#include "functional.hpp"
#include "tuple.hpp"
#include "iostream.hpp"

int main()
{
    // partial application
    std::cout << curry([](auto x, auto y, auto z) { return x + y + z; })(0)(1)(2) << std::endl;

    // one-line fuctorial!
    std::cout << fix([](auto f, auto n) -> int { return n ? n * f(f, n - 1) : 1; })(10) << std::endl;

    // print tuple!
    std::cout << "( ";

    forEach(std::forward_as_tuple(0, 0.0, "zero"), [](const auto& elem) { std::cout << elem << " "; });

    std::cout << ")" << std::endl;

    // ostream for tuple
    std::cout << std::forward_as_tuple(0, 0.0, "zero") << std::endl; 

    return 0;
}