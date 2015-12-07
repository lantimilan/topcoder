#include <bits/stdc++.h>
using namespace std;

int ND;
vector <int> indices[100005]; int arr[100005];
struct node
{
    node * first; node * second; int count;
    node (node * a, node * b, int c){first=a; second=b; count=c;}
};
node * root = new node (NULL, NULL, 0);
node * x[100005];
node * insert (int start, int end, node * r, int num)
{
    if (start<=num && end>=num)
    {
        ND++;
        if (r==NULL) r=new node (NULL, NULL, 0);
        if (start==end)
        {
            return new node (r->first, r->second, r->count+1);
        }
        node * n=insert(start, (start+end)/2, r->first, num);
        node * m=insert((start+end)/2+1, end, r->second, num);
        int z= (n==NULL)?0:n->count;
        int zz=(m==NULL)?0:m->count;
        return new node (n, m, z+zz);
    }
    return r;
}
int query (int start, int end, node * a, int kth)
{
    if (start==end) return start;
    int z=(a->first==NULL)?0:a->first->count;
    if (z>=kth)
    {
        return query(start, (start+end)/2, a->first, kth);
    }
    else return query((start+end)/2+1, end, a->second, kth-z);
}
int main()
{
    int a,b; cin >> a >> b;
    for (int g=1; g<=a; g++)
    {
        int c; cin >> c; arr[g]=c; indices[c].push_back(g);
    }
    x[100001]=root;
    for (int g=100000; g>=1; g--)
    {
        x[g]=x[g+1];
        for (int y=0; y<indices[g].size(); y++)
        {
            x[g]=insert(1, 100000, x[g], indices[g][y]);
        }
    }
    for (int g=0; g<b; g++)
    {
        int above, kth; cin >> above >> kth;
        cout << arr[query(1, 100000, x[above], kth)]<< '\n';
    }
    cout << "ND " << ND << endl;
    return 0;
}
