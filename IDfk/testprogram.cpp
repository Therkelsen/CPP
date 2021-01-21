
#include <iostream>

using namespace std;

int age = 0;
string name = "Ashley"; 

int main() {

    while (age < 100) {
        cout << name << " is " << age << " years old\n";
        if (age < 25) {
            cout << "She lives with stinky parents\n\n";
        } else {
            cout << "She lives with behbeh\n\n";
        }
        age++;
    }
    return 0;
}