#pragma once
#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <assert.h>

#include <memory>
#include <string>
#include <stdexcept>

enum AstNodeType {
    CONST,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE
};

class AstNode {
public:
    AstNodeType type;
    int value;
    std::unique_ptr<AstNode> left, right;
};

#endif  // AST_H
