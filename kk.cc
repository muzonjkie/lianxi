#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int main()
{
    bitset<3> a(4);
    size_t b = a.to_ulong();
    int c = 9999;
    cout << !c << "\n";
    return 0;
}

