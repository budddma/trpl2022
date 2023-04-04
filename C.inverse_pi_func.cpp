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

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t n, m = 0;
    while (std::cin >> n >> m && n != -1) {
        std::vector<size_t> p(n);
        for (auto &it: p) {
            std::cin >> it;
        }

        bool flag = true;

        if (p[0] != 0) {
            flag = false;
        }

        std::string s = "a";
        if (flag) {
            for (size_t i = 1; i < n; ++i) {
                if (p[i] > p[i - 1] + 1) {
                    flag = false;
                    break;
                }
                if (p[i] != 0) {
                    s += s[p[i] - 1];
                } else {
                    std::vector<bool> is_exist(26, false);

                    size_t k = p[i - 1];
                    while (k != 0) {
                        is_exist[s[k] - 'a'] = true;
                        k = p[k - 1];
                    }

                    size_t c = 1;
                    while (c < 26 && is_exist[c]) {
                        ++c;
                    }
                    if (c >= m) {
                        flag = false;
                        break;
                    }
                    s += 'a' + c;
                }
            }

            if (p != PrefFunc(s)) {
                flag = false;
            }
        }


        if (flag) {
            std::cout << "YES\n" << s << "\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
