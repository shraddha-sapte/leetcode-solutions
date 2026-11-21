
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> last(26, -1);
        vector<int> newParent(n, -1);

        function<void(int)> dfs = [&](int u) {
            int ch = s[u] - 'a';

            int prev = last[ch];

            if (prev != -1) {
                newParent[u] = prev;
            } else {
                newParent[u] = parent[u];
            }

            last[ch] = u;

            for (int v : adj[u]) {
                dfs(v);
            }

            last[ch] = prev;
        };

        dfs(0);

        vector<vector<int>> tree(n);

        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }

        vector<int> ans(n, 1);

        function<void(int)> calculate = [&](int u) {
            for (int v : tree[u]) {
                calculate(v);
                ans[u] += ans[v];
            }
        };

        calculate(0);

        return ans;
    }
};
