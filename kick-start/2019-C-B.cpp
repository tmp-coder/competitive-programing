#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset(x,(v), sizeof(x))
#define msn(x,v,n) memset(x,(v),sizeof(x[0]) * n)
#define INF 0x3f3f3f3f

typedef long long LL;
typedef pair<int,int> PII;

const int MAXN = 300 + 3;


struct RMQ{
    int minA[10][MAXN],maxA[10][MAXN];
    void init(const int * a,int n){
        for(int i=0 ; i<n ; ++i){
            minA[0][i] = maxA[0][i] = a[i];
        }
        for(int j=1 ; (1<<j)<=n ; ++j)
            for(int i=0 ; i+(1<<(j-1)) <n ; ++i){
                minA[j][i] = min(minA[j-1][i],minA[j-1][i+(1<<(j-1))]);
                maxA[j][i] = max(maxA[j-1][i],maxA[j-1][i+(1<<(j-1))]);
            }
    }

    pair<int,int> query_min_max(int l,int r){
        if(l>r)return PII(0,0);
        int k=0;
        while((1<<(k+1)) <= r-l+1) ++k;
        return make_pair(min(minA[k][l],minA[k][r-(1<<k)+1]),max(maxA[k][l],maxA[k][r-(1<<k)+1]));
    }

};

RMQ rmq[MAXN];
int rr,cc,kk;
int aux[MAXN];

int solve(){
    int ans =0;
    for(int l = 0 ; l < cc ; ++l)
        for(int r = l ; r < cc ; ++r){
            int len = 0;
            int cur_len = 0;
            for(int row = 0; row < rr ;  ++row){
                auto minmax = rmq[row].query_min_max(l,r);
                if( minmax.second - minmax.first <=kk){
                    cur_len ++;
                    if(len < cur_len)len = cur_len;
                }else cur_len = 0;
            }
            ans = max(ans , len * (r -l+1));
        }
    return ans;
}

int main(int argc, char const *argv[])
{   
    ios :: sync_with_stdio(0);
    cin.tie(0);
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    int T;
    cin >> T;

    for(int t =1;  t <= T ; ++t)
    {   
        cin >> rr >> cc >> kk;
        for(int i=0 ; i< rr ; ++i){
            for(int j=0 ; j< cc ; ++j)
                cin >> aux[j];
            rmq[i].init(aux,cc);
        }
        cout << "Case #"<<t << ": " << solve() << "\n";
    }

    return 0;
}
