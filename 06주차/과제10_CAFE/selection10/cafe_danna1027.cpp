#include <iostream>
#include <list>
using namespace std;

class Information {
public :
	int seat_num;
	int ID;
	int distance;
	Information(int seat_num, int ID, int distance) {
		this->seat_num = seat_num;
		this->ID = ID;
		this->distance = distance;
	}
};

int n, k = 0;
list<int> ID_list;
list<Information> assigned_seat;
list<Information>::iterator it_current, it_previous, it_next;

void read() {
	int id;
	while (1) {
		cin >> n >> k;
		if ((n >= 10 && n <= 10000000) & (k >= 5 && k <= 10000)) break;
	}
	for (int i = 0; i < k; i++) {
		while (1) {
			cin >> id;
			if (id >= 1 && id <= 10000) {
				ID_list.push_back(id);
				break;
			}
		}
	}
	assigned_seat.push_back(Information(n + 1, 0, 0));
	assigned_seat.push_front(Information(0, 0, n + 1));
}

int assign_seat_and_print(int ID) {
	for (auto it = assigned_seat.begin(); it != assigned_seat.end(); it++) {
		if ((*it).ID == ID) {
			it_next = assigned_seat.erase(it);
			it_previous = --it_next;
			(*it_previous).distance = (*++it_next).seat_num - (*it_previous).seat_num;
			return 0;
		}
	}

	if (assigned_seat.size() == n + 2) {
		return 0;
	}
	
	int max = 0;
	for (auto it = assigned_seat.begin(); it != assigned_seat.end(); it++) {
		if ((*it).distance > max) {
			max = (*it).distance;
			it_current = it;
		}
	}

	if (max == n + 1) {
		(*it_current).distance = 1;
		it_next = ++it_current;
		assigned_seat.insert(it_next, Information(1, ID, (*it_next).seat_num - 1));
		cout << ID << " 1" << endl;
		return 0;
	}
	int new_assign_seat = (*it_current).seat_num + max / 2;
	(*it_current).distance = new_assign_seat - (*it_current).seat_num;
	it_next = ++it_current;
	assigned_seat.insert(it_next, Information(new_assign_seat, ID, (*it_next).seat_num - new_assign_seat));
	cout << ID << " " << new_assign_seat << endl;
	return 0;
}

int main() {
	read();

	for (auto ID : ID_list) {
		assign_seat_and_print(ID);
	}

	return 0;
}