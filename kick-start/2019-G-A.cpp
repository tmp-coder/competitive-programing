#include<bits/stdc++.h>
#define ms(x,v) memset((x),v,sizeof(x))
#define INF 0x3f3f3f3f
using namespace std;
 
const int MAXN = 100+10;
typedef long long LL;


void solve(){
    int N,M,Q;
    cin >> N >> M >> Q;
    vector<bool> pg(N+1,true);
    for(int i=0 ; i<M ; ++i){
        int x;cin >> x;
        pg[x] = false;
    }
    vector<int> cnt(N+1,0);
    for(int i=0 ; i<Q; ++i)
    {
        int x;
        cin >> x;
        cnt[x] ++;
    }
    LL ans =0;
    for(int i=1 ; i<=N ; ++i){
        if(cnt[i]){
            LL v = 0;
            for(int j=i ; j<=N; j += i){
                v += pg[j];
            }
            ans += v * cnt[i];
        }
    }
    cout << ans << '\n';
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
