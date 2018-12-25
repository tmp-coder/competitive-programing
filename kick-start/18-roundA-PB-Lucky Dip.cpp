#include<bits/stdc++.h>

using namespace std;

const int MAXN = 2e4+6;

typedef long long LL;

int a[MAXN];
LL sum[MAXN];
int main(int argc, const char * argv[]) {

    ios :: sync_with_stdio(0);
    cin.tie(0);
    std::cout.precision(8);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield );
    int T;
    cin >> T;
    int n,k;
    for(int _ =1 ; _ <= T ; ++_){
        cout <<"Case #"<<_<<": ";
        cin>>n>>k;
        for(int i=1 ; i<=n ; ++i)cin >> a[i];
        sort(a+1,a+n+1);
        sum[0] =0;
        for(int i=1 ; i<=n ; ++i)sum[i] = sum[i-1] + a[i];
        double ans = sum[n]/(double)n;
        for(int j =1 ; j <=k; ++j){
            int pos = upper_bound(a+1,a+n+1,(int)ans) - a;
            pos--;
            ans = (sum[n]-sum[pos] + pos * ans)/n;
        }
        cout << ans <<"\n";
    }
    

    return 0;
}