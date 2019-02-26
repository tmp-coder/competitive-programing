#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

LL dp[20][10][2];


LL calc(int pos,int sum,bool less, const string & num){
    if(pos ==num.size())
        return sum !=0;
    if(dp[pos][sum][less] != -1)
        return dp[pos][sum][less];
    
    int lmt = less ? num[pos] -'0':8;
    if(lmt ==9)lmt =8;
    LL ret =0;
    for(int i=0 ; i<=lmt ; ++i){
        ret += calc(pos +1,(sum +i) % 9, less && i==lmt ,num);
    }
    return dp[pos][sum][less] = ret;
}

LL solve(LL n){
    memset(dp,-1,sizeof(dp));
    string s = to_string(n);
    return calc(0,0,1,s);
}

int main(){
    int T;
    cin >> T;
    for(int t=1 ; t <= T; ++t){
        LL n,m;
        cin >> n >> m;
        // cout << "solve(n-1) = " <<solve(n-1) << "\n";
        // cout << "solve(m) = " <<solve(m) << "\n";
        LL ans = solve(m) - solve(n-1);
        cout << "Case #"<<t <<": "<< ans << '\n';
    }
}
