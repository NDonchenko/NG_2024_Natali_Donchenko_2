#include <iostream>

using namespace std;

void drawSpace(int size) {
    if (size >= 0) {
        drawSpace(size - 1);
        if (size-1>0){
            cout << " ";
        }
    }
}
void drawStar(int size) {
    if (size >= 0) {
        drawStar(size - 1);
        if (size-1>0){
            cout << "*";
        }
    }
}
void drowStem(int size) {
    if (size > 0) {
        drawSpace(size);
            cout << "*";
    }
}

void drawTree(int rows, int columns) {
    if (rows > 0) {
        drawTree(rows - 1, columns);
        drawSpace(columns-rows);
        drawStar((rows)*2);
    }
    cout << endl;
}

int main() {
    int columns = 0;
    cout<<"Enter the height of the Christmas tree:";
    cin>> columns;
    int rows = columns;
    drawTree(rows, columns);
    drowStem(columns);
}
