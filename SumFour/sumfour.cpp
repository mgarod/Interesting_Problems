// http://www.spoj.com/problems/SUMFOUR/

#include <array>
#include <iostream>
#include <unordered_map>

const size_t kMax = 2500;

int main() {
  int64_t numlists;
  int64_t a, b, c, d;
  std::array<int64_t, kMax> A, B, C, D;

  std::cin >> numlists;
  for (int i = 0; i < numlists; ++i) {
    std::cin >> A[i] >> B[i] >> C[i] >> D[i];
  }

  std::unordered_map<int64_t, int64_t> AB(numlists*numlists);

  // Compute all pairs of a + b
  for (int i = 0; i < numlists; ++i) {
    const auto a = A[i];
    for (int j = 0; j < numlists; ++j) {
      const auto b = B[j];
        ++AB[a + b];
    }
  }
  
  // Compute all pairs of c + d, see if (c+d) == -(a+b)
  int result = 0;
  for (int i = 0; i < numlists; ++i) {
    const auto c = C[i];
    for (int j = 0; j < numlists; ++j) {
      const auto d = D[j];
        if (AB.count(-(c + d))) {
          result += AB[-(c + d)];
        }
    }
  }

  std::cout << result << std::endl;
  return 0;
}

/*
data.txt

6
-45 22 42 -16
-41 -27 56 30
-36 53 -37 77
-36 30 -75 -46
26 -38 -10 62
-32 -54 -6 45
*/