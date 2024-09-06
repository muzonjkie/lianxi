#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include <iostream>
#include <vector>
#include <queue>


using namespace std;

typedef struct BiTree{
    int value;
    struct BiTree *lchild, *mchild, *rchild;
}BiTree; 


BiTree* BST_Insert(BiTree* T, vector<int> array_);
int Bidepth(BiTree* T);

int main()
{
    BiTree* T = nullptr;
    int n;
    cin >> n;
    vector<int> arr;
    for(int i = 0; i < n; ++i)
    {
        int tmp;
        cin >> tmp;
        arr.push_back(tmp);
    }

    T = BST_Insert(T, arr);
    int res = Bidepth(T);
    cout << res << "\n";

    return 0;	
} 



BiTree* BST_Insert(BiTree* T, vector<int> array_)
{
    size_t i = 0;
    if(nullptr == T)
    {
        //第一个元素作为根节点 
        T = (BiTree*)malloc(sizeof(BiTree));
        T->value = array_[0];									
        T->lchild = nullptr;	
        T->mchild = nullptr;	
        T->rchild = nullptr;	
        ++i;
    }
    
    BiTree *p = T, *s = nullptr, *q = nullptr; 
    for(; i < array_.size(); ++i)
    {
        s = (BiTree*)malloc( sizeof(BiTree) );
        s->lchild = nullptr;
        s->mchild = nullptr;
        s->rchild = nullptr;
        s->value = array_[i];	
        while(p != nullptr)
        {
            //任有一个成立则寻找其插入位置
            q = p;													 
            if(s->value < p->value - 500)	
            {
                //小往左 
                p = p->lchild;	
            }
            else if(s->value > p->value + 500)
            {
                //大往右 	
                p = p->rchild;	
            }
            else 
            {
                p = p->mchild;
            }
        }					
        //则已经找到待插入位置的父节点 
        if(s->value < q->value - 500)
        {
            q->lchild = s; 
        }
        else if(s->value > q->value + 500) 
        {
            q->rchild = s;
        }
        else
        {
            q->mchild = s;
        }

       //next time 
        p = T;
    }
    return T; 				//只有全部建立成功此树根节点才返回 
} 


int Bidepth(BiTree* T)
{
	if(nullptr == T)    
    {
        return 0;
    } 
	else
    {
        queue<BiTree*> queue_;
		BiTree* last = T;
        int level=0;
        queue_.push(T);
		while(queue_.size())
        {
			T = queue_.front();
            queue_.pop();
			if(T->lchild)
            {
                queue_.push(T->lchild);
            }
            if(T->mchild)
            {
                queue_.push(T->mchild);
            }
            if(T->rchild)
            {
                queue_.push(T->rchild);
            }
			if(T == last)
            {		
                //出队到本层最后一个节点 
				++ level;
				last = queue_.back();			//更新本层最后一个节点 
			}					
		}
		return level;
	}
 } 


