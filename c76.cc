#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<exception> 
#include<map>
#include<cmath>
#include<unordered_map>
#include<set>
#include<climits>
using namespace std;
 
 

int count_ = 0;
//flag表示是否是A在报数
void backtrace(int x, int flag)
{
    if(x <= 7)
    {
        if(flag == 0 && 7 == x)
        {
            count_ += 1;
        }
        return;
    } 
    backtrace(x-1, flag == 1 ? 0:1);
    backtrace(x-2, flag == 1 ? 0:1);
}
    
int main() {
    // 输入处理
    int a;
    cin >> a;
    backtrace(a, 1);
    cout << count_ << "\n";
	return 0;
}
