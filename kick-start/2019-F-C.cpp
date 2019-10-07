#include<bits/stdc++.h>
#define ms(x,v) memset((x),v,sizeof(x))
#define INF 0x3f3f3f3f
using namespace std;
 
const int MAXN = 2e5+10;
typedef long long LL;

unordered_map<int,LL> dp;

vector<int> G[MAXN];
int b[MAXN];

inline int encode(int pc,int vc){
    return (vc<<1) | (pc);
}

LL dfs(int u,int v,int s){
    if(dp.count((v<<2)|s))
        return dp[(v<<2)|s];
    
    int pc = s&1;
    int vc = (s>>1) & 1;
    LL ans =0;
    if(s>0){// color this node
        ans += b[v];
        for(auto e : G[v]){
            if(e == u)continue;
            ans += max(dfs(v,e,encode(vc,0)),dfs(v,e,encode(vc,1)));
        }
    }else{
        vector<vector<int> > ansdp(G[v].size(),vector<int>(2,0));
        int i =-1;
        for(auto e : G[v]){
            if(e == u)continue;
            if(i==-1){
                i=0;
                ansdp[0][0] = dfs(v,e,encode(vc,0));
                ansdp[0][1] = dfs(v,e,encode(vc,1));
            }else{
                assert(i>0);
                ansdp[i][0] = ansdp[i-1][0] + dfs(v,e,encode(vc,0));
                ansdp[i][1] = max(ansdp[i-1][1]+max(dfs(v,e,encode(vc,0)),dfs(v,e,encode(vc,1)))
                            ,ansdp[i-1][0]+dfs(v,e,encode(vc,1)));
            }
            i++;
        }
        if(i==-1)ans =0;
        else 
            ans = max(ansdp[i-1][0],ansdp[i-1][1]+b[v]);
    }
    dp[(v<<2)|s] = ans;
    return ans;
}

void solve(){
    int N;
    cin >> N;
    for(int i=0 ; i<N ; ++i)cin >> b[i];
    for(int i=1 ; i<N ; ++i){
        int x,y;
        cin >> x >> y;
        x--,y--;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    cout << max(dfs(-1,0,encode(0,0)),dfs(-1,0,encode(0,1))) << "\n";
    dp.clear();
    for(int i=0 ; i<N ; ++i)G[i].clear();
}




int main(){
    ios :: sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0);
    std::cout.precision(10);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
 
    int T;
    cin >> T;
    for(int tt =1 ; tt <=T ; ++tt)
    {
        cout << "Case #" << tt << ": ";
        solve();
    }
    
 
    return 0;
}
