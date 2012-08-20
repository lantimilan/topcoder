import java.io.*;
import java.util.*;


public class Main
{
    static int W, H;
    public static void main(String[] args) throws Exception
    {
        try {
            FastScanner in = new FastScanner();
            while (true)
            {
                H = in.nextInt();
                W = in.nextInt();
                if ((W|H) == 0) break;
                new Main(in);
            }
        } catch (Exception e) {
        }
    }
    int[][] id;
    char[][] grid;
    boolean[][] blocked;
    static int[] dx = {-1,1,-1,1};
    static int[] dy = {-1,-1,1,1};
    boolean isValid(int x, int y)
    {
        return x >= 0 && y >= 0 && x < W && y < H;
    }

    boolean canPlaceNode(int x, int y)
    {
        return isValid(x,y) && !blocked[y][x];
    }

    boolean isConflict(int x, int y, int dx, int dy)
    {
        if (!isValid(x+dx,y+dy))
            return false;
        if (grid[y+dy][x+dx] == 'P')
            return false;
        dx *= 2;
        dy *= 2;
        if (!isValid(x+dx, y+dy))
            return false;
        return !blocked[y+dy][x+dx];
    }

    public Main(FastScanner in)
    {
        id = new int[H][W];
        grid = new char[H][];
        blocked = new boolean[H][W];
        for (int j=0; j<H; j++)
        {
            grid[j] = in.next().trim().toCharArray();
            Arrays.fill(blocked[j], false);
        }

        for (int j=0; j<H; j++)
            for (int i=0; i<W; i++)
            {
                if (grid[j][i] == 'G')
                {
                    blocked[j][i] = true;
                    for (int u=0; u<4; u++)
                        if (isValid(i+dx[u]*2, j+dy[u]*2) && grid[j+dy[u]][i+dx[u]] != 'P')
                            blocked[j+dy[u]*2][i+dx[u]*2] = true;
                }
                else if (grid[j][i] == 'P')
                    blocked[j][i] = true;
            }
        int numValid = 0;
        for (int j=0; j<H; j++)
            for (int i=0; i<W; i++)
                if (!blocked[j][i])
                    id[j][i] = numValid++;
        boolean[] isLeft = new boolean[numValid];
        Graph g = new Graph(numValid);
        BipartiteMatching bpm = new BipartiteMatching(g);
        for (int j=0; j<H; j++)
        {
            for (int i=0; i<W; i++)
            {
                if (blocked[j][i]) continue;
                int v = j/2;
                if ((v%2) == 0)
                {
                    bpm.match[id[j][i]] = -2;
                    for (int u=0; u<4; u++)
                        if (isConflict(i,j,dx[u],dy[u]))
                            g.add(id[j][i], id[j+dy[u]*2][i+dx[u]*2]);
                }
            }
        }
        try {
            int res = numValid-bpm.run();
            System.out.println(res);
        } catch (Exception e) {
            System.out.println(numValid);
        }
    }
}


class Graph
{
    int N;
    int[][] adj;
    public Graph(int n)
    {
        adj = new int[N=n][5];
    }
    void add(int i, int j)
    {
        adj[i][++adj[i][0]] = j;
        adj[j][++adj[j][0]] = i;
    }
}


class BipartiteMatching {
    Graph g;
    int[] match,prev,q;
    int count = 0;
    BipartiteMatching(Graph gg) {
        g=gg;
        match = new int[g.N];
        prev = new int[g.N];
        q = new int[g.N];
        Arrays.fill(match, -1);
    }
    int run() {
        while (true)
        {
            int cc = augment();
            if (cc == 0) break;
            count+=cc;
        }
        return count;
    }
    int augment() {
        int fptr=0, bptr=0;
        Arrays.fill(prev,-1);
        for (int i=0; i<g.N; i++)
            if (match[i] == -2)
            {
                q[bptr++] = i;
                prev[i] = g.N;
            }

        boolean failed = true;
        while(fptr < bptr) {
            int c = q[fptr++];
            for(int u=1; u<=g.adj[c][0]; u++)
            {
                int m = g.adj[c][u];
                if(match[m] < 0) {
                    prev[m] = g.N+4;
                    failed = false;
                }
                else if(prev[m] < 0) {
                    prev[m] = c;
                    prev[match[m]] = m;
                    q[bptr++] = match[m];
                }
            }
        }
        if (failed) return 0;

        int res = 0;
        for (int snk=0; snk<g.N; snk++)
        {
            if (prev[snk] != (g.N+4)) continue;
            for (int u=1; u<=g.adj[snk][0]; u++)
            {
                int pp = g.adj[snk][u];
                if (prev[pp] < 0) continue;
                prev[snk] = pp;
                boolean passed = false;
                for (int i=snk, next=-1; i>=0; i=next)
                {
                    if (prev[i] < 0) break;
                    next = match[prev[i]];
                    if (prev[prev[i]] == g.N)
                        passed = true;
                }
                if (!passed) continue;

                res++;
                for (int i=snk, next=-1; i>=0; i=next)
                {
                    if (prev[i] < 0) break;
                    next = match[prev[i]];
                    match[i] = prev[i];
                    match[prev[i]] = i;
                    prev[prev[i]] = -1;
                    prev[i] = -1;
                }
                break;
            }
        }
        return res;
    }
}


class FastScanner {
    private InputStream stream;
    private byte[] buf = new byte[1024];
    private int curChar;
    private int numChars;

    public FastScanner()
    {
        stream = System.in;
    }

    int read()
    {
        if (numChars == -1)
            throw new InputMismatchException();
        if (curChar >= numChars) {
            curChar = 0;
            try {
                numChars = stream.read(buf);
            } catch (IOException e) {
                throw new InputMismatchException();
            }
            if (numChars <= 0)
                return -1;
        }
        return buf[curChar++];
    }

    boolean isSpaceChar(int c)
    {
        return c==' '||c=='\n'||c=='\r'||c=='\t'||c==-1;
    }
    boolean isEndline(int c)
    {
        return c=='\n'||c=='\r'||c==-1;
    }

    int nextInt()
    {
        return Integer.parseInt(next());
    }
    long nextLong()
    {
        return Long.parseLong(next());
    }

    double nextDouble()
    {
        return Double.parseDouble(next());
    }

    String next() {
        int c = read();
        while (isSpaceChar(c))
            c = read();
        StringBuilder res = new StringBuilder();
        do {
            res.appendCodePoint(c);
            c = read();
        } while(!isSpaceChar(c));
        return res.toString();
    }
    String nextLine() {
        int c = read();
        while (isEndline(c))
            c = read();
        StringBuilder res = new StringBuilder();
        do {
            res.appendCodePoint(c);
            c = read();
        } while(!isEndline(c));
        return res.toString();
    }
}
