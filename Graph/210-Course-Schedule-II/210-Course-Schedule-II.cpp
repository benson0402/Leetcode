class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> G(numCourses);
        vector<int> in(numCourses);
        
        for(auto& req: prerequisites) {
            G[req[1]].push_back(req[0]);
            in[req[0]]++;
        }

        queue<int> que;
        for(int i = 0; i < numCourses; ++i) {
            if(in[i] == 0)
                que.push(i);
        }

        vector<int> ans;
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            ans.push_back(u);
            for(auto& v : G[u]) {
                in[v]--;
                if(in[v] == 0)
                    que.push(v);
            }
        }

        if(ans.size() != numCourses)
            return {};
        else
            return ans;
    }
};
