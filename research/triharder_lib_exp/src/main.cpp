#include "core/result.h"
#include <iostream>
using namespace TriHarder;

void resultExperiments() {
    auto r1 = Result<int>::ok(42);
    std::cout << "R1 is_ok = " << r1.is_ok() << "\n";
    std::cout << "R1 is_error = " << r1.is_error() << "\n";
    std::cout << "R1 Value = " << r1.unwrap() << "\n";

    std::cout << "\n";

    auto r2 = Result<int>::error("this is a error");
    std::cout << "R2 is_ok = " << r2.is_ok() << "\n";
    std::cout << "R2 is_error = " << r2.is_error() << "\n";
    std::cout << "R2 Value = " << r2.unwrap_err() << "\n";
    std::cout << "R2 unwrap_or = " << r2.unwrap_or(55) << "\n";
    std::cout << "R2 unwrap_or_default = " << r2.unwrap_or_default() << "\n";
    std::cout << "R2 unwrap_or_else = " << r2.unwrap_or_else([]() { return 36; }) << "\n";

    std::cout << "\n";

    auto r3 = Result<int, int>::ok(184);
    std::cout << "R3 is_ok = " << r3.is_ok() << "\n";
    std::cout << "R3 is_error = " << r3.is_error() << "\n";
    std::cout << "R3 Value = " << r3.unwrap() << "\n";

    std::cout << "\n";

    auto r4 = Result<int, int>::error(1240);
    std::cout << "R4 is_ok = " << r4.is_ok() << "\n";
    std::cout << "R4 is_error = " << r4.is_error() << "\n";
    std::cout << "R4 unwrap_or = " << r4.unwrap_or(1255) << "\n";
    std::cout << "R4 unwrap_or_default = " << r4.unwrap_or_default() << "\n";
    std::cout << "R4 unwrap_or_else = " << r4.unwrap_or_else([]() { return 1236; }) << "\n";

    std::cout << "\n";

    auto r5 = r4;
    std::cout << "R5 is_ok = " << r4.is_ok() << "\n";
    std::cout << "R5 is_error = " << r4.is_error() << "\n";
    std::cout << "R5 unwrap_or = " << r4.unwrap_or(1255) << "\n";
    std::cout << "R5 unwrap_or_default = " << r4.unwrap_or_default() << "\n";
    std::cout << "R5 unwrap_or_else = " << r4.unwrap_or_else([]() { return 1236; }) << "\n";
}

int main(int argc, char* argv[]) {
    resultExperiments();
    return 0;
}
