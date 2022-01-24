#include <bits/stdc++.h>
using namespace std;

vector<string> Command {"+", "-", "depth", "leaf", "quit"};
struct Node{
    Node* left;
    Node* right;
    string value;

    Node(string value, Node* left, Node* right){
        this->value = value;
        this->left = left;
        this->right = right;
    }
};

Node* getNode(string data){
    return new Node(data, nullptr, nullptr);
}

Node* insertNode(Node* root, string data){
    if(root==nullptr){
        root = getNode(data);
    }else if(data.compare(root->value)<0){
        root->left  = insertNode(root->left,  data);
    }else{
        root->right = insertNode(root->right, data);
    }
    return root;
}

string printNode(Node* root, int k, int l){
    if(root== nullptr) return "";
    if(k==l)           return root->value+" ";
    else{
        return printNode(root->left,k,l+1)+printNode(root->right,k,l+1);
    }
}

string printLeaf(Node* root){
    if(root== nullptr) return "";
    if(root->left== nullptr && root->right== nullptr) return root->value+" ";
    else {
        string left = printLeaf(root->left);
        string right = printLeaf(root->right);
        return left+right;
    }
}

Node* searchMax(Node* root){
    if    (root == nullptr) return nullptr;
    while (root->right != nullptr) {
        root = root->right;
    } return root;

    //출처: https://xtar.tistory.com/40 [EXTAR]
}

Node* searchMin(Node* root){
    if    (root == nullptr) return nullptr;
    while (root->left != nullptr) {
        root = root->left;
    } return root;

    //출처: https://xtar.tistory.com/40 [EXTAR]
}

bool searchData(Node* root, string data){
    Node* ptr = root;
    while (ptr!= nullptr){
        if     (ptr->value==data) return true;
        else if(ptr->value>data)  ptr = ptr->left;
        else                      ptr = ptr->right;
    }
    return false;
}


Node* deleteNode(Node* root, string data){
    if(root==nullptr) return root;
    else if(data<root->value) root->left = deleteNode(root->left,data);
    else if(data>root->value) root->right = deleteNode(root->right,data);
    else{
        //no child(leaf)
        if(root->left== nullptr && root->right== nullptr){
            delete root;
            root = nullptr;

        }else if(root->left== nullptr){//one child
            Node* tmp = searchMin(root->right);
            root->value = tmp->value;
            root->right = deleteNode(root->right, tmp->value);

        } else{ //2children
            Node* tmp = searchMax(root->left);
            root->value = tmp->value;
            root->left  = deleteNode(root->left,tmp->value);
        }
    }
    return root;
}

int main() {
    Node* root= nullptr;
    string cmd;
    string data;
    int k;
    int cmdidx;
    while (true){
        cin >> cmd;
        cmdidx = find(Command.begin(), Command.end(),cmd)-Command.begin();
        switch (cmdidx) {
            case 0:
                cin >> data;
                if(!searchData(root, data)){
                    root = insertNode(root, data);
                }
                break;
            case 1:
                cin >> data;
                if(searchData(root,data)){
                    root = deleteNode(root,data);
                }
                break;
            case 2:
                cin >> k;
                if(printNode(root, k,1)=="") cout << "NO" << endl;
                else cout << printNode(root, k, 1) << endl;
                break;
            case 3:
                if(printLeaf(root)!="") cout << printLeaf(root) << endl;
                break;
            case 4:
                return 0;
            default:break;
        }
    }
    return 0;
}
