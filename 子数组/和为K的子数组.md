# 和为K的子数组

给你一个整数数组 `nums` 和一个整数 `k` ，请你统计并返回该数组中和为 `k` 的子数组的个数 。

子数组是数组中元素的连续非空序列。

 

**示例 1：**

```
输入：nums = [1,1,1], k = 2
输出：2
```

**示例 2：**

```
输入：nums = [1,2,3], k = 3
输出：2
```

 

**提示：**

- `1 <= nums.length <= 2 * 104`
- `-1000 <= nums[i] <= 1000`
- `-107 <= k <= 107`



**思路：**

==🤔数组中出现求和，以及子数组等关键字➡️前缀和==

**前缀和 + 哈希表**

- 设 pre[i] 表示前 i 个数的和。

- 对于区间 [i, j]，其和为 pre[j+1] - pre[i]。

- 如果 pre[j+1] - pre[i] == k，则 [i, j] 是一个和为 k 的子数组。

- 用哈希表记录每个前缀和出现的次数，遍历数组时统计答案。

```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // 前缀和+哈希表
        // first:前缀和值，second：该前缀和出现次数
        unordered_map<int,int> pre;
        pre[0] =1;// 初始化（前缀和为0出现过1次）
        int sum =0, res =0;
        for(int i=0;i<nums.size();i++){
            sum+= nums[i];
            // 当存在pre[j+1]- pre[i] = k,则说明nums[i]+nums[i+1]+……+nums[j] = k
            if (pre.count(sum-k))
                res += pre[sum-k];
            pre[sum]++;
        }
        return res;
    }
};
```

