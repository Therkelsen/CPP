#include <iostream>
#include <vector>
#include <string>
#include <cmath>

//Exercise 1
int exercise1(int N) {
    //  N has to be greater than zero
    if (N < 1)
        return 0;
        //  if N is odd
    else if (N % 2 != 0)
        //  square it and add the next one recursively
        return (int(pow(N, 2)) + exercise1(N - 2));
    //  recursive call
    return exercise1(N - 1);
}

//Exercise 3
bool additive(std::string s) {
    // string has to be longer than 3 chars
    if (s.length() < 3)
        return false;
        // add 48 as that is the ascii value of 0
    else if (s.at(0) + s.at(1) == s.at(2) + 48)
        return true;
    // call the method with a substring
    return additive(s.substr(1, s.length()));
}

//Exercise 4
std::vector<int> exercise4(const std::vector<int> &a) { //Or use array[] if u want
    int res = INT_MAX;
    std::vector<int> results{0};
    // array must have three or more elements
    if (a.size() < 3)
        return results;

    // for all i
    for (int i = 0; i < a.size(); i++) {
        // for all j
        for (int j = i + 1; j < a.size(); j++) {
            // for all k
            for (int k = j + 1; k < a.size(); k++) {
                // comp sum
                int sum = a.at(i) + a.at(j) + a.at(k);
                // comp nearest power of 2
                int pow2 = int(pow(2, round(log2(sum))));
                // comp diff from sum to nearest power of 2
                int diff = abs(pow2 - sum);
                // save the results if they're closer
                if (diff < res) {
                    res = diff;
                    results = {a.at(i), a.at(j), a.at(k), pow2};
                }
            }
        }
    }

    return results;
}

//Exercise 6
int sumDivisibleBy3(int N) {
    // N must be at least 3 to be divisible by 3
    if (N < 3)
        return 0;
        //  if N is divisible by 3
    else if (N % 3 == 0)
        //  add it to the next one recursively
        return N + sumDivisibleBy3(N - 3);
    //  recursive call
    return sumDivisibleBy3(N - 1);
}

//Exercise 7
std::vector<int> exercise7(int Z) {
    // Z must be less than 100.000 and greater than 4
    if (Z > 100000 || Z < 4)
        return {0};

    // we find the maximum base value,
    // by taking the y_root of z_max
    int X_max = floor(pow(Z, 1/3));
    for (int X = X_max; X > 2; X--) {
        for (int Y = 10; Y > 2; Y--) {
            // if X^Y = Z, return that combination
            if (pow(X, Y) == Z)
                return {X, Y};
        }
    }
    return {0};
}

//Exercise 10
long logTo(int N) {
    // N is always positive and a power of 2
    // We count how many times N can be
    // divided by 2, before we reach 1
    if (N <= 1)
        return 0;
    return 1 + logTo(N / 2);
}

//Exercise 11
int exercise11(const std::vector<int>& a) {
    int winner = -1;
    int votes = 0;
    // finding the candidate with the majority of the votes
    for (int i : a) {
        // count votes
        if (votes == 0) {
            winner = i;
            votes = 1;
        } else {
            if (i == winner) {
                votes++;
            } else {
                votes--;
            }
        }
    }
    int count = 0;
    // checking if the candidate occurs more than a.size()/2 times
    for (int i : a) {
        if (i == winner)
            count++;
    }
    // if they do, they are the winner
    if (count > a.size() / 2)
        return winner;
    return -1;
}


