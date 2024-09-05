#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<cmath>
#include<list>
#include <sstream>

using namespace std;
 
vector<int> split(string params_str) {
    vector<int> p;
    istringstream iss(params_str);
    int out = 0;
    while (iss >> out) {
        p.push_back(out);
    }    
    return p;
}
 
 
int validMountainCount(vector<int>& arr) {
    int result = 0;
    for(size_t i = 0; i < arr.size(); ++i)
    {
        if(0 == i && arr[i] > arr[i+1])
        {
            ++result;
        }
        else if(arr.size()-1 == i && arr[i-1] < arr[i])
        {
            ++result;
        }
        else if(arr[i-1] << arr[i] && arr[i] >> arr[i+1])
        {
            ++result;
        }
    }
    return result;
}
 
int main()
{
    //输入,此处仅为测试，考试时为leetcode模式
    string input_str;
    getline(cin, input_str);
    vector<int> arr = split(input_str);
    cout<< validMountainCount(arr);
    return 0;
}
