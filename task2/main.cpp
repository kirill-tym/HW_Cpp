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

} // конец неймспейса хомворк
