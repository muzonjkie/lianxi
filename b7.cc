#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <utility>
#include <iterator>


using namespace std;

vector< vector< pair<int, int> > > fangan;



//这几个对accumulaye没用，但正常加可以
//pair<int, int> operator+ (const pair<int, int> & lhs, const pair<int, int> & rhs)
//{
//    return {lhs.first + rhs.first, 0};
//}
//template <typename T1, typename T2>
//std::pair<T1, T2> operator+(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) {
//    return std::make_pair(lhs.first + rhs.first, 0);
//}

//可以得到目标和的所有选择，且选择的元素不同一个，就是可以相等的元素但他们不是同一个
void choose(vector<int> nums, vector< pair<int, int> > have, int start, int target)
{
    int sum = 0;
    for(auto & i : have)
    {
        sum += i.first;
    }
    if(sum == target)
    {
        fangan.push_back(have);
        return;
    }
    for(int i = start; i < (int)nums.size(); ++i)
    {
        //这个可以去重，但是有类似全排列的（应该不是真的全排列，），且需要排序
        /* if(i > start && nums[i] == nums[i - 1]) */
        /* { */
        /*     continue; */
        /* } */
        //已经选过的就不要放进去了；附加了所在数组下标的信息，所以即便值相同但数组下标不同
        //能达到已经选了的不会再选（同一个元素不会在多次里面），且不必排序
        if(find(have.begin(), have.end(), make_pair(nums[i],i)) == have.end())
        {
            have.push_back({nums[i], i});
            choose(nums, have, i + 1, target);
            have.pop_back();
        }
    }
}


int main()
{
    string line;
    vector<int> nums;
    getline(cin, line, '\n');
    istringstream iss(line);
    int temp;
    while(iss >> temp)
    {
        nums.push_back(temp);
    }

    int n;
    cin >> n;
    vector< pair<int, int>> have;
    /* sort(nums.begin(), nums.end()); */
    choose(nums, have, 0, n);

    cout << fangan.size() << "\n";
    return 0;
}



