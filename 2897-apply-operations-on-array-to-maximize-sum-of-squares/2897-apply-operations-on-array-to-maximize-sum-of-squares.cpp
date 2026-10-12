
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        long long ans = 0;
        int cnt[31] = {0};
        int mod = 1e9 + 7;

        for (int x : nums)
            for (int i = 0; i < 31; i++)
                if (x & (1 << i))
                    cnt[i]++;

        while (k--) {
            long long x = 0;

            for (int i = 0; i < 31; i++) {
                if (cnt[i] > 0) {
                    x |= (1LL << i);
                    cnt[i]--;
                }
            }

            ans = (ans + x * x) % mod;
        }

        return ans;
    }
};
