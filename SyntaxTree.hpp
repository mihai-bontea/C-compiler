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

class ProgramNode: public SyntaxTreeNode
{
private:
    std::unique_ptr<FunctionNode> function_;

public:
    ProgramNode(std::unique_ptr<FunctionNode> function): function_(std::move(function)) {}
};

class FunctionNode: public SyntaxTreeNode
{
private:
    std::string return_type_;
    std::string name_;
    std::vector<std::string> parameters_;
    std::unique_ptr<StatementNode> body_;

public:
    FunctionNode(const std::string& return_type, const std::string& name, const std::vector<std::string>& parameters, std::unique_ptr<StatementNode> body):
        return_type_(return_type),
        name_(name),
        parameters_(parameters),
        body_(std::move(body))
        {}
};

class StatementNode: public SyntaxTreeNode
{
private:
    std::unique_ptr<ExpressionNode> expression_;
public:
    StatementNode(std::unique_ptr<ExpressionNode> expression): expression_(std::move(expression)) {}
};

class ExpressionNode: public SyntaxTreeNode
{
private:
    std::string value_;
public:
    ExpressionNode(std::string &value): value_(value) {}

};

// class IdentifierNode: public SyntaxTreeNode
// {

// };

// class IntegerNode: public SyntaxTreeNode
// {

// };