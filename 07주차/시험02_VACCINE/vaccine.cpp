#include <iostream>
#include <deque>

using namespace std;

class Info{
public:
    int id;
    int age;
    char sex;
};

void input();
void scheduling();
void output();

int n;
deque <deque<Info>> kVac;
deque <Info> childVac;
deque <Info> adultFVac;
deque <Info> adultMVac;
deque <Info> oldFVac;
deque <Info> oldMVac;

int main(){

    input();

    scheduling();

    output();
} // end of main()

void input(){

    cin >> n;

    Info tmpInfo;

    for (int i = 0; i < n; i++){
        cin >> tmpInfo.id >> tmpInfo.age >> tmpInfo.sex;

        if (tmpInfo.age <= 15) childVac.push_back(tmpInfo);

        else if (tmpInfo.age >= 61) {
            if (tmpInfo.sex == 'F') oldFVac.push_back(tmpInfo);
            else if (tmpInfo.sex == 'M') oldMVac.push_back(tmpInfo);
        }

        else {
            if (tmpInfo.sex == 'F') adultFVac.push_back(tmpInfo);
            else if (tmpInfo.sex == 'M') adultMVac.push_back(tmpInfo);
        }
    } // end of for()
} // end of input()

void scheduling(){
    kVac.push_back(oldMVac);
    kVac.push_back(oldFVac);
    kVac.push_back(childVac);
    kVac.push_back(adultFVac);
    kVac.push_back(adultMVac);
} // end of scheduling()

void output(){
    for (auto &i : kVac){
        while (!i.empty()){
            cout << i.front().id << endl;
            i.pop_front();
        }
    }
} // end of output()
