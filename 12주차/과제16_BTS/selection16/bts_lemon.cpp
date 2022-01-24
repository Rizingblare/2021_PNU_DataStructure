#include<iostream>
#include<string>
#include<algorithm>

using namespace std;


typedef struct Node{
  string data;
  Node* left, *right;
} node;


node* root;
bool check = false;


void LeftHigh(node* &root, node* &child){
  if(child->right == NULL){
    root->data = child->data;
    child = child->left;
    return;
  }
  LeftHigh(root, child->right);
}

void RightLow(node* &root, node* &child){
  if(child->left == NULL){
    root->data = child->data;
    child = child->right;
    return;
  }
  RightLow(root, child->left);
}

void Depth(node* &root, int n, int d){
  if(root == NULL) return;
  if(n == d){
    cout << root->data << ' ';
    check = true;
    return;
  }
  ++d;
  Depth(root->left, n, d);
  Depth(root->right, n, d);
}

void Leaf(node* root){
  if(root == NULL) return;
  if(root->left == NULL && root->right == NULL) cout << root->data << ' ';
  Leaf(root->left);
  Leaf(root->right);
}

void Add(node* &root, string s){
  if(root == NULL){
    root = new node();
    root -> data = s;
    root -> left = root -> right = NULL;
    return;
  }
  else if(root->data > s) Add(root->left, s);
  else if(root->data < s) Add(root->right, s);
}

void Delete(node * &root, string s){
  if(root == NULL) return;

  if(root->data > s)      Delete(root->left, s);
  else if(root->data < s) Delete(root->right, s);
  else{ // 지워야할 노드일 경우
    if(root->left != NULL)       LeftHigh(root, root->left);
    else if(root->right != NULL) RightLow(root, root->right);
    else                         root = NULL;
  }

}



int main(){

  string sel, str;
  int n;
  while(true){
    cin >> sel;
    if(sel == "-"){
      cin >> str;
      Delete(root, str);
    }         
    else if(sel == "+"){
      cin >> str;
      Add(root, str);
    }    
    else if(sel == "leaf"){
      Leaf(root);
      cout << '\n';
    }
    else if(sel == "depth") {
      cin >> n;
      Depth(root, n, 1);
      if(!check) cout << "NO\n";
      else {
        check = false;
        cout << '\n';
      }
    }
    else if(sel == "quit")  break;
  }
  return 0;
}