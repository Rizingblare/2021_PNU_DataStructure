#include <iostream>
#include <list>
#include <deque>

using namespace std;

int main(){
    int n;
    cin >> n;

    list <int> nlist(n);

    for (auto i: nlist)
        cout<< i << endl;

    cout<< "nlist.empty() = " << nlist.empty() <<endl;
}
