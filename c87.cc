#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int N, M, K;
vector< vector<int> > matrix;
set<int> kthLargestSet;

// 递归函数
void backtrack(vector<int>& chosen, vector<bool>& colsUsed, int row)
{
    if (row == N) {
        // 当前组合已满，计算第K大的数
        vector<int> selected;
        for (int i = 0; i < N; ++i) 
        {
            selected.push_back(chosen[i]);
        }
        sort(selected.begin(), selected.end(), greater<int>());
        kthLargestSet.insert(selected[K - 1]); // K大的数存入集合
        return;
    }

    for (int col = 0; col < M; ++col) 
    {
        // 检查是否已使用该列
        if (!colsUsed[col]) 
        { 
            chosen[row] = matrix[row][col];
            colsUsed[col] = true;
            backtrack(chosen, colsUsed, row + 1);
            colsUsed[col] = false; // 回溯
        }
    }
}

int main() {
    // 输入 N, M, K
    cin >> N >> M >> K;
    matrix.resize(N, vector<int>(M));

    // 输入矩阵
    for (int i = 0; i < N; ++i) 
    {
        for (int j = 0; j < M; ++j)
        {
            cin >> matrix[i][j];
        }
    }

    vector<int> chosen(N);
    vector<bool> colsUsed(M, false);
    
    // 进行回溯
    backtrack(chosen, colsUsed, 0);

    // 输出第K大的数的最小值
    cout << *kthLargestSet.begin() << endl;

    return 0;
}



