#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
 
  
int main()
{
    //土地的长宽
    int m, n;
    cin >> m >> n;
    //当值为1时表示有旗子
    vector<int> nums(501, 0);
    //某个数字的最大行数
    vector<int> max_row(501, 0);
    //某个数字的最大列数
    vector<int> max_col(501, 0);
    //某个数字的小行数
    vector<int> min_row(501, 502);
    //某个数字的最小列数
    vector<int> min_col(501, 502);
    
    //以上用501，旗子上的数的最大值500
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j) 
        {
            int temp ;
            cin >> temp;
            //该数存在
            nums[temp] = 1;
            max_row[temp] = max(max_row[temp], i);
            max_col[temp] = max(max_col[temp], j);
            min_row[temp] = min(min_row[temp], i);
            min_col[temp] = min(min_col[temp], j);
        }
    }
    int max_area = 0;
    for (int i = 1; i < 501; ++i)
    {
        if(nums[i] == 1)
        {
            //当某数只出现一次，最大行列就会等
            max_area = max(max_area, (max_row[i] - min_row[i] + 1) * (max_col[i] - min_col[i] + 1) );
        }
    }
    cout << max_area << "\n";
    return 0;
}
