import java.io.*;
import java.util.*;

public class Dreamoon {

    private static void solve() {
        int n = nextInt();
        int m = nextInt();
        int[] a = new int[n];
        ArrayList<Integer>[] primes = new ArrayList[n];
        HashSet<Integer> allPrimes = new HashSet<Integer>();
        for (int i = 0; i < n; i++) {
            a[i] = nextInt();
            primes[i] = new ArrayList<>();
            for (int j = 2; j * 1L * j <= a[i]; j++) {
                while (a[i] % j == 0) {
                    a[i] /= j;
                    primes[i].add(j);
                    allPrimes.add(j);
                }
            }
            if (a[i] != 1) {
                primes[i].add(a[i]);
                allPrimes.add(a[i]);
            }
        }
        Flow f = new Flow(n + 2);
        Edge[] edges = new Edge[n];
        for (int i = 0; i < m; i++) {
            int fr = nextInt() - 1, to = nextInt() - 1;
            if (fr % 2 == 0) {
                f.addEdge(fr + 1, to + 1, Integer.MAX_VALUE);
            } else {
                f.addEdge(to + 1, fr + 1, Integer.MAX_VALUE);
            }
        }
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                edges[i] = f.addEdge(0, i + 1, 0);
            } else {
                edges[i] = f.addEdge(i + 1, n + 1, 0);
            }
        }
        int ans = 0;
        for (int prime : allPrimes) {
            for (int i = 0; i < n; i++) {
                int cnt = 0;
                for (int pr : primes[i]) {
                    cnt += pr == prime ? 1 : 0;
                }
                edges[i].cap = cnt;
            }
            f.clear();
            ans += f.flow();
        }
        out.println(ans);
    }

    static class Edge {
        int fr, to;
        long flow, cap;
        Edge rev;

        Edge(int fr, int to, long cap) {
            this.fr = fr;
            this.to = to;
            this.cap = cap;
        }

        @Override
        public String toString() {
            return "Edge [fr=" + fr + ", to=" + to + ", flow=" + flow
                    + ", cap=" + cap + "]";
        }

    }

    static class Flow {
        int n;
        ArrayList<Edge>[] g;

        Flow(int n) {
            this.n = n;
            g = new ArrayList[n];
            for (int i = 0; i < n; i++) {
                g[i] = new ArrayList<>();
            }
            q = new int[n];
            h = new int[n];
            cur = new int[n];
        }

        void clear() {
            for (int i = 0; i < g.length; i++) {
                for (Edge e : g[i]) {
                    e.flow = 0;
                }
            }
        }

        Edge addEdge(int fr, int to, long cap) {
            Edge e1 = new Edge(fr, to, cap);
            Edge e2 = new Edge(to, fr, 0);
            e1.rev = e2;
            e2.rev = e1;
            g[fr].add(e1);
            g[to].add(e2);
            return e1;
        }

        int[] h;
        int[] cur;
        int[] q;

        boolean bfs() {
            int qIt = 0, qSz = 0;
            q[qSz++] = 0;
            Arrays.fill(h, -1);
            h[0] = 0;
            while (qIt < qSz) {
                int v = q[qIt++];
                for (Edge e : g[v]) {
                    if (e.flow == e.cap)
                        continue;
                    if (h[e.to] == -1) {
                        h[e.to] = h[e.fr] + 1;
                        q[qSz++] = e.to;
                    }
                }
            }
            return h[n - 1] != -1;
        }

        long dfs(int v, long flow) {
            if (v == n - 1 || flow == 0)
                return flow;
            for (; cur[v] < g[v].size(); cur[v]++) {
                Edge e = g[v].get(cur[v]);
                if (h[e.to] != h[e.fr] + 1 || e.flow == e.cap)
                    continue;
                long add = dfs(e.to, Math.min(flow, e.cap - e.flow));
                if (add == 0)
                    continue;
                e.flow += add;
                e.rev.flow -= add;
                return add;
            }
            return 0;
        }

        long flow() {
            long res = 0;
            while (bfs()) {
                Arrays.fill(cur, 0);
                while (true) {
                    long add = dfs(0, Long.MAX_VALUE);
                    if (add == 0)
                        break;
                    res += add;
                }
            }
            return res;
        }
    }

    private static void run() {
        br = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);

        solve();

        out.close();
    }

    private static StringTokenizer st;
    private static BufferedReader br;
    private static PrintWriter out;

    private static String next() {
        while (st == null || !st.hasMoreElements()) {
            String s;
            try {
                s = br.readLine();
            } catch (IOException e) {
                return null;
            }
            st = new StringTokenizer(s);
        }
        return st.nextToken();
    }

    private static int nextInt() {
        return Integer.parseInt(next());
    }

    private static long nextLong() {
        return Long.parseLong(next());
    }

    public static void main(String[] args) {
        run();
    }
}
