#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
 
vector<int> split(string params_str) {
    vector<int> p;
    while (params_str.find(" ") != string::npos) {
        int found = params_str.find(" ");
        p.push_back(stoi(params_str.substr(0, found)));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(stoi(params_str));
    return p;
}
 
  
 
int main()
{
    string input1, input2;
    getline(cin, input1, '\n');
    getline(cin, input2, '\n');
    vector<int> nums1 = split(input1); 
    vector<int> nums2 = split(input2); 
    int range_x_max = nums1[1] - 1;
    int y = nums2[0];
    int x = nums2[1];
    //该压缩矩阵是按行优先存储的；在该一维数组中的位置(下标)
    int target_position = y * (range_x_max + 1) + x;

    //前面有几个数了
    int total_sum = 0;
    size_t i = 3;
    while(total_sum < target_position)
    {
        total_sum += nums1[i];
        i += 2;
    }
    if(total_sum > target_position)
    {
        cout << nums1[i - 3] << "\n";
    }
    else
    {
        //前面有的数等于目标数的下标
        cout << nums1[i - 1] << "\n";
    }
    return 0;
}
