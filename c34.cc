#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;




int get_result(vector<int> nums)
{ 
    while(nums.size() > 2)
    {
        sort(nums.begin(), nums.end(), less<int>());
        vector<int> nums2;
        int z = nums.back();
        nums.pop_back();
        int y = nums.back();
        nums.pop_back();
        int x = nums.back();
        nums.pop_back();
        
        if (z == y && y != x)
        {
            nums2.push_back(y-x);
        }
        else if (z != y && y == x)
        {
            nums2.push_back(z - y);
        }
        else if (z != y && y != x)
        {
            nums2.push_back(abs( (z - y) - (y - x) ) );
        }
        for (size_t i = 0; i < nums2.size(); ++i)
        {
            nums.push_back(nums2[i]);
        }
    }

    if (nums.size() == 0)
    {
        return 0;
    }
    else if (nums.size() == 2)
    {
        return max(nums[0] , nums[1]);
    }
    else 
    {
        return nums[0];
    }
}

int main()
{
    //输入
    int count;
    cin >> count;
    vector<int> nums;
    for (int i = 0; i < count; ++i) 
    {
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }

    switch(count)
    {
    case 0 :
        cout << "0\n";
        break;

    case 1 :
        cout << nums[0] << "\n";
        break;

    case 2 :
        cout << max(nums[0], nums[1]) << "\n";
        break;

    default :
        cout << get_result(nums) << "\n";
        break;
    }
    
    return 0;
}
