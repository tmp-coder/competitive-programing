#include<bits/stdc++.h>
using namespace std;
 

#define char2int(x) ((x) - '0')

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
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> val(s.size()),sum(s.size()+1);
        transform(s.begin(),s.end(),val.begin(),[](char e){return char2int(e);});
        // const auto & print = for_each(val.begin(),val.end(),[](const int &e){cout << e << "\n";});
        partial_sum(val.begin(),val.end(),sum.begin()+1);
        sum[0] =0;
        // for_each(sum.begin(),sum.end(),print);
        int ans =0;
        for(int i= 0 ; i<= n/2 ; ++i)
        {
            ans = max(ans,sum[i+(n+1)/2] - sum[i]);
        }
        cout << ans <<"\n";
    }
    
 
    return 0;
}
