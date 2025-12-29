#include <bits/stdc++.h>
using namespace std;

static inline long long cost(int X, int Y, int Z, int MOD, int OFF) {
    long long a = (X + OFF) % MOD;
    long long b = (X + Y + OFF) % MOD;
    long long c = (X + Y + Z + OFF) % MOD;
    return (a * b % MOD) * c % MOD + 1;
}

int solve(int N, int M, int MOD, int OFF) {
    int R = N - M;
    if (R <= 0) return 0;

    vector<int> allCities(N);
    iota(allCities.begin(), allCities.end(), 0);

    long long ans = LLONG_MAX;

    vector<int> mask(N, 0);
    fill(mask.begin(), mask.begin() + M, 1);

    do {
        vector<int> party, nonparty;
        for (int i = 0; i < N; ++i) {
            if (mask[i]) party.push_back(i);
            else nonparty.push_back(i);
        }

        // Precompute cost from each nonparty city (with its reindeer index) to every possible destination
        vector<vector<long long>> travel(R, vector<long long>(N, LLONG_MAX));
        for (int i = 0; i < R; ++i) {
            int x = nonparty[i];
            int z = i; // reindeer index 0..R-1
            for (int y = 0; y < N; ++y) {
                if (y != x) {
                    travel[i][y] = cost(x + 1, y + 1, z + 1, MOD, OFF);
                }
            }
        }

        // DP over subsets to assign each nonparty to a destination
        int fullMask = (1 << R) - 1;
        vector<long long> dp(1 << R, LLONG_MAX);
        dp[0] = 0;

        for (int maskUsed = 0; maskUsed < (1 << R); ++maskUsed) {
            int assigned = __builtin_popcount(maskUsed);
            if (assigned >= R) continue;
            for (int dest = 0; dest < N; ++dest) {
                if (find(nonparty.begin(), nonparty.end(), dest) != nonparty.end()) {
                    // Destination is nonparty; must not already be assigned
                    int idx = find(nonparty.begin(), nonparty.end(), dest) - nonparty.begin();
                    if (maskUsed & (1 << idx)) continue;
                }
                int newMask = maskUsed;
                if (find(nonparty.begin(), nonparty.end(), dest) != nonparty.end()) {
                    int idx = find(nonparty.begin(), nonparty.end(), dest) - nonparty.begin();
                    newMask |= (1 << idx);
                }
                dp[newMask] = min(dp[newMask], dp[maskUsed] + travel[assigned][dest]);
            }
        }

        ans = min(ans, dp[fullMask]);

    } while (prev_permutation(mask.begin(), mask.end()));

    return (int)ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, MOD, OFF;
    cin >> N >> M >> MOD >> OFF;
    cout << solve(N, M, MOD, OFF) << "\n";
    return 0;
}
