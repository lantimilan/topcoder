#include <cstring>
#include <iostream>
using namespace std;

int get_team(char team)
{
    return team == 'h' ? 0 : 1;
}

int get_points(char card)
{
    return card == 'y' ? 1 : 2;
}

int main()
{
    int fouls[2][100];  // home=0, away=1, val=1 for yellow, 2 for red
    int rejected[2][100];
    memset(fouls, 0, sizeof fouls);
    memset(rejected, 0, sizeof rejected);

    string home; cin >> home;
    string away; cin >> away;
    int num_fouls; cin >> num_fouls;
    for (int i = 0; i < num_fouls; ++i) {
        int t; cin >> t;
        string team; cin >> team;
        int player; cin >> player;
        string card; cin >> card;
        int team_id = get_team(team[0]);
        int points = get_points(card[0]);
        fouls[team_id][player] += points;
        if (fouls[team_id][player] >= 2) {
            if (rejected[team_id][player]) {}
            else {
                string team_name = (team[0] == 'h') ? home : away;
                cout << team_name << ' ' << player << ' ' << t << endl;
                rejected[team_id][player] = 1;
            }
        }
    }
}
