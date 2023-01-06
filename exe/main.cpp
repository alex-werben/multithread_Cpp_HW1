#include <iostream>
#include "exceptionSafeInvoke.h"

// Example function to show exceptionSafeInvoke work with void return type
// exceptionSafeInvoke should return true if no exception, false if exception occurred
void print_str(const char* s) {
    if (s[0] == '0')    // basic example to throw exception when first symbol is '0'
        throw "exception";
    return;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./<program> <some_input>\n";
        return 1;
    }

    bool result = exceptionSafeInvoke(print_str, argv[1]);
    std::cout << result << '\n';


    return 0;
}
