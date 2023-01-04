//
// Created by Alexander on 28.12.2022.
//
#include "gtest/gtest.h"
#include "exceptionSafeInvoke.h"

void testFunc(int i) {
    if (i == 0)
        throw "exception";
    std::cout << i << '\n';
}

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

struct ReturnNum {
    int operator()(int i) const {
        if (i == 0)
            throw "i == 0 error!";
        return i;
    }
};

TEST(testInvoke, testMethodVoid) {
    Foo foo(2);
    EXPECT_EQ(true, exceptionSafeInvoke(&Foo::print_add, foo, 1));
    EXPECT_EQ(false, exceptionSafeInvoke(&Foo::print_add, foo, 0));
}

TEST(testInvoke, testMethodNonvoid) {
    Foo foo(2);
    EXPECT_EQ(12, exceptionSafeInvoke(&Foo::return_add, foo, 10));
    EXPECT_EQ(std::nullopt, exceptionSafeInvoke(&Foo::return_add, foo, 0));
}

TEST(testInvoke, testFieldAccess) {
    Foo foo(2);
    EXPECT_EQ(2, exceptionSafeInvoke(&Foo::num_, foo));
}
