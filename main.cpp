#include "functional.hpp"
#include "iostream.hpp"
#include "tuple.hpp"

using namespace std;

int main()
{
    std::cout << curry([](auto x, auto y, auto z) { return x + y + z; })(0)(1)(2) << std::endl;

    std::cout << fix([](auto f, auto n) -> int { return n ? n * f(f, n - 1) : 1; })(10) << std::endl;

    std::cout << std::forward_as_tuple(0, "zero", std::forward_as_tuple(0, "zero")) << std::endl; 

    return 0;
}
