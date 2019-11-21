#include<bits/stdc++.h>
#include<bits/extc++.h>
#define ms(x,v) memset((x),v,sizeof(x))
#define INF 0x3f3f3f3f
using namespace std;
// using namespace __gnu_pbds;

const int MAXN = 100+10;
typedef long long LL;


void solve(){
    vector<LL> A(9);
    for(int i=0 ; i<A.size() ; ++i)
    {
        cin >> A[i];
        if(A[i] > 20)
            A[i] = 20 + (A[i] & 1);
    }

    vector<vector<set<int>> > dp(10,vector<set<int>>(11));

    for(int i=0 ; i<A.size() ; ++i){
        for(int k = 0 ; k<=A[i]; ++k){
            int d = 2 * k * (i+1) % 11;
            for(int j=0 ; j<11 ; ++j){
                int v = (d +j) % 11;
                if(dp[i][j].empty())dp[i+1][d].insert(k);
                else {
                    for(const auto & e : dp[i][j]){
                        dp[i+1][v].insert((e + k));
                    }
                }
            }
        }
    }
    LL sum =0;
    LL x = 0;
    for(int i=0 ; i<A.size() ;++i){
        x = (x + A[i] * (i+1)) % 11;
        sum = (sum + A[i]);
    }
    if(dp[9][x].count((sum)/2) )
        cout << "YES\n";
    else cout << "NO\n";
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
