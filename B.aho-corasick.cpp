#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <map>

const size_t kSigma = 26;

struct Node {
    bool IsTerminal;
    size_t Cnt;
    size_t Pos;
    size_t Size;
    int Link;               // наибольший собственный суффикс в боре
    int CompLink;           // сжатая суффиксная ссылка
    int ExceptLink[kSigma]; // ссылка исключение или следующая вершина
    int Next[kSigma];       // следующая вершина

    Node() : IsTerminal(false), Cnt(0), Pos(0) {
        memset(Next, -1, sizeof(Next));
    }
};

class Trie {
public:

    explicit Trie(const std::vector<std::string> &patt) : Nodes_(1) {
        for (size_t i = 0; i < patt.size(); ++i) {
            Insert(patt[i], i);
        }
    }

    void AhoCorasick(const std::string &text) {
        BuildLinks();
        int v = 0;
        for (size_t i = 0; i < text.size(); ++i) {
            v = Nodes_[v].ExceptLink[text[i] - 'a'];
            int u = v;

            while (u) {
                if (!Nodes_[u].IsTerminal)
                    u = Nodes_[u].CompLink;
                if (Nodes_[u].IsTerminal) {
                    ++Nodes_[u].Cnt;
                    Nodes_[u].Pos = Min(Nodes_[u].Pos, i - Nodes_[u].Size + 2);
                }
                u = Nodes_[u].CompLink;
            }

        }
        PrintResult();
    }

private:

    size_t Min(size_t val, size_t new_val) {
        if (!val)
            return new_val;
        return std::min(val, new_val);
    }

    void Insert(const std::string &str, size_t idx) {
        int v = 0;
        for (auto symbol: str) {
            if (Nodes_[v].Next[symbol - 'a'] == -1) {
                Nodes_[v].Next[symbol - 'a'] = static_cast<int>(Nodes_.size());
                Nodes_.emplace_back();
            }
            v = Nodes_[v].Next[symbol - 'a'];
        }
        Nodes_[v].IsTerminal = true;
        Nodes_[v].Size = str.size();
        OrderedNodes_[idx] = v;
    }

    void BuildLinks() {
        Nodes_[0].CompLink = Nodes_[0].Link = 0;
        for (size_t symbol = 0; symbol < kSigma; ++symbol)
            Nodes_[0].ExceptLink[symbol] = (Nodes_[0].Next[symbol] == -1 ? 0 : Nodes_[0].Next[symbol]);

        std::queue<int> que;
        que.push(0);
        while (!que.empty()) {
            int v = que.front();
            que.pop();

            for (size_t i = 0; i < kSigma; ++i) {
                int u = Nodes_[v].Next[i];
                if (u == -1)
                    continue;
                Nodes_[u].Link = (v ? Nodes_[Nodes_[v].Link].ExceptLink[i] : 0);

                for (size_t j = 0; j < kSigma; ++j) {
                    if (Nodes_[u].Next[j] == -1)
                        Nodes_[u].ExceptLink[j] = Nodes_[Nodes_[u].Link].ExceptLink[j];
                    else
                        Nodes_[u].ExceptLink[j] = Nodes_[u].Next[j];
                }

                if (Nodes_[Nodes_[u].Link].IsTerminal)
                    Nodes_[u].CompLink = Nodes_[u].Link;
                else
                    Nodes_[u].CompLink = Nodes_[Nodes_[u].Link].CompLink;
                que.push(u);
            }

        }
    }

    void PrintResult() {
        for (size_t i = 0; i < OrderedNodes_.size(); ++i)
            std::cout << Nodes_[OrderedNodes_[i]].Cnt << " " << Nodes_[OrderedNodes_[i]].Pos << "\n";
    }

    std::vector<Node> Nodes_;
    std::map<size_t, size_t> OrderedNodes_;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    size_t patt_cnt;
    std::string text;
    std::cin >> text >> patt_cnt;

    std::vector<std::string> patt(patt_cnt);
    for (auto &p: patt) {
        std::cin >> p;
    }
    Trie trie(patt);
    trie.AhoCorasick(text);

    return 0;
}
