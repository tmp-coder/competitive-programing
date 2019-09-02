#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset(x,(v), sizeof(x))
#define msn(x,v,n) memset(x,(v),sizeof(x[0]) * n)
#define INF 0x3f3f3f3f
#define random(a,b) (rand() % ((b) -(a)) +(a))

typedef long long LL;
typedef pair<int,int> PII;

const double EPS = 2e-8;
const LL MOD = 1e9+7;
const int MAX_FAC = 1e5+10;
LL fac[MAX_FAC * 2];

void init(){
    fac[0] =1;
    for(int i=1 ; i < MAX_FAC * 2 ; ++i)
        fac[i] = fac[i-1] * i % MOD;
}

LL power_mod(LL x,LL n,LL mod){
    LL ret = 1;
    while (n)
    {
        if(n&1) ret = x * ret % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ret;
}

void solve(){
    int N,M;
    cin >> N >> M;

    LL ans =0;
    LL power2 = 1;
    for(int k=0;  k<=M; ++k){

        LL cur_ans = power2;
        power2 = power2 *2 % MOD;
        cur_ans = cur_ans * fac[M] % MOD * fac[2*N - k] % MOD;
        cur_ans = cur_ans * power_mod(fac[k] * fac[M-k]% MOD,MOD -2 ,MOD) % MOD;

        ans += k&1 ? MOD - cur_ans : cur_ans;
        ans %= MOD;
    }

    cout << " "<<ans;
}

int main(int argc, char const *argv[])
{   
    
    ios :: sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0);
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );

    init();


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
