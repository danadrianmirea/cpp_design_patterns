#include "interpreter.hpp"
#include <iostream>

void demonstrateInterpreterPattern() {
    std::cout << "\n=== Interpreter Pattern Demo ===\n" << std::endl;

    // Context: set variable values
    Context context;
    context.setVariable("x", 5);
    context.setVariable("y", 3);

    // Build the expression: (x + y) - 2
    auto expr = std::make_shared<SubtractExpression>(
        std::make_shared<AddExpression>(
            std::make_shared<VariableExpression>("x"),
            std::make_shared<VariableExpression>("y")
        ),
        std::make_shared<NumberExpression>(2)
    );

    std::cout << "Expression: (x + y) - 2, where x=5, y=3" << std::endl;
    int result = expr->interpret(context);
    std::cout << "Result: " << result << std::endl;

    std::cout << "\n=== End Interpreter Pattern Demo ===\n" << std::endl;
} 