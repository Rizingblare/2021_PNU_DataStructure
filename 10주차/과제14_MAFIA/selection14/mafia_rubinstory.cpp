#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, string> Data;
class Node {
private:
    string name;
    Node * parent = nullptr;
    vector<Node *> *childList = new vector<Node *>();
public:
    Node(string name) {
        this->name = name;
    }
    string getName() { return name; }
    void setParent(Node * node) { parent = node; }
    Node * getParent() { return parent; }
    vector<Node *> * getChildList() { return childList; }
};

class Tree {
private:
    int nodeCount = 0;
    Node * head = nullptr;
    vector<Node *> nodeList;
    map<string, int> nodeId;
public:
    void addNode(string parent, string child) {
        Node * pNode;
        Node * cNode;
        if (nodeId.find(parent) == nodeId.end()) {
            nodeId.insert({parent, nodeCount++});
            pNode = new Node(parent);
            nodeList.push_back(pNode);
        }
        else {
            pNode = nodeList[nodeId.find(parent)->second];
        }
        
        if (nodeId.find(child) == nodeId.end()) {
            nodeId.insert({child, nodeCount++});
            cNode = new Node(child);
            nodeList.push_back(cNode);
        }
        else {
            cNode = nodeList[nodeId.find(child)->second];
        }
        pNode->getChildList()->push_back(cNode);
        cNode->setParent(pNode);
        if (head == nullptr) head = pNode;
        if (cNode == head) head = pNode;
    }
    void calibrateHead() {
        Node * node = head;
        while(node->getParent()) node = node->getParent();
        head = node;
    }
    Node * getHead() { return head; }
};

struct cmp {
    bool operator() (Data n1, Data n2) {
        if (get<0>(n1) < get<0>(n2)) return true;
        else if (get<0>(n1) > get<0>(n2)) return false;
        
        if (get<1>(n1) < get<1>(n2)) return true;
        else if (get<1>(n1) > get<1>(n2)) return false;
        return get<2>(n1).compare(get<2>(n2)) > 0;
    }
};

int N;
string PARENT, CHILD;
priority_queue<Data, vector<Data>, cmp> pq;
int dfs(Node * node, int level, int childCnt) {
    int currChildCnt = 0;
    for (auto c: *node->getChildList()) {
        currChildCnt += dfs(c, level - 1, 0);
    }
    pq.push({currChildCnt, level, node->getName()});
    return childCnt + currChildCnt + 1;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    Tree t;
    for(int i = 0; i < N - 1; i++) {
        cin >> CHILD >> PARENT;
        t.addNode(PARENT, CHILD);
    }
    t.calibrateHead();
    dfs(t.getHead(), N - 1, 0);
    while(!pq.empty()) {
        string name = get<2>(pq.top());
        cout << name << "
";
        pq.pop();
    }
    return 0;
}