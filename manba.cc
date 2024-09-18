#include <iostream>
#include <vector>
#include <climits>

using  namespace std;

int total = 0;
/* vector<int> possible; */
int min_ =INT_MAX; 

void dfs(const std::vector<int>& arr, std::vector<int>& path, int index) {
    // 输出当前路径
    int temp_total = 0;
    for (int num : path) {
        temp_total += num;
    }
    if(abs(total - 3 * temp_total) < min_)
    {
        min_ = abs(total - 3 * temp_total);
        /* possible.push_back(min_); */
    }

    // 遍历从当前索引到数组末尾的所有元素
    for (size_t i = index; i < arr.size(); ++i) {
        // 选择当前元素
        path.push_back(arr[i]);
        // 递归调用 DFS，继续选择下一个元素
        dfs(arr, path, i + 1);
        // 撤销选择，回溯
        path.pop_back();
    }
}

void findSubsets(const std::vector<int>& arr) {
    std::vector<int> path;
    dfs(arr, path, 0);
}

int main() {
    // 示例数组
    std::vector<int> arr = {1, 2, 3};
    for(int & i : arr)
    {
        total += i;
    }
    findSubsets(arr);
    cout << min_ << "\n";
    return 0;
}

