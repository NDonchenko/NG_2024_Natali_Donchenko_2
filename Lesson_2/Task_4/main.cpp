#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str;
    cout << "Enter string: ";
    getline(cin, str);
    cout << "You entered: " << str << endl;
    int letters[26] ={0};
    for (int counter = 0; counter< str.length(); counter++) {
        if (str[counter]>= 'a'&&str[counter]<='z' ){
            letters[str[counter]-'a']++;
        }else if(str[counter]>= 'A'&&str[counter]<='Z'){
            letters[str[counter]-'A']++;
        }
    }
    for (int element =0; element<26; element++ ) {
        if (letters[element]>0){
            cout <<letters[element]<<endl;
        }
    }
    return 0;
}
