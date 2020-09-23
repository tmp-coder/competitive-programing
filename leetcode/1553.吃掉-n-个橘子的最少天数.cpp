/*
 * @lc app=leetcode.cn id=1553 lang=cpp
 *
 * [1553] 吃掉 N 个橘子的最少天数
 */
#include<bits/stdc++.h>
using namespace std;
// @lc code=start
class Solution {
public:
    unordered_map<int,int> ans;
    int minDays(int n) {
        if(n <=1)
            return n;
        if(ans.count(n))
            return ans[n];
        else {
            int v = min(n % 2  + 1  + minDays(n/2),n % 3 + 1 + minDays(n/3));
            ans[n] = v;
            return v;
        }
    }
};
// @lc code=end

int mian(){
    Solution s = Solution();
    cout << s.minDays(10);
    return 0;
}
