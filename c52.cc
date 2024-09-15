#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <sstream>
using namespace std;
 

 
int main()
{
    string str;
    getline(cin, str, '\n');
    istringstream iss(str);
    vector<int> nums;
    int temp;
    while(iss >> temp)
    {
        nums.push_back(temp);
    }
    size_t jump, surplus;
    cin >> jump >> surplus;
    if(surplus >= nums.size())
    {
        cout << "不处理\n";
    }
    else
    {
        size_t result = 0;
        int index = 0;
        size_t erase_ = 0;
        while(surplus != nums.size() - erase_)
        {
            size_t cnt = 0;
            //找到中间有jump个未删除的数
            for(size_t i = index + 1; ; i = (i + 1) % nums.size())
            {
                if(nums[i] != 0)
                {
                    ++cnt;
                }
                index = i;
                if(cnt == jump + 1)
                {
                    break;
                }
            }
            ++ erase_;
            nums[index] = 0;
        }
        for(size_t i = 0; i < nums.size(); ++i)
        {
            result += nums[i];
        }
        cout << result << "\n";
    }
    return 0;
}
