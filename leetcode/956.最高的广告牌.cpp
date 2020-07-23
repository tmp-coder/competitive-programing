/*
 * @lc app=leetcode.cn id=956 lang=cpp
 *
 * [956] 最高的广告牌
 */

#include<bits/stdc++.h>
using namespace std;
// @lc code=start
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        if(rods.empty())
            return 0;
        int sum = accumulate(rods.begin(), rods.end(), 0);
        int n = rods.size();
        vector<vector<int> > dp(n+1,vector<int>(2*sum +1, INT32_MIN /2));
        dp[0][sum] = 0;
        for(int i=0 ; i<n ;++i){
            for(int j = rods[i]; j<=2*sum-rods[i] ; ++j){
                dp[i+1][j] = max({dp[i][j], dp[i][j-rods[i]] + rods[i], dp[i][j+rods[i]]});
            }
        }
        
        for(int i=0 ; i<n ; ++i)
            cout << dp[i][sum] << '\n';
        return dp[n][sum];
    }
};
// @lc code=end

int main(){
     vector<int> t({3,4,3,3,2});
    cout << Solution().tallestBillboard(t);
    return  0;

}

