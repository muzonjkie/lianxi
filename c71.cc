#include<iostream>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<climits>
using namespace std;
 

 
vector<string> split_str(string params_str, string delim) {
    vector<string> p;
    while (params_str.find(delim) != string::npos) {
        int found = params_str.find(delim);
        p.push_back(params_str.substr(0, found));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(params_str);
    return p;
}
 
 
 
int main()
{
    // 元素的依赖关系
    vector<vector<int>> relation(26);
    //存在的元素为true
    vector<bool> have(26, false);
    string input_str;
    getline(cin, input_str, '\n');
    //每个元素为，如A->B
    vector<string> temp = split_str(input_str, " ");
    for(size_t i = 0; i < temp.size(); ++i)
    {
        //如：A 依赖B，将其放进A的依赖关系
        relation[ temp[i][0] - 'A'].push_back( temp[i][3] - 'A');
        have[ temp[i][0] - 'A'] = true;
        have[ temp[i][3] - 'A'] = true;
    }

    vector<int> stack_1, stack_2;
    //有几个节点
    int total_num = 0;
    for(size_t i = 0; i < have.size(); ++i)
    {
        //将存在的、无依赖关系的放进栈
        if(have[i] && ! relation[i].size())
        {
            stack_1.push_back(i);
        }
        if(have[i])
        {
            ++total_num;
        }
    }
    //已经处理了几个可以是拓扑排序的节点了
    int count = 0;
    vector<int> print;
    while(stack_1.size() || stack_2.size())
    {
        //模拟栈，将序号较小的放在栈顶，以便优先打印
        sort(stack_1.begin(), stack_1.end(), std::greater());
        while(stack_1.size())
        {
            print.push_back(stack_1.back());
            ++ count;
            int now = stack_1.back();
            //出栈
            stack_1.erase(-- stack_1.end());
            //出栈之后，将有依赖该节点的节点的依赖关系去除
            for(size_t i = 0; i < relation.size(); ++i)
            {
                //存在本元素
                if(have[i])
                {
                    for(size_t j = 0; j < relation[i].size(); ++j)
                    {
                        //有依赖关系
                        if(relation[i][j] == now)
                        {
                            relation[i].erase( relation[i].begin() + j );
                            //擦除该依赖关系后没依赖关系了，进二栈
                            if(! relation[i].size())
                            {
                                stack_2.push_back(i);
                            }
                            break;
                        }
                    }
                }
            }
        }

        //模拟栈，将序号较小的放在栈顶，以便优先打印
        sort(stack_2.begin(), stack_2.end(), std::greater());
        while(stack_2.size())
        {
            print.push_back(stack_2.back());
            ++ count;
            int now = stack_2.back();
            //出栈
            stack_2.erase(-- stack_2.end());
            //出栈之后，将有依赖该节点的节点的依赖关系去除
            for(size_t i = 0; i < relation.size(); ++i)
            {
                //存在本元素
                if(have[i])
                {
                    for(size_t j = 0; j < relation[i].size(); ++j)
                    {
                        //有依赖关系
                        if(relation[i][j] == now)
                        {
                            relation[i].erase( relation[i].begin() + j );
                            //擦除该依赖关系后没依赖关系了，进二栈
                            if(! relation[i].size())
                            {
                                stack_1.push_back(i);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    //有回路
    if(count != total_num)
    {
        cout << "有回路！\n"; 
    }
    else
    {
        string output_str = "";
        for(size_t i = 0; i < print.size(); ++i)
        {
            char temp = print[i] + 'A';
            string tmp(1, temp);
            output_str += tmp + " ";
        }

        output_str = output_str.substr(0, output_str.size() - 1);
        cout << output_str << "\n";
    }


    return 0;
}
