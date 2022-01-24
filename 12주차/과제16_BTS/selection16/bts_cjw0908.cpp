#include <bits/stdc++.h>
using namespace std;
string str,find_name;
int dep_index=0;
struct node {
	string name;
	int dep=1;
	node* left_child;
	node* right_child;
};

node* root = 0;
node* createNode() {
	string data;
	cin >> data;
	node* newNode = new node;
	newNode->name = data;
	int dep = 1;
	newNode->left_child = 0;
	newNode->right_child = 0;
	return newNode;
}

bool Plus() {
	node* newNode = createNode();
	node* p = root;
	node* q = 0;

	while (p) {
		q = p;
		if (newNode->name == p->name) return false;
		else if (newNode->name < p->name) {
			p = p->left_child;
		}
		else {
			p = p->right_child;
		}
	}
	
	if (!root) {//root가 비어있을때
		root = newNode;
	}
	else if (newNode->name < q->name) {
		q->left_child = newNode;
		newNode->dep = (q->dep) + 1;
	}
	else {
		q->right_child = newNode;
		newNode->dep = (q->dep) + 1;
	}
	return true;
}
void Minus() {
	cin >> find_name;
	int find_index = 0 , left_right=-1;
	node* m_p = root;
	node* temp = 0;
	node* parent = 0;
	node* m_q = 0;
	while (m_p) {
		m_q = m_p;
		if (find_name == m_p->name) {
			find_index++;
			break;
		}
		else if (find_name < m_p->name) {
			parent = m_q;
			left_right = 0;
			m_p = m_p->left_child;
		}
		else {
			parent = m_q;
			left_right = 1;
			m_p = m_p->right_child;
		}
	}
	temp = m_q;
	int right=0,child=0,inde=0;
	if (find_index != 0) {
		while (true) {
			
			if (temp->left_child == 0 && temp->right_child == 0 && temp==m_q) {
				if (parent == 0) {
					root = 0;
				}
				else if (left_right == 0) parent->left_child = 0;
				else parent->right_child = 0;
				break;
			}
			if (temp->left_child == 0 && temp->right_child == 0 && temp != m_q ||right==1) {
				if (left_right == 0) {
					m_q->name = temp->name;
					parent->left_child = 0;
					break;
				}
				else {
					m_q->name = temp->name;
					if (child == 0) {
						parent->right_child = 0;
						break;
					}
					else {
						m_q = temp;
						right = 0;
						continue;
					}
				} 
			}
			else if (temp->left_child == 0) {
				
				parent = temp;
				temp = temp->right_child;
				left_right = 1;
				right = 1;
				if(temp->left_child!=0 || temp->right_child!=0) child = 1;
			}
			else{
				parent = temp;
				temp = temp->left_child;
				left_right = 0;
			}
		}
	}
}
void Depth(node* tree, int k) {
	
	if (tree == 0) {
		return;
	}
	if (tree->dep == k) {
		cout << tree->name << " ";
		dep_index++;
	}
	Depth(tree->left_child,k);
	Depth(tree->right_child,k);
}

void Leaf(node* L_tree) {
	if (L_tree == 0) {
		return;
	}
	if (L_tree->left_child == 0 && L_tree->right_child == 0) {
		cout<< L_tree->name << " ";
	}
	Leaf(L_tree->left_child);
	Leaf(L_tree->right_child);
}

void readInput() {
	int index = 0;
	vector<string> ops = { "+","-","depth","leaf","quit"};
	while (index!=4) {
		cin >> str;
		index = find(ops.begin(), ops.end(), str) - ops.begin();
		switch (index) {
		case 0:
			Plus();
			break;
		case 1:
			Minus();
			break;
		case 2:
			int k;
			cin >> k;
			dep_index = 0;
			Depth(root,k);
			if (dep_index == 0) cout << "NO";
			cout << endl;
			break;
		case 3:
			Leaf(root);
			cout << endl;
			break;
		case 4:
			break;
		default:
			break;
		}
	}
}

int main() {
	readInput();
	return 0;
}

