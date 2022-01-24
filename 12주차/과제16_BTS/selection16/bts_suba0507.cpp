#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    string key = "";
    Node* left = NULL;
    Node* right = NULL;
    Node(string _key) : key(_key){}
    void setKey(string _key){key = _key;}
    void setLeft(Node* _left){left = _left;}
    void setRight(Node* _right){right = _right;}
    string getKey(){return key;}
    Node* getLeft(){return left;}
    Node* getRight(){return right;}
};

Node* insertNode(Node* node, string key){
    if(node == NULL){return new Node(key);}
    if(node->getKey() > key){
        node->setLeft(insertNode(node->getLeft(), key));
    }
    else if(node->getKey() < key){
        node->setRight(insertNode(node->getRight(), key));
    }
    return node;
}

Node* deleteNode(Node* node, string key){
    if(node == NULL){return node;}
    if(node->getKey() > key){
        node->setLeft(deleteNode(node->getLeft(), key));
    }
    else if(node->getKey() < key){
        node->setRight(deleteNode(node->getRight(), key));
    }
    else{   //equal
        if((node->getLeft() == NULL) && (node->getRight() == NULL)){
            delete node;
            return NULL;
        }
        Node *alt, *alt_parent = node;
        int mode;
        if(node->getLeft() != NULL){
            mode = 1;
            alt = node->getLeft();
            while(alt->getRight()){
                mode = 0;
                alt_parent = alt;
                alt = alt->getRight();
            }
        }
        else{
            mode = 0;
            alt = node->getRight();
            while(alt->getLeft()){
                mode = 1;
                alt_parent = alt;
                alt = alt->getLeft();
            }
        }
        string temp = node->getKey();
        node->setKey(alt->getKey());
        alt->setKey(temp);
        if(mode == 1){
            alt_parent->setLeft(deleteNode(alt, key));
        }
        else{
            alt_parent->setRight(deleteNode(alt, key));
        }
    }
    return node;
}

void printLeaves(Node* node){
    if(node == NULL){return;}
    if((node->getLeft() == NULL) && (node->getRight() == NULL)){
        cout << node->getKey() << " ";
    }
    else{
        printLeaves(node->getLeft());
        printLeaves(node->getRight());
    }
}

int printDepthK(Node* node, int k){
    if(node == NULL || k == 0){return 0;}
    if(k == 1){
        cout << node->getKey() << " ";
        return 1;
    }
    else{
        return printDepthK(node->getLeft(), k-1) + printDepthK(node->getRight(), k-1);
    }
}

int main() {
    Node* root = NULL;
    bool run = true;
    vector<string> ops{"+", "-", "leaf", "depth", "quit"};
    while(run){
        string op, key;
        int k;
        cin >> op;
        switch(find(ops.begin(), ops.end(), op)-ops.begin()){
            case 0:
                cin >> key; root = insertNode(root, key); break;
            case 1:
                cin >> key; root = deleteNode(root, key); break;
            case 2:
                printLeaves(root); cout << endl; break;
            case 3:
                cin >> k; if(printDepthK(root, k) == 0){cout << "NO";} cout << endl; break;
            case 4:
                run = !run; break;
        }
    }
}
