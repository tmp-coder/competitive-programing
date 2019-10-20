#include<bits/stdc++.h>
#define ms(x,v) memset((x),v,sizeof(x))
#define INF 0x3f3f3f3f
using namespace std;
 
const int MAXN = 100+10;
typedef long long LL;

LL N,H;

pair<LL,LL> val[MAXN];
LL sa[MAXN],sb[MAXN];
LL ans;
LL pow3[MAXN];
void dfs(LL v1,LL v2,int idx){//0,...,N-1
    
    if(v1 >= H && v2 >=H){
        ans += pow3[N-idx];
        return;
    }
    if(idx >= N)return;
    if(v1 + sa[N-idx] < H || v2 + sb[N-idx] < H)return;
    dfs(v1 + val[idx].first,v2,idx+1);
    dfs(v1,v2+val[idx].second,idx+1);
    dfs(v1+val[idx].first,v2 + val[idx].second,idx+1);
}


void solve(){
    cin >> N >> H;
    for(int i=0 ; i<N ; ++i)cin >> val[i].first;
    for(int i=0 ; i<N ; ++i)cin >> val[i].second;
    sort(val,val+N,greater<pair<LL,LL> >());
    sa[0] =0;
    sb[0] = 0;
    for(int i = N-1 ; i>=0 ; --i){
        sa[N-i] = sa[N-i -1] + val[i].first;
        sb[N-i] = sb[N-i - 1] + val[i].second;
    }
    ans =0;
    dfs(0,0,0);
    cout << ans << "\n";
}





int main(){
    ios :: sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0);
    std::cout.precision(10);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    pow3[0] =1;
    for(int i=1 ; i<=20;++i)pow3[i] = pow3[i-1] * 3;
    int T;
    cin >> T;
    for(int tt =1 ; tt <=T ; ++tt)
    {
        cout << "Case #" << tt << ": ";
        solve();
    }
    
 
    return 0;
}
