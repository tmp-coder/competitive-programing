#include<bits/stdc++.h>

using namespace std;

struct Node{
    int son;
    int cnt;
    Node():son(-1),cnt(0){};
};


struct Trie{
    vector<vector<Node>> nodes;
    Trie(){
        nodes.push_back(vector<Node>(26));
    }
    int add_node(){
        nodes.push_back(vector<Node>(26));
        return nodes.size() -1;
    }
    void add_string(const string & str){
        int cur = 0;
        for(const auto  e : str){
            int idx = e - 'A';
            auto &node = nodes[cur][idx];
            if (node.son == -1){// add new node
                node.son = add_node();
            }
            node.cnt ++;
            cur = node.son;
        }
    }
    int size(){
        return nodes.size();
    }
};

pair<int,int> dfs(int u,int cnt, int dep,const Trie & trie,int K){
    int ans =0;
    int used = 0;
    for(const auto & e : trie.nodes[u]){
        if (e.son != -1 && e.cnt >=K){
            auto ret = dfs(e.son,e.cnt,dep +1, trie, K);
            ans += ret.first;
            used += ret.second;
        }
    }
    if ( cnt -used>=K){
        ans += (cnt - used)/K * dep;
        used += (cnt - used)/ K * K;
    }
    return make_pair(ans, used);
}

void solve(){
    int N,K;
    cin >> N >> K;
    Trie trie;
    for(int i=0 ; i< N ; ++i)
    {
        string s;
        cin >> s;
        trie.add_string(s);
    }
    auto ans = dfs(0,N,0,trie,K);
    cout << ans.first << "\n";
}

int main(){
    int T;
    cin >> T;

    for(int t =1 ; t <= T ; ++ t){
        cout << "Case #"<<t<<": ";

        solve();
    }
    return 0;
}
