#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;
typedef struct { string name ;  vector<int> report; }  Stud ;

bool cmpName ( Stud a, Stud b) { 
    return ((a.name) < ( b.name )) ;
}

bool cmpMin ( Stud a, Stud b) {
	vector<int>::iterator iterA = a.report.begin();
	vector<int>::iterator iterB = b.report.begin();
	
	while (iterA < a.report.end() && iterB < a.report.end()) {
		if (*iterA == *iterB) { iterA++; iterB++; }
		else return (*iterA > *iterB);
	}
    return cmpName(a, b);
}

bool cmpSize ( Stud a, Stud b) {
    if ((a.report.size()) == ( b.report.size())) return cmpMin(a, b);
	else return ((a.report.size()) > ( b.report.size())) ;
}

bool cmpFunc ( Stud a, Stud b) {
	return cmpSize(a, b);
}

void printClass( vector < Stud > Sreport ){
    for(auto s : Sreport) cout << "\n" << s.name;
    return;
}


int main() {

    int studNum, score;
    string sname;
    Stud   student;
    vector < Stud > Sreport;

    cin >> studNum ;
    for(int i=1; i <= studNum; i++){
        cin >> sname ;
        student.name = sname;
        student.report.clear();

        while( 1 ){
            cin >> score ;
            if( score == 0 ) break ;
            else student.report.push_back(score);
       }
       sort( student.report.begin(), student.report.end());
       Sreport.push_back(student);
   }

    sort( Sreport.begin(), Sreport.end(), cmpFunc) ;
	printClass( Sreport ) ;
	   
	return 0;
}
