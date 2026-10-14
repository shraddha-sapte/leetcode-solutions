class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if(sum >9 * num){
            return "";
        }
    string  ans="";
        for(int i=0;i<num;i++){
            int digits = min (9,sum);

            ans+= char('0'+digits);
            sum -= digits;
        }
        return ans;

    }  

};