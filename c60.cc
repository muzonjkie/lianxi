#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<sstream>
using namespace std;
 
 
  
 
int main()
{
    //屏幕数量，每屏展示数据个数
    size_t n, m;
    cin >> n >> m;
    //每一个元素即为一个列表
    vector<vector<int>> matrix;
    string str;
    while (getline(cin, str))
    {
        istringstream iss(str);
        int temp;
        vector<int> tmp;
        while(iss >> temp)
        {
            tmp.push_back(temp);
        }
        matrix.push_back(tmp);
    }
    //几个列表
    int list_length = matrix.size();
    //第一个列表开始
    int choose = 0;
    vector<int> nums;
    while(nums.size() < n * m)
    {
        int cnt = n;
        //从第几个列表选
        int now = choose % list_length;
        //从该列表中选cnt个若足够
        while(cnt && matrix[now].size())
        {
            nums.push_back(matrix[now].front());
            matrix[now].erase(matrix[now].begin());
            --cnt;
        }
        //要选的列表中不够选了，从其下一个列表选；若下一个列表不够继续下一个
        while(cnt)
        {
            ++ choose;
            now = choose % list_length;
            while(cnt && matrix[now].size())
            {
                nums.push_back(matrix[now].front());
                matrix[now].erase(matrix[now].begin());
                --cnt;
            }
        }
        //问题在这里，若从一个列表中选不够，到了第二个列表补够了，那下一次选是在当前列表还是再下一个
        ++choose;
    }
 
    string output_str = "";
    //第j个窗口
    for (size_t j = 0; j < n; ++j) 
    {
        //该窗口的m个
        for (size_t i = 0; i < m; ++i) 
        {
            output_str += to_string(nums[i * n + j]) + " ";
        }
    }
    //将最后一个空格去除
    cout << output_str.substr(0, output_str.size() - 1) << "\n"; 

    return 0;
}
