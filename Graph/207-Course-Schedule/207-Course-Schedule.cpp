class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> G(numCourses);
        vector<int> in(numCourses);
        for(auto& course : prerequisites) {
            int u = course[0], v = course[1];
            G[u].push_back(v);
            in[v]++;
        } 
         
        int cnt = 0;
        vector<int> vec;
        for(int i = 0; i < numCourses; ++i) if(in[i] == 0)
            vec.push_back(i);
        while(!vec.empty()) {
            int u = vec.back();
            vec.pop_back();
            cnt++;

            for(auto& v : G[u]) {
                in[v]--;
                if(in[v] == 0)
                    vec.push_back(v);
            }
        }
        return cnt == numCourses;
    }
};
