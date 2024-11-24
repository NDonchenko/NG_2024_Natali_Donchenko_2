#include <iostream>

using namespace std;
const int MaxSize = 3;
struct matrix
{
    int dat[MaxSize][MaxSize];
};
void sum( const matrix&firstM,const matrix&secondM, matrix&buffer){

    for(int elemRow = 0; elemRow<3; elemRow++){
        for(int elemCol = 0; elemCol<3; elemCol++){
            buffer.dat[elemRow][elemCol] = firstM.dat[elemRow][elemCol] + secondM.dat[elemRow][elemCol];
        }
    }
}

void difference( const matrix&firstM,const matrix&secondM, matrix&buffer){

    for(int rowD = 0; rowD<3; rowD++){
        for(int colD = 0; colD<3; colD++){
            buffer.dat[rowD][colD] = firstM.dat[rowD][colD] - secondM.dat[rowD][colD];
        }
    }
}

void multiplication( const matrix&firstM,const matrix&secondM, matrix&buffer){

    for(int rowM = 0; rowM<3; rowM++){
        for(int colM = 0; colM<3; colM++){
            buffer.dat[rowM][colM] = firstM.dat[rowM][colM] * secondM.dat[rowM][colM];
        }
    }
}
ostream& operator << (ostream& os, const matrix buffer) {

    for (int row=0; row<3; row++) {
        for (int col=0; col<3; col++) {
            os << buffer.dat[row][col] << " ";
        }
        os << endl;
    }
    return os;
}
int main()
{
    matrix firstM, secondM, buffer;
    cout << "Enter the value of each element of the first matrix " << endl;

    for(int row = 0; row<MaxSize; row++){
        for(int col = 0; col<MaxSize; col++){
            cin>>firstM.dat[row][col];
        }
    }
    cout<< endl;
    cout << "Enter the value of each element of the second matrix " << endl;

    for(int row = 0; row<MaxSize; row++){
        for(int col = 0; col<MaxSize; col++){
            cin>>secondM.dat[row][col];
        }
    }

    buffer = {0};

    sum(firstM,secondM,buffer);
    cout << "first matrix:" << endl << firstM ;
    cout << "second matrix:"  << endl << secondM;
    cout << "sum matrix:" << endl << buffer ;
    difference(firstM,secondM,buffer);
    cout << "difference matrix:" << endl << buffer ;
    multiplication(firstM,secondM,buffer);
    cout << "multiplication matrix:" << endl << buffer ;

    return 0;
}
