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
const ll LLONG_INF = 0x7f7f7f7f7f7f7f7fLL, LLONG_NINF = 0x8080808080808080LL;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

struct wall {
    ll pos, s, e;
    int id;
};

struct bird {
    ll x, y;
    int id;
};

bool lt_wall(const wall& left, const wall& right) { return left.pos < right.pos; }
bool lt_bird_x(const bird& left, const bird& right) { return left.x < right.x; }
bool lt_bird_y(const bird& left, const bird& right) { return left.y < right.y; }

const int mxn = 100000;
wall vwall[mxn], hwall[mxn];
bird birds[mxn];
int N, M, n_vw, n_hw;
int wall_hit[mxn], bird_hit_wall_id[mxn];
ll bird_hit_d[mxn];
ll xs[mxn * 5], ys[mxn * 5];
ll rmq[mxn * 10];
int rmq_id[mxn * 10];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll x1, y1, x2, y2;
    scanf("%d%d", &N, &M);

    n_vw = n_hw = 0;
    for (int i = 0; i < N; i++) {
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        if (x1 == x2) {
            wall w;
            w.pos = x1, w.s = min(y1, y2), w.e = max(y1, y2), w.id = i;
            vwall[n_vw] = w, n_vw++;

            wall ws, we;
            ws.pos = w.s, ws.s = x1, ws.e = x1, ws.id = i;
            we.pos = w.e, we.s = x1, we.e = x1, we.id = i;
            hwall[n_hw] = ws, n_hw++;
            hwall[n_hw] = we, n_hw++;
        }
        if (y1 == y2) {
            wall w;
            w.pos = y1, w.s = min(x1, x2), w.e = max(x1, x2), w.id = i;
            hwall[n_hw] = w, n_hw++;

            wall ws, we;
            ws.pos = w.s, ws.s = y1, ws.e = y1, ws.id = i;
            we.pos = w.e, we.s = y1, we.e = y1, we.id = i;
            vwall[n_vw] = ws, n_vw++;
            vwall[n_vw] = we, n_vw++;
        }
    }
    for (int i = 0; i < M; i++) {
        scanf("%lld%lld", &birds[i].x, &birds[i].y);
        birds[i].id = i;
    }

    // compress
    int ixs = 0, iys = 0;
    for (int i = 0; i < n_hw; i++) {
        xs[ixs++] = hwall[i].s;
        xs[ixs++] = hwall[i].e;
    }
    for (int i = 0; i < n_vw; i++) {
        ys[iys++] = vwall[i].s;
        ys[iys++] = vwall[i].e;
    }
    for (int i = 0; i < M; i++) xs[ixs++] = birds[i].x, ys[iys++] = birds[i].y;
    sort(xs, xs + ixs); 
    sort(ys, ys + iys);
    int nxs = unique(xs, xs + ixs) - xs;
    int nys = unique(ys, ys + iys) - ys;

    // initilize
    memset(wall_hit, 0, N * sizeof(int));
    memset(bird_hit_d, 0x7f, M * sizeof(ll));
    memset(bird_hit_wall_id, -1, M * sizeof(int));
    
    // vwall
    sort(vwall, vwall + n_vw, lt_wall);
    sort(birds, birds + M, lt_bird_x);
    memset(rmq, 0x80, nys * 2 * sizeof(ll));
    for (int ib = 0, iw = 0; ib < M; ib++) {
        while (iw < n_vw && vwall[iw].pos < birds[ib].x) {
            int y1 = lower_bound(ys, ys + nys, vwall[iw].s) - ys;
            int y2 = lower_bound(ys, ys + nys, vwall[iw].e) - ys + 1;
            for (int l = y1 + nys, r = y2 + nys; l < r; l >>= 1, r >>= 1) {
                if (l & 1) rmq[l] = vwall[iw].pos, rmq_id[l++] = vwall[iw].id;
                if (r & 1) rmq[--r] = vwall[iw].pos, rmq_id[r] = vwall[iw].id;
            }
            iw++;
        }
        int y = lower_bound(ys, ys + nys, birds[ib].y) - ys, besti = -1;
        ll bestx = LLONG_NINF;
        for (y += nys; y; y >>= 1) {
            if (rmq[y] > bestx) bestx = rmq[y], besti = rmq_id[y];
        }
        ll birdx = birds[ib].x; int birdi = birds[ib].id;
        if (besti >= 0 && birdx - bestx < bird_hit_d[birdi]) {
            bird_hit_d[birdi] = birdx - bestx;
            bird_hit_wall_id[birdi] = besti;
        }
    }
    memset(rmq, 0x7f, nys * 2 * sizeof(ll));
    for (int ib = M - 1, iw = n_vw - 1; ib >= 0; ib--) {
        while (iw >= 0 && vwall[iw].pos > birds[ib].x) {
            int y1 = lower_bound(ys, ys + nys, vwall[iw].s) - ys;
            int y2 = lower_bound(ys, ys + nys, vwall[iw].e) - ys + 1;
            for (int l = y1 + nys, r = y2 + nys; l < r; l >>= 1, r >>= 1) {
                if (l & 1) rmq[l] = vwall[iw].pos, rmq_id[l++] = vwall[iw].id;
                if (r & 1) rmq[--r] = vwall[iw].pos, rmq_id[r] = vwall[iw].id;
            }
            iw--;
        }
        int y = lower_bound(ys, ys + nys, birds[ib].y) - ys, besti = -1;
        ll bestx = LLONG_INF;
        for (y += nys; y; y >>= 1) {
            if (rmq[y] < bestx) bestx = rmq[y], besti = rmq_id[y];
        }
        ll birdx = birds[ib].x; int birdi = birds[ib].id;
        if (besti >= 0 && bestx - birdx < bird_hit_d[birdi]) {
            bird_hit_d[birdi] = bestx - birdx;
            bird_hit_wall_id[birdi] = besti;
        }
    }

    // hwall
    sort(hwall, hwall + n_hw, lt_wall);
    sort(birds, birds + M, lt_bird_y);
    memset(rmq, 0x80, nxs * 2 * sizeof(ll));
    for (int ib = 0, iw = 0; ib < M; ib++) {
        while (iw < n_hw && hwall[iw].pos < birds[ib].y) {
            int x1 = lower_bound(xs, xs + nxs, hwall[iw].s) - xs;
            int x2 = lower_bound(xs, xs + nxs, hwall[iw].e) - xs + 1;
            for (int l = x1 + nxs, r = x2 + nxs; l < r; l >>= 1, r >>= 1) {
                if (l & 1) rmq[l] = hwall[iw].pos, rmq_id[l++] = hwall[iw].id;
                if (r & 1) rmq[--r] = hwall[iw].pos, rmq_id[r] = hwall[iw].id;
            }
            iw++;
        }
        int x = lower_bound(xs, xs + nxs, birds[ib].x) - xs, besti = -1;
        ll besty = LLONG_NINF;
        for (x += nxs; x; x >>= 1) {
            if (rmq[x] > besty) besty = rmq[x], besti = rmq_id[x];
        }
        ll birdy = birds[ib].y; int birdi = birds[ib].id;
        if (besti >= 0 && birdy - besty < bird_hit_d[birdi]) {
            bird_hit_d[birdi] = birdy - besty;
            bird_hit_wall_id[birdi] = besti;
        }
    }
    memset(rmq, 0x7f, nxs * 2 * sizeof(ll));
    for (int ib = M - 1, iw = n_hw - 1; ib >= 0; ib--) {
        while (iw >= 0 && hwall[iw].pos > birds[ib].y) {
            int x1 = lower_bound(xs, xs + nxs, hwall[iw].s) - xs;
            int x2 = lower_bound(xs, xs + nxs, hwall[iw].e) - xs + 1;
            for (int l = x1 + nxs, r = x2 + nxs; l < r; l >>= 1, r >>= 1) {
                if (l & 1) rmq[l] = hwall[iw].pos, rmq_id[l++] = hwall[iw].id;
                if (r & 1) rmq[--r] = hwall[iw].pos, rmq_id[r] = hwall[iw].id;
            }
            iw--;
        }
        int x = lower_bound(xs, xs + nxs, birds[ib].x) - xs, besti = -1;
        ll besty = LLONG_INF;
        for (x += nxs; x; x >>= 1) {
            if (rmq[x] < besty) besty = rmq[x], besti = rmq_id[x];
        }
        ll birdy = birds[ib].y; int birdi = birds[ib].id;
        if (besti >= 0 && besty - birdy < bird_hit_d[birdi]) {
            bird_hit_d[birdi] = besty - birdy;
            bird_hit_wall_id[birdi] = besti;
        }
    }

    for (int i = 0; i < M; i++) {
        if (bird_hit_wall_id[i] < 0) return -1;
        wall_hit[bird_hit_wall_id[i]]++;
        // printf("%d\n", bird_hit_wall_id[i] + 1);
    }
    for (int i = 0; i < N; i++) printf("%d\n", wall_hit[i]);

    return 0;
}
