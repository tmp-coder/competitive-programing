#include<bits/stdc++.h>

using namespace std;

#define ms(x,v) memset(x,(v), sizeof(x))
#define msn(x,v,n) memset(x,(v),sizeof(x[0]) * n)
#define INF 0x3f3f3f3f

typedef long long LL;
typedef pair<int,int> PII;

const int MAXN = 1000 + 3;



int n,K;
int main(int argc, char const *argv[])
{   
    cin.tie(0);
    ios :: sync_with_stdio(0);
    
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    int T;
    cin >> T;
    
    const int BASE = 1024;
    bool xorodd[BASE];
    for(int i=0 ; i<= BASE ; ++i){
        xorodd[i] = bitset<11>(i).count()&1;
    }
    for(int t =1;  t <= T ; ++t)
    {   
        cout << "Case #"<<t << ":";
        int n,q;
        cin >> n >> q;
        std::set<int> odd;
        for(int i=1 ; i<=n ; ++i){
            int x;
            cin >> x;
            if(xorodd[x])odd.insert(i);
        }
        while(q--){
            int idx,x;
            cin >> idx >> x;
            idx++;
            if(odd.count(idx))odd.erase(idx);
            if(xorodd[x])odd.insert(idx);
            if(odd.size()&1){
                int first = *odd.begin();
                int end = *(--odd.end());
                cout <<" "<< max(end -1, n - first);
            }else cout << " " << n;
        }
        cout << "\n";
    }

    return 0;
}
