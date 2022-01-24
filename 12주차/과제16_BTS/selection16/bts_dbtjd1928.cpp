#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    string data;
    Node* left = NULL;
    Node* right = NULL;

    Node(string d) : data(d) {}
};

queue<string> q_inp, q_out;
Node* root = NULL;

void InsertNode(Node* tree, Node* node) {
    if (node->data < tree->data) {
        if (tree->left == NULL) {
            tree->left = node;
            return;
        } else {
            InsertNode(tree->left, node);
        }
    } else if (node->data > tree->data) {
        if (tree->right == NULL) {
            tree->right = node;
            return;
        } else {
            InsertNode(tree->right, node);
        }
    } else {
        return;
    }
}
Node* SearchMinNode(Node* tree) {
    if (tree == NULL)       return NULL;
    if (tree->left == NULL) return tree;
    else                    return SearchMinNode(tree->left);
}
Node* SearchMaxNode(Node* tree) {
    if (tree == NULL)        return NULL;
    if (tree->right == NULL) return tree;
    else                     return SearchMaxNode(tree->right);
}
void RemoveNode(Node* tree, Node* parent, string target) {
    if (tree == NULL)
        return;

    if (tree->data > target)        
        RemoveNode(tree->left, tree, target);
    else if (tree->data < target)
        RemoveNode(tree->right, tree, target);
    else
        if (tree->left == NULL && tree->right == NULL) {
            if (tree == root) {
                root = NULL;
                return;
            }

            if (parent->left == tree) 
                parent->left = NULL;
            else
                parent->right = NULL;
        } else if (tree->left == NULL) {
            Node* min_Right = SearchMinNode(tree->right);
            string minData = min_Right->data;
            RemoveNode(tree, NULL, minData);
            tree->data = minData;
        } else {
            Node* max_Left = SearchMaxNode(tree->left);
            string maxData = max_Left->data;
            RemoveNode(tree, NULL, maxData);
            tree->data = maxData;
        }
}
void Depth(Node* tree, queue<string>& q, int depth, int target) {
    if (tree == NULL)
        return;
    
    Depth(tree->left, q, depth + 1, target);
    if (depth == target)
        q.push(tree->data);
    Depth(tree->right, q, depth + 1, target);
}
void Leaf(Node* tree, queue<string>& q) {
    if (tree == NULL)
        return;
    
    Leaf(tree->left, q);
    if (tree->left == NULL && tree->right == NULL)
        q.push(tree->data);
    Leaf(tree->right, q);
}
void PrintOutput(queue<string>& q) {
    if (q.empty()) {
        cout << "NO\n";
        return;
    }
    while (!q.empty()) {
        cout << q.front() << ' ';
        q.pop();
    }
    cout << '\n';
}
int main() {
    string inp;
    do {
        cin >> inp;
        q_inp.push(inp);
    } while (inp != "quit");

    vector<string> tokens = {"+", "-", "leaf", "depth", "quit"};
    while (!q_inp.empty()) {
        string opr = q_inp.front();
        q_inp.pop();
        int idx = find(tokens.begin(), tokens.end(), opr) - tokens.begin();
        string data;
        switch (idx) {
            case 0 :
            case 1 :
            case 3 :
                data = q_inp.front();
                q_inp.pop();
                break;
        }
        int targetDepth;
        switch (idx) {
            case 0 :
                if (root == NULL) root = new Node(data);
                else              InsertNode(root, new Node(data));
                break;
            case 1 :
                RemoveNode(root, NULL, data);
                break;
            case 2 :
                Leaf(root, q_out);
                PrintOutput(q_out);
                break;
            case 3 :
                targetDepth = stoi(data);
                Depth(root, q_out, 1, targetDepth);
                PrintOutput(q_out);
                break;
            case 4 :
                return 0;
        }
    }
}