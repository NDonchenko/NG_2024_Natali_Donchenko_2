#include <iostream>
#include <limits>
using namespace std;

int main() {

    int size = 5;
    int arr[size];

     for (int counter = 0; counter < size ; counter++) {
        cout << "Enter value " << counter+1 << ": ";
         cin >> arr[counter];
     }
     for (int counter = 0; counter+1 <= size ; counter++) {
         if (counter+1 < size){
            cout << arr[counter]<<",";
         }else {
             cout << arr[counter]<<".";
         }
     }
    return 0;
}
