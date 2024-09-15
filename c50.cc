#include<iostream>
#include<vector>
using namespace std;
 
 
int main()
{
    int n;
    cin >> n;
    vector<int> nums;
    for(int i = 0; i < n; ++i)
    {
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }
    int count;
    cin >> count;
 
    int temp_sum = 0;
    //暂且选数组头部连续的count个
    for(int i = 0; i < count; ++i)
    {
        temp_sum += nums[i];
    }
 
    int result = temp_sum;
    //当前选到的最右位置
    int right = count - 1;
    //尝试将要选的左一点的位置来换掉当前最右位置
    int left = n - 1;
    //将香蕉数组看成是连续的一个环，可以知道选中的是一段连续的香蕉，并要求其值最大
    while (right >= 0)
    {
        //连续窗口向左移
        temp_sum = temp_sum + nums[left] - nums[right];
        if(temp_sum > result)
        {
            result = temp_sum;
        }
        right -= 1;
        left -= 1;
    }
    cout << result;
    return 0;
}
