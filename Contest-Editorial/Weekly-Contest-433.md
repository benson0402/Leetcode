# Weekly Contest 433

> Contest (3/4)

## Q1. Sum of Variable Length Subarrays

> [Problem Link](https://leetcode.com/problems/sum-of-variable-length-subarrays/)

We can use prefix sum to solve this problem.

```cpp
class Solution {
public:
  int subarraySum(vector<int>& nums) {
    int n = nums.size();
    vector<int> pre(n);
    pre[0] = nums[0];
    for(int i = 1; i < n; ++i)
      pre[i] = pre[i - 1] + nums[i];
    auto rng = [&](int l, int r) {
      if(l == 0) return pre[r];
      else return pre[r] - pre[l - 1];
    };

    int ans = 0;
    for(int i = 0; i < n; ++i) {
      int l = max(0, i - nums[i]);
      ans += rng(l, i);
    }
    return ans;
  }
};
```

## Q2. Maximum and Minimum Sums of at Most Size K Subsequences

> [Problem Link](https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-k-subarrays/)

At first, I found this problem quite difficult. However, I realized that since the goal is to find a `subsequence`, we can simplify the approach by sorting the array first.

Then, assume each element as the minimum/maximum element of the subsequence and we can count is appearances using combinations.

Since `k` is small in this problem, we can solve it in $O(nk)$ time.

```cpp
using ll = long long;
class Solution {
public:
  ll mod = 1e9 + 7;
  ll power(ll a, ll b) {
    ll ret = 1;
    for(; b; b >>= 1, a = a * a % mod) if(b & 1)
      ret = ret * a % mod;
    return ret;
  }
  int minMaxSums(vector<int>& nums, int k) {
    // C(n, 0) + C(n, 1) + C(n, 2) + C(n, k-1);

    int n = nums.size();
    vector<ll> fact(n + 1), invf(n + 1);
    fact[0] = 1;
    for(ll i = 1; i <= n; ++i)
      fact[i] = fact[i - 1] * i % mod;
    invf[n] = power(fact[n], mod - 2);
    for(int i = n - 1; i >= 0; --i)
      invf[i] = invf[i + 1] * (i + 1) % mod;
    sort(nums.begin(), nums.end());

    auto Cnk = [&](ll a, ll b) {
      // cout << a << ' ' << b << endl;
      return ((fact[a] * invf[b]) % mod) * invf[a - b] % mod;
    };
    ll ans = 0;
    vector<ll> cntvec(n);
    // min element
    for(int i = 0; i < n; ++i) {
      // C(n - i - 1, 0) + C(n - i - 1, 1)
      ll cnt = 0;
      ll top = n - i - 1;
      for(int down = 0; down <= top && down <= k - 1; down++)
        cnt = (cnt + Cnk(top, down)) % mod;
      // cout << nums[i] << ' ' << cnt << endl;
      ans = (ans + 1ll * nums[i] * cnt % mod) % mod;
      cntvec[i] = cnt;
    }

    reverse(nums.begin(), nums.end());
    for(int i = 0; i < n; ++i) {
      ans = (ans + 1ll * nums[i] * cntvec[i] % mod) % mod;
    }
    
    return ans; 
  }
};
```

## Q3. Paint House IV

> [Problem Link](https://leetcode.com/problems/paint-house-iv/)

I think this problem is fascinating because you can conceptualize the relationship of "not using the same color" as a graph, where edges are added between houses that cannot use the same color.

In this way, we build a rectangle-like graph with dimensions 2 x (n/2).

The next step is to analyze this graph column by column. Each column will have 3×3 possible states, representing every color combination. We can then transition these states from the previous column to the next.

```cpp
using ll = long long;
class Solution {
public:
  
  long long minCost(int n, vector<vector<int>>& cost) {
    // 0   1   2   3   ...
    // n-1 n-2 n-3 n-4

    ll LINF = 1e16;
    ll dp[2][3][3];
    int cur = 0;
    for(int i = 0; i < 3; ++i)
      for(int j = 0; j < 3; ++j)
        dp[cur][i][j] = dp[cur ^ 1][i][j] = LINF;

    vector<pair<int, int>> pos;
    for(int i = 0; i < 3; ++i)
      for(int j = 0; j < 3; ++j) if(i != j)
        pos.push_back({i, j});
    
    for(int now = 0; now < n / 2; ++now) {
      int up = now, down = n - 1 - now;
      for(int i = 0; i < 3; ++i)
        for(int j = 0; j< 3; ++j)
          dp[cur][i][j] = LINF;
      for(auto [c1, c2] : pos) {
        if(now == 0) {
          dp[cur][c1][c2] = min(dp[cur][c1][c2],
            1ll * cost[up][c1] + cost[down][c2]);
        }
        else {
          for(auto [pc1, pc2] : pos) {
            if(c1 != pc1 && c2 != pc2) {
              dp[cur][c1][c2] = min(dp[cur][c1][c2],
                dp[cur ^ 1][pc1][pc2] + cost[up][c1] + cost[down][c2]);
            }
          }
        }
      }

      cur ^= 1;
    }

    ll ans = LINF;
    for(auto& [c1, c2] : pos)
      ans = min(ans, dp[cur ^ 1][c1][c2]);
    return ans;
  }
};
```

## Q4. Maximum and Minimum Sums of at Most Size K Subarrays

> [Problem Link](https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/)

It's an interesting problem.

My initial thought was to use a divide-and-conqure approach with a segment tree or binary search, but I found it a bit complicated and not very elegant. I felt there might be a more refined technique to solve it. 

After the contest, I realized this is actually a monotone queue problem.

At that moment, I reconginzed that I'm very weak in this topic and need to practice it more.

For this problem, we can start by simplifying it and considering how to calculate the maximum and minimums sums of fixed-length `k` subarrays.
This is a classical problem that can be solved using a sliding window with a monotone deque to solve it, and we can extend this technique further.
Actually, we can think what the elements in the deque acutually represent. Waht informantion do they provide?
What I think about is these elements will reshape the elements of this window we currently search for.
For example, if current window is `[l, r]` and we want to find maximum in this range, we definatly want to use a decreasing deque to do it and what it exactly mean is we know, if the we want the window to move rightward and if the newest element is the biggest, why won't we just use this value as a `representation` of this window ?
We can think the deque as storing the decreasing `peak` of the current window, so basicly if we want to know all the subarray maximum with fixed `r` in this window, we can know its maximum by iterating througth of this deque.
Furthermore, we can actually maintain these value everytime we add or delete the element.

With this approach, we can solve this problem in linear time.



```cpp
using ll = long long;
#define F first
#define S second
class Solution {
public:
  long long minMaxSubarraySum(vector<int>& nums, int k) {
    int n = nums.size();
    ll ret = 0;

    {
      // maximum
      ll cur = 0;
      deque<pair<int, int>> dq; // {val, idx} decraseing val
      for(int l = 0, r = 0; r < n; ++r) {
        if(dq.empty()) {
          dq.push_back({nums[r], r});
          cur += 1ll * nums[r] * (r - l + 1);
        }
        else {
          while(!dq.empty() && dq.back().F < nums[r]) {
            auto [b_num, b_idx] = dq.back();
            dq.pop_back();
            int last = (dq.empty() ? l - 1 : dq.back().S);
            cur -= 1ll * b_num * (b_idx - last);
          }
          int last = (dq.empty() ? l - 1 : dq.back().S);
          dq.push_back({nums[r], r});
          cur += 1ll * nums[r] * (r - last);
        }

        if(r - l + 1 > k) {
          cur -= dq.front().F;
          if(dq.front().S == l)
            dq.pop_front();
          l++;
        }

        ret += cur;
      }
    }

    {
      // minimum
      ll cur = 0;
      deque<pair<int, int>> dq; // {val, idx} decraseing val
      for(int l = 0, r = 0; r < n; ++r) {
        if(dq.empty()) {
          dq.push_back({nums[r], r});
          cur += 1ll * nums[r] * (r - l + 1);
        }
        else {
          while(!dq.empty() && dq.back().F > nums[r]) {
            auto [b_num, b_idx] = dq.back();
            dq.pop_back();
            int last = (dq.empty() ? l - 1 : dq.back().S);
            cur -= 1ll * b_num * (b_idx - last);
          }
          int last = (dq.empty() ? l - 1 : dq.back().S);
          dq.push_back({nums[r], r});
          cur += 1ll * nums[r] * (r - last);
        }

        if(r - l + 1 > k) {
          cur -= dq.front().F;
          if(dq.front().S == l)
            dq.pop_front();
          l++;
        }

        ret += cur;
      }
    }

    return ret;
  }
};
```
