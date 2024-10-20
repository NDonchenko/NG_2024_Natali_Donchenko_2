#include <iostream>

using namespace std;

int main()
{
    int qantytyR = 20;
    int horizFigure[qantytyR];
    int counter = 0;
    int maxRow=0;
    for (int count=0; count< qantytyR; count++){
        cout << "Enter value " << count+1 << ": ";
        cin>>horizFigure[count];
        if (horizFigure[count]> maxRow){
            maxRow= horizFigure[count];
        }
        if (horizFigure[count]==0){
            break;
        }
    }
    for( int col = 0; col<qantytyR;col++){

        if (horizFigure[col]==0){
            break;
        }
        cout <<endl;
        for( int space = 0; space < (maxRow-horizFigure[col])/2;space++){
           cout << " ";
        }
        for( int row = 0; row < horizFigure[col] ;row++){
            cout << "*";
        }
            counter++;
        }

    return 0;
}
