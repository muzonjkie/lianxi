#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<cmath>
#include<set>
#include<climits>
#include<ctype.h>
#include<queue>
using namespace std;
 
vector<int> split(string params_str, string split_char) {
    vector<int> p;
    while (params_str.find(split_char) != string::npos) {
        int found = params_str.find(split_char);
        p.push_back(stoi(params_str.substr(0, found)));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(stoi(params_str));
    return p;
}
 

bool check(vector<int> cur_map, vector<int> target_map) {
    for(int i=0;i<1000;i++){
        if (cur_map[i] < target_map[i]) {
            return false;
        }
    }
    return true;
}
 
int main()
{
    int n,m;
    cin >> n >> m;
 
    vector< vector<int> > matrix(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
          int temp;
          cin >> temp;
          matrix[i][j] = temp;
        }
    }
 
    int k;
    cin >> k;
    set<int> temp_nums;
    for (int i = 0; i < k; ++i)
    {
      int temp;
      cin >> temp;
      temp_nums.insert(temp);
    }
    //当对应位置为1时说明目标矩阵中出现了目标数
    vector<int> target_map(1000, 0);

    /* //有序且无重复 */
    /* vector<int> nums(temp_nums.begin(), temp_nums.end()); */
    /* //标记目标数有哪些 */
    /* for(size_t i = 0; i < nums.size(); ++i) */
    /* { */
    /*     target_map[ nums[i] ] = 1; */
    /* } */

    for(auto & i : temp_nums)
    {
        target_map[i] = 1;
    }
    
    //若等于上面那个，就完成
    vector<int> cur_count_map(1000, 0);
    int width = -1;
    for(size_t i = 0; i < matrix[0].size(); ++i)
    {
        for(size_t j = 0; j < matrix.size(); ++j)
        {
            //存在于数中
            if(temp_nums.count(matrix[j][i]))
            {
                cur_count_map[ matrix[j][i] ] = 1;
            }
        }
        if(cur_count_map == target_map)
        {
            width = i + 1;
            break;
        }
    }

    cout << width << "\n";
    return 0;
}
