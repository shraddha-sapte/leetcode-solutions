class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<int> par(n), dep(n), tin(n), sz(n, 1), ord;
        vector<vector<int>> up(20, vector<int>(n));
        vector<int> st = {0};

        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            tin[u] = ord.size(); ord.push_back(u);
            for (int v : g[u]) if (v != par[u] && u != 0) {
                // handled below
            }
            for (int v : g[u]) {
                if (u && v == par[u]) continue;
                if (u == 0 && v == 0) continue;
                par[v] = u; dep[v] = dep[u] + 1; st.push_back(v);
            }
        }

        for (int i = n - 1; i > 0; --i) sz[par[ord[i]]] += sz[ord[i]];
        for (int u = 0; u < n; ++u) up[0][u] = par[u];
        for (int k = 1; k < 20; ++k)
            for (int u = 0; u < n; ++u) up[k][u] = up[k-1][up[k-1][u]];

        vector<int> p(n), fw(n+1);
        for (int u : ord) p[u] = (u ? p[par[u]] : 0) ^ (1 << (s[u]-'a'));

        auto add = [&](int i, int x) {
            for (++i; i <= n; i += i & -i) fw[i] ^= x;
        };
        auto get = [&](int i) {
            int x = 0;
            for (++i; i; i -= i & -i) x ^= fw[i];
            return x;
        };
        auto mask = [&](int u) { return p[u] ^ get(tin[u]); };

        auto lca = [&](int u, int v) {
            if (dep[u] < dep[v]) swap(u, v);
            for (int k = 19; k >= 0; --k)
                if (dep[u] - (1 << k) >= dep[v]) u = up[k][u];
            if (u == v) return u;
            for (int k = 19; k >= 0; --k)
                if (up[k][u] != up[k][v]) u = up[k][u], v = up[k][v];
            return par[u];
        };

        vector<bool> ans;
        for (auto& q : queries) {
            string t; int u; char c;
            stringstream ss(q); ss >> t >> u;
            if (t == "update") {
                ss >> c;
                int d = (1 << (s[u]-'a')) ^ (1 << (c-'a'));
                for (int i = tin[u]; i <= tin[u]+sz[u]-1; i = tin[u]+sz[u])
                    add(i, d);
                if (tin[u]+sz[u] < n) add(tin[u]+sz[u], d);
                s[u] = c;
            } else {
                int v; ss >> v;
                int w = lca(u, v);
                int x = mask(u) ^ mask(v) ^ (1 << (s[w]-'a'));
                ans.push_back(!(x & (x-1)));
            }
        }
        return ans;
    }
};