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

int main() {
    using namespace homework;

    // стратегия
    std::cout << "Strategy: changing the operation" << endl;
    Calculator calculator(add);
    std::cout << "Add: " << calculator.calculate(8, 2) << endl;

    calculator.set_strategy(multiply);
    std::cout << "Multi: " << calculator.calculate(8, 2) << endl;

    calculator.set_strategy(divide);
    std::cout << "Div: " << calculator.calculate(8, 2) << endl;

    // стратегией может быть и лямбда-функция
    calculator.set_strategy([](double a, double b) { return a - b; });
    std::cout << "Lambda: " << calculator.calculate(8, 2) << endl;

    // декораторы
    std::cout << endl << "Decorators: logging and validation" << endl;
    calculator.set_strategy(with_logging(div_with_validation(divide), "divide"));
    const double result = calculator.calculate(8, 2);
    std::cout << "Decorated result: " << result << endl;

    // исключения декоратора (нельзя делить на ноль - это нписано в 50-52)
    try {
        calculator.calculate(8, 0);
    } catch (const std::domain_error& error) {
        std::cout << "Caught: " << error.what() << endl;
    }
}
