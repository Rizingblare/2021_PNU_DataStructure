    #include <iostream>
#include <deque>
#include <list>

using namespace std;

class Seat{
public:
    int seatNum;
    int userID;
};

void input();
void admission();
int isExit(int);
void first_admit();
void after_admit();

int n, k;
int ID_list[10001] = {};
deque <int> admit_list;
list <Seat> seat_list;
int dist, max_dist;

int main() {

    input();

    admission();

    return 0;
} // end of main()

void input() {
    cin >> n >> k;

    Seat tmpSeat;
    for (int i = 1; i <= n; i++) {
        tmpSeat.seatNum = i;
        tmpSeat.userID = 0;
        seat_list.push_back(tmpSeat);
    }

    int tmp;
    for (int i = 0; i < k; i++) {
        cin >> tmp;
        admit_list.push_back(tmp);
    }

} // end of input()

void admission() {

    first_admit();

    after_admit();

} // end of admission()

int isExit(int id) {
    if (ID_list[id]) {
        ID_list[id] = 0; return 1;
    }
    else {
        ID_list[id] = 1; return 0;
    }
} // end of isExit()

void first_admit() {
    auto iter = seat_list.begin();
    if (!admit_list.empty()) {
        if (isExit(admit_list.front()) == 0)
            (*iter).userID = admit_list.front();
        cout << (*iter).userID << " " << (*iter).seatNum << endl;
        admit_list.pop_front();
    }
} // end of first_admit()

void after_admit() {

    while (!admit_list.empty()) {
        int EXIT = isExit(admit_list.front());

        if (EXIT) {
            if (!admit_list.empty()) {
                for (auto& i : seat_list)
                    if (i.userID == admit_list.front()) {
                        i.userID = 0;
                        admit_list.pop_front();
                    }
            }
        } // end of if(EXIT == 1)

        auto iter = seat_list.begin();
        int isFull = 1;

        for (; iter != seat_list.end(); iter++)
            if ((*iter).userID == 0 ) {isFull=0; break;}

        if (isFull) {
                if (!admit_list.empty()){
                     ID_list[admit_list.front()]=0;
                     admit_list.pop_front();
                }
            }

        else {
            auto iter = seat_list.begin();

            for (int i = 0; i<n; i++,iter++)
                if ((*iter).userID != 0) break;

            dist = 0; max_dist = 0;
            auto pre_seat = iter;
            auto max_pre_seat = iter;

            for (int cnt=0; cnt<=n; iter++){
                if (iter == seat_list.end()) continue;
                if ((*iter).userID != 0){
                    dist = (*iter).seatNum - (*pre_seat).seatNum;
                    if (dist < 0) dist = dist + n;
                    if (dist > max_dist) {
                        max_dist = dist;
                        max_pre_seat = pre_seat;
                    }
                    pre_seat = iter;
                }
                cout << "cnt " << cnt << ", dist " << dist << ", max dist "<<max_dist <<", (*iter) " <<(*iter).userID << " " << (*iter).seatNum <<", (*pre_seat) "<< (*pre_seat).userID << " " << (*pre_seat).seatNum << ", (*max_pre_seat) " << (*max_pre_seat).userID << " " << (*max_pre_seat).seatNum << endl;
                cnt++;
            }
            if (max_dist==0) max_dist = n;
            iter = max_pre_seat;
            for (int i = 0; i<max_dist/2; iter++){
                if (iter == seat_list.end()) continue;
                i++;
            }

            if (!admit_list.empty()) {
                (*iter).userID = admit_list.front();
                cout << (*iter).userID << " " << (*iter).seatNum << endl;
                admit_list.pop_front();
            }
        } // end of else(EXIT != 1)
    } // end of while()
} // end of after_admit()
