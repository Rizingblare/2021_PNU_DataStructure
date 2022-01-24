#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void input();
void depart_airplane();
void output();
void find_priority_plane();
void depart_that_plane();
int checking_empty_line();

int n;
int input_airID=-1;
int priority;
vector <deque<int>> all_airline;
deque <int> depart_order;

int main(){

    input();

    depart_airplane();

    output();

    return 0;

}//end of main()

void input(){
    cin >> n;

    for (int i=0; i<n; i++){
        deque <int> input_airline;
        while (1){
            cin >> input_airID;
            if (input_airID != 0)
                input_airline.push_back(input_airID);
            else break;
        }
        all_airline.push_back(input_airline);
    }

} // end of input()

void depart_airplane(){
    while (1){
        find_priority_plane();

        depart_that_plane();

        if (checking_empty_line()==all_airline.size())
            break;
    }
} // end of depart_airplane()

void find_priority_plane(){
    priority = 100000;

    for (auto i : all_airline){
        if (i.empty()) continue;
        if (priority > i.front())
            priority = i.front();
    }
} // end of find_priority_plane()

void depart_that_plane(){
    for (auto &i : all_airline){
        if (i.empty()) continue;
        if (priority == i.front()){
            depart_order.push_back(i.front());
            i.pop_front();
            break;
        }
    }
} // end of depart_that_plane()

int checking_empty_line(){
    int cnt = 0;

    for (auto i : all_airline){
        if (i.empty()) cnt++;
    }
    return cnt;
} // end of checking_empty_line()

void output(){
    while(!depart_order.empty()){
        cout << depart_order.front() << endl;
        depart_order.pop_front();
    }
} // end of output()
