#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<tuple>
using namespace std;
typedef tuple<int,char> comp_tuple;
typedef struct Queue_data{
    char v_name;
    int distance;
}Q_data;

struct each_friend_v_compare{
    bool operator()(Q_data &a,Q_data &b){ 
        return(a.v_name>b.v_name);
    }
};
struct best_compare{
    bool operator()(Q_data &a,Q_data &b){
        comp_tuple X,Y;
        X = make_tuple(a.distance,a.v_name);
        Y = make_tuple(b.distance,b.v_name);
        return X>Y;
    }
};
int N;
char each_sp[3];
vector<char> Vertexes;
vector<bool> Vertex_enable;
vector<vector<char>> Adj_s;

class my_graph{
private:
    priority_queue<Q_data,vector<Q_data>,best_compare>Q_for_best;
    priority_queue<Q_data,vector<Q_data>,each_friend_v_compare>f1;
    priority_queue<Q_data,vector<Q_data>,each_friend_v_compare>f2;
    priority_queue<Q_data,vector<Q_data>,each_friend_v_compare>f3;
public:
    void add_edge();
    void BFS(char sp,priority_queue<Q_data,vector<Q_data>,each_friend_v_compare> &a);
    void get_min_common();
};

int main(){
    my_graph graph_for_meeting;
    graph_for_meeting.add_edge();
    graph_for_meeting.get_min_common();
    return 0;
}

void my_graph::add_edge(){
    char name_tmp;
    vector<char>*adj_tmp;

    cin>>N;
    for(int i=0;i<3;i++){
        cin >> name_tmp;
        each_sp[i] = name_tmp;
    }
    for(int i=0;i<N;i++){
        cin>> name_tmp;
        Vertexes.push_back(name_tmp);
        Vertex_enable.push_back(true);
        adj_tmp=new vector<char>();
        while(1){
            cin>>name_tmp;
            if(name_tmp=='$'){break;}
            adj_tmp->push_back(name_tmp);
        }
        Adj_s.push_back(*adj_tmp);
    }
}
void my_graph::BFS(char sp,priority_queue<Q_data,vector<Q_data>,each_friend_v_compare> &a){
    Q_data tmp, adj_tmp;
    queue<Q_data> BFS_queue;
    char adj_v;
    int sp_index = find(Vertexes.begin(),Vertexes.end(),sp)-Vertexes.begin();
    int now_data_index, adj_v_index;
    Vertex_enable.at(sp_index) = false;
    tmp.v_name = sp;
    tmp.distance = 0;
    BFS_queue.push(tmp);
    while(!BFS_queue.empty()){
        tmp = BFS_queue.front();
        BFS_queue.pop();
        a.push(tmp);
        now_data_index = find(Vertexes.begin(),Vertexes.end(),tmp.v_name)-Vertexes.begin();
        for(int i=0;i< Adj_s.at(now_data_index).size();i++){
            adj_v = Adj_s.at(now_data_index).at(i);
            adj_v_index = find(Vertexes.begin(),Vertexes.end(),adj_v)-Vertexes.begin();
            if(Vertex_enable.at(adj_v_index)){
                adj_tmp.distance = tmp.distance+1;
                adj_tmp.v_name = adj_v;
                BFS_queue.push(adj_tmp);
                Vertex_enable.at(adj_v_index)=false;
            }
        }
    }
    for(auto w:Vertex_enable) w=true;
}

void my_graph::get_min_common(){
    BFS(each_sp[0],f1);
    BFS(each_sp[1],f2);
    BFS(each_sp[2],f3);

    char max;
    
    while(1){
        if(f1.empty()||f2.empty()||f3.empty()) break;

        if(f1.top().v_name == f2.top().v_name && f2.top().v_name == f3.top().v_name){
            Q_data common_v;
            int max_distance = f1.top().distance;
            if(max_distance<f2.top().distance) max_distance = f2.top().distance;
            if(max_distance<f3.top().distance) max_distance = f3.top().distance;
            common_v.distance = max_distance;
            common_v.v_name = f1.top().v_name;
            Q_for_best.push(common_v);
            f1.pop();
            f2.pop();
            f3.pop();
        }

        else{
            max = f1.top().v_name; 
            if(max<f1.top().v_name) max = f1.top().v_name;
            if(max<f2.top().v_name) max = f2.top().v_name;
            if(max<f3.top().v_name) max = f3.top().v_name;

            if(f1.top().v_name<max) f1.pop();
            if(f2.top().v_name<max) f2.pop();
            if(f3.top().v_name<max) f3.pop();
        }
    }

    if(Q_for_best.empty()){cout<< '@' <<endl; cout<< -1; }
    else{
        cout<<Q_for_best.top().v_name<<endl;
        cout<< 2 * ((Q_for_best.top().distance)-1) + Q_for_best.top().distance;
    }
}