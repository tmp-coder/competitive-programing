#include<bits/stdc++.h>
#define ms(x,v) memset((x),v,sizeof(x))
#define INF 0x3f3f3f3f
using namespace std;
 
const int MAXN = 100+10;
typedef long long LL;


void solve(){
    LL N,M;
    cin >> N >> M;
    LL ans =0;
    LL sum[64];
    ms(sum,0);
    const int MAX_BIT = 52;
    for(int i=0 ;i< N ; ++i){
        LL x;
        cin >> x;
        for(int j =0;j<MAX_BIT ; ++j)
            if((x >>j) & 1)sum[j] ++;
            
    }
    vector<LL> dp(MAX_BIT+1,0);
    dp[0] = 0;
    for(int i=0; i<MAX_BIT ; ++i){
        dp[i+1] = dp[i] + min(sum[i],N-sum[i]) * (1LL << i);
    }
    for(int j = MAX_BIT -1 ; j>=0 ; --j){
        LL val = (N-sum[j]) * (1LL << j);
        if(dp[j] <= M - val){
            ans |= (1LL << j);
            M-=val;
        }else{
            M-=sum[j] * (1LL << j);
        }
        if( M < dp[j]){
            ans = -1;
            break;
        }
    }
    cout << ans << "\n";
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
