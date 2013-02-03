// generate all upper/lower combination of a given hash

#include <cctype>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string dec_to_bin(int n)
{
    string bin(32, '0');
    for (int i=0; i<32; ++i)
        if (n & 1<<i) bin[i] = '1';
        else bin[i] = '0';
    for (int i=0, j=bin.length()-1; i<j; ++i, --j) {
        char ch = bin[i]; bin[i] = bin[j]; bin[j] = ch;
    }
    return bin;
}

vector<string> gen_hash(const string &hash)
{
    int perf_cnt = 0;  // performance counter
    int mask = 0;
    int len = hash.length();
    for (int i=0; i<len; ++i)
        if (isalpha(hash[i])) mask |= 1<<i;

    vector<string> all_hash;
    string tmp;
    for (int sub = mask; sub > 0; sub = (sub-1) & mask) {
        perf_cnt++;  // update perf count
        tmp = hash;
        for (int i=0; i<len; ++i) {
            if (sub & 1<<i) tmp[i] = tolower(tmp[i]);
            else tmp[i] = toupper(tmp[i]);
        }
        all_hash.push_back(tmp);
    }
    for (int i=0; i<len; ++i)
        tmp[i] = toupper(tmp[i]);
    all_hash.push_back(tmp);
    cout << "mask " << dec_to_bin(mask) << ", perf-count: " << perf_cnt << endl;
    return all_hash;
}

int main()
{
    string hash = "A46dx8Z";
    vector<string> all_hash = gen_hash(hash);
    for (int i=0; i<all_hash.size(); ++i)
        cout << all_hash[i] << endl;
}
