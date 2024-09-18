#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>

using namespace std;

// 检查在 maxDays 天内是否可以完成所有需求
bool canCompleteInDays(const vector<int> & workloads, int maxDays, int numDevelopers)
{
    int currentSum = 0;
    int developersRequired = 1; // 至少需要一个开发人员

    for (int workload : workloads)
    {
        if (workload > maxDays) 
        {
            return false; // 单个需求超出最大天数
        }
        //若加此需求当前员工超出时间范围，分给下一个员工
        if (currentSum + workload > maxDays) 
        {
            ++developersRequired;
            currentSum = workload;
            //人数多了
            if (developersRequired > numDevelopers)
            {
                return false;
            }
        } 
        else
        {
            currentSum += workload;
        }
    }
    return true;
}

// 主函数
int main() {
    string line;
    getline(cin, line);
    
    vector<int> workloads;
    size_t pos = 0;
    while ((pos = line.find(' ')) != string::npos)
    {
        workloads.push_back(stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);
    }
    workloads.push_back(stoi(line));
    
    int numDevelopers;
    cin >> numDevelopers;

    int maxWorkload = *max_element(workloads.begin(), workloads.end());
    int totalWorkload = accumulate(workloads.begin(), workloads.end(), 0);

    int left = maxWorkload;
    int right = totalWorkload;
    int result = right;

    while (left <= right) 
    {
        int mid = (right + left) / 2;
        if (canCompleteInDays(workloads, mid, numDevelopers)) 
        {
            result = mid;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    cout << result << endl;
    return 0;
}

