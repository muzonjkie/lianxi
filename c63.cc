#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<string>
#include<climits>
using namespace std;

int minimumDifference(vector<int> & a, const vector<int> & b);
void genSubsets(vector<int> & nums, size_t start, vector< vector<int> > & subs); 


vector<int> split(string str, string delim)
{
    vector<int> res;
    while(str.find(delim) != string::npos)
    {
        int pos = str.find(delim);
        string tmp = str.substr(0, pos);
        res.push_back(stoi(tmp));
        str = str.substr(pos + 1);
    }
    res.push_back(stoi(str));
    return res;
}



int main() {
    //输入
    vector<int> a, b;
    string one, two;
    getline(cin, one, '\n');
    getline(cin, two, '\n');
    a = split(one, " ");
    b = split(two, " ");
    cout << "最优数量：" << minimumDifference(a, b) << "\n";

    return 0;
}



int minimumDifference(vector<int> & a, const vector<int> & b)
{
    vector< vector<int> > possiable_a;
    genSubsets(a, 0, possiable_a);
    int max_ = 0;
    int possiable = 0;
    for(size_t i = 0; i < possiable_a.size(); ++i)
    {
        int have = 0;
        for(size_t j = 0; j < possiable_a[i].size(); ++j)
        {
            if(possiable_a[i][j] > b[j])
            {
                ++have;
            }
        }
        if(have > max_)
        {
            max_ = have;
            possiable = 1;
        }
        else if (have == max_)
        {
            ++ possiable;
        }
    }
    return possiable;
}

void genSubsets(vector<int> & nums, size_t start, vector< vector<int> > & subs) 
{
    if (start == nums.size())
    {
        bool flag = true;
        //去重
        for(size_t j = 0; j < subs.size(); ++j)
        {
            if(subs[j] == nums)
            {
                flag = false;
                break;
            }
        }
        if(flag)
        {
            subs.push_back(nums);
        }
        return;
    }
    /*第一步就是在第一个位置取遍所有的元素
      第二步就是按照第一步处理方式递归求解剩下的元素*/
    for (size_t i = start; i < nums.size(); ++i)
    {
        //与下一个换
        swap(nums[start], nums[i]);
        //将下一个位置分别和后面的元素再交换
        genSubsets(nums, start + 1, subs);
        //换了之后要换回来，然后再跟下下个换
        swap(nums[start], nums[i]);
    }
}
