#include <iostream>
#include <string>

#include "stack.cpp"
#include "dynamic_array.cpp"

using std::cout;
using std::cin;
using std::string;
using std::getline;

const char enter_key = 13, esc_key = 27;

enum Error {
    BRACKET_SKIPPED = 1,
    INCORRECT_EXPRESSION = 2
};

bool is_number(char a) {
    return a >= '0' && a <= '9';
}

bool is_function(char a) {
    return a == 's' || a == 'c';
}

bool is_operator(char a) {
    return a == '+' || a == '-' || a == '/' || a == '*' || a == '^';
}

char get_priority(char a) {
    switch (a) {
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        case 0:
            return 4;
    }
}

bool is_priority_higher(char a, char b) {
    return get_priority(a) <= get_priority(b);
}

void handle_number(char a, string &rpn) {
    rpn += a;
}

void handle_function(char a, int &i, string &rpn, stack &stack) {
    stack.push(a);
    i += 2;
}

void handle_operator(char a, string &rpn, stack &stack) {
    while (is_priority_higher(a, stack.peek().val) && is_operator(stack.peek().val) && !stack.is_empty()) {
        rpn += " ";
        rpn += stack.peek().val;
        stack.pop();
    }
    rpn += " ";
    stack.push(a);
}

void handle_left_bracket(stack &stack) {
    stack.push('(');
}

void handle_right_bracket(string &rpn, stack &stack, int &errors) {
    while (stack.peek().val != '(') {
        rpn += " ";
        rpn += stack.peek().val;
        stack.pop();
        if (stack.is_empty()) {
            errors = BRACKET_SKIPPED;
            break;
        }
    }
    stack.pop();

    if (is_function(stack.peek().val)) {
        rpn += " ";
        rpn += stack.peek().val;
        if (stack.peek().val == 's') {
            rpn += "in";
        } else if (stack.peek().val == 'c') {
            rpn += "os";
        }
        stack.pop();
    }
}

void handle_space(char a, int &errors) {
    if (a != ' ') {
        errors = INCORRECT_EXPRESSION;
    }
}

void convert_to_rpn(const string &line, string &rpn, int &errors) {
    int i = 0, line_size = line.length();
    char a = 0;

    stack stack;

    while (i < line_size && !errors) {
        a = line[i];
        i++;

        if (is_number(a)) {
            handle_number(a, rpn);
        } else {
            if (is_function(a)) {
                handle_function(a, i, rpn, stack);
            } else {
                if (is_operator(a)) {
                    handle_operator(a, rpn, stack);
                } else {
                    if (a == '(') {
                        handle_left_bracket(stack);
                    } else {
                        if (a == ')') {
                            handle_right_bracket(rpn, stack, errors);
                        } else {
                            handle_space(a, errors);
                        }
                    }
                }
            }
        }
    }

    while (!stack.is_empty()) {
        if (stack.peek().val == '(') {
            errors = BRACKET_SKIPPED;
            break;
        }

        rpn += " ";
        rpn += stack.peek().val;
        stack.pop();
    }
}

void print_result(const string &line, const string &rpn, int errors) {
    cout << " [i] Your expression: \033[0;33m" << line
         << "\033[0;37m\n\n RPN (reverse Polish notation) expression: ";

    if (errors == 0) {
        cout << "\033[0;32m" << rpn << "\n\n\033[0;37m";
    } else {
        if (errors == BRACKET_SKIPPED) {
            cout << "\033[0;31mError - Bracket skipped \n\n\033[0;37m";
        } else if (errors == INCORRECT_EXPRESSION) {
            cout << "\033[0;31mError - Incorrect expression \n\n\033[0;37m";
        }
    }
}

int main() {
    int cycle = 1;
    while (cycle) {
        string line, rpn;
        int errors = 0, key = 0;

        cout << " [i] Write expression \n ";

        getline(cin, line);

        convert_to_rpn(line, rpn, errors);

        system("cls");

        print_result(line, rpn, errors);

        cout << " [i] Press [Enter] to \033[0;33mcontinue\033[0;37m or [Esc] to \033[0;33mexit\033[0;37m\n";

        while (key != enter_key && key != esc_key) {
            key = _getwch();
        }
        if (key == esc_key) {
            cycle = 0;
        }

        system("cls");
    }
}
