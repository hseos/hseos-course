#pragma once

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

int Eval(AstNode* node) {
    switch(node->type) {
    case CONST:
        return node->value;
    case PLUS:
        return Eval(node->left.get()) + Eval(node->right.get());
    case MINUS:
        return Eval(node->left.get()) - Eval(node->right->right.get());
    case MULTIPLY:
        return Eval(node->left.get()) * Eval(node->right.get());
    case DIVIDE:
        return Eval(node->left.get()) / Eval(node->right.get());
    default:
        assert(!"Unknown node type");
    }
}

void Strip(std::string* line) {
    while(!line->empty() && line->back() == ' ') line->pop_back();
    while(!line->empty() && line->front() == ' ') line->erase(line->begin());
}

bool Split(const std::string& line, char symbol, std::string* left, std::string* right) {
    size_t symbol_pos = line.rfind(symbol);
    if (symbol_pos != std::string::npos) {
        *left = line.substr(0, symbol_pos);
        *right = line.substr(symbol_pos + 1);
        Strip(left);
        Strip(right);
        return true;
    } else {
        return false;
    }
}

// expr := expr + factor | expr - factor | factor
// factor := factor * const | factor / const | const
std::unique_ptr<AstNode> Parse(const std::string& line) {
    std::string left, right;
    std::unique_ptr<AstNode> node(new AstNode());

    if (Split(line, '+', &left, &right)) {
        node->type = PLUS;
    } else if (Split(line, '-', &left, &right)) {
        node->type = MINUS;
    } else if (Split(line, '*', &left, &right)) {
        node->type = MULTIPLY;
    } else if (Split(line, '/', &left, &right)) {
        node->type = DIVIDE;
    } else {
        node->type = CONST;
    }

    if (node->type == CONST) {
        char* endp;
        node->value = strtol(line.c_str(), &endp, 10);

        if (line.empty() || *endp != '\0')
            throw std::runtime_error("invalid number '" + line + "'");
    } else {
        node->left = Parse(left);
        node->right = Parse(right);
    }

    return node;
}
