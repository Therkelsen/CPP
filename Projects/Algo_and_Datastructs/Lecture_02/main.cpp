#include <iostream>

using namespace std;

bool balPar(string text) { // Checks whether parentheses are matching pairs in source text, using a simple stack (string)
    string stack;
    for(int i = 0; i < text.size(); i++) {
        if(text.at(i) == '(') {
            stack.append("*");
        } else if (text.at(i) == ')') {
            if(text.empty()) {
                return false;
            } else {
                stack.pop_back();
            }
        }
    }
    if(!stack.empty())
        return false;
    return true;
}

int main() {
    string test = "(())";
    string test2 = "(()";
    string test3 = "())";
    string test4 = "()";

    cout << boolalpha << "Brackets balanced in '" << test << "': " <<  balPar(test) << endl;
    cout << boolalpha << "Brackets balanced in '" << test2 << "': " <<  balPar(test2) << endl;
    cout << boolalpha << "Brackets balanced in '" << test3 << "': " <<  balPar(test3) << endl;
    cout << boolalpha << "Brackets balanced in '" << test4 << "': " <<  balPar(test4) << endl;

    return 0;
}