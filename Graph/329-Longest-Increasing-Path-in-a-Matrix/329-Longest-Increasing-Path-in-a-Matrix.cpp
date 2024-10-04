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
        vector<vector<vector<pii>>> G(n, vector<vector<pii>>(m));
        vector<vector<int>> in(n, vector<int>(m, 0));
        vector<vector<int>> ans(n, vector<int>(m, 1));
        
        auto isValid = [&](pii x) { return 0 <= x.F && x.F < n && 0 <= x.S && x.S < m; };
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                pii cur = {i, j};
                for(int k = 0; k < 4; ++k) {
                    pii nxt = {i + go[k].F, j + go[k].S};
                    if(isValid(nxt) && matrix[cur.F][cur.S] < matrix[nxt.F][nxt.S]) {
                        G[i][j].push_back(nxt);
                        in[nxt.F][nxt.S]++;
                    }
                }
            }
        }
        queue<pii> que;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(in[i][j] == 0)
                    que.push({i, j});
            }
        }
        while(!que.empty()) {
            auto cur = que.front(); que.pop();
            for(auto& nxt: G[cur.F][cur.S]) {
                ans[nxt.F][nxt.S] = max(ans[nxt.F][nxt.S], ans[cur.F][cur.S] + 1);
                in[nxt.F][nxt.S]--;
                if(in[nxt.F][nxt.S] == 0)
                    que.push(nxt);
            }
        }
        int ret = 0;
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j)
            ret = max(ret, ans[i][j]);
        return ret;
    }
};
