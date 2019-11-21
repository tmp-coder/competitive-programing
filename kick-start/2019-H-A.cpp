#include<bits/stdc++.h>
#include<bits/extc++.h>
#define ms(x,v) memset((x),v,sizeof(x))
#define INF 0x3f3f3f3f
using namespace std;
using namespace __gnu_pbds;

const int MAXN = 100+10;
typedef long long LL;

typedef tree<pair<LL,int>,
null_type,
less<pair<LL,int>>,
rb_tree_tag,
tree_order_statistics_node_update> ordered_tree;




void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0 ; i<n ; ++i)
        cin >> a[i];
    
    ordered_tree se;
    vector<int> ans(n);
    ans[0] =1;
    se.insert(make_pair(a[0],0));

    // const auto ok = [se](int h){
    //     cout << h << "\n";
    //     cout << se.size() <<" " << se.order_of_key(make_pair(h-1,INF)) <<"\n";
    //     return se.size() - se.order_of_key(make_pair(h-1,INF)) >= h;
    // };
    for(int i=1 ; i<n ; ++i){
        se.insert(make_pair(a[i],se.size()));

        int left = ans[i-1]-1;
        int right = i+1;
        // if(i==5 )
        //     for(const auto & e : se)
        //         cout << e.first << " "<< e.second << "\n";
        while(left <= right){
            int mid = (left + right) >>1;
            bool ok = se.size() - se.order_of_key(make_pair(mid-1,INF)) >= mid;
            if(ok)left = mid +1;
            else right = mid -1;
        }
        ans[i] = left - 1;
    }
    for(int i=0 ; i<n ; ++i)
        cout << " " << ans[i];
    cout << '\n';
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
