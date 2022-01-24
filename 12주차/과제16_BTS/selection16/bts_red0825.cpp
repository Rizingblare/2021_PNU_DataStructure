#include <bits/stdc++.h>
using namespace std;
class Node{
public:
string data;
Node* leftChild=NULL;
Node* rightChild=NULL;
Node(string key){data=key;}};
Node* root=NULL;
int mytype(string whichType){
vector<string> tokens{"+","-","leaf","depth","quit"};
int type=0;
for(string cut:tokens){
if(whichType==cut)return type;
else type++;}
return type;}
void insertNode(Node* tree,Node* node){
if(node->data<tree->data){
if(tree->leftChild==NULL){
tree->leftChild=node;
return;}
else insertNode(tree->leftChild,node);}
else if(node->data>tree->data){
if(tree->rightChild==NULL){
tree->rightChild=node;
return;}
else insertNode(tree->rightChild,node);}
else return;}
void leafData(Node *tree){
if(tree==NULL)return;
else if(tree->leftChild==NULL&&tree->rightChild==NULL)cout<<tree->data<<" ";
leafData(tree->leftChild);
leafData(tree->rightChild);}
void depthData(Node *tree,int depth){
if(tree==NULL||depth<0)return;
else if(depth==0)cout<<tree->data<<" ";
depthData(tree->leftChild,depth-1);
depthData(tree->rightChild,depth-1);}
int maxDepth(Node* tree) {
if(tree == NULL)return 0;
int left=maxDepth(tree->leftChild);
int right=maxDepth(tree->rightChild);
left+=1;
right+=1;
return max(left, right);}
Node* minNode(Node* tree){
if(tree==NULL)return NULL;
if(tree->leftChild==NULL)return tree;
else return minNode(tree->leftChild);}
Node* maxNode(Node* tree){
if(tree==NULL)return NULL;
if(tree->rightChild==NULL)return tree;
else return maxNode(tree->rightChild);}
Node* removeNode(Node* tree,Node* parent,string target){
if(tree==NULL)return NULL;
Node* removedNode=NULL;
if(tree->data>target)removedNode=removeNode(tree->leftChild,tree,target);
else if(tree->data<target)removedNode=removeNode(tree->rightChild,tree,target);
else{
removedNode=tree;
if(tree->leftChild==NULL&&tree->rightChild==NULL){
if(parent->leftChild==tree) parent->leftChild=NULL;
if(parent->rightChild==tree) parent->rightChild=NULL;}
else if(tree->leftChild==NULL||tree->rightChild==NULL){
if(tree->leftChild!=NULL){
Node* maxnode=maxNode(tree->leftChild);
tree->data=maxnode->data;
removeNode(tree->leftChild,tree,maxnode->data);}
else{
Node* minnode=minNode(tree->rightChild);
tree->data=minnode->data;
removeNode(tree->rightChild,tree,minnode->data);}}
else{
Node* maxnode=maxNode(tree->leftChild);
tree->data=maxnode->data;
removeNode(tree->leftChild,tree,maxnode->data);}}
return removedNode;}
int main(){
int k;
string val,whichType;
bool keep=true;
while(keep){
cin>>whichType;
switch(mytype(whichType)){
case 0:
cin>>val;
if(root==NULL)root=new Node(val);
else{
Node *node=new Node(val);
insertNode(root,node);
}
break;
case 1:
cin>>val;
if(maxDepth(root)==1)root=NULL;
else removeNode(root,NULL,val);
break;
case 2:
leafData(root);
cout<<endl;
break;
case 3:
cin>>k;
if(maxDepth(root)<k)cout<<"NO";
else depthData(root,k-1);
cout<<endl;
break;
case 4:
keep=false;
break;
default:break;
}
}
return 0;
}
