#include<iostream>
#include<vector>
#include<stdlib.h>
#include<string.h>
#include <sstream>
using namespace std;
 
 
  
 
bool checkStraightLine(vector<int> point1, vector<int> point2, vector<int> point3) 
{
    int y1 = point2[1] -point1[1];
    int x1 = point2[0] -point1[0];
    int y2 = point3[1] -point2[1];         
    int x2 = point3[0] -point2[0];
    //斜率不一样，向量不成比例，即满秩 
    if (y1*x2 != y2*x1) 
    {
        return false;
    }
    return true;
}
 
int main()
{
    string str;
    getline(cin, str);
    istringstream iss(str);
    vector<int> nums;
    int temp = 0;
    while(iss >> temp)
    {
        nums.push_back(temp);
    }
 
 
    vector<int> result;
    result.push_back(nums[0]);
    result.push_back(nums[1]);
    for (size_t i = 2; i < nums.size() - 2; i += 2) 
    {
        if (! checkStraightLine( {nums[i-2], nums[i-1]}, 
                            {nums[i], nums[i+1]}, 
                            {nums[i+2], nums[i+3]} ) ) 
        {
            //中间那个点是拐点
            result.push_back(nums[i]);
            result.push_back(nums[i+1]);
        }
    }
    //终点
    if(nums.size() >= 4)
    {
        result.push_back(nums[nums.size()-2]);
        result.push_back(nums[nums.size()-1]);
    }
 
    string output_path = "";
    for (size_t i = 0; i < result.size(); ++i)
    {
        output_path += to_string(result[i]);
        if (i != result.size() - 1) 
        {
            output_path += " ";
        }
    }
    cout << output_path << "\n";
    
    return 0;
}
