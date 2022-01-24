#include <iostream>
#include <deque>
#include <list>
#include <tuple>

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
void find_present_seat();
void isMaxDist(int);
void seatNotice(int);

int n, k;
int ID_list[10001] = {};
deque <int> admit_list;
list <Seat> seat_list;
list <Seat>::iterator iter = seat_list.begin();
int seatNum, pre_seat;
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
    if (!admit_list.empty()) {
        if (isExit(admit_list.front()) == 0)
            (*iter)->userID = admit_list.front();
        seatNotice(0);
        admit_list.pop_front();
    }
} // end of first_admit()

void after_admit() {

    while (!admit_list.empty()) {
        int EXIT = isExit(admit_list.front());
        //cout << admit_list.front() << " is Exit?? " << EXIT << endl;

        if (EXIT) {
            if (!admit_list.empty()) {
                for (auto& i : seat_list)
                    if (i.userID == admit_list.front()) {
                        i.userID = 0;
                        admit_list.pop_front();
                    }
            }
        } // end of if(EXIT == 1)
        else {
            pre_seat = 0; dist = 0; max_dist = 0;

            find_present_seat();

            int cnt = 0;
            while (cnt <= n) {
                if (iter == seat_list.end()) { iter++; continue; }
                if (cnt == 0) { cnt++; seatNum++;  iter++; continue; }
                if (seatNum >= n) seatNum -= n;

                dist++;
                if (*iter) isMaxDist(seatNum);
                iter++; cnt++; seatNum++;
            }

            int yourSeat = pre_seat + max_dist / 2;
            if (yourSeat >= n) yourSeat -= n;
            iter = seat_list.begin();
            advance(iter, yourSeat);

            if (!admit_list.empty()) {
                *iter = admit_list.front();
                seatNotice(yourSeat);
                admit_list.pop_front();
            }
        } // end of else(EXIT != 1)
    } // end of while()
} // end of after_admit()

//cout<<"*iter = " << *iter << ", count = " << count <<", seatNum = " << seatNum << ", pre_seat = " << pre_seat << ", dist = " << dist << ", max_dist = " << max_dist <<endl;

void find_present_seat(){
    iter = seat_list.begin();
     for (int i = 0; i < n; i++,iter++)
                if (*iter.) { seatNum = i; break; }
} // end of find_present_seat()

void isMaxDist(int seatNum) {
    if (dist > max_dist) {
        if (dist > seat_list_num)
            pre_seat = seatNum + n - dist;
        else pre_seat = seatNum - dist;
        max_dist = dist;
    }
    dist = 0;
} // end of isMaxDist()

void seatNotice(int num) {
    cout << admit_list.front() << " " << num + 1 << endl;
} // end of seatNotice()
