#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

#define REP(i, a, b) for(auto i=a;i<b;i++)

struct SEAT {
    int ID;
    int distance;
};


class CAFE {
  private:
    int numofseat;
    int start_seat_number;
    list<SEAT> seats;

    list<SEAT>::iterator seat_arrangement(int id, list<SEAT>::iterator previous_seat);
    void ENTER(int id);
    void EXIT(list<SEAT>::iterator seat);

  public:
    CAFE(int n): numofseat(n) {}
    
    int find_seat_number(list<SEAT>::iterator seat);
    list<SEAT>::iterator max_distance_seat();

    bool isfull() {return seats.size() == numofseat;}
    bool isempty() {return seats.size() == 0;}
    
    void print_SEAT(list<SEAT>::iterator seat) {cout << seat->ID << ' ' << find_seat_number(seat)+1 << endl;}
    
    void ENTER_OR_EXIT(int id) {
        list<SEAT>::iterator it = find_if(seats.begin(), seats.end(), [id](SEAT seat)->bool{return seat.ID == id;});
        if(it == seats.end()) ENTER(id);
        else EXIT(it);
    }
};


int main() {
    int n, k;
    cin >> n >> k;
    CAFE C(n);

    REP(_,0,k) {
        int id;
        cin >> id;        
        C.ENTER_OR_EXIT(id);
    }

    return 0;
}


int CAFE::find_seat_number(list<SEAT>::iterator seat) {
    if(seat == seats.begin()) return start_seat_number;

    int res = start_seat_number;
    
    for(auto it = seats.begin(); it != seat; it++)
        res += it->distance;
    
    res %= numofseat;
    return res;
}


list<SEAT>::iterator CAFE::max_distance_seat() {
    return max_element(seats.begin(), seats.end(),[](SEAT seat1, SEAT seat2)->bool{return (seat1.distance < seat2.distance);});
}


list<SEAT>::iterator CAFE::seat_arrangement(int id, list<SEAT>::iterator previous_seat) {

    int tmp = previous_seat->distance;
    previous_seat->distance /= 2;

    int new_seat_distance   = tmp - previous_seat->distance;
    int new_seat_number     = find_seat_number(previous_seat)                             + previous_seat->distance;
    list<SEAT>::iterator new_seat;

    if(new_seat_number >= numofseat) { // case that new seat number is lowest
        new_seat_number %= numofseat;
        start_seat_number = new_seat_number;
        seats.push_front({id, new_seat_distance});
        new_seat = seats.begin();
    }
    else {
        new_seat = previous_seat; ++new_seat;
        seats.insert(new_seat, {id, new_seat_distance});
        --new_seat;
    }

    return new_seat;
}


void CAFE::ENTER(int id) {
    if(isfull()) {return;}
    if(isempty()) {
        start_seat_number = 0;
        seats.push_back({id, numofseat});
        cout << id << ' ' << 1 << endl;
        return;
    }

    else {
        list<SEAT>::iterator previous_seat  = max_distance_seat();
        list<SEAT>::iterator new_seat       = seat_arrangement(id, previous_seat);
        
        print_SEAT(new_seat);
        return;
    }
}


void CAFE::EXIT(list<SEAT>::iterator seat) {
    list<SEAT>::iterator previous_seat = seat; 

    if(seat == seats.begin()) { // case that exiting seat number is lowest
        previous_seat     = (--seats.end()); // largest seat number
        start_seat_number = (start_seat_number + seat->distance) % numofseat; // next lowest seat number
    }
    else --previous_seat;
    
    previous_seat->distance += seat->distance;
    
    seats.erase(seat);
}