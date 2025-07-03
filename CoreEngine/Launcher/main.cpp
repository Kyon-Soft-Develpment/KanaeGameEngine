#include "Launcher.h"
#include <iostream>

int main() {
    try {
        Launcher launcher;
        launcher.run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
} 