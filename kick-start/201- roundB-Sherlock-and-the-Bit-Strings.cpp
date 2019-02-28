#include<bits/stdc++.h>

using namespace std;

#define popcnt(x) __builtin_popcount(x)
#define ms(x,v) memset((x),(v), sizeof(x))
typedef long long LL;
typedef unsigned int ui;
LL dp[1<<16][105];
LL p;
int n,k;
vector<pair<int,int> > R[105];

int ans[105];
bool ok(ui mask,int i,const vector<pair<int,int> >& r){
    for(auto e : r){
        int l =  i - e.first +1;
        int cnt = popcnt(mask) - popcnt(((ui(-1)) <<l) & mask);
        // cout << cnt <<"\n";
        // cout << bitset<16>(mask) <<" :" << l << ":cnt =  "<< cnt<<"\n";
        if(cnt != e.second)
            return false;
    }
    return true;
}

LL solve(ui mask,int i){
    if(dp[mask][i]!=-1)
        return dp[mask][i];
    if(!ok(mask,i,R[i])){
        return dp[mask][i]=0;
    }
    if(i==n)
        return dp[mask][i]=1;
    ui next_mask = (mask<<1) & 0xffff;
    LL ret = solve(next_mask,i+1);
    if(ret <p)
        ret += solve((next_mask|1),i+1);
    
    if(ret >p)ret =p;
    return dp[mask][i] = ret;
}


int main() {
    int T = 0;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cin >> n>> k >>p;
        // cout << n << " " << k << " " << p << "\n"; 
        ms(dp,-1);
        for(int i=1 ; i<=n ; ++i)
            R[i].clear();
        for(int i =0 ; i<k ; ++i){
            int l,r,c;
            cin >> l>> r>> c;
            R[r].push_back(make_pair(l,c));
        }
        solve(0,0);
        ui mask =0;
        for(int i=1 ; i<=n ; ++i){
            mask = (mask<<1) & 0xffff;
            if(dp[mask][i]>=p){
                ans[i] =0;
                
            }
            else{
                p-=dp[mask][i];
                mask |=1;
                ans[i]=1;
                
            }
            
        }

        cout << "Case #" << t << ": " ;
        // cout << "n = "<<n;
        for(int i=1 ; i<=n ; ++i)cout << ans[i];
        cout << "\n";
     }
}
