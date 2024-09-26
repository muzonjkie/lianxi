#include <iostream>
#include <vector>
using namespace std;

vector<int> split(string params_str) {
    vector<int> p;
    while (params_str.find(" ") != string::npos) {
        int found = params_str.find(" ");
        p.push_back(stoi(params_str.substr(0, found)));
        params_str = params_str.substr(found + 1);
    }    
    p.push_back(stoi(params_str));
    return p;
}




int main()
{
    string input_str1, input_str2, input_str3, input_str4;
    getline(cin, input_str1, '\n');
    getline(cin, input_str2, '\n');
    getline(cin, input_str3, '\n');
    getline(cin, input_str4, '\n');
    vector<int> params = split(input_str1);
    //可投资产品
    int m = params[0];
    //拥有资金
    int n = params[1];
    //可接受的总风险
    int x = params[2];
    //每项产品的投资回报率（整数）
    vector<int> line2 = split(input_str2);
    //每项产品的投资风险
    vector<int> line3 = split(input_str3);
    //每项产品能投的最大额度
    vector<int> line4 = split(input_str4);

    //PS:最多只能投资两种产品

    //选一个用
    int target = -1;
    int max_value = 0;
    vector<int> investI(m, 0);
    //选两个用
    int target1 = -1, target2 = -1;
    int max_worth = 0;
    vector<int> investII(m, 0);

    for(int i = 0; i < m; ++i)
    {
        //确保产品的风险小于可接受风险
        if(line3[i] <= x)
        {
            //选一种
            //拥有资金少于该产品的最大可投资额
            if(n <= line4[i])
            {
                int temp = n * line2[i];
                if(temp > max_value)
                {
                    max_value = temp;
                    target = i;
                }
            }
            else
            {
                int temp = line4[i] * line2[i];
                if(temp > max_value)
                {
                    max_value = temp;
                    target = i;
                }
            }//end of 选一种


            //选两种的第二种
            //这里当i = m -1 时，j已不满足也没问题，因为有只选一种的兜底
            for(int j = i + 1; j < m; ++j)
            {
                //确保产品总风险合适
                if(line3[i] + line3[j] <= x)
                {
                    //计算两种产品各自投资多少获益较多
                    if(n >= line4[i] + line4[j])
                    {
                        //各按最大投
                        if(line2[i] * line4[i] + line2[j] * line4[j] > max_worth)
                        {
                            max_worth = line2[i] * line4[i] + line2[j] * line4[j];
                            target1 = i;
                            target2 = j;
                            //投资
                            investII[i] = line4[i];
                            investII[j] = line4[j];
                        }
                        continue;
                    }
                    //分别投多少合适，取小于n保证至少也投了另一产品
                    for(int a = 1, b = n - a; a < n; ++a, b = n -a)
                    {
                        if(a <= line4[i] && b <= line4[j])
                        {
                            if(line2[i] * a + line2[j] * b > max_worth)
                            {
                                max_worth = line2[i] * a + line2[j] * b;
                                target1 = i;
                                target2 = j;
                                //投资
                                investII[i] = a;
                                investII[j] = b;
                            }
                        }
                    }
                }
            }// end of 选两种的第二种
        }
    }

    //对于只选一种
    //除非每款单产品的风险都大于可接受风险（那这题就不用写了）
    if(target != -1)
    {
        investI[target] = n > line4[target] ? line4[target] : n;
    }

    //对于选两种，清除过程中的遗留的过程信息
    //除非每两两组合产品的风险大于可接受风险（那这题就不用写了）
    if(target1 != -1 && target2 != -1)
    {
        for(size_t k = 0; k < investII.size(); ++k)
        {
            if((int)k == target1 || (int)k == target2)
            {
                continue;
            }
            investII[k] = 0;
        }
    }


    //优先投两种；当然只投一种中会有满足的相同收益，这里只留一个序列
    //当然投两种也会有满足的相同收益，这里也只留一个序列
    if(max_value > max_worth)
    {
        for(size_t i = 0; i < investI.size(); ++i)
        {
            cout << investI[i];
            if(i != investI.size() - 1)
            {
                cout << " ";
            }
        }
    }
    else
    {
        for(size_t i = 0; i < investII.size(); ++i)
        {
            cout << investII[i];
            if(i != investII.size() - 1)
            {
                cout << " ";
            }
        }
    }
    cout << "\n";

    return 0;
}
