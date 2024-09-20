#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <iostream>
#include <stack>


#define MAX 99999
#define M 2000

using namespace std;

typedef struct {
    int weight;				//存放权值 
    int parent;
    int lchild,rchild;
}HTnode;		

void HTnodeCreat(HTnode ht[], int weight[], int n);


int main()
{
    int N;
    cin >> N;
    int weight[N];
    for(int i = 0; i < N; ++i)
    {
        int temp;
        cin >> temp;
        weight[i] = temp;
    }
    HTnode ht[M];		
    HTnodeCreat(ht, weight, N);
    return 0;
} 
void HTnodeCreat(HTnode ht[], int weight[], int n)
{
    for(int i = 1; i <= n; ++i)
    {
        //对节点初始化，不用0处，因为会与其他数组产生逻辑错误；无法区分谁是谁的谁 
        ht[i].weight = weight[i-1];		
        ht[i].parent = 0;
        ht[i].lchild = ht[i].rchild = 0;		
    }
    //最大节点数 
    int m = 2 * n - 1;					
    for(int i = n + 1; i <= m; ++i)
    {			
        //后续存放由叶子节点合成的新节点 
        ht[i].weight = 0;
        ht[i].parent = 0;
        ht[i].lchild = ht[i].rchild = 0;		
    }

    int s1, s2, min1, min2;
    for(int i = n + 1; i <= m; ++i)
    {
        //初始为极大值 
        min1 = MAX, min2 = MAX;					
        s1 = s2 = 0;
        //从所有节点中选出最小的两个 
        for(int j = 1; j <= i - 1; ++j)
        {								
            //父节点为零则说明还没有加入树中 
            if(ht[j].parent == 0)
            {						
                //min1为选出的最小那个，min2比它稍大 
                if(ht[j].weight < min1)
                {
                    min2 = min1;								
                    //s1记录是哪个节点取得最小值，此处若找到比min1还小的值就把原来min1的编号给s2 
                    s2 = s1;  	
                    min1 = ht[j].weight;
                    //然后再把找到的节点编号赋给s1 
                    s1 = j;
                }			
                else if(ht[j].weight < min2)
                {				
                    //若找到了min1的值后续则在此处寻找min2的值；为剩余的里面寻找 
                    min2 = ht[j].weight;
                    s2 = j;	
                }
            }
        }
        ht[i].weight = ht[s1].weight + ht[s2].weight;
        //s1较小作为左孩子 
        ht[i].lchild = s1;				
        ht[i].rchild = s2;				
        //从叶子结点挑选出来组成新节点 
        ht[s1].parent = i;				
        ht[s2].parent = i;
    }
    //根节点
    int root = m;
    string output_str = "";
    int T = root;
    stack<int> stack_;
    while(T || stack_.size())
    {
        if(T != 0)
        {
            stack_.push(T);
            T = ht[T].lchild;
        }
        else
        {
            T = stack_.top();
            stack_.pop();
            output_str += to_string(ht[T].weight) + " ";
            T = ht[T].rchild;
        }
    }
    if(output_str.size())
    {
        output_str = output_str.substr(0, output_str.size() - 1);
        cout << output_str << "\n";
    }
}
