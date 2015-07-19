#include <iostream>

#include "ast.h"

int main(int argc, char* argv[]) {
    std::string line;
    while(std::getline(std::cin, line)) {
        try {
            std::cout << Eval(Parse(line).get()) << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "error: " << e.what() << std::endl;
        }
    }

    return 0;
}
