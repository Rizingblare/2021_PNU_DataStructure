#include<bits/stdc++.h>
using namespace std;

int N;
struct Node {
    string name;
    int childSize = 0;
    int depth = -1;
    vector<string> children;
    Node() {};
    Node(string name) : name(name) {};
};
map<string, Node> tree;

int countChildren(string name) {
    Node info = tree.at(name);
    if(info.childSize) return info.childSize;
    int cnt = 0;
    for(auto &child : info.children) {
        Node node = tree[child];
        if(node.children.empty()) cnt++;
        else cnt += countChildren(child) + 1;
    }
    return cnt;
}
string findRoot() {
    int maxSize = 0; 
    string rootNodeName;
    for(auto &node : tree) 
        if(maxSize < node.second.childSize) {
            maxSize = node.second.childSize;
            rootNodeName = node.first;
        }
    return rootNodeName;
}
void measureDepth(string boss, int depth) {
    for(auto &child : tree[boss].children) {
        tree[child].depth = depth+1;
        if(tree[child].childSize) measureDepth(tree[child].name, depth+1);
    }
}

int main() {
    string person, boss;
    cin >> N;

    while(--N) {
        cin >> person >> boss;
        if(tree.find(boss)   == tree.end()) tree.insert({boss,   Node{boss}});
        if(tree.find(person) == tree.end()) tree.insert({person, Node{person}});
        tree[boss].children.push_back(person);
    }

    for(auto &node : tree) node.second.childSize = countChildren(node.first);
    measureDepth(findRoot(), 0);

    vector<Node> nodes;
    for(auto &pos : tree) nodes.push_back(pos.second);

    sort(nodes.begin(), nodes.end(), [](Node &a, Node &b) {
        if(a.childSize != b.childSize) return a.childSize > b.childSize;
        if(a.depth != b.depth) return a.depth < b.depth;
        return a.name < b.name;
    });

    for(auto &node : nodes) cout << node.name << '
';
}