
class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> lo, hi;
        long long sumLo = 0, sumHi = 0;

        auto balance = [&]() {
            while (lo.size() > hi.size() + 1) {
                int v = *lo.rbegin();
                lo.erase(prev(lo.end()));
                sumLo -= v;
                hi.insert(v);
                sumHi += v;
            }

            while (lo.size() < hi.size()) {
                int v = *hi.begin();
                hi.erase(hi.begin());
                sumHi -= v;
                lo.insert(v);
                sumLo += v;
            }
        };

        auto add = [&](int v) {
            if (lo.empty() || v <= *lo.rbegin()) {
                lo.insert(v);
                sumLo += v;
            } else {
                hi.insert(v);
                sumHi += v;
            }
            balance();
        };

        auto remove = [&](int v) {
            auto it = lo.find(v);

            if (it != lo.end()) {
                lo.erase(it);
                sumLo -= v;
            } else {
                it = hi.find(v);
                hi.erase(it);
                sumHi -= v;
            }
            balance();
        };

        vector<long long> cost;

        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x)
                remove(nums[i - x]);

            if (i >= x - 1) {
                long long m = *lo.rbegin();

                cost.push_back(
                    m * lo.size() - sumLo +
                    sumHi - m * hi.size()
                );
            }
        }

        int m = cost.size();
        const long long INF = 1e18;

        vector<long long> prev(n + 1, 0), curr(n + 1, INF);

        for (int t = 1; t <= k; t++) {
            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {
                curr[i] = curr[i - 1];

                if (i >= x) {
                    curr[i] = min(curr[i],
                        prev[i - x] + cost[i - x]);
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};
