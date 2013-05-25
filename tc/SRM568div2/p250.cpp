class TheSimilarNumbers
{
public:
int find(int lower, int upper)
{
	int cnt = 0;
	int val = lower;
	while (val <= upper) {
		cnt++;
		val = 10*val + 1;
	}
	return cnt;
}
};
