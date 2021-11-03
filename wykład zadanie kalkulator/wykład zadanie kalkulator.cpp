// wykład zadanie kalkulator.cpp : 
//
/*
 * A reverse-polish notation calculator.
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>


    auto pop_top(std::stack<double>&stack) -> double
{
    if (stack.empty()) {
        throw std::logic_error{ "empty stack" };
    }
    auto element = std::move(stack.top());
    stack.pop();
    return element;
}


auto evaluate_addition(std::stack<double>& stack) -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{ "not enough operands for +" };
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a + b);
}

auto evaluate_multiplication(std::stack<double>& stack) -> void
{
    if (stack.size() < 2)
    {
        throw std::logic_error{ "not enough operands for *" };
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a * b);
    
}

auto evaluate_divide1(std::stack<double>& stack) -> void
{
    if (stack.size() < 2)
    {
        throw std::logic_error{ "not enough operands for /" };
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);    
    if (b == 0)
    {
        throw std::logic_error{ "you cannot divide by 0!" };
    }
    stack.push(a / b);
}

auto evaluate_divide2(std::stack<double>& stack) -> void
{
    if (stack.size() < 2)
    {
        throw std::logic_error{ "not enough operands for //" };
    }
    auto const b = (int)pop_top(stack);
    auto const a = (int)pop_top(stack);
    if (b == 0)
    {
        throw std::logic_error{ "you cannot divide by 0!" };
    }
    stack.push(a / b);

}

auto evaluate_modulo(std::stack<double>& stack) -> void
{
    if (stack.size() < 2)
    {
        throw std::logic_error{ "not enough operands for %" };
    }
    auto const b = (int)pop_top(stack);
    auto const a = (int)pop_top(stack);
    if (b == 0)
    {
        throw std::logic_error{ "you cannot divide by 0!" };
    }
    stack.push(a % b);

}

auto evaluate_power(std::stack<double>& stack) -> void
{
    if (stack.size() < 2)
    {
        throw std::logic_error{ "not enough operands for **" };
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(std::pow (a, b));

}
auto evaluate_sqrt(std::stack<double>& stack) -> void
{
    if (stack.size() < 1)
    {
        throw std::logic_error{ "not enough operands for *sqrt" };
    }
    auto const a = pop_top(stack);
  
    stack.push(std::sqrt (a));

}
auto evaluate_negation(std::stack<double>& stack) -> void
{
    if (stack.size() < 1)
    {
        throw std::logic_error{ "not enough operands for +-" };
    }  
    auto const a = pop_top(stack);
    stack.push(-a);

}
auto evaluate_subtraction(std::stack<double>& stack) -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{ "not enough operands for -" };
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a - b);
}


auto make_args(int argc, char* argv[]) -> std::vector<std::string>
{
    auto args = std::vector<std::string>{};
    std::copy_n(argv, argc, std::back_inserter(args));
    return args;
}

auto main(int argc, char* argv[]) -> int
{
    auto const args = make_args(argc - 1, argv + 1);

    auto stack = std::stack<double>{};
    for (auto const each : args) {
        try {
            if (each == "p") {
                std::cout << pop_top(stack) << "\n";
            }
            else if (each == "+") {
                evaluate_addition(stack);
            }
            else if (each == "*") {
                evaluate_multiplication(stack);
            }
            else if (each == "**") {
                evaluate_power(stack);
            }
            else if (each == "/") {
                evaluate_divide1(stack);
            }
            else if (each == "//") {
                evaluate_divide2(stack);
            }
            else if (each == "%") {
                evaluate_modulo(stack);
            }
            else if (each == "sqrt") {
                evaluate_sqrt(stack);
            }
            else if (each == "+-") {
                evaluate_negation(stack);
            }
            else if (each == "-") {
                evaluate_subtraction(stack);
            }
            else {
                stack.push(std::stod(each));
            }
        }
        catch (std::logic_error const& e) {
            std::cerr << "error: " << each << ": " << e.what() << "\n";
        }
    }

    return 0;
}