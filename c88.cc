#include <unordered_map>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>


using namespace std;

int find_group(int man, vector< vector<int> > relations);
void change_pos(int group_now, vector<int>::iterator it, int off, vector<int> & nums, vector< vector<int> > relations);

int main()
{
    string str1, str2;
    getline(cin, str1, '\n');
    getline(cin, str2, '\n');
    vector<int> nums;
    istringstream iss1(str1);
    int temp;
    while(iss1 >> temp)
    {
        nums.push_back(temp);
    }
    //组关系
    vector< vector<int> > relations(nums.size() / 3, vector<int>());
    istringstream iss2(str2);
    int i = 0;
    int count = 0;
    while(iss2 >> temp)
    {
        //第i组
        relations[i].push_back(temp);
        ++count;
        if(count == 3)
        {
            ++i;
            count = 0;
        }
    }

    //还不是一组的三个位置的起始位置
    vector<int> nois;
    for(size_t i = 0; i < nums.size(); i += 3)
    {
        nois.push_back(i);
    }
    auto it = nois.begin();
    int result = 0;
    while(nois.size())
    {
        //都一组
        int group_one = find_group(nums[*it], relations);
        int group_two = find_group(nums[*it + 1], relations);
        int group_three = find_group(nums[*it + 2], relations);

        if(group_one == group_two && group_one == group_three) 
        {
            nois.erase(it);
            it = nois.begin();
        }
        //前两个相同组
        else if(group_one == group_two)
        {
            change_pos(group_one, it, 2, nums, relations);
            ++result;
            nois.erase(it);
            it = nois.begin();
        }
        //第一和第三同组
        else if(group_one == group_three)
        {
            change_pos(group_one, it, 1, nums, relations);
            ++result;
            nois.erase(it);
            it = nois.begin();
        }
        //第二和第三同组
        else if(group_two == group_three)
        {
            change_pos(group_two, it, 0, nums, relations);
            ++result;
            nois.erase(it);
            it = nois.begin();
        }
        //三个不同组
        else
        {
            //先不处理该组，处理到后面后该组就不用动多次了
            ++it;
            //有可能到最后一组都是互不相近的
            if(it == nois.end())
            {
                --it;
                int lack = 0;
                vector<int> member = relations[group_one];
                for(size_t i = 0; i < member.size(); ++i)
                {
                    if(member[i] == nums[*it])
                    {
                        continue;
                    }
                    lack = member[i];
                    break;
                }
                size_t index = 0;
                for(; index < nums.size(); ++index)
                {
                    if(lack == nums[index])
                    {
                        break;
                    }
                }
                //交换成员到此固定位置
                int temp = nums[*it + 1];
                nums[*it + 1] = nums[index];
                nums[index] = temp;
                ++result;
            }
        }
    }

    cout << result << "\n";
    return 0;
}


int find_group(int man, vector< vector<int> > relations)
{
    for(size_t i = 0; i < relations.size(); ++i)
    {
        for(size_t j = 0; j < relations[i].size(); ++j)
        {
            if(relations[i][j] == man)
            {
                return i;
            }
        }
    }
}


void change_pos(int group_now, vector<int>::iterator it, int off, vector<int> & nums, vector< vector<int> > relations)
{
    //得到该组所有成员的编号
    vector<int> member = relations[group_now];            
    int lack;
    //是那个编号成员不在此连续的位置
    for(size_t i = 0; i < member.size(); ++i)
    {
        //这三个位置中有哪两个位置是本组成员的
        if(member[i] == nums[*it] || member[i] == nums[*it + 1] || member[i] == nums[*it + 2])
        {
            continue;
        }
        lack = member[i];
        break;
    }
    //找到该成员所在的位置
    size_t index = 0;
    for(; index < nums.size(); ++index)
    {
        if(lack == nums[index])
        {
            break;
        }
    }
    //交换成员到此位置
    int temp = nums[*it + off];
    nums[*it + off] = nums[index];
    nums[index] = temp;
}


