class Solution {
public:

    int n;
    vector<vector<int>> G;
    vector<multiset<int>> h;
    vector<int> h2;

    void dfs(int u, int p) {
        h[u].insert(0);
        for(auto& v : G[u]) if(v != p) {
            dfs(v, u);
            h[u].insert((*(h[v].rbegin())) + 1);
        }
    }

    void dfs2(int u, int p) {
        h2[u] = *h[u].rbegin();
        for(auto& v : G[u]) if(v != p) {
            int tmp = *h[v].rbegin() + 1;
            h[u].erase(h[u].find(tmp));
            int tmp2 = *h[u].rbegin() + 1;
            h[v].insert(tmp2);
            dfs2(v, u);
            h[v].erase(h[v].find(tmp2));
            h[u].insert(tmp);
        }
    }

    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        G.resize(n);
        h.resize(n);
        h2.resize(n);

        for(auto& edge: edges) {
            G[edge[0]].push_back(edge[1]);
            G[edge[1]].push_back(edge[0]);
        }
        
        dfs(0, -1);
        dfs2(0, -1);

        int mn = 1e6;
        vector<int> ans;
        for(int i = 0; i < n; ++i) {
            if(h2[i] < mn) {
                ans.clear();
                ans.push_back(i);
                mn = h2[i];
            }
            else if(h2[i] == mn) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};
