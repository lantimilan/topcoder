import java.io.OutputStreamWriter;
import java.io.BufferedWriter;
import java.util.Comparator;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.Writer;
import java.io.IOException;
import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.math.BigInteger;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 * @author Egor Kulikov (egor@egork.net)
 */
public class Solution {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		OutputWriter out = new OutputWriter(outputStream);
		ReverseShuffleMerge solver = new ReverseShuffleMerge();
		solver.solve(1, in, out);
		out.close();
	}
}

class ReverseShuffleMerge {
    public void solve(int testNumber, InputReader in, OutputWriter out) {
		char[] s = in.readString().toCharArray();
		ArrayUtils.reverse(s);
		int[] next = new int[26];
		int[] haveTo = new int[26];
		int[] qty = new int[26];
		for (int i = 0; i < s.length; i++)
			qty[s[i] - 'a']++;
		int[] remaining = new int[26];
		for (int i = 0; i < 26; i++)
			remaining[i] = qty[i] /= 2;
		Arrays.fill(haveTo, s.length);
		for (int i = 0; i < 26; i++) {
			if (qty[i] == 0)
				continue;
			for (int j = s.length - 1; j >= 0; j--) {
				if (s[j] == i + 'a')
					qty[i]--;
				if (qty[i] == 0) {
					haveTo[i] = j;
					break;
				}
			}
		}
		Arrays.fill(next, s.length);
		for (int i = s.length - 1; i >= 0; i--)
			next[s[i] - 'a'] = i;
		char[] answer = new char[s.length / 2];
		int position = 0;
		for (int i = 0; i < answer.length; i++) {
			for (int j = 0; j < 26; j++) {
				if (remaining[j] == 0)
					continue;
				boolean good = true;
				for (int k = j + 1; k < 26; k++) {
					if (haveTo[k] < next[j]) {
						good = false;
						break;
					}
				}
				if (good) {
					answer[i] = (char) ('a' + j);
					remaining[j]--;
					position = next[j] + 1;
					if (remaining[j] == 0)
						haveTo[j] = s.length;
					else {
						for (int k = haveTo[j] + 1; k < s.length; k++) {
							if (s[k] == 'a' + j) {
								haveTo[j] = k;
								break;
							}
						}
					}
					for (int k = 0; k < 26; k++) {
						if (next[k] < position) {
							next[k] = s.length;
							for (int l = position; l < s.length; l++) {
								if (s[l] == 'a' + k) {
									next[k] = l;
									break;
								}
							}
						}
					}
					break;
				}
			}
		}
		out.printLine(answer);
    }
}

class InputReader {

	private InputStream stream;
	private byte[] buf = new byte[1024];
	private int curChar;
	private int numChars;
	private SpaceCharFilter filter;

	public InputReader(InputStream stream) {
		this.stream = stream;
	}

	public int read() {
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

	public String readString() {
		int c = read();
		while (isSpaceChar(c))
			c = read();
		StringBuilder res = new StringBuilder();
		do {
			res.appendCodePoint(c);
			c = read();
		} while (!isSpaceChar(c));
		return res.toString();
	}

	public boolean isSpaceChar(int c) {
		if (filter != null)
			return filter.isSpaceChar(c);
		return isWhitespace(c);
	}

	public static boolean isWhitespace(int c) {
		return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
	}

	public interface SpaceCharFilter {
		public boolean isSpaceChar(int ch);
	}
}

class OutputWriter {
	private final PrintWriter writer;

	public OutputWriter(OutputStream outputStream) {
		writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
	}

	public OutputWriter(Writer writer) {
		this.writer = new PrintWriter(writer);
	}

	public void printLine(char[] array) {
		writer.println(array);
	}

	public void close() {
		writer.close();
	}

	}

class ArrayUtils {

	public static void reverse(char[] array) {
		for (int i = 0, j = array.length - 1; i < j; i++, j--) {
			char temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}

	}

