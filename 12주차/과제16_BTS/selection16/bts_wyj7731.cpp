#include <bits/stdc++.h>
using namespace std;
struct node {
    string data;
    node *left, *right;
};
struct bst {
    node* root = 0;
    node* find(string val){return find_im(root, val);}
    void insert(string val){
        if(!root) root=new node{val,0,0};
        else insert_im(root,val);
    }
    void del(string val){root=del_im(root,val);}
    void depth(int dep){
        depth_im(root,dep);
    }
    void leaf(){
        leaf_im(root);
    }
private:
    node* find_im(node* rt,string val){
        if(!rt) return 0;
        if(val==rt->data)return rt;
        if(val<rt->data)return find_im(rt->left, val);
        if(val>rt->data)return find_im(rt->right, val);
    }
    void insert_im(node* rt,string val){
        if(!find(val)){
            if(val<rt->data){
                if(!rt->left) rt->left=new node{val, 0, 0};
                else insert_im(rt->left, val);
            }else{
                if(!rt->right) rt->right=new node{val, 0, 0};
                else insert_im(rt->right, val);
            }
        }
    }
    node* successor(node* start){
        node* cur=start->right;
        while(cur&&cur->left) cur=cur->left;
        return cur;
    }
    node* predecessor(node* start) {
        node* cur=start->left;
        while(cur&&cur->right) cur=cur->right;
        return cur;
    }
    node* del_im(node* start,string val) {
        if(!start)return 0;
        if(val<start->data){
            start->left=del_im(start->left,val);
        }else if(val>start->data){
            start->right=del_im(start->right,val);
        }else{
            if(!start->left&&!start->right){
                delete(start);
                return 0;
            }
            if(start->left){
                auto pre=predecessor(start);
                start->data=pre->data;
                start->left=del_im(start->left, pre->data);
            }else{
                auto suc=successor(start);
                start->data=suc->data;
                start->right=del_im(start->right, suc->data);
            }
        }
        return start;
    }
    void depth_im(node* rt,int dep) {
        if(!rt) {cout<<"NO"<<"\n"; return;}
        set<string> depth; int d=1;
        queue<node*> q; q.push(rt);
        while(!q.empty()){
            int size=q.size();
            for(int i=0; i<size; i++){
                auto cur=q.front();
                if(d==dep)depth.insert(cur->data);
                q.pop();
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            d++;
        }
        if(depth.empty()) cout<<"NO"<<"\n";
        else{
            for_each(begin(depth),end(depth),[](string s){ cout<<s<<" "; }); cout<<"\n";
        }
    }
    void leaf_im(node* rt){
        if(!rt)return;
        set<string> leaf;
        queue<node*> q; q.push(rt);
        while(!q.empty()){
            auto cur=q.front();
            q.pop();
            if(!cur->left&&!cur->right) leaf.insert(cur->data);
            if(cur->left) q.push(cur->left);
            if(cur->right) q.push(cur->right);
        }
        if(leaf.empty())return;
        for_each(begin(leaf),end(leaf),[](string s){cout<<s<<" ";});
        cout<<"\n";
    }
};
int getTok(string s){
    vector<string> cmd = {"+","-","depth","leaf","quit"};
    return find(cmd.begin(),cmd.end(),s)-cmd.begin();
}
int main(void){
    bst tree; int tok, k; string in;
    while(true){
        cin>>in;
        tok=getTok(in);
        if(tok==4)break;
        switch(tok){
            case 0: cin>>in; tree.insert(in); break;
            case 1: cin>>in; tree.del(in);    break;
            case 2: cin>>k;  tree.depth(k);   break;
            case 3: tree.leaf(); break;
            default: break;
        }
    }
    return 0;
}