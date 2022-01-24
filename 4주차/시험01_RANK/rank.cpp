#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Student {
public:
    vector <int> report;
    string name;
};

int n;
Student stu[200];
vector <Student> stuReport;

void input();
void student_sort();
bool myRank(Student, Student);
void output();

int main() {

    input();

    student_sort();

    output();

    return 0;
} //end of main()

void input(){
    cin >> n;
    for(int i = 0 ; i < n ; i++) {
        cin >> stu[i].name;
        int score = -1;
        while(1) {
            cin >> score;
            if(score) {
                stu[i].report.push_back(score);
            }
            else break;
        }
    sort(stu[i].report.begin(), stu[i].report.end());
    stuReport.push_back(stu[i]);
    }
} // end of input()

void student_sort(){
    sort(stuReport.begin(), stuReport.end(), myRank);
} // end of student_sort()

bool myRank(Student s1, Student s2) {
    if(s1.report.size() == s2.report.size()) {
        for(int i = 0 ; i < s1.report.size() ; i++) {
            if(s1.report[i] != s2.report[i]) {
                return s1.report[i] > s2.report[i];
            }
        }
        return s1.name < s2.name;
    }
    return s1.report.size() > s2.report.size();
} // end of myRank()

void output(){
     for(int i = 0 ; i < stuReport.size() ; i++) {
        cout << stuReport[i].name << endl;
    }
} // end of output()
