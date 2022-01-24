#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Node{
public:
    string value;
    Node* left;
    Node* right;
};

class BinarySearchTree {
public:
    void inOrder(Node* curr){
        if (curr != nullptr){
            inOrder(curr->left);
            cout << curr->value << " ";
            inOrder(curr->right);
        }
    }
    void add(string s){
        Node* addNode = new Node();
        addNode->value = s;
        if (R == nullptr) R = addNode;
        else{
            Node* addLoc = check_node(R,s,'+',nullptr);
            if (addLoc == nullptr) addLoc = addNode;
            else return;
        }
    }
    Node* check_node(Node* curr,string s,char mode,Node* parent){
        if (curr == nullptr) return curr;
        else if (curr->value < s) check_node(curr->right,s,mode,curr);
        else if (s < curr->value) check_node(curr->left,s,mode,curr);
        else {
            if (mode =='+') return curr;
            else if (mode == '-') return parent;
        }
    }

    void del(string s){
        if (R == nullptr) return;
        else if (R->value == s){
            if ((R->left == nullptr)&&(R->right == nullptr))
                R = nullptr;
            else NodeSwap(R);
        }
        else{
            Node* del_par = check_node(R,s,'-',nullptr);
            string ps = del_par->value;
            Node* del_ptr = nullptr;
            if (del_par == nullptr) return;
            else if (ps < s) del_ptr = del_par->right;
            else if (s < ps) del_ptr = del_par->left;

            if ((del_ptr->left == nullptr)&&(del_ptr->right == nullptr)){
                if (ps < s) del_par->right = nullptr;
                else if (s < ps) del_par->left = nullptr;
                delete del_ptr;
            }
            else NodeSwap(del_ptr);
        }
}
    void NodeSwap(Node* pre_ptr){
        Node* ptr = pre_ptr;
        Node* parent = nullptr;
        if (ptr->left != nullptr){
            parent = ptr;
            ptr = ptr->left;
            while (ptr->right != nullptr){
                parent = ptr;
                ptr = ptr->right;
            }
        }
        else if (ptr->right != nullptr){
                parent = ptr;
                ptr = ptr->right;
            while (ptr->left != nullptr){
                parent = ptr;
                ptr = ptr->left;
            }
        }
        if ((ptr->left == nullptr)&&(ptr->right == nullptr)){
            if (parent->value < ptr->value) parent->right = nullptr;
            else if (ptr->value < parent->value) parent->left = nullptr;
            pre_ptr->value = ptr->value;
            delete ptr;
            ptr = nullptr;
        }
        else {pre_ptr->value = ptr->value; NodeSwap(ptr);}
    }
    void leaf(Node* curr){
        if ((curr->left == nullptr)&&(curr->right == nullptr))
            cout << curr->value << " ";
        if (curr->left != nullptr)
            leaf(curr->left);
        if (curr->right != nullptr)
            leaf(curr->right);
    }
    void depth(string s){
        int i = s.at(0) - '0';
        check_depth(R,0,i);
    }
    void check_depth(Node *curr, int mydepth, int check){
        if (curr != nullptr){
            mydepth++;
            if (check == mydepth) cout << curr->value << " ";
            check_depth(curr->left,mydepth,check);
            check_depth(curr->right,mydepth,check);
        }
    }
    Node* R;
} BTS;

void bts_input();
void bts_output();

vector <string> com_list;

int main(){
    bts_input();

    bts_output();
    return 0;
} // end of main()

void bts_input(){

    ifstream cin("04.inp");

    string tmp;

    cin >> tmp;
    while (tmp != "quit"){
        com_list.push_back(tmp);
        cin >> tmp;
    }
} // end of bts_input()


void bts_output(){
    string pre_i;
    for (auto i : com_list){
        if      (i == "leaf") {BTS.leaf(BTS.R); cout<<endl;}

        else if (pre_i == "+") {BTS.add(i); BTS.inOrder(BTS.R);}

        else if (pre_i == "-") BTS.del(i);

        else if (pre_i == "depth") {BTS.depth(i); cout<<endl;}

        pre_i = i;
    }

} // end of bts_output()
