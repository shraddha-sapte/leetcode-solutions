
class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            long long product = 1;
            long long gcd = 0;
            long long lcm = 1;

            for (int j = i; j < n; j++) {

                gcd = std::gcd(gcd, (long long)nums[j]);

                lcm = std::lcm(lcm, (long long)nums[j]);

                // Check product overflow
                if (product > LLONG_MAX / nums[j])
                    break;

                product *= nums[j];

                if (product == lcm * gcd) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};
