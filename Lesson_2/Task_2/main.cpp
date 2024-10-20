#include <iostream>

using namespace std;

int main()
{
    int size=5;
    int arr[size];
    int maxCol = 0;
    for (int count=0; count< size; count++){
       cout << "Enter value " << count+1 << ": ";
       cin>>arr[count];
       if (arr[count]> maxCol){
           maxCol= arr[count];
       }
    }
    for(int row=0; row<maxCol; row++){
        cout<<endl;
        for(int col=0; col<size; col++ ){
                if(row<arr[col]){
                    cout << "*";
                }else{
                    cout << " ";
                }
        }
    }
}
