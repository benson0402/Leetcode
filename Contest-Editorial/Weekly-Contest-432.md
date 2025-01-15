# Weekly Contest 432

> Virtual Contest (3/4)

## Q1. Zigzag Grid Traversal With Skip

> [Problem Link](https://leetcode.com/problems/zigzag-grid-traversal-with-skip/description/)

At first, I was a bit confused about what `alternate` meant in the statement. However, after reading the example input/output, I realized that the problem requires iterating through the grid in a zigzag pattern and outputting an array where every step skips one block.

The solution is quite naive: zigzaggin through the grid, storing the values in a vector, and the simulating the skips on the vector. This approach simplifies the implementation compared to directly simulating the skips during the zigzag traversal.

```cpp
class Solution {
public:
    vector<int> zigzagTraversal(vector<vector<int>>& grid) {
      vector<int> ret;
      int n = grid.size(), m = grid[0].size();
      for(int i = 0; i < n; ++i) {
        if(i % 2 == 0) {
          for(int j = 0; j < m; ++j)
            ret.push_back(grid[i][j]);
        }
        else {
          for(int j = m - 1; j >= 0; --j)
            ret.push_back(grid[i][j]);
        }
      }
      vector<int> newret;
      for(int i = 0; i < ret.size(); i += 2) {
        newret.push_back(ret[i]);
      }
      return newret;
    }
};
```

## Q2. Maximum Amount of Money Robot Can Earn

> [Problem Link](https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/description/)

This is a classical dynamic programming (DP) problem. The state of the DP can be defined as follows: `dp[k][i][j]`, where `dp[k][i][j]` represesnts the mamximum money the robot can earn upon arriving at `Grid[i][j]` after using the `netutralize` operation exactly `k` times.

By clearly defining the state of the DP, we can now determine how to transition between states.

1. We check `dp[k][i - 1][j]` and `dp[k][i][j - 1]`, which represent moving to the current position `(i, j)` from the previous block without using `neutralize`.
2. We also consider `dp[k - 1][i - 1][j]` and `dp[k - 1][i][j - 1]`, which represent using the `neutralize` operation at `Grid[i][j]`

```cpp
using ll = long long;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
ll dp[3][501][501];
class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
      int n = coins.size(), m = coins[0].size();
      
      for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
          for(int k = 0; k < 3; ++k)
            dp[k][i][j] = -LINF;

      dp[0][0][0] = coins[0][0];
      dp[1][0][0] = 0;
      for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
          for(int k = 0; k < 3; ++k) {
            if(i) {
              if(k)
                dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i - 1][j]);
              dp[k][i][j] = max(dp[k][i][j], dp[k][i - 1][j] + coins[i][j]);
            }
            if(j) {
              if(k)
                dp[k][i][j] = max(dp[k][i][j], dp[k - 1][i][j - 1]);
              dp[k][i][j] = max(dp[k][i][j], dp[k][i][j - 1] + coins[i][j]);
            }
          }
        }
      }

      ll ans = -LINF;
      for(int k = 0; k < 3; ++k)
        ans = max(ans, dp[k][n - 1][m - 1]);
      return ans;
    }
};
```

## Q3. Minimize the Maximum Edge Weight of Graph

> [Problem Link](https://leetcode.com/problems/minimize-the-maximum-edge-weight-of-graph/)

This is an interesting problem, especially when you approach it from different perspectives.

At first glance, I thought hte problem seemed overly constrained and a bit messy due to the following conditions:

1. Node 0 must be reachable from all other nodes
2. The maximum edge weight in the resulting graph is minimized.
3. Each node has at moast `threshold` outgoing edges.

However, after analyzing each condition, I realized what the problem was asking me to do. Here's a break down how I approached these conditions:

1. Essentially, we can reverse the input graph and check whether all nodes are reachable from Node 0 by using DFS. 
2. May be a typcial approach that would invovlve binary search or MST. However, I think MST might not be the one because its a directed graph. Binary Search will be much more better.
3. Confused at first. No clue.

The first step I took was to use binary search to rebuild the graph, ensuring that the edge weights remained within a specific range. Then, I performed a DFS starting from Node 0 to check whether all nodes could be visited.

At this point, I realized that condition 3 was essentially redundant. During the DFS process starting from Node 0, the traversal forms a DFS tree with Node 0 as the root. In such a tree, every node has exactly one parent which means that in the original graph, all nodes (except Node 0) will have at most one outgoing edge.


Thus, the problem is successfully solved !


```cpp
class Solution {
public:
  vector< vector<pair<int, int>> > G;
  vector<bool> vis;
  void dfs(int u, int k) {
    vis[u] = 1;
    for(auto& [v, w] : G[u]) {
      if(w <= k) {
        if(!vis[v])
          dfs(v, k);
      }
    }
  }
  bool check(int n, int k) {
    vis = vector<bool>(n);
    dfs(0, k);
    for(int i = 0; i < n; ++i)
      if(!vis[i])
        return false;
    return true;
  }
  int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
    G = vector<vector<pair<int, int>>>(n);
    for(auto& edge : edges) {
      G[edge[1]].push_back({edge[0], edge[2]});
    }
    int l = 1, r = 1e6 + 1;
    while(l < r) {
      int m = (l + r) / 2;
      if(check(n, m))
        r = m;
      else
        l = m + 1;
    }
    int qq = 1e6 + 1;
    if(l == qq) {
      return -1; 
    }
    return l;
  }
};
```

## Q4. Count Non-Decreasing Subarrays After K Operations

> [Problem Link](https://leetcode.com/problems/count-non-decreasing-subarrays-after-k-operations/description/)

I think this was a challenging problem. During the virtual contest, I initially couldn’t figure out how to solve it.

Here are some thoughts that came to mind:

1. For an $O(n^2)$ solution, we would need to check every fixed left pointer and find the maximum possible right pointer. Perheps this can be done more efficiently using binary search of a data structure like segment tree.
2. Is seems like divide and conqure could be used to solve this problem. However, the challenge lies in figuring out how to merge the left and right segments in $O(n)$ or $O(n \log n)$
3. I had no idea how to solve it in linear time, but I discovered through the discussion that it is indeed possible after contest.

### Approach 1: Divide and Conquer

This was an appraoch that I came up etirely, and it was successfully accepted, but not witnin the contest time limit. QQ

In divide-and-conqure problems, the most challenging part is often figuring out how to merge the left and right intervals. Specifically, in this problem, we need to find the number of subarrays that satisfy the given condition that cross the midpoint.

My solution involves the following steps:

1. Count the operations of each subarrary need to do within the ranges `(all possible left pointers, midpoint]` and `[midpoint + 1, all possible right pointers)`. This can be done in linear time by using some monotone technique. 
2. Once these subarrays are calculated, use two-pointer approach to merge the left and right subarrays by checking whether their total operations exceed the given constraint `k`.

There's a key trick here: you need to keep track of the maximum number in the left subarray. 

This is because when some elements in the right subarray are smaller than the maximum value of the left subarray, you may need to do more operations on the right subarray. This step can also do in linear time, since we can maintain a pointer to the biggest element (after doing operation on right array) that is smaller than the left subarray's maximum element. The pointer is moved in an amortized $O(1)$ time.

Overall, the merging process is amortized to $O(n)$, resulting in a total time complexity of $O(n \log n)$

By the way, I feel my implementation is somewhat messy. XD

```cpp
#define F first
#define S second
using ll = long long;
class Solution {
public:
  vector<ll> vec;
  ll dc(ll l, ll r, ll k) {
    if(l == r) {
      return 1;
    }
    else if(l + 1 == r) {
      if(vec[l] <= vec[r]) return 3;
      return 2 + (vec[l] - vec[r] <= k);
    }
    ll m = (l + r) / 2;
    ll lcnt = dc(l, m, k), rcnt = dc(m + 1, r, k);
    vector<pair<ll, ll>> lvec; // {cnt, max}

    vector<pair<ll, ll>> dq;
    ll tmp = 0;
    for(int i = m; i >= l; --i) {
      if(dq.empty()) {
        dq.push_back({vec[i], i});
      }
      else {
        if(vec[i] <= dq.back().F)
          dq.push_back({vec[i], i});
        else {
          int nidx = i;
          while(!dq.empty() && vec[i] > dq.back().F) {
            tmp += (vec[i] - dq.back().F) * (dq.back().S - nidx);
            nidx = dq.back().S;
            dq.pop_back();
          }
          dq.push_back({vec[i], nidx});
        }
      }
      lvec.push_back({tmp, dq[0].F});
    }

    vector<array<ll, 3>> rvec; // {cnt, sum, mx}
    ll rtmp = 0, rsum = 0, rmx = 0;
    for(int i = m + 1; i <= r; ++i) {
      if(rmx < vec[i]) {
        rmx = vec[i];
        rsum += vec[i];
        rvec.push_back({rtmp, rsum, rmx});
      }
      else {
        rsum += rmx;
        rtmp += rmx - vec[i];
        rvec.push_back({rtmp, rsum, rmx});
      }
    }

    int smalleridx = rvec.size() - 1;
    int lidx = lvec.size() - 1;
    int ridx = 0;

    ll ans = 0;
    while(ridx < rvec.size()) {
      while(lidx >= 0) {
        ll cnt = 0;
        while(smalleridx >= 0 && rvec[smalleridx][2] > lvec[lidx].S)
          smalleridx--;
        
        if(smalleridx >= 0) {
          int tri = min(ridx, smalleridx);  
          cnt += lvec[lidx].S * (tri + 1) - (rvec[tri][1]);
        }
        cnt += lvec[lidx].F;
        cnt += rvec[ridx][0];
        if(cnt > k)
          lidx--;
        else
          break;
      }
      if(lidx < 0) break;
      ans += lidx + 1;
      ridx++;
    }
    
    return ans + lcnt + rcnt;
  }  
  long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
    for(auto& x : nums)
      vec.push_back(x);
    return dc(0, nums.size() - 1, k);
  }
};
```

### Approach 2: Monotone Deque

This is a very elegant solution. Here is a [reference](https://leetcode.com/problems/count-non-decreasing-subarrays-after-k-operations/solutions/6267498/java-c-python-mono-decreasing-deque-o-n).

Here are my thoughts of this solution.

We can think of the problem as follows: for a given subarray, each element must be fileld with the same height as the maximum element on its left side. WWhat we're trying to maintain in the monotone deque are the `maximum` values that shape the subarray.

For the fixed right pointer, we can try to expand our left pointer to find out the limit it can put in the deque by checking the new value will cost operation or not. If the new value is larger then the front (the leftest) value in deque, that means we'll need to reshape the deque, and maintain the total cost of reshaping it.

Once the cost is larger than `k`, we'll now trying to move the right pointer to left. And here is an amazing part, we actually know how much the rightest element have cost because we know the its maximum element of its left side (i.e. back() in deque). So we can just maintain the cost very well.'

I think the first part of this solution is kind of straightforward for me, but the second part is just amazing. Maybe it's because I'm not really good at this type of problem ( i.e. amortizing stuff, and analzing cool properties). 

The good thing is in that disccusion, the author has provided a problem list to practice, very appreciate that.

```cpp
using ll = long long;
class Solution {
public:
  long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
    int n = nums.size();

    ll ans = 0;
    ll cost = 0;
    deque<int> deq;
    for(int l = n - 1, r = n - 1; l >= 0; l--) {
      while(!deq.empty() && nums[l] > nums[deq.front()]) {
        int ori_h = nums[deq.front()]; 
        ll upd_l = deq.front(); deq.pop_front();
        ll upd_r = (deq.empty() ? r + 1 : deq.front());
        cost += 1ll * (upd_r - upd_l) * (nums[l] - ori_h);
      }
      deq.push_front(l);

      while(cost > k) {
        cost -= (nums[deq.back()] - nums[r]);
        if(deq.back() == r)
          deq.pop_back();
        r--;
      }
      
      ans += r - l + 1;
    }  
    return ans;
  }
};
```
