#include <iostream>

using namespace std;

int main()
{
    int quantity = 0;
    cout << "Enter the height of the Christmas tree!";
    cin >>quantity;
    int height = 0;
    for (int height =0; height<quantity; height++){
        for (int width =0; width<=(quantity-height); width++){
            cout << " ";
        }
        for (int star = 0; star <= height*2;star ++){
            cout << "*";
        }
        cout << endl;     
    }
    for (int stem =0; stem<=(quantity+1); stem++){
        if(stem<(quantity+1)){
            cout << " ";
        }else{
            cout << "*";
        }
    }
    return 0;
}
