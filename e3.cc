#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;



int main()
{
    string input_str;
    getline(cin, input_str, '\n');
    int count = 0;
    string result = "";
    for (size_t i = 0; i < input_str.size(); ++i)
    {
        if (input_str[i] == '[') 
        {
            ++count;
        }
        else if (input_str[i] == ']') 
        {
            --count;
        }
        //使用count来判断是否在方括号内部，在内部的不做替换
        if (count == 0) 
        {
            if (input_str[i] == '_' && (i == 0 || input_str[i - 1] != '\\')) 
            {
                result += "(^|$|[,+])";
            }
            else
            {
                result += input_str[i];
            }
        }
        else
        {
            result += input_str[i];
        }
    }
    cout << result << "\n";
    return 0;
}
