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
#define cin fin
std::ifstream cin("__sample.in");
#endif

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
const int INT_INF = 0x3f3f3f3f;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

int nums[7];

int solve() {
    int ret = 0;
    ret += nums[6];
    ret += nums[5]; nums[1] = max(0, nums[1] - 11 * nums[5]);
    ret += nums[4]; 
    if (nums[2] >= 5 * nums[4]) nums[2] -= 5 * nums[4];
    else {
        int slots = (5 * nums[4] - nums[2]) << 2;
        nums[1] = max(0, nums[1] - slots);
        nums[2] = 0; 
    }
    ret += nums[3] / 4, nums[3] %= 4;
    int remove2[] = {0, 5, 3, 1};
    if (nums[3] > 0) {
        ret++;
        int box2 = min(remove2[nums[3]], nums[2]);
        int slots = 36 - 9 * nums[3] - box2 * 4;
        nums[2] -= box2;
        nums[1] = max(0, nums[1] - slots);
    }
    ret += nums[2] / 9, nums[2] %= 9;
    if (nums[2] > 0) {
        ret++; 
        int slots = 36 - nums[2] * 4;
        nums[1] = max(0, nums[1] - slots);
    }
    ret += nums[1] / 36, nums[1] %= 36;
    if (nums[1] > 0) ret++;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int ks = 0;
    while (true) {
        for (int i = 0; i < 6; i++) cin >> nums[i + 1];
        int ret = solve();
        if (ret == 0) break;
        else {
            if (ks) cout << endl;
            ks++;
            cout << ret;
        }
    }

    return 0;
}