#include <iostream>
#include <string>
#include <vector>

static std::vector<std::vector<int> > adj;
static std::vector<int> matchL, matchR;
static std::vector<char> visited;

static bool match(int i)
{
    if (visited[i]) return false;
    visited[i] = true;
    for (size_t n = 0; n < adj[i].size(); ++n)
    {
        const int j = adj[i][n];
        if (matchR[j] < 0 || match(matchR[j])) 
        {
            matchL[i] = j;
            matchR[j] = i;
            return true;
        }
    }
    return false;
}

static bool match_one()
{
    for (int i = 0; i < adj.size(); ++i) 
    {
        if (matchL[i] < 0 && match(i)) return true;
    }
    return false;
}

static int maximum_matching()
{
    int res = 0;
    matchL.assign(adj.size(), -1);
    matchR.assign(adj.size(), -1);
    while (visited.assign(adj.size(), 0), match_one()) ++res;
    return res;
}

static bool compatible(const std::string &s, const std::string &t)
{
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (s[i] != '?' && t[i] != '?' && s[i] != t[i]) return false;
    }
    return true;
}

static bool possible(const std::string &K1, const std::string &K2, int M)
{
    int L = K1.size() / M;
    adj.assign(M, std::vector<int>());
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if (compatible(K1.substr(L*i, L), K2.substr(L*j, L)))
                adj[i].push_back(j);
        }
    }
    return maximum_matching() == M;
}

int main()
{
    int cases = 0;
    std::cin >> cases;
    for (int caseno = 1; caseno <= cases; ++caseno)
    {
        int M;
        std::string K1, K2;
        std::cin >> M >> K1 >> K2;

        std::cout << "Case #" << caseno << ": ";
        if (!possible(K1, K2, M))
        {
            std::cout << "IMPOSSIBLE" << std::endl;;
            continue;
        }
        for (std::string::iterator it = K1.begin(); it != K1.end(); ++it)
        {
            if (*it == '?')
            {
                *it = 'a';
                while (!possible(K1, K2, M))
                    ++*it;
            }
        }
        std::cout << K1 << std::endl;
    }
}
