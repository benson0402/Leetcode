#define F first
#define S second
class Solution {
public:
    vector<double> calcEquation(
        vector<vector<string>>& equations, 
        vector<double>& values,
        vector<vector<string>>& queries) {

        int n = equations.size();
        map<string, vector<pair<string, double>>> G;
        for(int i = 0; i < n; ++i) {
            auto eq = equations[i]; 
            G[eq[0]].push_back({eq[1], values[i]});
            G[eq[1]].push_back({eq[0], 1 / values[i]});
        }

        auto bfs = [&](string s, string t) -> double {
            if(!G.count(s) || !G.count(t)) return -1;

            double ans = 1;
            map<string, bool> visit;
            queue<pair<string, double>> que;
            que.push({s, 1});
            while(!que.empty()) {
                auto u = que.front(); que.pop();
                if(u.F == t) return u.S;
                for(auto& v : G[u.F]) {
                    if(visit[v.F]) continue;
                    visit[v.F] = 1;
                    que.push({v.F, v.S * u.S});
                    if(v.F == t) return v.S * u.S;
                }
            }
            return -1;
        };
        vector<double> ans(queries.size());
        for(int i = 0; i < ans.size(); ++i)
            ans[i] = bfs(queries[i][0], queries[i][1]);
        return ans;
    }
};
