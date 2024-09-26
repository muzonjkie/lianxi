#include <iostream>
#include <time.h>

using namespace std;

long findMinK(long x, long y, long cntx, long cnty) 
{
    long k = 0;
    long gox = 0;
    long goy = 0;
    long nice = 0;

    while (gox < cntx || goy < cnty) 
    {
        ++ k;
        if(k % (x * y) == 0)
        {
            //都不能去
            continue;
        }
        else if (k % x == 0 && goy < cnty) 
        {
            //不能去x但能去y
            ++goy;
        }
        else if (k % y == 0 && gox < cntx) 
        {
            //不能去y但能去x
            ++gox;
        }
        else
        {
            //都能去的
            ++nice;
        }
        if(gox + goy + nice == cntx + cnty )
        {
            break;
        }
    }

    return k;
}

int main()
{
    long x, y, cntx, cnty;
    cin >> x >> y >> cntx >> cnty;

    time_t start = clock();
    long k = findMinK(x, y, cntx, cnty);
    time_t end = clock();
    cout << k << endl;
    printf("用时：%f毫秒\n", (double)(end - start)/(double)1000);
    return 0;
}

