#include <iostream>

using namespace std;

int main()
{
     int box[10][10];

     for (int height = 0; height < 10; height++) {
         for (int width = 0; width < 10; width++)
             box[height][width] = 0;
     }

     box[1][4] = 1;

     for (int height = 0; height < 10; height++) {
         for (int width = 0; width < 10; width++)
             cout << box[height][width];
         cout << endl;
     }
     for (char element = 'a'; element < 'z' + 1; element++)
     {
        cout << element << " - " << (int)element << endl;
    }
}
