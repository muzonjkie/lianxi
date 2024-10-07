#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
 
 

 
int main() {
    // 输入处理
    int M, n;
    cin >> M >> n;
    double N = (double) n;
    vector<int> cars(M, 0);
    for (int i = 0; i < M; ++i)
    {
        int temp;
        cin >> temp;
        cars[i] = temp;
    }

    vector<double> dp(M, 0);
    dp[0] = N / cars[0];
    //原来只要最后一辆车走到终点的时间而不要求从第一辆车启动的时间
    for(size_t i = 1; i < cars.size(); ++i)
    {
        //能追上
        if(N / cars[i] + 1 < dp[i - 1])
        {
            dp[i] = dp[i -1] + 1;
        }
        else
        {
            //追不上
            dp[i] = N / cars[i];
        }
    }

    cout << dp[M - 1] << "\n";

	return 0;
}
