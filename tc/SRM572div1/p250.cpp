// find equivalent pos and exclude max occurred letter
// transitive closure
#include <cstring>
#include <string>
using namespace std;

int edge[60][60];

class NewArenaPassword {
public:
int minChange(string oldPassword, int K)
{
  int n = oldPassword.size();
  for (int i = 0; i < K; ++i) {
    int j = n - K + i;
    edge[i][i] = 1;
    edge[i][j] = edge[j][i] = 1;
  }

  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
	if (edge[i][k] && edge[k][j])
	  edge[i][j] = 1;

  int seen[60] = {0};
  int ans = 0;
  for (int i = 0; i < n; ++i) if (!seen[i]) {
      int cnt[30] = {0};
      for (int j = 0; j < n; ++j) if (edge[i][j]) {  // edge[i][i] = 1 for all i
	  cnt[oldPassword[j]-'a']++;
	  seen[j] = 1;
	}
      int sum = 0;
      int mx = 0;
      for (int i = 0; i < 26; ++i) { sum += cnt[i]; mx = max(cnt[i], mx); }
      ans += sum - mx;
    }
  return ans;
}
};


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
