#include <iostream>

using namespace std;

int main()
{
    char string[256];
    cout << "Enter string: ";
    cin.getline(string, 256);
    int element = 0;
    while (string[element] != 0) {
        element++;
    }
    cout<<"Number of characters: "<<element;
    return 0;
}
