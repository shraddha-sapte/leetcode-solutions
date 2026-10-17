class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int,int>> a;

        for (int x : nums) {
            int s = 0, t = x;
            while (t) {
                s += t % 10;
                t /= 10;
            }
            a.push_back({s, x});
        }

        sort(a.begin(), a.end());

        unordered_map<int,int> pos;
        for (int i = 0; i < n; i++)
            pos[a[i].second] = i;

        vector<bool> vis(n, false);
        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (vis[i]) continue;

            int j = i, cnt = 0;
            while (!vis[j]) {
                vis[j] = true;
                j = pos[nums[j]];
                cnt++;
            }

            if (cnt > 1) ans += cnt - 1;
        }
        return ans;
    }
};