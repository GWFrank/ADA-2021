#include <iostream>
#include <vector>
typedef long long lli;
using namespace std;

int64_t RiskValue(const std::vector<int64_t> &b) {
    int64_t value = 0;
    for (size_t i = 0; i < b.size(); ++i) value += b[i];
    for (size_t i = 1; i < b.size(); ++i) value -= std::abs(b[i] - b[i - 1]);
    for (size_t i = 2; i < b.size(); ++i)
        value += b[i - 1] * ((b[i - 2] & b[i - 1]) ^ (b[i - 1] | b[i]) ^ (b[i - 2] + b[i]));
    return value;
}

lli cutValue(int i, const vector<lli> &b, int N) {
    if (i > 0)
        return - abs(b[i+1]-b[i])
               + b[i+1] * ((b[i]&b[i+1]) ^ (b[i+1]|b[i+2]) ^ (b[i]+b[i+2]))
               + b[i]   * ((b[i-1]&b[i]) ^ (b[i]|b[i+1])   ^ (b[i-1]+b[i+1]));
    else
        return - abs(b[1]-b[0])
               + b[1] * ((b[0]&b[1])   ^ (b[1]|b[2]) ^ (b[0]+b[+2]))
               + b[0] * ((b[N-1]&b[0]) ^ (b[0]|b[1]) ^ (b[N-1]+b[1]));
}

lli overlapValue(int i, int j, const vector<lli> &b, int N) {
    if (j != i+1) {
        return 0;
    } else {
        if (i<0)
            return b[0] * ((b[N-1]&b[0]) ^ (b[0]|b[1]) ^ (b[N-1]+b[1]));
        else
            return b[i+1] * ((b[i]&b[i+1]) ^ (b[i+1]|b[i+2]) ^ (b[i]+b[i+2]));
    }
}

int main() {
    // std::cout << "[Sample 1] RiskValue: "
    //           << RiskValue({5, 1, 2}) + RiskValue({3, 4}) << std::endl;
    // cuts: 1, 3
    // std::cout << "[Sample 2] RiskValue: "
    //           << RiskValue({5, 1}) + RiskValue({2, 3}) + RiskValue({4}) << std::endl;
    // cuts: 0, 2, 3
    // std::cout << "[Sample 3] RiskValue: "
    //           << RiskValue({1}) + RiskValue({2}) + RiskValue({3}) + RiskValue({4}) + RiskValue({5})
    //           << std::endl;
    // std::cout << RiskValue({1, 2, 3, 4, 5}) << std::endl;
    std::cout << RiskValue({8, 2, 4}) + RiskValue({9}) + RiskValue({8}) << std::endl;
    std::cout << RiskValue({8, 2, 4}) + RiskValue({9}) + RiskValue({8}) << std::endl;
    std::cout << RiskValue({8, 2, 4}) + RiskValue({9}) + RiskValue({8}) << std::endl;
    std::cout << RiskValue({8, 2}) + RiskValue({4, 9}) + RiskValue({8}) << std::endl;
    std::cout << RiskValue({8, 2}) + RiskValue({4, 9}) + RiskValue({8}) << std::endl;
    std::cout << RiskValue({8, 2}) + RiskValue({4}) + RiskValue({9, 8}) << std::endl;

    cout << "--------\n";
    for (int i=0; i<5; i++) {
        cout << cutValue(i, {2, 4, 9, 8, 8, 2, 4}, 5) << "\n";
    }
    cout << "--------\n";
    for (int i=0; i<4; i++) {
        cout << overlapValue(i, i+1, {2, 4, 9, 8, 8, 2, 4}, 5) << "\n";
    }
    cout << overlapValue(-1, 0, {2, 4, 9, 8, 8, 2, 4}, 5) << "\n";
    return 0;
}