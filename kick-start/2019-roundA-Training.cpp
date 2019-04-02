#include<bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f


typedef long long LL;

const int MAXN = 1e5 +10;

LL s[MAXN];
LL sum[MAXN];

int main(){

    ios :: sync_with_stdio(0);
    cin.tie(0);
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    
    int T;
    cin >> T;

    for(int t =1 ; t <= T; ++t){
        
        int n,p;
        cin >> n>> p;
        for(int i=1 ; i<=n ; ++i)cin >> s[i];
        
        sort(s+1,s+n+1);
        
        sum[0] =0;
        for(int i=1 ; i<=n ; ++i)sum[i] = sum[i-1] + s[i];
        LL ans = INT64_MAX >> 1;
        for(int i=p ; i <=n ;++i){
            LL sc = sum[i] - sum[i-p];
            LL need =  s[i] * p - sc;

            if(ans > need) ans = need;
        }
        cout << "Case #"<<t<<": "<<ans << "\n";
    }
    

    return 0;
}
