#include<iostream>
#include <utility>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<numeric>
#include<set>
#include <sstream>

using namespace std;
 
 
  
 
 

 
namespace std
{
    template<>
        struct less< pair<string, int> >
    {
        bool operator() (const pair<string, int> & lhs, const pair<string, int> & rhs) const
        {
            if(lhs.second == rhs.second)
            {
                return lhs.first < rhs.first;
            }
            return lhs.first > rhs.first;
        }

    };

    template<>
        struct less< pair<string, vector<int> > >
        {
            bool operator() (const pair<string, vector<int> > & lhs, const pair<string, vector<int> > & rhs) const
            {
                //得到标志位
                int flag = lhs.second[lhs.second.size() - 1];
                if(lhs.second[flag] == rhs.second[flag])
                {
                    return lhs.first < rhs.first;
                }
                return lhs.second[flag] < rhs.second[flag];
            }
        };
}


int main()
{
    //学生数，科目数
    int n, m;
    cin >> n >> m;
    cin >> std::ws;
    string count_str;
 
    //按总分排
    vector<pair<string, int> > all_student;
    //按某科目排
    vector<pair<string, vector<int> > > all_student2;
 
    string subject_str;
    getline(cin, subject_str);
    istringstream iss(subject_str);
    vector<string> subject;
    string temp;
    while(iss >> temp)
    {
        subject.push_back(temp);
        temp.clear();
    }
    cin >> std::ws;
 
    for (int i = 0; i < n; ++i)
    {
        string input_str;
        getline(cin, input_str);
        cin >> std::ws;
        istringstream iss(input_str);
        string name;
        iss >> name;
        int temp;
        int total_score = 0;
        vector<int> score;
        while(iss >> temp)
        {
            score.push_back(temp);
            total_score += temp;
        }
        all_student.push_back({name, total_score});
        all_student2.push_back({name, score});
    }

    //排序的科目，若有
    string input_str;
    getline(cin, input_str);
    istringstream iss2(input_str);
    string condition;
    iss2 >> condition;
    int flag = -1;
    for(size_t i = 0 ; i < subject.size(); ++i)
    {
        if(subject[i] == condition)
        {
            flag = i;
            break;
        }
    }

    if(-1 != flag)
    {
        //给每个vector最后加上标志，代表按vector的哪科分数排序
        for(size_t i = 0; i < all_student2.size(); ++i)
        {
            all_student2[i].second.push_back(flag);
        }
        //重载两次less竟不能识别吗？居然还要显式实例化
        sort(all_student2.begin(), all_student2.end(), std::less< pair<string, vector<int> > >());
        for(size_t i = 0; i < all_student2.size(); ++i)
        {
            cout << all_student2[i].first << " " << all_student2[i].second[flag] << "\n";
        }
    }
    else
    {
        //按总分
        sort(all_student.begin(), all_student.end(), std::less< pair<string, int> >());
        for(size_t i = 0; i < all_student.size(); ++i)
        {
            cout << all_student[i].first << " " << all_student[i].second << "\n";
        }
    }
 
    return 0;
}



 
