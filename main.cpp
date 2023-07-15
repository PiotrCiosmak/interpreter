#include <iostream>
#include <unordered_map>

// Interfejs abstrakcyjny dla wyrażeń
class Expression
{
public:
    virtual int interpret(std::unordered_map<std::string, int>& variables) = 0;
};

// Konkretna implementacja wyrażenia stałej
class ConstantExpression : public Expression
{
private:
    int value;

public:
    ConstantExpression(int val) : value(val)
    {}

    int interpret(std::unordered_map<std::string, int>& variables)
    {
        return value;
    }
};

// Konkretna implementacja wyrażenia zmiennych
class VariableExpression : public Expression
{
private:
    std::string variableName;

public:
    VariableExpression(const std::string& varName) : variableName(varName)
    {}

    int interpret(std::unordered_map<std::string, int>& variables)
    {
        return variables[variableName];
    }
};

// Konkretna implementacja wyrażenia dodawania
class AddExpression : public Expression
{
private:
    Expression* left;
    Expression* right;

public:
    AddExpression(Expression* l, Expression* r) : left(l), right(r)
    {}

    int interpret(std::unordered_map<std::string, int>& variables)
    {
        return left->interpret(variables) + right->interpret(variables);
    }
};

int main()
{
    // Przykładowe użycie wzorca Interpreter
    std::unordered_map<std::string, int> variables;
    variables["x"] = 5;
    variables["y"] = 10;

    Expression* expression = new AddExpression(
            new VariableExpression("x"),
            new ConstantExpression(7)
    );

    int result = expression->interpret(variables);

    std::cout << "Wynik: " << result << std::endl;

    delete expression;

    return 0;
}

