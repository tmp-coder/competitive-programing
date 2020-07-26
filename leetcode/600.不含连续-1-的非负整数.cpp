/*
 * @lc app=leetcode.cn id=600 lang=cpp
 *
 * [600] 不含连续1的非负整数
 */
#include<bits/stdc++.h>
using namespace std;
// @lc code=start
class Solution {
public:
    int solve(int len, int last, int over, vector<vector<vector<int>>>&dp, bitset<32> & dim){
        if(len == 32)
            return 1;
        if(dp[len][last][over] != -1)
            return dp[len][last][over];
        
        auto & ans = dp[len][last][over];
        ans = 0;
        int k = dim[31-len];
        int maxx = over ? k : 1 ;
        if(last==1)
            maxx = 0;
        for(int i=0; i<=maxx; ++i){
            ans += solve(len + 1, i, over && (i==k), dp, dim);
        }
        return ans;
    }
    int findIntegers(int num) {
        vector<vector<vector<int> > > dp(32,vector<vector<int>>(2,vector<int>(2,-1)));
        bitset<32> dim(num);
        
        // for(int i=0 ; i<32; ++i)
        //     cout << dim[i] << "\n";
        // cout << dim << "\n";
        return solve(0, 0,1, dp, dim);
    }
};
// @lc code=end

