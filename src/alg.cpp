// Copyright 2025 NNTU-CS

#include <string>
#include <stack>
#include <cctype>
#include <sstream>
#include <map>

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    std::stack<char> ops;
    std::string output;
    for (size_t i = 0; i < inf.length(); ++i) {
        char token = inf[i];
        if (std::isalnum(token)) {
            output += token;
            output += ' ';
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                output += ops.top();
                output += ' ';
                ops.pop();
            }
            ops.push(token);
        } else if (token == '(') {
            ops.push(token);
        } else if (token == ')') {
            while (!ops.empty() && ops.top() != '(') {
                output += ops.top();
                output += ' ';
                ops.pop();
            }
            ops.pop();
        }
    }
    while (!ops.empty()) {
        output += ops.top();
        output += ' ';
        ops.pop();
    }
    return output;
}

int eval(const std::string& post) {
    std::stack<int> values;
    std::istringstream iss(post);
    std::string token;
    while (iss >> token) {
        if (std::isdigit(token[0])) {
            values.push(std::stoi(token));
        } else {
            int right = values.top(); values.pop();
            int left = values.top(); values.pop();
            switch (token[0]) {
                case '+': values.push(left + right); break;
                case '-': values.push(left - right); break;
                case '*': values.push(left * right); break;
                case '/': values.push(left / right); break;
            }
        }
    }
    return values.top();
}
