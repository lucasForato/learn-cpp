#include <iostream>
#include <string>

// this tells the compiler that I am using this namespace, this will make it possible to write shorter code for I do not have to write std::cout
using namespace std;

string get_instructions() {
    string instructions = "first, you get up, then you go upstairs, then you open the door on the left, and then you enter";
    return instructions;
}

int main() {
    string instructions = get_instructions();
    cout << instructions << endl;
    return 0;
}

// comments
// We can chain << operators together to print out multiple things
