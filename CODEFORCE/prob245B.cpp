#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int pos, p;
    string in, out;
    cin >> in;

    pos = 0;
    // http or ftp
    if (in[0] == 'h') { out += "http"; pos += strlen("http"); }
    else { out += "ftp"; pos += strlen("ftp"); }
    out += "://";

    // look for ru, notice domain is nonempty, so p starts pos+1
    for (p=pos+1; p < in.length(); ++p) {
        if (in[p] == 'r' && in[p+1] == 'u') break;
    }
    out += in.substr(pos, p-pos);
    out += ".";
    out += "ru";

    pos = p+2;
    if (pos < in.length()) {
        out += "/";
        out += in.substr(pos);
    }
    cout << out << endl;
}

// Accepted
