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
using namespace std;
 

  
int main()
{
    int count;
    cin >> count;
    vector<int> money;
    //0处不用
    money.push_back(0);
    for (int i = 1; i <= count; ++i)
    {
        int a;
        cin >> a;
        money.push_back(a);
    }
    //family relationship
    map<int, int> relations;
    for (int i = 1; i <= count; ++i)
    {
        //本身的钱
        relations[i] =  money[i];
    }
    for (int i = 1; i < count; ++i)
    {
        int a ,b;
        cin >> a >> b;
        //小家庭其它成员的钱
        relations[a] += money[b];
    }
 
    int max_val= 0;
    for (int i = 1; i <= count; ++i)
    {
        max_val = max(max_val,relations[i] ) ;
    }
    cout << max_val;

    return 0;
}
