#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>

class SyntaxTreeNode
{
public:
    virtual void print(int indent = 0) const = 0;

    virtual ~SyntaxTreeNode() = default;
};

void print_indent(int indent)
{
    for (int i = 0; i < indent; ++i) std::cout << "  ";
}

class ExpressionNode : public SyntaxTreeNode {};

class StatementNode : public SyntaxTreeNode {};

class LiteralNode : public ExpressionNode
{
    std::string value;
public:
    explicit LiteralNode(const std::string& val) : value(val) {}

    void print(int indent = 0) const override
    {
        print_indent(indent);
        std::cout << "Literal: " << value << "\n";
    }
};

class BinaryOpNode : public ExpressionNode
{
    std::string op;
    std::unique_ptr<ExpressionNode> left;
    std::unique_ptr<ExpressionNode> right;
public:
    BinaryOpNode(const std::string& oper, std::unique_ptr<ExpressionNode> lhs, std::unique_ptr<ExpressionNode> rhs)
        : op(oper), left(std::move(lhs)), right(std::move(rhs)) {}

    void print(int indent = 0) const override
    {
        print_indent(indent);
        std::cout << "BinaryOp: " << op << "\n";
        if (left)
            left->print(indent + 1);
        if (right)
            right->print(indent + 1);
    }
};

class VariableDeclNode : public StatementNode
{
    std::string type;
    std::string name;
public:
    VariableDeclNode(const std::string& typ, const std::string& nm) : type(typ), name(nm) {}

    void print(int indent = 0) const override
    {
        print_indent(indent);
        std::cout << "VariableDecl: " << type << " " << name << "\n";
    }
};

class BlockNode : public StatementNode
{
    std::vector<std::unique_ptr<StatementNode>> statements;
public:
    void addStatement(std::unique_ptr<StatementNode> stmt)
    {
        statements.push_back(std::move(stmt));
    }

    void print(int indent = 0) const override {
        print_indent(indent);
        std::cout << "Block:\n";
        for (const auto& stmt : statements) {
            stmt->print(indent + 1);
        }
    }
};

class IfNode : public StatementNode
{
    std::unique_ptr<ExpressionNode> condition;
    std::unique_ptr<StatementNode> thenBranch;
    std::unique_ptr<StatementNode> elseBranch;
public:
    IfNode(std::unique_ptr<ExpressionNode> cond, std::unique_ptr<StatementNode> thenBr, std::unique_ptr<StatementNode> elseBr = nullptr)
        : condition(std::move(cond)), thenBranch(std::move(thenBr)), elseBranch(std::move(elseBr)) {}

    void print(int indent = 0) const override
    {
        print_indent(indent);
        std::cout << "If:\n";
        print_indent(indent + 1);
        std::cout << "Condition:\n";
        condition->print(indent + 2);
        print_indent(indent + 1);
        std::cout << "Then:\n";
        thenBranch->print(indent + 2);
        if (elseBranch)
        {
            print_indent(indent + 1);
            std::cout << "Else:\n";
            elseBranch->print(indent + 2);
        }
    }
};

class FunctionDeclNode : public StatementNode
{
    std::string returnType;
    std::string name;
    std::vector<std::string> parameters;
    std::unique_ptr<BlockNode> body;
public:
    FunctionDeclNode(const std::string& retType, const std::string& nm, const std::vector<std::string>& params, std::unique_ptr<BlockNode> bdy)
        : returnType(retType), name(nm), parameters(params), body(std::move(bdy)) {}
        
    void print(int indent = 0) const override
    {
        print_indent(indent);
        std::cout << "FunctionDecl: " << returnType << " " << name << "(";
        for (size_t i = 0; i < parameters.size(); ++i)
        {
            std::cout << parameters[i];
            if (i < parameters.size() - 1) std::cout << ", ";
        }
        std::cout << ")\n";
        body->print(indent + 1);
    }
};