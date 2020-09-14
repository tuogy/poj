#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <climits>
#include <bitset>
#include <functional>

#ifdef __APPLE__
FILE *__fp = fopen("__sample.in", "r");
#define scanf(...) fscanf(__fp, __VA_ARGS__)
#define cin fin
std::ifstream cin("__sample.in");
#endif

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
const int INT_INF = 0x3f3f3f3f, INT_NINF = 0xc0c0c0c0;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

const int mxn = 10001;
bool isprime[mxn];
int primes[mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(isprime, true, sizeof(isprime));
    int nprimes = 0;
    for (int p = 2; p < mxn; p++) {
        if (!isprime[p]) continue;
        primes[nprimes++] = p;
        for (int q = p * p; q < mxn; q += p) isprime[q] = false;
    }
    int target, tot;
    while (scanf("%d", &target), target) {
        tot = 0;
        for (int sum = 0, l = 0, r = 0; ; sum -= primes[l++]) {
            while (r < nprimes && sum < target) sum += primes[r++];
            if (sum < target) break;
            else if (sum == target) tot++;
        }
        printf("%d\n", tot);
    }


    return 0;
}