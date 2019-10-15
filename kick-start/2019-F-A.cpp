#include<bits/stdc++.h>
#define ms(x,v) memset((x),v,sizeof(x))
#define INF 0x3f3f3f3f
using namespace std;
 
const int MAXN = 100+10;
typedef long long LL;



void solve(){
    int N,K;
    cin >> N >> K;
    
    vector<vector<int> > dp(N,vector<int>(K+1,INF));
    vector<vector<int> > num(N,vector<int>(N,0));
    vector<int> h(N);
    for(int i=0 ; i<N ; ++i)cin >> h[i];

    for(int i=0 ; i<N ; ++i){
        unordered_map<int,int> cnt;
        int max_value = -1;
        for(int j=i ; j<N ; ++j)
        {
            cnt[h[j]]++;
            if(cnt[max_value] < cnt[h[j]])
                max_value = h[j];
            num[i][j] = j -i +1 - (cnt[max_value]);
        } 
    }

    for(int i=0; i<N ; ++i)
    {
        dp[i][0] = num[0][i];
        for(int k=1 ; k<=K ; ++k){
            if(k >=i)
                dp[i][k] =0;      
            for(int j=1 ; j<=i ; ++j)
                dp[i][k] = min(dp[i][k], dp[j-1][k-1]+num[j][i]);
        }
    }
    cout << dp[N-1][K] << "\n";
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