int main() {
    printf("------------------------- Exercise 1 -------------------------\n\n");
    printf("---- Test 1 ----\n\n");
    int some_input1 = 8;//Fill in your input

    printf("Input is: %2d\n\n", some_input1); //Print the input
    int some_result1 = exercise1(some_input1);
    printf("Result is:  %2d\n\n", some_result1); //Print the result

    printf("---- Test 2 ----\n\n");
    int some_input12 = 42;
    printf("Input is: %2d\n\n", some_input12); //Print the input
    int some_result12 = exercise1(some_input12);
    printf("Result is:  %2d\n\n", some_result12); //Print the result

    printf("------------------------- Exercise 3 -------------------------\n\n");

    printf("---- Test 1 ----\n\n");
    std::string some_input2 = "82842605";//
    printf("Input is: %s\n\n", some_input2.c_str()); //Print the input
    bool some_result2 = additive(some_input2);
    printf("Result is: %s\n\n", some_result2 ? "True" : "False"); //Print the result

    printf("---- Test 2 ----\n\n");
    std::string some_input22 = "123";//
    printf("Input is: %s\n\n", some_input22.c_str()); //Print the input
    bool some_result22 = additive(some_input22);
    printf("Result is: %s\n\n", some_result22 ? "True" : "False"); //Print the result

    printf("---- Test 3 ----\n\n");
    std::string some_input23 = "124";//
    printf("Input is: %s\n\n", some_input23.c_str()); //Print the input
    bool some_result23 = additive(some_input23);
    printf("Result is: %s\n\n", some_result23 ? "True" : "False"); //Print the result

    printf("------------------------- Exercise 4 -------------------------\n\n");
    printf("---- Test 1 ----\n\n");
    std::vector<int> some_input3 = {23, 56, 22, 11, 65, 89, 3, 44, 87, 910, 45, 35, 98};//
    printf("Input is: ");
    for (int i = 0; i < some_input3.size(); i++) {
        if (i < some_input3.size() - 1) {
            printf("%d", some_input3.at(i));
            printf(",");
        } else {
            printf("%d", some_input3.at(i));
        }
    }

    std::vector<int> some_result3 = exercise4(some_input3);
    printf("\n\nResult is: ");
    for (int i = 0; i < some_result3.size() - 1; i++) {
        if (i < some_result3.size() - 2) {
            printf("%d", some_result3.at(i));
            printf(",");
        } else {
            printf("%d", some_result3.at(i));
        }
    }

    printf("\n\nSum is : ");
    printf("%d", some_result3.at(0) + some_result3.at(1) + some_result3.at(2));

    printf("\n\nPower of 2 is : ");
    printf("%d\n\n", some_result3.at(some_result3.size() - 1));

    printf("---- Test 2 ----\n\n");
    std::vector<int> some_input32 = {7, 3, 2, 12372137, 42, 314};//
    printf("Input is: ");
    for (int i = 0; i < some_input32.size(); i++) {
        if (i < some_input32.size() - 1) {
            printf("%d", some_input32.at(i));
            printf(",");
        } else {
            printf("%d", some_input32.at(i));
        }
    }

    std::vector<int> some_result32 = exercise4(some_input32);
    printf("\n\nResult is: ");
    for (int i = 0; i < some_result32.size() - 1; i++) {
        if (i < some_result32.size() - 2) {
            printf("%d", some_result32.at(i));
            printf(",");
        } else {
            printf("%d", some_result32.at(i));
        }
    }

    printf("\n\nSum is : ");
    printf("%d", some_result32.at(0) + some_result32.at(1) + some_result32.at(2));

    printf("\n\nPower of 2 is : ");
    printf("%d\n\n", some_result32.at(some_result32.size() - 1));

    printf("---- Test 3 ----\n\n");
    std::vector<int> some_input33 = {365, 6, 210, 4576, 1, 117000};//
    printf("Input is: ");
    for (int i = 0; i < some_input33.size(); i++) {
        if (i < some_input33.size() - 1) {
            printf("%d", some_input33.at(i));
            printf(",");
        } else {
            printf("%d", some_input33.at(i));
        }
    }

    std::vector<int> some_result33 = exercise4(some_input33);
    printf("\n\nResult is: ");
    for (int i = 0; i < some_result33.size() - 1; i++) {
        if (i < some_result33.size() - 2) {
            printf("%d", some_result33.at(i));
            printf(",");
        } else {
            printf("%d", some_result33.at(i));
        }
    }

    printf("\n\nSum is : ");
    printf("%d", some_result33.at(0) + some_result33.at(1) + some_result33.at(2));

    printf("\n\nPower of 2 is : ");
    printf("%d\n\n", some_result33.at(some_result33.size() - 1));

    printf("------------------------- Exercise 6 -------------------------\n\n");
    printf("---- Test 1 ----\n\n");
    int some_input4 = 12;//Fill in your input

    printf("Input is: %2d\n\n", some_input4); //Print the input
    int some_result4 = sumDivisibleBy3(some_input4);
    printf("Result is:  %2d\n\n", some_result4); //Print the result

    printf("---- Test 2 ----\n\n");
    int some_input42 = 14;
    printf("Input is: %2d\n\n", some_input42); //Print the input
    int some_result42 = sumDivisibleBy3(some_input42);
    printf("Result is:  %2d\n\n", some_result42); //Print the result

    printf("------------------------- Exercise 7 -------------------------\n\n");
    printf("---- Test 1 ----\n\n");
    int some_input5 = 6561;
    printf("Input is: %d\n\n", some_input5);

    std::vector<int> some_result5 = exercise7(some_input5);
    printf("\n\nResult is: ");
    for (int i = 0; i < some_result5.size(); i++) {
        if (i < some_result5.size() - 1) {
            printf("%d", some_result5.at(i));
            printf(",");
        } else {
            printf("%d", some_result5.at(i));
        }
    }

    printf("------------------------- Exercise 10 -------------------------\n\n");
    printf("---- Test 1 ----\n\n");
    int some_input6 = 2;//Fill in your input

    printf("Input is: %2d\n\n", some_input6); //Print the input
    int some_result6 = logTo(some_input6);
    printf("Result is:  %2d\n\n", some_result6); //Print the result

    printf("------------------------- Exercise 11 -------------------------\n\n");
    printf("---- Test 1 ----\n\n");
    std::vector<int> some_input7 = {7,4,3,5,3,1,6,4,5,1,7,5};//Fill in your input

    printf("Input is: ");
    for (int i = 0; i < some_input7.size(); i++) {
        if (i < some_input7.size() - 1) {
            printf("%d", some_input7.at(i));
            printf(",");
        } else {
            printf("%d", some_input7.at(i));
        }
    }
    int some_result7 = exercise11(some_input7);
    printf("\n\nResult is:  %2d\n\n", some_result7); //Print the result

    printf("---- Test 2 ----\n\n");
    std::vector<int> some_input72 = {7,7,7,7,7,7,6,4,5,1,7,5};//Fill in your input

    printf("Input is: ");
    for (int i = 0; i < some_input72.size(); i++) {
        if (i < some_input72.size() - 1) {
            printf("%d", some_input72.at(i));
            printf(",");
        } else {
            printf("%d", some_input72.at(i));
        }
    }
    int some_result72 = exercise11(some_input72);
    printf("\n\nResult is:  %2d\n\n", some_result72); //Print the result

    return 0;
}

