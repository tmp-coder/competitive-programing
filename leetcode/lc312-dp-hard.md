https://leetcode.com/problems/burst-balloons/

# 题解

一列连续的气球， 每个的价值为 nums[i],烧掉其中一个获得收益 nums[i-1] * nums[i] * nums[i+1], 求烧完所有气球的最大收益

区间dp，dp[l][r] 表示烧完(l,r)的收益，需要注意的时这个问题要反过来想，最后烧完气球i，的最大收益，这样才不会影响[l,i-1],[i+1,r]

```cpp
class Solution {
public:
    int dfs(int l,int r,const vector<int>& nums, vector<vector<int>>& dp){
        if(r<l)
            return 0;
        if(dp[l][r] != -1)
            return dp[l][r];
        int & ans = dp[l][r];
        for(int i=l; i<=r ; ++i){
            ans = max(ans, dfs(l,i-1,nums, dp) + dfs(i+1,r,nums,dp) + nums[i]*(l-1<0?1:nums[l-1]) * (r+1<nums.size()?nums[r+1]:1));
        }
        return ans;
    }
    int maxCoins(vector<int>& nums) {
        int n= nums.size();
        vector<vector<int>>dp(n, vector<int>(n, -1));
        return dfs(0, n-1, nums, dp);
    }
};

```
