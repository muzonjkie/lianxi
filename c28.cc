// Online C++ compiler to run C++ program online
#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<string>
#include<exception> 
#include<map>
#include<unordered_map>
#include<set>
#include<climits>
using namespace std;
 
int minimumDifference(vector<int>& nums) {
        // 取出一半元素
        int nn = nums.size(), n = nn / 2;
        //情况key，选出那n个，目前的和，已选与未选
        unordered_map<int, set<int> > mps;
        //n个字节能表示的数的范围
        for(int i = 0; i < (1 << n); ++i)
        {
            int key = 0, now = 0;
            //查看每位是否为1，为1表示选了该元素
            for(int j = 0; j < n; ++ j)
            {
                if(i & (1 << j))
                {
                    ++key;
                    now += nums[j];
                    //表示选了该元素
                }
                else
                {
                    --key;
                    now -= nums[j];
                    //表示没选该元素
                }
            }
            //选择个数一样的会在同一个set
            mps[key].insert(now);
        }
        int ans = INT_MAX;
        for(int i = 0; i < (1 << n); ++i)
        {
            int key = 0, now = 0;
            for(int j = 0; j < n; ++j)
            {
                //表示选中
                if(i & (1 << j))
                {
                    //这样才能使得选了足够的队员对应于mps中key对应的set
                    -- key;
                    // -是因为lower_bound能顺利找到且在abs里取负才是真的和前面循环选中合到一起
                    //若取正的话在mps的对应key的set中全部满足查找条件
                    now -= nums[j + n];
                }
                else
                {
                    ++ key;
                    now += nums[j + n];
                }
            }
            if(mps.find(key) != mps.end())
            {
                //找到不大于的第一个，且一定是同符号的
                auto it = mps[key].lower_bound(now);
                if(it != mps[key].end())
                {
                    ans = min(ans, abs(*it - now));
                }
                //
                if(it != mps[key].begin())
                {
                    -- it;
                    ans = min(ans, abs(*it - now));
                }
            }
        }
        return ans;
    }
 
int main() {
    //输入
    vector<int> picked;
    int N = 10;
    while(N) {
        int score;
        cin>>score;
        picked.push_back(score);
        N--;
    }
    cout << minimumDifference(picked);
 
	return 0;
}
