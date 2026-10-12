
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const long long MOD = 1e9 + 7;
        int cnt[31] = {0};
        long long ans = 0;

        for (int num : nums) {
            for (int i = 0; i < 31; i++) {
                if ((num >> i) & 1)
                    cnt[i]++;
            }
        }

        while (k--) {
            long long x = 0;

            for (int i = 0; i < 31; i++) {
                if (cnt[i] > 0) {
                    x |= (1LL << i);
                    cnt[i]--;
                }
            }

            ans = (ans + x * x) % MOD;
        }

        return ans;
    }
};
