#include <bits/stdc++.h>
 
using namespace std;
 
long x, y, cntx, cnty;
 
bool check(long k) {
    long A = k / x; // 1~k范围内x倍数的数量
    long B = k / y; // 1~k范围内y倍数的数量
    long C = k / (x * y); // 1~k范围内x*y倍数的数量
 
    return max(0L, cntx - (B - C)) + max(0L, cnty - (A - C)) <= k - A - B + C;
}
 
int main() {
    cin >> x >> y >> cntx >> cnty;
 
    // 使用此范围，实际通过率55%
//    long low = cntx + cnty;
//    long max = LONG_MAX;
 
    // 使用此范围，实际通过率可以100%
    long low = 1;
    long high = 1000000000L;
 
    while (low <= high) {
        long mid = low + (high - low) / 2;
 
        if (check(mid)) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
 
    cout << low << endl;
 
    return 0;
}
