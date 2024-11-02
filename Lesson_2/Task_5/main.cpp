#include <iostream>

using namespace std;

int main(){

    char string[256];
    cout << "Enter string: ";
    cin.getline(string, 256);
    bool itsWord = false;
    int cWords = 0;
    int element = 0;
    while (string[element] != 0){
        if ((string[element]>= 'A' && (string[element])<= 'Z')
            ||(string[element]>= 'a' && (string[element])<= 'z')){
            if (! itsWord ){
                itsWord = true;
                cWords++;
            }
        }else {
            itsWord = false;
            }
        element++;
    }
    cout<<"Number of words in a line "<< cWords;
}
