#include<bits/stdc++.h>

using namespace std;



void solve(){
    int N,K,P;
    cin >> N >> K >> P;
    vector<vector<pair<int,int>>> a(N,vector<pair<int,int>>());

    for(int i=0 ; i<N ; ++i)
    {
        int val;
        cin >> val;
        a[i].push_back(make_pair(1, val));
        for(int j=1 ; j< K ; ++j){
            int x;
            cin >> x;
            val += x;
            a[i].push_back(make_pair(j+1,val));
        }
    }

    // vector<vector<int>> dp(P,vector<int>(a.size(),0));

    // for(int i=0)
    vector<int> dp(P+1,0);

    for(int i=0 ; i< N ; ++i)
        for(int v = P ;v >=0 ; --v){
            for(const auto& e : a[i])
                if(v >= e.first)
                    dp[v] = max(dp[v], dp[v - e.first] + e.second);
        }
    cout << dp[P] << "\n";
}

int main(){
    int T;
    cin >> T;

    for(int t =1 ; t <= T ; ++ t){
        cout << "Case #"<<t<<": ";

        solve();
    }
    return 0;
}
