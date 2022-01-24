#include <bits/stdc++.h>
using namespace std;
struct Node{
    string data;
    struct Node *left, *right;
};
void removeNode(Node* &root, string input);
Node* newNode(string data){
    Node* tmp = new Node();
    tmp->data = data;
    tmp->left = tmp->right = NULL;
    return tmp;
}
void addNode(Node* &root, string input){
    if(!root){
        root = newNode(input);
        return;
    }
    if(root->data.compare(input)>0)
        addNode(root->left , input);
    else 
        addNode(root->right, input);
}
void right(Node*&root, string& tmp){
    if(!root) return;
    if(!root->right){
        tmp = root->data;
        removeNode(root, root->data);
        return;
    }
    right(root->right, tmp);
}
void removeNode(Node* &root, string input){
    if(!root) return;
    if(root->data == input){
        string tmp;
        right(root->left, tmp = "noChange");
        if(tmp == "noChange") root = root->right;
        else root->data = tmp;
        return;            
    }
    removeNode(root->left , input);
    removeNode(root->right, input);
}
void leaf(Node* root){
    if(!root) return;
    leaf(root-> left );
    if(!root->left && !root->right)
        cout << root->data << " ";
    leaf(root-> right);
}
void depth(Node* root, int& dep, int& out){
    if(!root) return;
    dep--;
    if(!dep){
        cout<<root->data<< " ";
        out++;
    }
    depth(root->left , dep, out);
    depth(root->right, dep, out);
    dep++;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int idx, dpt, out;
    string query, input;
    vector<string> ops = { "+", "-", "depth",  "leaf", "quit"};
    Node* root = NULL;
    while(1){
        cin >> query;
        idx = find(ops.begin(), ops.end(), query) - ops.begin();
        if(idx == 4) break;
        switch(idx){
            case 0:
                cin >> input;
                addNode (root, input);
                break;
            case 1:
                cin >>input;
                removeNode(root, input);
                break;
            case 2:
                cin >> dpt;
                depth(root, dpt, out=0);
                if(!out) cout << "NO";
                cout << endl;
                break;
            case 3:
                leaf(root);
                cout << endl;
                break;
        }
    }
    return 0;
}