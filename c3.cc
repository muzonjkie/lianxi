#include<iostream>
#include<vector>
#include<stdlib.h>
#include<string.h>
#include <string>
#include <ctype.h>
#include<cmath>
using namespace std;
 
 
 
// 判断字符是否为小写字母
bool isLower(char ch)
{
	return ch >= 'a' && ch <= 'z';
}
 
// 判断字符是否为大写字母
bool isUpper(char ch)
{
	return ch >= 'A' && ch <= 'Z';
}
 
// 判断字符是否为数字
bool isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}
 
void  handle(string str)
{
    int contains_big_char = 0;
    int contains_small_char = 0;
    int contains_number = 0;
    int contains_special_char = 0;
    string passwd = "";
    for(size_t i = 0; i <str.size(); ++i)
    {
        if(i>=str.size() - 1)
        {
            if (contains_number && contains_small_char && contains_big_char && contains_special_char && passwd.size() >= 7) 
            {
                cout<<passwd + ",true";
            } else 
            {
                cout<<passwd + ",false";
            }
            break;
        }
        else 
        {
            if (str[i] != '<') 
            {
                passwd += str[i];
                if (isDigit(str[i] )) 
                {
                   ++ contains_number;
                }
                else if (isLower(str[i] )) 
                {
                    ++ contains_small_char;
                }
                else if (isUpper(str[i] )) 
                {
                    ++ contains_big_char;
                }
                else if (! isspace(str[i]) )
                {
                   ++ contains_special_char;
                }
            } 
            else 
            {
                if(passwd.size())
                {
                    passwd.pop_back();
                }
            }
        }
    }
}
 
int main()
{
    string str;
    getline(cin, str);
    handle(str);
 
    return 0;
}
