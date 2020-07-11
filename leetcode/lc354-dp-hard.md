https://leetcode.com/problems/russian-doll-envelopes/

给一个二维的子序列: (a_i,b_i) ,....,
求最长覆盖路径: a_i<a_j && b_i < b_j

# 题解:

1. 二维LISO(NlogN)

同一维的LIS，设计cmp函数时注意，一定是在啊a[0]相同的情况下将a[1]替换为更小的。

```cpp
static bool comp(vector<int>& v1, vector<int>& v2){
        return v1[0] < v2[0] || (v1[0]==v2[0] && v1[1] > v2[1]);
    }
```
