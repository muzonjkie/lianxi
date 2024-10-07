#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <climits>
#include <stack>
using namespace std;
 
 
struct Fraction
{
    Fraction(int A, int B = 1)
    :up_(A)
     ,down_(B)
    {}
    int up_;
    int down_;

    Fraction operator+ (const Fraction & rhs)
    {
        //通分后
        this->up_ = this->up_ * rhs.down_ + this->down_ * rhs.up_; 
        this->down_ = this->down_ * rhs.down_;
        return *this;
    }
    Fraction operator- (const Fraction & rhs)
    {
        //通分后
        this->up_ = this->up_ * rhs.down_ - this->down_ * rhs.up_ ;
        this->down_ = this->down_ * rhs.down_;
        return *this;
    }
    Fraction operator* (const Fraction & rhs)
    {
        //通分后
        this->up_ = this->up_ * rhs.up_;
        this->down_ = this->down_ * rhs.down_;
        return *this;
    }
    Fraction operator/ (const Fraction & rhs)
    {
        //通分后
        this->up_ = this->up_ * rhs.down_;
        this->down_ = this->down_ * rhs.up_;
        return *this;
    }
};
  
//计算最大公约数
int gcd(int a, int b)
{
    while (b) 
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

// 计算最小公倍数
int lcm(int a, int b)
{
    return a * b / gcd(a, b);
} 
 
 
int main()
{
    string str;
    getline(cin, str, '\n');

    string current = "";
    //优先级，操作符
    stack< pair<int, char> > operation;
    for(size_t i = 0; i < str.size(); ++i)
    {
        if(isdigit(str[i]))
        {
            while(isdigit(str[i]))
            {
                current += str[i];
                ++i;
            }
            //抵抗++i
            --i;
            //用于区分两个数字
            current += " ";
        }
        else if('-' == str[i] || '+' == str[i] || '*' == str[i] || '/' == str[i])
        {
            if('-' == str[i] || '+' == str[i])
            {
                //优先级高于该运算符的出栈
                while(operation.size() && operation.top().first >= 1)
                {
                    current += operation.top().second;
                    operation.pop();
                }
                operation.push({1, str[i]});
            }
            else
            {
                while(operation.size() && operation.top().first >= 2)
                {
                    current += operation.top().second;
                    operation.pop();
                }
                operation.push({2, str[i]});
            }
        }
        else if('(' == str[i])
        {
            operation.push({0, str[i]});
        }
        else if(')' == str[i])
        {
            while(operation.size() && operation.top().second != '(')
            {
                current += operation.top().second;
                operation.pop();
            }
            //要把 ( 也出栈
            operation.pop();
        }
    }
    //字符串处理完后若栈中还有运算符
    while(operation.size())
    {
        current += operation.top().second;
        operation.pop();
    }

    stack<Fraction> temp_result;
    for(size_t i = 0; i < current.size(); ++i)
    {
        if(isdigit(current[i]))
        {
            string temp;
            while(isdigit(current[i]))
            {
                temp += current[i];
                ++i;
            }
            --i;
            temp_result.push(Fraction( stoi(temp) ) );
        }
        else if('-' == current[i] || '+' == current[i] || '*' == current[i] || '/' == current[i])
        {
            Fraction right = temp_result.top();
            temp_result.pop();
            Fraction left = temp_result.top();
            temp_result.pop();
            if('-' == current[i])
            {
                temp_result.push(left - right);
            }
            else if('+' == current[i])
            {
                temp_result.push(left + right);
            }
            else if('*' == current[i])
            {
                temp_result.push(left * right);
            }
            else
            {
                if(0 == right.up_)
                {
                    cout << "ERROR\n";
                    return 1;
                }
                temp_result.push(left / right);
            }
        }
        //余下的是空格不处理便是
    }
    
    Fraction result = temp_result.top();
    int temp = gcd(result.up_, result.down_); 
    result.up_ /= temp;
    result.down_ /= temp;
    if(result.up_ * result.down_ > 0)
    {
        if(abs(result.down_) == 1)
        {
            cout << abs(result.up_) << "\n";
        }
        else
        {
            cout << abs(result.up_) << "/" << abs(result.down_) << "\n";
        }
    }
    else if(result.up_ == 0)
    {
        cout << "0\n";
    }
    else
    {
        if(abs(result.down_) == 1)
        {
            cout << -abs(result.up_) << "\n";
        }
        else
        {
            cout << -abs(result.up_) << "/" << abs(result.down_) << "\n";
        }
    }


    return 0;
}
