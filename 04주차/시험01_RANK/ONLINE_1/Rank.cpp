#include <bits/stdc++.h>
using namespace std ;


void read_show(  ){
    int N, score  ;
    string sname ;

    cin >> N ;
    for(int i=1; i <= N; i++){
        cin >> sname ;
        cout << "\n" << sname ;

        while( 1 ){
            cin >> score ;
            if( score == 0 ) break ;
            else cout << " " << score ;
       }
    } // end of for i

} // end of read_show( )





int main () {

    read_show(  ) ;

    return 0;
}
