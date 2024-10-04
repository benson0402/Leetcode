using ll = long long;
class Solution {
public:
    long long dividePlayers(vector<int>& skill) {
        int n = skill.size();
        sort(skill.begin(), skill.end());
        ll sum = 0;
        ll need = -1;
        for(int i = 0; i < n / 2; ++i) {
            ll tmp = skill[i] + skill[n - 1 - i];
            if(need == -1) need = tmp;
            if(need != tmp) {
                return -1;
            }
            sum += skill[i] * skill[n - 1 - i];
        }
        return sum;
    }
};
