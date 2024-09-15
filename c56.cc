#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<sstream>
using namespace std;
 
 
         
int cal(vector<int> nums, vector<vector<int>> element) 
{
    //可能存在气的地方
    vector< vector<int> > matrix(19, vector<int>(19, 0));
    //标记每个棋子的四周
    for (size_t i = 0; i < nums.size(); i += 2) 
    {
        int x = nums[i];
        int y = nums[i + 1];
        
        if (x > 0) 
        {
            matrix[x-1][y] = 1;
        }
        if (x < 18) 
        {
            matrix[x+1][y] = 1;
        }
        if (y > 0) 
        {
            matrix[x][y-1] = 1;
        }
        if (y < 18)
        {
            matrix[x][y+1] = 1;
        }
    }
 
    int result = 0;
    for(int i = 0; i < 19; ++i)
    {
        for(int j = 0; j < 19; ++j)
        {
            //标记可能存在气的地方没有棋子
            if(matrix[i][j] == 1 && element[i][j] != 1)
            {
                result += 1;
            }
        }
    }
 
    return result;
}
 
int main()
{
 
    string input_str1, input_str2;
    getline(cin, input_str1, '\n');
    getline(cin, input_str2, '\n');
    //黑棋
    vector<int> nums1;
    int temp;
    istringstream iss1(input_str1);
    while(iss1 >> temp)
    {
        nums1.push_back(temp);
    }
    //白棋
    vector<int> nums2;
    istringstream iss2(input_str2);
    while(iss2 >> temp)
    {
        nums1.push_back(temp);
    }

    //棋盘
    vector<vector<int>> element(19, vector<int>(19, 0));
 
    for (size_t i = 0; i < nums1.size(); i += 2)
    {
        element[ nums1[i] ][ nums1[i+1] ] = 1;
    }
    
    for (size_t i = 0; i < nums2.size(); i += 2)
    {
        element[ nums2[i] ][ nums2[i+1] ] = 1;
    }
    cout << cal(nums1, element) << " " << cal(nums2, element) << "\n";
    return 0;
}
