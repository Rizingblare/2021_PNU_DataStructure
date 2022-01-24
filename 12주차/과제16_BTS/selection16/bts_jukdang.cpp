#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

#define NP nullptr

using namespace std;

struct node{
	node* left;
	node* right;
	string str;
};

class bts{
	public:
		node* root;
		
		bts():root(NP){};
		
		void add_node();
		void remove_node();
		void print_depth();
		void print_leaf();
		
		node* remove_process(node* ptr, string s);
		node* get_max_node(node* p);
		node* get_min_node(node* p);
		int depth_process(int k,int n,node* p);
		void leaf_process(node* p);
};

int main(){
	vector<string> menu={"+","-","depth","leaf","quit"};
	bool run=true;
	bts BTS=bts();
	
	while(run){
		string s;
		cin>>s;
		
		int select=find(menu.begin(),menu.end(),s)-menu.begin();
		switch(select){
			case 0:
				BTS.add_node();		break;
			case 1:
				BTS.remove_node();	break;
			case 2:
				BTS.print_depth();	break;
			case 3:
				BTS.print_leaf();	break;
			case 4:
				run=false;			break;
			default:
				exit(1);
		}
	}
}

void bts::add_node(){
	string s;
	cin>>s;
	
	node* new_node = new node{NP,NP,s};
	new_node->str = s;
	
	if(root==NP)	root=new_node;
	else{
		node* ptr=root;
		node* parent=NP;
		
		while(ptr!=NP){
			parent=ptr;
			if		(s==ptr->str)	return;
			else if	(s> ptr->str)	ptr = ptr->right;
			else 						ptr = ptr->left;
		}
		if(s > parent->str)		parent->right = new_node;
		else						parent->left  = new_node;
	}
}
void bts::remove_node(){
	string s;
	cin>>s;
	root=remove_process(root,s);
}
void bts::print_depth(){
	int k;
	cin>>k;
	k=depth_process(k,1,root);
	if(k==0) cout<<"NO";
	cout<<endl;
}
void bts::print_leaf(){
	leaf_process(root);
	cout<<endl;
}

node* bts::remove_process(node* ptr, string s){
	if(ptr==NP) return ptr;
	else if(ptr->str < s) ptr->right = remove_process(ptr->right,s);
	else if(ptr->str > s) ptr->left  = remove_process(ptr->left ,s);
	else{
		node* change=ptr;
		if(ptr->left!=NP){
			change=get_max_node(ptr->left);
			ptr->str=change->str;
			ptr->left=remove_process(ptr->left,ptr->str);
		}
		else if(ptr->right!=NP){
			change=get_min_node(ptr->right);
			ptr->str=change->str;
			ptr->right=remove_process(ptr->right,ptr->str);
		}
		else if(ptr->left==NP && ptr->right==NP){
			delete ptr;
			ptr=NP;
		}
	}
	return ptr;
}
node* bts::get_max_node(node* p){
	node* ret=p;
	if(ret->right==NP) return ret;
	ret=get_max_node(p->right);
	return ret;
}
node* bts::get_min_node(node* p){
	node* ret=p;
	if(ret->left==NP) return ret;
	ret=get_min_node(p->left);
	return ret;
}
int bts::depth_process(int k,int n,node* p){
	if(p==NP) return 0;
	if(n==k){
		cout<<p->str<<" ";
		return 1;
	}	
	return depth_process(k,n+1,p->left)+depth_process(k,n+1,p->right);
}
void bts::leaf_process(node* p){
	if(p==NP) return;
	if(p->left==NP && p->right==NP)	cout<<p->str<<" ";
	else{
		leaf_process(p->left);
		leaf_process(p->right);
	}
}
