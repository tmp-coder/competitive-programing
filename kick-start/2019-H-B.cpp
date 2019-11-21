#include<bits/stdc++.h>
#include<bits/extc++.h>
#define ms(x,v) memset((x),v,sizeof(x))
#define INF 0x3f3f3f3f
using namespace std;
// using namespace __gnu_pbds;

const int MAXN = 100+10;
typedef long long LL;
typedef pair<int,bool> PIB;



void dfs(int u,bool flip,int &cnt,vector<bool>& col,vector<bool>&vis,const vector<vector<PIB>> & G){
    if(vis[u]){
        if(col[u] != flip)
            cnt = INF;
        return;
    }   
    vis[u] = true;
    col[u] = flip;
    if(flip)cnt ++ ;
    for(const auto & e : G[u])
        dfs(e.first,flip ^ e.second,cnt,col,vis,G);
}

void solve(){
    int n;
    cin >> n;
    const int offset = 2 *n -2 + n;
    const int MAX_V = 4 *n - 2;
    vector<vector<PIB> > G(MAX_V);
    for(int i=0 ; i<n ; ++i){
        string s;
        cin >> s;
        for(int j=0 ; j<n ; ++j)
        {
            int x = i + j;
            int y = i-j + offset;
            bool v = (s[j] == '.');
            G[x].push_back(make_pair(y,v));
            // cout  << x << " " << y << " "<< v << "\n";
            G[y].push_back(make_pair(x,v));
        }
    }

    vector<bool> vis1(MAX_V,false),vis2(MAX_V,false),col(MAX_V,false);
    int ans =0;

    for(int i=0 ; i< MAX_V ; ++i){
        if(vis1[i])
            continue;
        int cnt1 = 0,cnt2 = 0;
        dfs(i,0,cnt1,col,vis1,G);
        dfs(i,1,cnt2,col,vis2,G);

        ans += min(cnt1,cnt2);
    }
    cout << ans << '\n';
}





int main(){
    ios :: sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    std::cout.precision(10);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    int T;
    cin >> T;
    // cout << T << '\n';
    for(int tt =1 ; tt <=T ; ++tt)
    {
        cout << "Case #" << tt << ": ";
        solve();
    }
    return 0;
}
