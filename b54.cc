#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<exception> 
#include<map>
#include<cmath>
#include<unordered_map>
#include<numeric>
#include<set>
#include<climits>
#include<ctype.h>
#include<queue>
#include<stack>
#include<list>
#include<bitset>
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
 

void kmp_thought(vector<int> nums, int n);
void dier(vector<int> nums);
vector<int> computeLPS(const vector<int>& nums); 
 
int main()
{
    int n;
    cin >> n >> std::ws;
    string input;
    getline(cin, input, '\n');
    vector<int> nums = split(input);
 
    /* dier(nums); */
    cout << "----------\n";
    /* kmp_thought(nums, n); */ 
    computeLPS(nums);
    return 0;
}


//这个对于kmp来说是可以的，但解这题不对
void kmp_thought(vector<int> nums, int n)
{
    // 构造next数组
    vector<int> next(n + 1, 0);
    nums.insert(nums.begin(), 0);

    //i表示当前要算的字符的next值的位置
    int i = 1, j = 0;
    next[1] = 0;
    while (i < n)
    {
        //当j=0时，next[2] = 1，固定的；
        //若当前算的与前一个相同，next值等于前一个的加一
        if(j == 0 || nums[i] == nums[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        //否则往前找到与当前字符相同的字符
        else
        {
            j = next[j];
        }
    }

    // 最长相同前后缀长度
    int m = next[n];
    // 最小重复子串的长度
    int length = n % (n - m) == 0 ? n - m : n;

    for (int i = 1; i <= length; ++i)
    {
        cout << nums[i];
        if (1 != length - 1)
        {
            cout << " ";
        }
    }
    cout << "\n";
}

// 计算LPS数组，即最长相等前后缀
vector<int> computeLPS(const vector<int>& nums) 
{
    int n = nums.size();
    vector<int> lps(n, 0);
    int len = 0;
    int i = 1;

    while (i < n)
    {
        if (nums[i] == nums[len])
        {
            ++len;
            lps[i] = len;
            ++i;
        } 
        else
        {
            if (len != 0) 
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                ++i;
            }
        }
    }
           int m = lps[n-1];
        // 最小重复子串的长度
        int length = n % (n - m) == 0 ? n - m : n;

        if (length < n) 
        {
            cout << "可以\n";
        }
        else
        {
            cout << "不可以\n";
        }
    return lps;
}

void dier(vector<int> nums)
{
    string str = "";
    for(size_t i = 0; i < nums.size(); ++i)
    {
        str += to_string(nums[i]);
    }

    string dstr = str + str;
    int pos = dstr.find(str, 1);
    if(pos < (int)str.size())
    {
        string out_str = "";
        for(int i = 0; i < pos; ++i)
        {
            out_str += to_string(nums[i]) + " ";
        }
        if(out_str.size())
        {
            out_str = out_str.substr(0, out_str.size() - 1);
        }
        cout << out_str << "\n";
    }
    else
    {
        string out_str = "";
        for(size_t i = 0; i < nums.size(); ++i)
        {
            out_str += to_string(nums[i]) + " ";
        }
        if(out_str.size())
        {
            out_str = out_str.substr(0, out_str.size() - 1);
        }
        cout << out_str << "\n";
    }
}

