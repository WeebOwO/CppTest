#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

using namespace std;
class RandomTest {
private:
    mt19937                       gen;
    uniform_int_distribution<int> dis;
    vector<int>                   pre;

public:
    RandomTest(vector<int>& w) : gen(random_device{}()), dis(1, accumulate(w.begin(), w.end(), 0)) {
        partial_sum(w.begin(), w.end(), back_inserter(pre));
    }

    int pickIndex() {
        int x = dis(gen);
        return lower_bound(pre.begin(), pre.end(), x) - pre.begin();
    }
};

int main() {
    // To do
}
