using pii = pair<int, int>;
#define F first
#define S second
class Solution {
public:

    pii go[4] = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        auto isValid = [n, m](int i, int j) -> bool { return 0 <= i && i < n && 0 <= j && j < m; };
        function<int(int, int)> doDP = [&](int x, int y) {
            if(!isValid(x, y)) return 0;
            if(dp[x][y] != -1) return dp[x][y];
            dp[x][y] = 1;
            for(int i = 0; i < 4; ++i) {
                int nx = x + go[i].F, ny = y + go[i].S;
                if(isValid(nx, ny) && matrix[x][y] > matrix[nx][ny]) {
                    dp[x][y] = max(dp[x][y], doDP(nx, ny) + 1);
                }
            }
            return dp[x][y];
        };
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                ans = max(ans, doDP(i, j));
            }
        }
        return ans;
    }
};
