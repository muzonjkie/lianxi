#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution{
public:
	vector<vector<int>> permute(vector<int>& nums) {
		//sort(nums.begin(), nums.end());
		vector<vector<int>> subs;
		vector<int> sub;
		genSubsets(nums, 0, subs);
		return subs;
	}
	void genSubsets(vector<int> & nums, size_t start, vector< vector<int> > & subs) 
    {
        //若原始数组不包含重复元素，那全排列就很OK
        //但是若存在重复元素，就会出现一模一样的全排列，若不想要，则去重
		if (start == nums.size())
        {
            bool flag = true;
            //去重
            for(size_t j = 0; j < subs.size(); ++j)
            {
                if(subs[j] == nums)
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                subs.push_back(nums);
            }
			return;
		}
        /*第一步就是在第一个位置取遍所有的元素
          第二步就是按照第一步处理方式递归求解剩下的元素*/
		for (size_t i = start; i < nums.size(); ++i)
        {
            //与下一个换
			swap(nums[start], nums[i]);
            //将下一个位置分别和后面的元素再交换
			genSubsets(nums, start + 1, subs);
            //换了之后要换回来，然后再跟下下个换
			swap(nums[start], nums[i]);
		}
	}
};

int main()
{
    std::cout << "Hello world" << std::endl;
    vector<int> nums = {1, 2, 1};
    Solution man;
    vector< vector<int> > res =  man.permute(nums);
    for(size_t i = 0; i < res.size(); ++i)
    {
        for(size_t j = 0; j < res[0].size(); ++j)
        {
            cout << res[i][j];
        }
        cout << "\n";
    }
    return 0;
}



