#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<cmath>
using namespace std;
 

int main()
{
    //宝石数量
    int count;
    cin >> count;
    vector<int> gems;
    for (int i = 0; i < count; ++i) {
        int a;
        cin >> a;
        gems.push_back(a);
    }
    //有多少钱
    int value;
    cin >> value;
 
    size_t length = 0;
    int real_used = 0;
    for(size_t i = 0; i < gems.size(); ++i)
    {
        //先选一个宝石，从此开始
        int used = gems[i];
        //直到钱不够用
        for(size_t j = i + 1; j < gems.size(); ++j)
        {
            //钱够用
            if(used + gems[j] <= value)
            {
                used += gems[j];
                if(length < j - i + 1)
                {
                    real_used = used;
                    length =  j - i + 1;
                }
            }
            else
            {
                //该序列结束，换另一个序列
                break;
            }
        }
        //不可能存在更长序列
        if(gems.size() - i < length)
        {
            break;
        }
    }
    
    cout << "buyed " << length << " used " << real_used << endl;
    return 0;
}
