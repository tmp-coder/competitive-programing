#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset(x,(v), sizeof(x))
#define msn(x,v,n) memset(x,(v),sizeof(x[0]) * n)

#define INF 0x3f3f3f3f

typedef long long LL;

const int MAXN = 100 + 3;

int T;
int n;

struct Node{
    LL s,l,e;
};

Node stone[MAXN];

inline bool cmp(const Node& a,const Node& b){
    auto va = a.e + b.e - b.l * a.s;
    auto vb = a.e + b.e - a.l * b.s;
    return va > vb;
}

LL dp[MAXN*MAXN];


int main(int argc, char const *argv[])
{   
    ios :: sync_with_stdio(0);
    cin.tie(0);
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    
    cin >> T;

    for(int t =1;  t <= T ; ++t)
    {
        cin >> n ;
        for(int i=0 ; i< n ; ++i)
            cin >>stone[i].s >> stone[i].e >> stone[i].l;
        
        sort(stone,stone+n,cmp);
        ms(dp,0);

        int sum_time =0;
        for(int i=0 ; i<n ; ++i){
            sum_time += stone[i].s;
            for(LL time = sum_time ; time>=stone[i].s ; --time){
                auto value = stone[i].e - stone[i].l * (time - stone[i].s);
                if(value <=0)continue;
                dp[time] = max(dp[time],dp[time-stone[i].s] + value);
            }
        }
        cout << "Case #"<<t << ": " << *max_element(dp,dp+sum_time+1) << "\n";
    }

    return 0;
}
