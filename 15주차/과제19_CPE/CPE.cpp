#include <iostream>
#include <string>

using namespace std;

void cpe_input();

int main(){

    cpe_input();

return 0;
} // end of main()

void cpe_input(){

    string tmp;

    cin >> tmp;

//    u16string tmp = s;

//
//    for (auto i : tmp)
//        cout << i;
//
//
    for (int i=0; i<(int)tmp.size(); i+=3){
        if (tmp[i].size()==3)         cout << tmp.substr(i,3);
    }

/*
    size_t i=0;
    while (i<tmp.size())
        if (0xAC00 <= i && i <= 0xD7A3)
            cout<<tmp.substr(i,2)<<endl;
        else cout<<"이상한 문자 발견!"<<endl;
        i += 2;
    }
*/
} // end of cpe_input()
