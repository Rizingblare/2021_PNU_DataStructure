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
    void add(string s){
        Node* addNode = new Node();
        addNode->value = s;

        if (root == nullptr) root = addNode;
        else {
            Node* ptr = root;
            while (ptr != nullptr){
                if      ((ptr->value) < (addNode->value)){
                    if (ptr->right == nullptr){ptr->right = addNode;return;}
                    else ptr = ptr->right;
                }
                else if ((addNode->value) < (ptr->value)){
                    if (ptr->left == nullptr) {ptr->left = addNode; return;}
                    else ptr = ptr->left;
                }
                else return;
            }
        }
    }
    void del(string s){
        Node* del_ptr = root;
        Node* parent = nullptr;
        string way = "";
        while (1){
            if (del_ptr == nullptr) return;
            else if      ((del_ptr->value) < s){
                if (del_ptr->right == nullptr) return;
                else {parent = del_ptr; del_ptr = del_ptr->right; way = "r";}
            }
            else if ( s < (del_ptr->value)){
                if (del_ptr->left == nullptr) return;
                else {parent = del_ptr; del_ptr = del_ptr->left; way = "l";}
            }
            else break;
        }
        if ((del_ptr->left == nullptr)&&(del_ptr->right == nullptr)){
            if (way == "r") parent->right = nullptr;
            else if (way == "l") parent->left = nullptr;
            else root = nullptr;
            delete del_ptr;
        }
        else NodeSwap(del_ptr);
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
        check_depth(root,0,i);
    }
    void check_depth(Node *curr, int mydepth, int check){
        if (curr != nullptr){
            mydepth++;
            if (check == mydepth) cout << curr->value << " ";
            check_depth(curr->left,mydepth,check);
            check_depth(curr->right,mydepth,check);
        }
    }
    Node* root;
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
        if      (i == "leaf") {BTS.leaf(BTS.root); cout<<endl;}

        else if (pre_i == "+") BTS.add(i);

        else if (pre_i == "-") BTS.del(i);

        else if (pre_i == "depth") {BTS.depth(i); cout<<endl;}

        pre_i = i;
    }

} // end of bts_output()
