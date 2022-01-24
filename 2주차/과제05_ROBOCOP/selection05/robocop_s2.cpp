#include <iostream>
#include <array>
#include <vector>
using namespace std;

vector<pair<int, int>> dot;
vector<pair<int, int>> result;
pair<int, int> now_d;
pair<int, int> next_d;
array<int, 5> second = { 0, };

pair<int, int> computing(int num, int second) {
    int i = 0;
    int time = 0;
    now_d = dot[i % num];
    while (1) {
        now_d = dot[i % num];
        if (i % num == num - 1) next_d = dot[0];
        else next_d = dot[i % num + 1];
        while (now_d.first != next_d.first || now_d.second != next_d.second) {
            if (now_d.first < next_d.first) {
                now_d.first++;
            }
            else if (now_d.first > next_d.first) {
                now_d.first--;
            }
            else if (now_d.second < next_d.second) {
                now_d.second++;
            }
            else if (now_d.second > next_d.second) {
                now_d.second--;
            }
            time++;
            if (second == time) return now_d;
        }
        if (second == time) return now_d;
        i++;
    }
}

int main()
{
    //input
    int num, x, y;
    cin >> num;

    for (int i = 0; i < num; i++) {
        cin >> x >> y;
        dot.push_back(make_pair(x, y));
    }

    cin >> second[0] >> second[1] >> second[2] >> second[3] >> second[4];
    
    //output
    for (int i = 0; i < 5; i++) {
        cout << computing(num, second[i]).first << ' ' << computing(num, second[i]).second << '\n';
    }
}