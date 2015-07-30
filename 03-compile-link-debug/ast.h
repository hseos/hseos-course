#pragma once
#ifndef AST_H
#define AST_H

#include <memory>

enum AstNodeType {
    CONST,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    UNKNOWN = 255
};

class AstNode {
public:
    AstNodeType type = UNKNOWN;
    int value = 0;
    std::unique_ptr<AstNode> left, right;
};

#endif  // AST_H
