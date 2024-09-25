#include <iostream>
#include <string>
#include <vector>

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


void kmp(vector<int> nums, vector<int> model);


int main()
{
    string input1, input2;
    getline(cin, input1, '\n');
    getline(cin, input2, '\n');
    vector<int> nums = split(input1);
    vector<int> model = split(input2);
    kmp(nums, model); 
    return 0;
}


void kmp(vector<int> nums, vector<int> model)
{
    string str_nums = "";
    for(size_t i = 0; i < nums.size(); ++i)
    {
        str_nums += to_string(nums[i]);
    }

    string str_model = "";
    for(size_t i = 0; i < model.size(); ++i)
    {
        str_model += to_string(model[i]);
    }

    // 构造next数组
    vector<int> next(model.size() + 1, 0);

    //i表示当前要算的字符的next值的位置
    size_t i = 1, j = 0;
    next[1] = 0;
    while (i < str_model.size())
    {
        //当j=0时，next[2] = 1，固定的；
        //若当前算的与前一个相同，next值等于前一个的加一
        if(j == 0 || str_model[i] == str_model[j])
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

    i = 1, j = 1;
    //为从一开始就都给零位置搞了东西
    str_nums.insert(str_nums.begin(), ' ');
    str_model.insert(str_model.begin(), ' ');
    while(i < str_nums.size() && j < str_model.size())
    {
        if(j == 0 || str_nums[i] == str_model[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = next[j];
        }
    }
    if(j == str_model.size())
    {
        string str = "";
        str = str_nums.substr(i - str_model.size() + 1);
        cout << str << "\n";
    }
    else
    {
        cout << "匹配不成功\n";
    }
}
