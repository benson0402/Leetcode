class Solution {
public:


    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n == 1) return {0};

        vector<vector<int>> G(n);
        vector<int> deg(n);

        for(auto& edge: edges) {
            G[edge[0]].push_back(edge[1]);
            G[edge[1]].push_back(edge[0]);

            deg[edge[0]]++;
            deg[edge[1]]++;
        }

        vector<int> leaf;
        for(int i = 0; i < n; ++i) {
            if(deg[i] == 1)
                leaf.push_back(i);
        }

        int left = n;
        while(left > 2) {
            vector<int> nxt;
            for(auto& u: leaf) {
                left--;
                for(auto& v: G[u]) {
                    deg[v]--;
                    if(deg[v] == 1)
                        nxt.push_back(v);
                }
            }
            leaf = nxt;
        }
        
        return leaf;
    }
};
