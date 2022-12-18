#include <iostream>
#include <string>
#include <vector>

std::vector<size_t> PrefFunc(const std::string &s) {
    std::vector<size_t> pf(s.size(), 0);

    for (size_t i = 1; i < s.size(); ++i) {
        size_t k = pf[i - 1];
        while (s[k] != s[i] && k != 0) {
            k = pf[k - 1];
        }
        if (s[k] == s[i]) {
            pf[i] = k + 1;
        }
    }

    return pf;
}

int main() {
    std::string str;
    std::string patt;
    std::cin >> str >> patt;

    std::vector<size_t> pf = PrefFunc(patt + '#' + str);

    size_t count = 0;
    std::vector<size_t> ans;
    for (size_t i = 1; i < pf.size() - patt.size(); ++i) {
        if (pf[i + patt.size()] == patt.size()) {
            ++count;
            ans.emplace_back(i - patt.size() + 1);
        }
    }
    std::cout << count << '\n';

    for (const auto &it: ans) {
        std::cout << it << " ";
    }

    return 0;
}
