#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Student{
public:
    string name;
    vector <int> score;
};

int n;
Student stu[200];
vector <Student> stuscore;

void input();
void indivisual_sort();
bool myRank(Student,Student);
void output();

int main(){

    input();

    indivisual_sort();

    sort(stuscore.begin(),stuscore.end(),myRank);
    output();

} // end of main()

void input(){

    cin >> n;

    int score;

    for (int i = 0; i<n; i++){
        cin >> stu[i].name;

        while(1){
            cin >> score;
            if (score) {
                stu[i].score.push_back(score);
            }
            else break;
        }
    }

/*
    for (int i=0; i<n; i++){
        cout <<"i = "<< i << " " << stu[i].name << " " << stu[i].score[0] << endl;
    }
*/
/*
    string s;
    int a;
    for(int i=0; i<n; i++){
        cin >> s;
        studentName.push_back(s);

        studentScore.push_back(vector<int>());
        do {
            cin >> a;
            studentScore[i].push_back(a);
        } while (a!=0);
    }


    for(auto i:studentName)
        cout << i << endl;

    for(const auto &i:studentScore){
        for (const auto &j:i)
            cout << j << " ";
        cout << endl;
    }
*/
} // end of input()

void indivisual_sort(){
    for (int i = 0; i<n; i++){
        sort    (stu[i].score.begin(),stu[i].score.end());
        stuscore.push_back(stu[i]);
    }
}

bool myRank(Student a, Student b){ // compare ÇÔ¼ö
    if (a.score.size()==b.score.size()){
        for(int i = 0 ; i<a.score.size(); i++){
            if (a.score[i]!=b.score[i]) return a.score[i]>b.score[i];
        }
        return a.name < b.name;
    }
    return a.score.size() > b.score.size();
}


void output(){
    for(int i=0; i<n; i++){
        cout << stuscore[i].name <<endl;
    }
}
