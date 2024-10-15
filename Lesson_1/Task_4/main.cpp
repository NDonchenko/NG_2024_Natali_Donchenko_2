#include <iostream>

using namespace std;

int main()
{
    int salary = 0;
    cout << "how much do you earn?" << endl;
    cin>> salary;

    if (salary>999) {
        //cout << " ok, but you can do better)))"<<endl;
        if (salary>999999){
            cout << " o it turns out you're a millionaire? Handsome!!!"<<endl;
        }

        if (salary<1000000) {
            cout << " ok, but you can do better)))"<<endl;
        }
    }
    if (salary<1000){
        cout << " work harder! "<<endl;
    }
    cout << "but you are great, mom loves you in any way, even poor:)))"<<endl;
    return 0;
}
