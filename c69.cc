#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<climits>
using namespace std;
 
vector<int> split(string input_str, string delim)
{
    vector<int> v;
    while (input_str.find(delim) != string::npos) 
    {
        int found = input_str.find(delim);
        v.push_back(stoi(input_str.substr(0, found)));
        input_str = input_str.substr(found + 1);
    }    
    v.push_back(stoi(input_str));
    return v;
}
 

 
 
int main() {
    // 输入处理
    string input1, input2;
    getline(cin, input1, '\n');
    getline(cin, input2, '\n');
    vector<int> nums = split(input1, " ");
    vector<int> target_nums = split(input2, " ");
 
    vector<int> arr(201, INT_MAX);
    int left = 0;
    int right = 0;
    int target_pos = 0;
 
    string result = "";
    size_t i = 0;
    while(i < nums.size())
    {
        //放进一个球
        arr[right] = nums[i];
        ++ right;
        //有球；放一次尝试拿一次
        while (left < right)
        {
            //优先左边取当只有一个符合的时候
            if (arr[left] == target_nums[target_pos]) 
            {
                result += "L";
                left += 1;
                target_pos += 1;
                continue;
            }
            else if (arr[right-1] == target_nums[target_pos])
            {
                result += "R";
                right -= 1;
                target_pos += 1;
                continue;
            } 
            //每次来球，若能拿一个再试试拿下一个，一个都拿不了到这
            break;
        }
        ++i;
    }
    //若存在取出序列，则left等于right，不然里边还有球未取出
    if (left != right) 
    {
      cout << "NO\n";
    }
    else
    {
      cout << result << "\n";
    }
 
	return 0;
}
