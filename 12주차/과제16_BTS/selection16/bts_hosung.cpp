# include <iostream>
# include <string>
# include <algorithm>
using namespace std;

bool cmp(string l, string r) {
    return lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
}

template<typename T>
struct Node {
    T v;
    int d;
    Node *l, *r;
};

template<typename T>
class tree{
public:
    tree() : root(nullptr) { }
    
    void add_node(T _v);
    bool find_v(T _v);
    void find_k_d(int k, bool &is_in) {
        if (root == nullptr) return;
        root->d = 1;
        d_sub(root, k, is_in);
    }
    void find_leaf(){ print_leaf(root); }
    void remove_node (T _v){
        if (root->v == _v && !root->l && !root->r) {
            delete root;
            root = nullptr;
            return;
        }
        Node<T>* ptr = root;
        remove(ptr, _v);
    }

private:
    Node<T>* root;

    void d_sub(Node<T> *now, int k, bool &is_in) {
        if (now) {
            if (now->d == k) {
                cout << now->v << " ";
                is_in = true; 
            }
            if (now->l) now->l->d = now->d + 1;
            if (now->r) now->r->d = now->d + 1;
            d_sub(now->l, k, is_in);
            d_sub(now->r, k, is_in); 
        }
    }

    void print_leaf(Node<T> *now) {
        if (now) {
            if (!now->l && !now->r) cout << now->v << " ";
            print_leaf(now->l);
            print_leaf(now->r); 
        }
    }

    Node<T>* max_node (Node<T> *node) {
        if (!node) return nullptr;

        while (node->r) { node = node->r; }
        return node;
    }

    Node<T>* min_node (Node<T> *node) {
        if (!node) return nullptr;

        while (node->l) { node = node->l; }
        return node;
    }

    Node<T>* remove(Node<T> *node, T _v);
};

template <typename T>
Node<T>* tree<T>::remove(Node<T>* node, T _v) {
    if (!node) return node;
    else if (cmp(_v, node->v)) 
        node->l = remove(node->l, _v);
    else if (cmp(node->v, _v)) 
        node->r = remove(node->r, _v);
    else {
        Node<T>* ptr = node;
        if (!node->r && !node->l) {
            delete node;
            node = nullptr;
        }
        else if (!node->r) {
            ptr = max_node(node->l);
            node->v = ptr->v;
            node->l = remove(node->l, ptr->v);
        }
        else if (!node->l) {
            ptr = min_node(node->r);
            node->v = ptr->v;
            node->r = remove(node->r, ptr->v); 
        }
        else {
            ptr = max_node(node->l);
            node->v = ptr->v;
            node->l = remove(node->l, ptr->v);
        }
    }
    return node;
}

template <typename T>
bool tree<T>::find_v(T _v) {
    Node<T>* ptr = root;

    while (ptr) {
        if (ptr->v == _v) return true;
        else if (cmp(_v, ptr->v)) ptr = ptr->l; 
        else ptr = ptr-> r;
    }
    return false;
}

template <typename T>
void tree<T>::add_node(T _v) {
    Node<T> *node = new Node<T>();
    Node<T>* tmp_root = nullptr;

    node->v = _v;

    if (!root) root = node;
    else { 
        Node<T> *ptr = root;
        while (ptr) {
            tmp_root = ptr;
            if (cmp(node->v, ptr->v)) ptr = ptr->l; 
            else ptr = ptr->r;
        }

        if (cmp(node->v, tmp_root->v)) tmp_root->l = node; 
        else if (cmp(tmp_root->v, node->v)) tmp_root->r = node;
        else return;
    }
}

int main() {
    tree<string>* BST = new tree<string>();
    string op, v;
    int k; 

    while (1) { 
        cin >> op;
        if (op == "quit") break;

        if (op == "+") {
            cin >> v;
            BST->add_node(v);
        }
        else if (op == "-") {
            cin >> v;
            if (BST->find_v(v)) BST->remove_node(v);
        }
        else if (op == "depth") { 
            cin >> k;
            bool is_in = false;
            BST->find_k_d(k, is_in);
            if (is_in) cout << endl;
            else cout << "NO" << endl;
        }
        else { 
            BST->find_leaf();
            cout << endl;
        }
    }
}