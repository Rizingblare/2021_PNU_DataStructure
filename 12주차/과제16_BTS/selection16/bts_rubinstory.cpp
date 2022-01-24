#include <bits/stdc++.h>
#define SORT(vec) sort(vec.begin(), vec.end())
using namespace std;

typedef struct Node {
    string data;
    struct Node * parent, * left, * right;
    Node(string data): data(data) { parent = left = right = NULL; }
    bool isLeaf(void) { return !left && !right; }
    void remove(Node * child) {
        if (left == child) left = NULL;
        else right = NULL;
    }
};

class BST {
private:
    Node * head;
public:
    BST() {}
    BST(Node * head): head(head) {}
    void add(Node * node) {
        if (!head) { head = node; return; }
        Node * curr = head;
        while(curr && curr != node) {
            if (node->data == curr->data) return;
            if (node->data < curr->data) {
                if (!curr->left) {
                    curr->left = node;
                    node->parent = curr;
                }
                curr = curr->left;
            }
            else {
                if (!curr->right) {
                    curr->right = node;
                    node->parent = curr;
                }
                curr = curr->right;
            }
        }
    }
    
    void remove(string &target) { recursiveRemove(head, target); }
    
    void recursiveRemove(Node * curr, string &target) {
        if (!curr) return;
        if (curr->data == target) {
            if (curr->isLeaf()) {
                if (curr == head) head = NULL;
                else curr->parent->remove(curr);
            }
            else {
                Node * next;
                if (curr->left) next = findMax(curr->left);
                else next = findMin(curr->right);
                string temp = curr->data;
                curr->data = next->data;
                next->data = temp;
                recursiveRemove(next, target);
            }
            return ;
        }
        recursiveRemove(curr->left, target);
        recursiveRemove(curr->right, target);
    }
    
    Node * findMax(Node * curr) { return curr->right ? findMax(curr->right) : curr; }
    Node * findMin(Node * curr) { return curr->left ? findMin(curr->left) : curr; }
    
    void print(bool leafFlag, int depth) {
        vector<string> vec;
        queue<pair<Node *, int>> que;
        if (head) que.push({head, 1});
        
        while(!que.empty()) {
            Node * curr = que.front().first;
            int level = que.front().second;
            que.pop();
            if (!curr) continue;
            
            if (leafFlag){
                if (curr->isLeaf()) vec.push_back(curr->data);
            }
            else if (level == depth) {
                vec.push_back(curr->data);
            }
            que.push({curr->left, level + 1});
            que.push({curr->right, level + 1});
        }
        sort(vec.begin(), vec.end());
        if (!vec.size() && !leafFlag) { cout << "NO"; }
        else {
            for (auto &s: vec) cout << s << " ";
        }
        cout << "\n";
    }
};

vector<string> token = {"+", "-", "leaf", "depth"};
enum MENU {ADD, REMOVE, LEAF, DEPTH};

int main(void) {
    BST * tree = new BST();
    string s;
    cin >> s;
    while(s != "quit") {
        int idx = find(token.begin(), token.end(), s) - token.begin();
        switch(idx) {
            case ADD:
                cin >> s;
                tree->add(new Node(s));
                break;
            case REMOVE:
                cin >> s;
                tree->remove(s);
                break;
            case LEAF:
                tree->print(1, 0);
                break;
            case DEPTH:
                int n; cin >> n;
                tree->print(0, n);
        }
        cin >> s;
    }
    return 0;
}
