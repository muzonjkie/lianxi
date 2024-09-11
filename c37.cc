#include <iostream>

int findMinK(int x, int y, int cntx, int cnty) 
{
    int k = 0;
    int gox = 0;
    int goy = 0;
    int nice = 0;

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

int main() {
    int x, y, cntx, cnty;
    std::cin >> x >> y >> cntx >> cnty;

    int k = findMinK(x, y, cntx, cnty);
    std::cout << k << std::endl;

    return 0;
}

