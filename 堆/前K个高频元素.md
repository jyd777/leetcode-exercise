# 前K个高频元素

给你一个整数数组 `nums` 和一个整数 `k` ，请你返回其中出现频率前 `k` 高的元素。你可以按 **任意顺序** 返回答案。

 

**示例 1:**

```
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]
```

**示例 2:**

```
输入: nums = [1], k = 1
输出: [1]
```

 

**提示：**

- `1 <= nums.length <= 105`
- `k` 的取值范围是 `[1, 数组中不相同的元素的个数]`
- 题目数据保证答案唯一，换句话说，数组中前 `k` 个高频元素的集合是唯一的

 

**进阶：**你所设计算法的时间复杂度 **必须** 优于 `O(n log n)` ，其中 `n` 是数组大小。



## 堆解法

使用最小堆的思想，结合pair记录数值和频率：

1. 统计每个元素的出现次数
2. 使用最小堆维护前k个高频元素
3. 堆中存储pair<频率, 数值>，按频率排序

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> freq;
        for(int num:nums)
            freq[num]++;
        // 最小堆，按照频率排序
        // pair<频率，数值> 频率小的在堆顶
        priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> heap;
        for(auto& [num, count]:freq){
            heap.push({count, num});
            if(heap.size()>k)
                heap.pop();
        }
        // 结果
        vector<int> ret;
        while(!heap.empty()){
            ret.push_back(heap.top().second);
            heap.pop();
        }
        return ret;
    }
};
```

**时间复杂度分析：**
- 统计频率：O(n)
- 建堆：O(n log k)
- 总时间复杂度：O(n log k) < O(n log n)

**空间复杂度：** O(n)

**思路解释：**
- 使用unordered_map统计每个元素的出现次数
- 使用最小堆维护前k个高频元素
- pair中first是频率，second是数值
- 堆按频率排序，频率小的在堆顶
- 最终堆中存储的就是前k个高频元素