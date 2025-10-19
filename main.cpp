#include "Application.h"
#include <iostream>
using namespace std;

int main() {
    try {
        Application app(1200, 800, "ZPG");
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << "EXCEPTION OCCURRED" << std::endl;
        std::cerr << e.what() << std::endl; 

        std::cout << "\nPress Enter to exit...";
        std::cin.get();

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}