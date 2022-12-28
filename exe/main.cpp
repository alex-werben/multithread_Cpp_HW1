#include <iostream>
#include "exceptionSafeInvoke.h"

struct Foo {
    Foo(int num) : num_(num) {}
    void print_add(int i) const {
        if (i == 0)
            throw "i == 0 error!";
        std::cout << num_+i << '\n';
    }
    int return_add(int i) const {
        if (i == 0)
            throw "i == 0 error!";
        return num_ + i;
    }
    int num_;
};

void print_num(int i)
{
    if (i == 0)
        throw "i == 0 error!";
    std::cout << i << '\n';
}

double return_double(double i) {
    return i;
}

int return_num(int i) {
    if (i == 0)
        throw "i == 0 error!";
    return i;
}

struct PrintNum {
    void operator()(int i) const
    {
        if (i == 0)
            throw "i == 0 error!";
        std::cout << i << '\n';
    }
};

int main() {
//    std::cout << invoke(print_num, 9) << '\n';
//    std::cout << invoke(return_num, 9) << '\n';
    // invoke a free function
    std::cout << exceptionSafeInvoke(print_num, -9) << '\n';
    exceptionSafeInvoke(print_num, 0);
    std::cout << exceptionSafeInvoke(return_num, 9).value() << '\n';
    std::cout << exceptionSafeInvoke(return_num, 0).value_or(0) << '\n';

    std::cout << "________________________________\n";
    // invoke a lambda
    exceptionSafeInvoke([]() { print_num(42); });
    std::cout << exceptionSafeInvoke([]() { print_num(0); }) << '\n';
    std::cout << exceptionSafeInvoke([]() { return return_num(42); }).value() << '\n';
    std::cout << exceptionSafeInvoke([]() { return return_num(0); }).value_or(0) << '\n';

    std::cout << "________________________________\n";

    // invoke a member function
    const Foo foo(2);
    exceptionSafeInvoke(&Foo::print_add, foo, 1);
    std::cout << exceptionSafeInvoke(&Foo::print_add, foo, 0) << '\n';
    std::cout << exceptionSafeInvoke(&Foo::return_add, foo, 90).value() << '\n';
    std::cout << exceptionSafeInvoke(&Foo::return_add, foo, 0).value_or(0) << '\n';
    std::cout << "________________________________\n";
    // invoke (access) a data member
    exceptionSafeInvoke(&Foo::num_, foo);
    std::cout << "num_: " << exceptionSafeInvoke(&Foo::num_, foo).value() << '\n';
    std::cout << "________________________________\n";
    // invoke a function object
    exceptionSafeInvoke(PrintNum(), 18);
    exceptionSafeInvoke(PrintNum(), 0);
//    invoke(PrintNum(), 18);

    return 0;
}
