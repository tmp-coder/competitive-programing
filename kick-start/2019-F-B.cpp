#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 2e5+10;
typedef long long LL;
void solve(){
    int N,S;
    cin >> N >> S;
    
    vector<int> skill[S];
    vector<int> ee[N];
    for(int i=0 ; i<N ; ++i){
        int c;
        cin >>c;
        for(int _=0 ; _ < c; ++_){
            int x;
            cin >>x;x--;
            ee[i].push_back(x);
            skill[x].push_back(i);
        }
    }
    LL ans =0;
    map<vector<int>,int> cnt;
    for(int i=0 ; i<N ; ++i){
        sort(ee[i].begin(),ee[i].end(),[&](const int a,const int b){return skill[a].size() < skill[b].size();});
        cnt[ee[i]]++;
    }
    for(const auto &e : cnt){
        vector<int> out = skill[e.first[0]];
        // assert deep copy
        for(int j=1 ; j<e.first.size() ; ++j){
            auto sk = e.first[j];
            auto it = set_intersection(skill[sk].begin(),skill[sk].end(),
            out.begin(),out.end(),out.begin()
            );
            out.resize(it - out.begin());
        }
        ans += (LL)(N - out.size()) * e.second;
    }
    cout << ans << "\n";
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
