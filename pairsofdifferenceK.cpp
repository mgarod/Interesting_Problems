#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int numPairsDiffK(const int k, const vector<int>& v) {
	int answer = 0;
	unordered_map<int, bool> map;

	for (const auto element : v)
		map[element] = true;

	for (const auto element : v)
		if (map[element - k]) {
			cout << "\t(" << element << ", " << element - k << ")" << endl;
			++answer;
		}

	return answer;
}

int main(){
	vector<int> vec = {1, 7, 9, 12, 5, 2, 12, 3, 22, 18, 19, -5, -3, -1};

	cout << "k=2:\n" << numPairsDiffK(2, vec) << endl;
	cout << "k=3:\n" << numPairsDiffK(3, vec) << endl;
	cout << "k=4:\n" << numPairsDiffK(4, vec) << endl;
	cout << "k=5:\n" << numPairsDiffK(5, vec) << endl;
	cout << "k=6:\n" << numPairsDiffK(6, vec) << endl;
}
