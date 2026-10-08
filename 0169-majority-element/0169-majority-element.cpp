class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int freq= 0;
        int count = 0;

        for (int num : nums) {
            if (count == 0)
                freq = num;

            if (num == freq)
                count++;
            else
                count--;
        }

        return freq;
    }
};