#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#define maxsize 10
#include <time.h>

using namespace std;



struct ListNode 
{
    int val;
    struct ListNode* next;
    ListNode(int x) 
        :val(x)
         ,next(nullptr) 
    {}
};

ListNode* Merge(ListNode* left, ListNode* right);


//int main()
//{
//    int i;
//    //	int list[maxsize]={35,32,6,13,22,28,31,20,23,18};
//    srand((unsigned)time(0));
//    int list[maxsize];
//    for (i = 0; i < maxsize; i++)
//    {
//        list[i] = rand() % 100 + 1;
//    }
//    time_t start = clock();
//    Mergesort(list, 0, maxsize - 1);
//    time_t end = clock();
//    printf("用时%fs\n", (double)(end - start) / CLOCKS_PER_SEC);
//    return 0;
//}





ListNode* Merge(ListNode* left, ListNode* right)
{
    if(left == nullptr)
    {
        return right;
    }
    if(right == nullptr)
    {
        return left;
    }
    ListNode* res = new ListNode(0);
    ListNode* now = res;
    while(left && right)
    {
        if(left->val < right->val)
        {
            now->next = left;
            now = left;
            left = left->next;
        }
        else if(left->val > right->val)
        {
            now->next = right;
            now = right;
            right = right->next;
        }
        else
        {
            now->next = left;
            now = left;
            left = left->next;
            now->next = right;
            now = right;
            right = right->next;
        }
    }
    //出来至少一个为空
    now->next = left ? left : right;
    ListNode* result = res->next;
    free(res);
    return result;
}

ListNode* Mergesort(vector<ListNode*> lists, int low, int high)
{
    if (low < high)
    { // 划分到最小一段只有一个元素
        int mid = (low + high) / 2;
        ListNode* left = Mergesort(lists, low, mid);
        ListNode* right = Mergesort(lists, mid + 1, high);
        return Merge(left, right);
    }
    else if(low == high)
    {
        return lists[low];
    }
    else
    {
        return nullptr;
    }
}
