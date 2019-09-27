#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 2e5+10;
typedef long long LL;
void solve(){
    int n;
    cin >> n;

    vector<LL> num(n,0);
    for(int i=0; i<n ; ++i)
    {
        cin >> num[i];
    }
    sort(num.begin(),num.end());
    LL ans =0;
    LL zeros =0;
    for(int i=0 ; i<n ; ++i){
        if(!num[i])
        {
            zeros++;
            continue;
        }
        for(int j=i+1 ; j<n;++j){
            LL k = num[i] * num[j];
            ans+= upper_bound(num.begin()+j+1,num.end(),k) - lower_bound(num.begin()+j+1,num.end(),k);
            
        }
    }
    ans += (zeros -1) * zeros /2 * (n - zeros);
    ans += (zeros -1) * zeros * (zeros -2)/6;
    cout << ans << '\n';
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
