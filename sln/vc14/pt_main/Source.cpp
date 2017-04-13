#include "pt.h"
#include <clocale>

int main(void) {
    setlocale(LC_CTYPE, "Ru");
    std::cout << "Вариант №6:\n" <<
        "Случайная величина etha - время обслуживания \n\
        покупателя в кассе магазина. Пусть etha распределена\n\
        показательно с параметром lambda." << std::endl;
    std::cout << "Введите число проводимых испытаний: " << std::endl;
    size_t n;
    std::cin >> n;
    std::cout << "Введите lambda: " << std::endl;
    double lambda;
    std::cin >> lambda;
    if (lambda < 0) {
        std::cout << "Incorrect input." << std::endl;
        return 1;
    }
    VX vx = generateXs(n, lambda);
    std::vector<double> v = vx.getVs();
    std::cout << "Result:\n";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << (((i + 1) % 7 == 0) ? "\n" : "\t");
    }
    std::cout << std::endl;
    system("pause");
    return 0;
}