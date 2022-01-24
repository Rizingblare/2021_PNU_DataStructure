#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Node{
private:
    Node* parent_node = NULL;
    string parent_value;
    string value;
    vector<Node*> child_nodes;
    int child_number = 0;
    int descendant_number = -1;
public:
    Node(string _value, string _parent_value):value(_value), parent_value(_parent_value){}
    Node* get_parent_node(){
        return parent_node;
    }
    void set_parent_node(Node* _parent_node){
        parent_node = _parent_node;
    }
    string get_parent_value(){
        return parent_value;
    }
    string get_value(){
        return value;
    }
    void add_child(Node* new_child){
        if(new_child==NULL) {return;}
        child_nodes.push_back(new_child);
        child_number++;
    }
    void calc_descendant_number(){
        descendant_number = child_number;
        for(auto child : child_nodes){
            child->calc_descendant_number();
            descendant_number += child->get_descendant_number();
        }
    }
    int get_descendant_number(){
        return descendant_number;
    }
};

void get_input(vector<Node*>& nodes){
    int number;
    string name, parent_name;
    cin >> number;
    for(int i=1; i<number; i++){
        cin >> name >> parent_name;
        nodes.push_back(new Node(name, parent_name));
    }
}
Node* connect_nodes(vector<Node*>& nodes){
    string root_name;
    vector<Node*> semi_roots;
    for(auto node_1 : nodes){
        for(auto node_2 : nodes){
            if(node_1->get_parent_value() == node_2->get_value()){
                node_1->set_parent_node(node_2);
                node_2->add_child(node_1);
            }
        }
        if(node_1->get_parent_node() == NULL){
            root_name = node_1->get_parent_value();
            semi_roots.push_back(node_1);
        }
    }
    Node* root = new Node(root_name,"");
    for(auto node : semi_roots){
		node->set_parent_node(root);
		root->add_child(node);
		}
    nodes.push_back(root);
    return root;
}
int calc_depth(Node* node){
    int depth = -1;
    while(node != NULL){
        node = node->get_parent_node();
        depth++;
    }
    return depth;
}
bool cmp(Node* node_1, Node* node_2){
    if(node_1->get_descendant_number() != node_2->get_descendant_number()){return node_1->get_descendant_number() > node_2->get_descendant_number();}
    int depth_1 = calc_depth(node_1);
    int depth_2 = calc_depth(node_2);
    if(depth_1 != depth_2){return depth_1 < depth_2;}
    return node_1->get_value() < node_2->get_value();
}
void print_result(vector<Node*>& nodes){
	for(auto node : nodes){
		cout << node->get_value() <<endl;
	}
}

int main(void){
    vector<Node*> nodes;
    get_input(nodes);
    Node* root = connect_nodes(nodes);
    root->calc_descendant_number();
    sort(nodes.begin(), nodes.end(), cmp);
    print_result(nodes);
}