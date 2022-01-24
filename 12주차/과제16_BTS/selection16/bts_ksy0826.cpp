#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	string data;
	Node* left;
	Node* right;
};

vector<string> printVec;

int myCmd(string cmd) {
	vector<string> cmdVec = { "+", "-", "depth", "leaf", "quit" };
	auto it = find(cmdVec.begin(), cmdVec.end(), cmd);
	if (it == cmdVec.end()) return -1;
	else return (it - cmdVec.begin());
}
enum { ADD, DELETE, DEPTH, LEAF, QUIT };

Node* addNode(string str) {
	Node* node = new Node;
	node->data = str;
	node->left = nullptr;
	node->right = nullptr;
	return node;
}

void addStr(Node*& node, string str) {
	if (node == nullptr) {
		node = addNode(str);
	}
	else {
		if (node->data > str) addStr(node->left, str);
		else if (node->data < str) addStr(node->right, str);
		else return;
	}
}

bool isLeaf(Node* node) {
	return (node->left == nullptr) && (node->right == nullptr);
}

string findReplaceData(Node*& root) {
	Node* node = root;
	string data;
	if (node->left != nullptr) {
		if (node->left->right == nullptr) {
			data = node->left->data;
			node->left = node->left->left;
		}
		else {
			node = node->left;
			while (node->right->right != nullptr) node = node->right;
			data = node->right->data;
			node->right = node->right->left;
		}
	}
	else {
		if (node->right->left == nullptr) {
			data = node->right->data;
			node->right = node->right->right;
		}
		else {
			node = node->right;
			while (node->left->left != nullptr) node = node->left;
			data = node->left->data;
			node->left = node->left->right;
		}
	}
	return data;
}

void delStr(Node*& node, string str) {
	if (node == nullptr) return;
	else if (node->data == str) {
		if (isLeaf(node)) {
			node = nullptr;
			return;
		}
		string replaceStr = findReplaceData(node);
		node->data = replaceStr; //!!
	}
	else {
		delStr(node->left, str);
		delStr(node->right, str);
	}
}

void printDepth(Node* node, int depth, int i) {
	if (node == nullptr) return;
	else {
		if (depth == i) printVec.push_back(node->data);
		printDepth(node->left, depth, i + 1);
		printDepth(node->right, depth, i + 1);
	}
}

void printLeaf(Node* node) {
	if (node == nullptr) return;
	else {
		if (isLeaf(node)) printVec.push_back(node->data);
		printLeaf(node->left);
		printLeaf(node->right);
	}
}

void printData() {
	sort(printVec.begin(), printVec.end());
	for (auto str : printVec) cout << str << " ";
	cout << endl;
	printVec.clear();
}

int main() {
	Node* root = nullptr;

	string cmd, str;
	int depth, i = 1;
	int cmdIdx;
	bool isQuit = false;
	while (!isQuit) {
		cin >> cmd;
		cmdIdx = myCmd(cmd);
		switch (cmdIdx) {
		case ADD:
			cin >> str;
			addStr(root, str);
			break;
		case DELETE:
			cin >> str;
			delStr(root, str);
			break;
		case DEPTH:
			cin >> depth;
			printDepth(root, depth, i);
			if (printVec.empty()) cout << "NO" << endl;
			else printData();
			break;
		case LEAF:
			printLeaf(root);
			printData();
			break;
		case QUIT:
			isQuit = true;
			break;
		default:
			break;
		}
	}
}