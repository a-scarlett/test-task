#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>

std::set<int> solution(int N, const std::vector<int> &T,
                       const std::vector<int> &K) {
  int i, w;
  std::vector<std::vector<int>> R(static_cast<int>(T.size()) + 1,
                                  std::vector<int>(N + 1, 0));

  for (i = 0; i <= static_cast<int>(T.size()); i++) {
    for (w = 0; w <= N; w++) {
      if (i == 0 || w == 0) {
        R[i][w] = 0;
      } else if (T[i - 1] <= w) {
        R[i][w] = std::max(K[i - 1] + R[i - 1][w - T[i - 1]], R[i - 1][w]);
      } else {
        R[i][w] = R[i - 1][w];
      }
    }
  }

  // stores the result of Knapsack
  int ans = R[static_cast<int>(T.size())][N];
  std::set<int> res;
  w = N;
  for (i = static_cast<int>(T.size()); i > 0 && ans > 0; i--) {
    if (ans == R[i - 1][w])
      continue;
    else {
      res.insert(i - 1);
      ans = ans - K[i - 1];
      w = w - T[i - 1];
    }
  }
  return res;
}

void test() {
  // Test case 1
  {
    int N = 10;
    std::vector<int> T = {3, 4, 2};
    std::vector<int> K = {2, 3, 4};
    std::set<int> ans{0, 1, 2};
    assert(ans == solution(N, T, K));
  }

  // Test case 2
  {
    int N = 5;
    std::vector<int> T = {2, 3};
    std::vector<int> K = {1, 2};
    std::set<int> ans{0, 1};
    assert(ans == solution(N, T, K));
  }

  // Test case 3
  {
    int N = 8;
    std::vector<int> T = {2, 3, 4};
    std::vector<int> K = {1, 2, 3};
    std::set<int> ans{1, 2};
    assert(ans == solution(N, T, K));
  }

  // Test case 4
  {
    int N = 6;
    std::vector<int> T = {2, 3, 4};
    std::vector<int> K = {1, 2, 3};
    std::set<int> ans{0, 2};
    assert(ans == solution(N, T, K));
  }
}

int main() {
  test();
  std::cout << "All tests passed\n";
  return 0;
}