#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main() {
    string inputStr;
    getline(cin, inputStr); // 读取需求工作量列表

    stringstream ss(inputStr);
    string work;
    vector<int> works; // 需求工作量列表
    while (getline(ss, work, ',')) {
        works.push_back(stoi(work));
    }

    int n; // 项目组人员数量
    cin >> n;

    // 根据工作量从大到小排序
    sort(works.begin(), works.end(), greater<int>());

    vector<int> developers(n, 0); // 开发人员当前工作量列表

    for (size_t i = 0; i < works.size(); i++) {
        // 找到当前最空闲的开发人员
        int minIndex = 0;
        for (int j = 1; j < n; j++) {
            if (developers[j] < developers[minIndex]) {
                minIndex = j;
            }
        }
        // 分配工作给最空闲的开发人员
        developers[minIndex] += works[i];
    }

    // 找到所有开发人员中工作量最大的值
    int maxWork = 0;
    for (int i = 0; i < n; i++) {
        if (developers[i] > maxWork) {
            maxWork = developers[i];
        }
    }

    cout << maxWork << endl; // 输出最快完成工作的天数

    return 0;
}

