#include <bits/stdc++.h>
using namespace std;
bool out;

typedef struct node {
    string data;
    struct node *left, *right;
} Node;

void addNode(Node*& head, string mystr) {
    if (!head) {
        head = new Node();
        head->data = mystr;
        head->left = NULL;
        head->right = NULL;
    }
    else {
        if (head->data > mystr) addNode(head->left, mystr);
        else addNode(head->right, mystr);
    }
}

void right(Node*& head, string& temp);
void delNode(Node*& head, string mystr) {
    if (!head) return;
    if (head->data == mystr) {
        string temp = "NULL";
        right(head->left, temp);
        if (temp == "NULL")
            head = head->right;
        else
            head->data = temp;
        return;
    }
    delNode(head->left, mystr);
    delNode(head->right, mystr);
}

void right(Node*& head, string& temp) {
    if (!head) return;
    if (!head->right) {
        temp = head->data;
        delNode(head, head->data);
        return;
    }
    right(head->right, temp);
}

void depth(Node* head, int dep) {
    if (!head) return;
    if (dep == 1) {
        out = false;
        cout << head->data << " ";
        return;
    }
    depth(head->left, dep - 1);
    depth(head->right, dep - 1);
}

void leaf(Node* head) {
    if (!head) return;
    if (!head->left && !head->right) cout << head->data << " ";
    leaf(head->left);
    leaf(head->right);
}

int main(){
    int index, mydep;
    string mycom, mystr;
    vector<string> command = { "+", "-", "depth",  "leaf", "quit"};
    Node* head = NULL;

    while(1) {
        cin >> mycom;
        index = find(command.begin(), command.end(), mycom) - command.begin();
        switch (index) {
            // + string
            case 0:
                cin >> mystr;
                addNode(head, mystr);
                break;
            // - string
            case 1:
                cin >> mystr;
                delNode(head, mystr);
                break;
            // depth k
            case 2:
                cin >> mydep;
                out = true;
                depth(head, mydep);
                if (out) cout << "NO";
                cout << endl;
                break;
            // leaf
            case 3:
                leaf(head);
                cout << endl;
                break;
            // quit
            case 4:
                return 0;
            default:
                break;
        }
    }
    return 0;
}