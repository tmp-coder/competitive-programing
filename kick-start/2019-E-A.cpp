#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset(x,(v), sizeof(x))
#define msn(x,v,n) memset(x,(v),sizeof(x[0]) * n)
#define INF 0x3f3f3f3f

typedef long long LL;
typedef pair<int,int> PII;

const int MAXN = 1e5+10;

int par[MAXN];

int FIND(int x){
    return x == par[x] ? x : par[x] = FIND(par[x]);
}
void UNOIN(int x,int y){
    x = FIND(x);
    y = FIND(y);
    if(x !=y)
        par[x] = par[y];
}
void solve(){
    int n,m;
    cin >> n >> m;
    for(int i=1 ; i <=n ; ++i)
        par[i] = i;
    for(int i=0 ; i<m ; ++i){
        int x,y;
        cin >>x >> y;
        UNOIN(x,y);
    }
    vector<vector<int> > G(n+1);
    for(int i=1 ; i<=n ; ++i)
        G[FIND(i)].push_back(i);
    
    int k=0;
    int ans =0;
    for(int i=1 ; i<=n ; ++i){
        if(!G[i].empty()){
            ans += G[i].size() -1;
            k+=1;
        }
    }
    ans += 2 * (k-1);
    cout << " " << ans ;
}

int main(int argc, char const *argv[])
{   
    
    ios :: sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0);
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    int T;
    cin >> T;
    
    for(int kase =1;  kase <= T ; ++kase)
    {   
        cout << "Case #"<<kase << ":";

        solve();
        cout << '\n';
    }

    return 0;
}
