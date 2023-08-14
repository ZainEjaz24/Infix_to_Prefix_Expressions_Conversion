#include <iostream>
#include <cstring>

using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int getPrecedence(char c) {
    if (c == '^') {
        return 3;
    }
    if (c == '*' || c == '/') {
        return 2;
    }
    else if (c == '+' || c == '-') {
        return 1;
    }
    else {
        return 0;
    }
}

void reverseString(char str[]) {
   
    int length = 0;
    for (length =0; str[length] != '\0'; length++);

    for (int i = 0, j = length - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void infixToPrefix(char infix[], char prefix[]) {
    char stack[100];
    int top = -1, i = 0, j = 0;

    reverseString(infix);

    while (infix[i] != '\0') {
        char c = infix[i];
        if (isalnum(c)) {
            prefix[j] = c;
            j++;
        }
        else if (c == ')') {
            top++;
            stack[top] = c;
        }
        else if (c == '(') {
            while (top >= 0 && stack[top] != ')') {
                prefix[j] = stack[top];
                j++;
                top--;
            }
            if (top >= 0 && stack[top] == ')') {
                top--;
            }
            else {
                cout << "Invalid expression: Unmatched ')'" << endl;
                return;
            }
        }
        else if (isOperator(c)) {
            while (top >= 0 && getPrecedence(stack[top]) > getPrecedence(c)) {
                prefix[j] = stack[top];
                j++;
                top--;
            }
            top++;
            stack[top] = c;
        }
        i++;
    }

    while (top >= 0) {
        if (stack[top] == ')') {
            cout << "Invalid expression: Unmatched ')'" << endl;
            return;
        }
        prefix[j] = stack[top];
        j++;
        top--;
    }

    prefix[j] = '\0';
    reverseString(prefix);
}

int main() {
    char infix[50], prefix[50];
    cout << "Enter an infix expression: ";
    cin.getline(infix, 50);

    infixToPrefix(infix, prefix);
    cout << "Prefix expression: " << prefix << endl;
    return 0;
}
