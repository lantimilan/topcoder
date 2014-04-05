// phonebook.cpp
//
// given a digit string, generate all possible strings from keypad of phone

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> phone_strings;
vector<string> keymap;

void init()
{
    keymap.push_back("+");  // 0
    keymap.push_back("");   // 1
    keymap.push_back("ABC");   // 2
    keymap.push_back("DEF");   // 3
    keymap.push_back("GHI");   // 4
    keymap.push_back("JKL");   // 5
    keymap.push_back("MNO");   // 6
    keymap.push_back("PQRS");   // 7
    keymap.push_back("TUV");   // 8
    keymap.push_back("WXYZ");   // 9
}

void gen_string(string prefix, string digits)
{
    if (digits.empty()) {
        phone_strings.push_back(prefix);
        return;
    }
    int d = digits[0] - '0';
    for (int x = 0; x < keymap[d].size(); ++x) {
        char ch = keymap[d][x];
        gen_string(prefix + ch, digits.substr(1));
    }
}

int main()
{
    init();
    string cmd;
    while (1) {
        cout << "Command:\n";
        cout << "digits, example 123\n";
        cout << "To quit, Q or q or quit\n";
        cin >> cmd;
        if (cmd[0] == 'q' || cmd[0] == 'Q') break;
        phone_strings.clear();
        gen_string("", cmd);
        for (int i = 0; i < phone_strings.size(); ++i)
            cout << phone_strings[i] << endl;
    }
}
