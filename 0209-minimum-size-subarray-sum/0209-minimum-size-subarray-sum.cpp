class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
    int l=0;
    int r=0;
    int currSum=0;
    int res = INT_MAX;
    int n = nums.size();
    while(r<n){
        currSum += nums[r];
        while(currSum>= target){
            res= min(res, r-l+1);
            currSum-=nums[l];
            l++;
        }
        r++;
    }
    return res == INT_MAX ? 0 : res;     
        
    }
};