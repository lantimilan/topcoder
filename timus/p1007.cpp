// if len = N, try each 1 flip to 0, sum -= pos
// if len = N-1, insert a 0 or 1, need to know # of 1 from pos to end
// if len = N+1, remove a 0 or 1, need to know # of 1 from pos to end

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int N; cin >> N;
    string code;
    while (cin >> code) {
        if (!(abs((int)code.length() - N) <= 1)) break;
        if (!(code[0] == '0' || code[0] == '1')) break;
        int cnt[1005] = {0};
        int len = code.length();
        int sum = 0;
        for (int i=len-1; i>=0; --i) {
            cnt[i] = cnt[i+1] + (code[i]=='1');
        }
        for (int i=0; i<len; ++i)
            if (code[i] == '1') sum += i+1;
        if (len == N) {
            if (sum % (N+1) == 0) { cout << code << endl; }
            else {
                for (int i=0; i<len; ++i) if (code[i] == '1') {
                    int sub = sum - (i+1);
                    if (sub % (N+1) == 0) {
                        code[i] = '0'; cout << code << endl; break;
                    }
                }
            }
        } else if (len == N-1) {
            string newcode(N, ' ');
            for (int i=0; i<=len; ++i) {  // can also insert in the end
                int add = sum + cnt[i];
                char ch = 'x';
                if (add % (N+1) == 0) ch = '0';
                else if ((add + i+1) % (N+1) == 0) ch = '1';
                if (ch != 'x') {
                    int j;
                    for (j=0; j<i; ++j) newcode[j] = code[j];
                    newcode[j++] = ch;
                    for (; j<N; ++j) newcode[j] = code[j-1];
                    cout << newcode << endl;
                    break;
                }
            }
        } else {  // len == N+1
            string newcode(N, ' ');
            for (int i=0; i<len; ++i) {
                int sub = sum - cnt[i];
                if (code[i] == '1') sub -= i;
                if (sub % (N+1) == 0) {
                    for (int j=0, k=0; j < len; ++j)
                        if (j != i) newcode[k++] = code[j];
                    cout << newcode << endl;
                    break;
                }
            }
        }
    }
}

// 4730026  14:22:03 20 Jan 2013
// lantimilan  1007. Code Words    C++ Accepted    0.062   192 KB
