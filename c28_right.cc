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
 
int minimumDifference(vector<int> & nums) {
        // 取出一半元素
        int n = nums.size();
        int differen = INT_MAX;
        vector<int> choose(n, 0);
        //n个字节能表示的数的范围
        //从第一次能够选半数个开始
        for(int i = (1 << n / 2) -1; i < (1 << n); ++i)
        {
            int now = 0;
            vector<int> temp(n, 0);
            int oneque = 0;
            //查看每位是否为1，为1表示选了该元素
            for(int j = 0; j < n; ++j)
            {
                if(i & (1 << j))
                {
                    //1队选了
                    ++oneque;
                    temp[j] = 1;
                    now += nums[j];
                    //表示选了该元素
                }
                else
                {
                    now -= nums[j];
                    //表示没选该元素
                }
            }
            //选了一半才能
            if(oneque == n / 2)
            {
                if(abs(now) < differen)
                {
                    //更新最小差距并记录是选了哪几个
                    differen = abs(now);
                    choose = temp;
                }
            }
        }

        for(size_t i = 0; i < choose.size(); ++i)
        {
            if(choose[i] != 0)
            {
                cout << "choose" << i+1 << "号\n";
            }
        }
        return differen;
    }
 
int main() {
    //输入
    vector<int> picked;
    int N = 10;
    while(N)
    {
        int score;
        cin >> score;
        picked.push_back(score);
        --N;
    }
    cout << "最小差距：" << minimumDifference(picked) << "\n";
 
	return 0;
}
