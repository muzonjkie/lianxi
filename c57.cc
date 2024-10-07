#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<sstream>
using namespace std;
 
  
 
//这是错的
//错错错，是我的错，是我……………………
int main()
{
    vector<int> nums;
    int temp;
    string str;
    getline(cin, str, '\n');
    istringstream iss(str);
    while(iss >> temp)
    {
        nums.push_back(temp);
    }
 
    //可以用set去重，但我要用位图
    long long* bitmap = new long long[1 << 7]{0};

    int pos, bit_pos;
    for(size_t i = 0; i < nums.size(); ++i)
    {
        //数组的每一个元素所占的字节数为8，64个比特
        pos = nums[i] / 64;
        //在该元素中的第几个比特
        bit_pos = nums[i] % 64;
        if((long long)1 << bit_pos & bitmap[pos])
        {
            //已经出现过
        }
        else
        {
            //未出现过
            bitmap[pos] |= (long long)1 << bit_pos;
        }
    }
    int man = 0;
    for(size_t i = 0; i < 1000; ++i)
    {
        int pos = i / 64;
        int bit_pos = i % 64;
        if((long long)1 << bit_pos & bitmap[pos])
        {
            //已经出现过
            man += (i + 1);
        }
    }
 
    cout << man << "\n";
    delete [] bitmap;
    return 0;
}
