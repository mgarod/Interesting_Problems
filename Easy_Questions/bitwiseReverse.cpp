/*
Given an unsigned 32 bit number,
*/

#include <iostream>
using namespace std;

u_int32_t reverse(u_int32_t A) {
    u_int32_t answer = 0;
    for (int i = 0; i < 32; ++i) {
        int bit = A & 1;
        A >>= 1;
        answer <<= 1;
        answer |= bit;
    }
    return answer;
}

int main() {
    u_int32_t x = 123, reversed = reverse(x);
    cout << x << endl << reversed << endl;

    return 0;
}
