#include <iostream>
#include<windows.h>
#include <cstdlib>

using namespace std;

int main()
{
    int stars = 0;
    cout << "enter height of triangle:";
    cin>>stars;
    while (true){
        for (int height = 0; height<=stars; height++ ){
            for (int widthR = 0; widthR<stars-(stars-height); widthR++ ){
                cout << "*";
            }
        cout<<endl;
        }
        Sleep(500);
        system("cls");
        for (int height = 0; height<=stars; height++ ){
            for (int space = 0; space<stars -height ; space++ ){
                cout << " ";
            }
            for (int widthL = 0; widthL<stars-(stars-height); widthL++ ){
                cout << "*";
            }
            cout<<endl;
        }
        Sleep(500);
        system("cls");
    //return 0;
    }
}
