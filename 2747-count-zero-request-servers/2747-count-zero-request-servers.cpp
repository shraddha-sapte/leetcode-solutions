class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        sort(logs.begin(), logs.end(), [](auto &a, auto &b) {
            return a[1] < b[1];
        });

        vector<pair<int,int>> q;
        for (int i = 0; i < queries.size(); i++)
            q.push_back({queries[i], i});

        sort(q.begin(), q.end());

        vector<int> ans(queries.size());
        unordered_map<int,int> mp;

        int l = 0, r = 0, active = 0;

        for (auto [t, idx] : q) {
            while (r < logs.size() && logs[r][1] <= t) {
                if (++mp[logs[r][0]] == 1)
                    active++;
                r++;
            }

            while (l < r && logs[l][1] < t - x) {
                if (--mp[logs[l][0]] == 0)
                    active--;
                l++;
            }

            ans[idx] = n - active;
        }

        return ans;
    }
};