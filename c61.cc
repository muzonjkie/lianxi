#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
 
int main()
{
    //数字个数，要写成几行
    int count, n;
    cin >> count >> n;
    int m = 1;
    //适宜的列数
    while(n * m < count)
    {
        ++m;
    }

    vector< vector<string> > matrix(n, vector<string>(m , "*"));
    //当前处理位置
    int x = 0;
    int y = 0;
    //上界与下界
    int range_x_max = m - 1;
    int range_x_min = 0;
    int range_y_max = n - 1;
    int range_y_min = 0;
    int now = 1; 
    //目前除了偶数个的数和其开根的行都可以
    //现在完全OK了！！！我真牛犇!
    while(now <= count)
    {
        matrix[y][x] = to_string(now);
        ++now;
        if(x < range_x_max && y == range_y_min)
        {
            ++x;
            //到右边界
            if(x == range_x_max)
            {
                ++ range_y_min; 
            }
        }
        else if(y < range_y_max && x == range_x_max)
        {
            ++y;
            //到下边界
            if(y == range_y_max)
            {
                --range_x_max;
            }
        }
        else if(y == range_y_max && x > range_x_min)
        {
            --x;
            //到左边界
            if(x == range_x_min)
            {
                --range_y_max;
            }
        }
        else if(x == range_x_min && y > range_y_min)
        {
            --y;
            //到上边界
            if(y == range_y_min)
            {
                ++ range_x_min;
            }
        }
    }


    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[0].size(); ++j)
        {
            cout << matrix[i][j];
            if(j != matrix[0].size() - 1)
            {
                cout << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}
