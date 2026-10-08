#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>

using std::endl;

namespace homework {

using Operation = std::function<double(double, double)>;

// стратегия
// тут калькулятор хранит выбранную операцию и позволяет заменить её
class Calculator {
public:
    Calculator(Operation operation) {
        set_strategy(std::move(operation));
    }

    void set_strategy(Operation operation) {
        operation_ = std::move(operation);
    }

    double calculate(double a, double b) const {
        return operation_(a, b);
    }

private:
    Operation operation_;
};

double add(double a, double b) {
    return a + b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}

// декоратор проверки
// он проверяет на деление на ноль и возвращает исходную функцию
Operation div_with_validation(Operation operation) {
    return [operation = std::move(operation)](double a, double b) {
        if (b == 0.0) {
            throw std::domain_error("Division by zero");
        }
        const double result = operation(a, b);
        return result;
    };
}

// декоратор журнала
// он печатает аргументы и результат
Operation with_logging(Operation operation, std::string name) {
    return [operation = std::move(operation), name = std::move(name)]
           (double a, double b) {
        std::cout << name << '(' << a << ", " << b << ")" << endl;
        const double result = operation(a, b);
        std::cout << "result = " << result << endl;
        return result;
    };
}

} // конец неймспейса хомворк
