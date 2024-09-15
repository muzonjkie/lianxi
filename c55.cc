#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
 
  
 
int main()
{

    int n;
    cin >> n;
    if(n < 3)
    {
        cout << "N\n";
    }
    else
    {
        string result = to_string(n) + "=";
        //任意一个奇数必定存在两个连续的数之和等于它
        if(n % 2 == 1)
        {
            int a = 1, b = 2;
            while(a + b != n)
            {
                ++a;
                ++b;
            }
            result += to_string(a) + "+" + to_string(b);
        }
        else
        {
            //偶数至少是三位连续的数之和才可以
            int m = 3;
            //等差求和超过
            while(m * (m + 1) / 2 <= n)
            {
                //k必须是正整数
                if ((n - m * (m - 1) / 2) % m == 0) 
                {
                    for (int i = 0; i < m; ++i)
                    {
                        //由等差数列求和公式可推导出
                        result += to_string((n - m * (m - 1) / 2) / m + i);
                        if (i != m - 1) 
                        {
                            result += "+";
                        }
                    }
                    //要最短
                    break;
                }
                m += 1;
            }
        }
        cout << result << "\n";
    }
    return 0;
}

