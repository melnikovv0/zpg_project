#include "Application.h"
#include <iostream>
using namespace std;

int main() {
    try {
        Application app(1200, 800, "ZPG");
        app.run();
    }
    catch (const std::exception& e) {
        // Ловим ошибку и выводим ее в консоль
        std::cerr << "!!! AN EXCEPTION OCCURRED !!!" << std::endl;
        std::cerr << e.what() << std::endl; // e.what() будет содержать точное сообщение от OpenGL

        // Оставляем консоль открытой, чтобы можно было прочитать ошибку
        std::cout << "\nPress Enter to exit...";
        std::cin.get();

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}