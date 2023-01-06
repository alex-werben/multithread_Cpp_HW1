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

TEST(testInvoke, testFunctionVoid) {
    EXPECT_TRUE(exceptionSafeInvoke(testFunc, 111));
    EXPECT_FALSE(exceptionSafeInvoke(testFunc, 0));
    EXPECT_FALSE(exceptionSafeInvoke([]() { print_num(0); }));
    EXPECT_TRUE(exceptionSafeInvoke([]() { print_num(11); }));
}

TEST(testInvoke, testFunctionNonvoid) {
    EXPECT_EQ(std::nullopt, exceptionSafeInvoke(return_num, 0));
    EXPECT_EQ(11, exceptionSafeInvoke(return_num, 11).value());
    EXPECT_EQ(123, exceptionSafeInvoke([]() { return return_num(123); }));
    EXPECT_EQ(std::nullopt, exceptionSafeInvoke([]() { return return_num(0); }));
}

TEST(testInvoke, testFunctionObjectVoid) {
    EXPECT_TRUE(exceptionSafeInvoke(PrintNum(), 18));
    EXPECT_FALSE(exceptionSafeInvoke(PrintNum(), 0));
}

TEST(testInvoke, testFunctionObjectNonvoid) {
    EXPECT_EQ(18, exceptionSafeInvoke(ReturnNum(), 18));
    EXPECT_EQ(std::nullopt, exceptionSafeInvoke(ReturnNum(), 0));
}
