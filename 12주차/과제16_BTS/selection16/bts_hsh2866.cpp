#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#define L 0
#define R 1
#define P make_pair
using namespace std;
struct N {
    N *B[2];
    string d;
    N(){B[L] = NULL; B[R] = NULL;};
    N(string _d){ d = _d; B[L] = NULL; B[R] = NULL; };
    void display(){ cout << this->d << " "; }
    bool operator ==(N* N){ return this->d == N->d; }
};
typedef pair<N*, N*> pNN;
bool isLeaf(N* n){
    return (n->B[L] == NULL) && (n->B[R] == NULL);
}
class BST {
public:
    BST(){ root = NULL; }
    pNN searchN(string d){
        N *pN = NULL, *cN = root;
        while(cN){
            if(d == cN->d) return P(pN, cN);
            pN = cN;
            if (d.compare(cN->d) < 0)  cN = cN->B[L];
            else    cN = cN->B[R];
        }
        return P(pN, cN);
    }
    void setN(N* Na, N* Nb, N* d){
        if(Na->B[L] == Nb)  Na->B[L] = d;
        else    Na->B[R] = d;
    }
    void insertN(string d){
        pNN Ns = searchN(d);
        N *cN = Ns.first, *tN = new N(d);
        if (!root)  root = tN;
        if (Ns.second || !cN)  return;
        if (d.compare(cN->d) < 0) cN->B[L] = tN;
        else cN->B[R] = tN;
    }
    pNN getNs(N* _root, N* n, int dir){
        N* pN = n, *MN;
        int d_ = (dir+1)%2;
        if (pN->B[d_] == NULL)   return P(_root, n);
        while(pN->B[d_]){
            MN = pN->B[d_];
            if(MN->B[d_] == NULL)  return P(pN, MN);
            pN = pN->B[d_];
        }
    }
    void deleteN(string d){
        pNN Ns = searchN(d);
        N *pN = Ns.first, *tN = Ns.second, *nF, *nS;
        if(!tN)  return;
        if(isLeaf(tN)){
            if (tN == root) root = NULL;
            else    setN(pN, tN, NULL);
            return;
        }
        if(tN->B[L] != NULL)   Ns = getNs(tN, tN->B[L], 0);
        else    Ns = getNs(tN, tN->B[R], 1);
        nF = Ns.first; nS = Ns.second;
        if(isLeaf(nS))  setN(nF, nS, NULL);
        else    deleteN(nS->d);
        nS->B[L] = tN->B[L];
        nS->B[R] = tN->B[R];
        if(tN != root)  setN(pN, tN, nS);
        else    root = nS;
    }
    void getkN(vector<N*>& Ns, N* n, int d, int k){
        if (!n)  return;
        if (d == k) Ns.push_back(n);
        else {
            getkN(Ns, n->B[L], d+1, k);
            getkN(Ns, n->B[R], d+1, k);
        }
    }    
    void printkN(int depth){
        vector<N*> kNs;
        getkN(kNs, root, 1, depth);
        if (!kNs.size())    cout << "NO";
        else { for (N* N : kNs)  N->display(); }
        cout << "\n";
    }
    void getLeaf(vector<N*>& Ns, N* n){
        if (!n)  return;
        if (isLeaf(n))   Ns.push_back(n);
        else {
            getLeaf(Ns, n->B[L]);
            getLeaf(Ns, n->B[R]);
        }
    }
    void printLeafN(){
        vector<N*> Ns;
        getLeaf(Ns, root);
        for (N* N : Ns)    N->display();
        cout << "\n";
    }
private:
    N* root;
};

int main(){
    int depth;
    string d, op;
    BST* tree = new BST();
    do {
        cin >> op;
        switch (op[0]){
            case '+': 
                cin >> d;
                tree->insertN(d); break;
            case '-': 
                cin >> d;
                tree->deleteN(d); break;
            case 'd': 
                cin >> depth;
                tree->printkN(depth); break;
            case 'l': 
                tree->printLeafN(); break;
            default : break;
        }
    } while(op != "quit");
}