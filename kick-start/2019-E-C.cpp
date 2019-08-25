#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset(x,(v), sizeof(x))
#define msn(x,v,n) memset(x,(v),sizeof(x[0]) * n)
#define INF 0x3f3f3f3f
#define random(a,b) (rand() % ((b) -(a)) +(a))

typedef long long LL;
typedef pair<int,int> PII;

const int MAXN = 1e6+10;

namespace Prime{
    LL power_mod(LL x,LL n,LL mod){
        LL ret =1;
        while(n){
            if(n & 1) ret = x * ret % mod;
            x = x * x % mod;
            n >>=1;
        }
        return ret;
    }
    LL mulmod(LL x,LL y,LL n){
        return x * y % n;
    }
    bool witness(LL a,LL n,LL u,LL t){
        LL x0 = power_mod(a,u,n),x1;
        for(int i=1 ;i<=t ; ++i){
            x1 = mulmod(x0,x0,n);
            if(x1==1 && x0!=1 && x0!=n-1)
                return false;
            x0 = x1;
        }
        if(x1 !=1)return false;
        return true;
    }

    bool miller_rabin(LL n, int times = 20){
        if(n<2)return false;
        if(n==2)return true;
        if(!(n&1))return false;
        LL u = n-1,t =0;
        while (u%2==0) {
            t++;u>>=1;
        }
        while (times--) {
            LL a = random(1,n-1);
            //if(a == 0)std::cout << a << " "<<n<< " "<<u<<" " << t<<'\n';
            if(!witness(a,n,u,t))return false;
        }
        return true;
    }
};

int start;
inline bool check_prime(int x){
    return x == 1 || Prime::miller_rabin(x);
}

int check(int x){
    int cnt =0;
    while(x %2 ==0){
        x /=2;
        cnt ++;
        if(cnt >=4)break;
    }
    if(cnt ==4)return 0;
    else if(cnt ==3) return x ==1;
    else if(cnt ==2) return check_prime(x);
    else if(cnt == 1)return 1;
    else return check_prime(x);
    
}
void solve(){
    LL l, r;
    cin >> l >> r;
    int ans =0;

    for(int i = l ; i<=r ; ++i){
        ans += check(i);
    }
    cout << " " << ans;
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
