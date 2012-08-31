#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <map>
using namespace std;


pair< int, int > dp[20][131073];
map< string, int > atom;
int sum[131073];


main(){
        atom["H"] = 1;
        atom["He"] = 2;
        atom["Li"] = 3;
        atom["Be"] = 4;
        atom["B"] = 5;
        atom["C"] = 6;
        atom["N"] = 7;
        atom["O"] = 8;
        atom["F"] = 9;
        atom["Ne"] = 10;
        atom["Na"] = 11;
        atom["Mg"] = 12;
        atom["Al"] = 13;
        atom["Si"] = 14;
        atom["P"] = 15;
        atom["S"] = 16;
        atom["Cl"] = 17;
        atom["Ar"] = 18;
        atom["K"] = 19;
        atom["Ca"] = 20;
        atom["Sc"] = 21;
        atom["Ti"] = 22;
        atom["V"] = 23;
        atom["Cr"] = 24;
        atom["Mn"] = 25;
        atom["Fe"] = 26;
        atom["Co"] = 27;
        atom["Ni"] = 28;
        atom["Cu"] = 29;
        atom["Zn"] = 30;
        atom["Ga"] = 31;
        atom["Ge"] = 32;
        atom["As"] = 33;
        atom["Se"] = 34;
        atom["Br"] = 35;
        atom["Kr"] = 36;
        atom["Rb"] = 37;
        atom["Sr"] = 38;
        atom["Y"] = 39;
        atom["Zr"] = 40;
        atom["Nb"] = 41;
        atom["Mo"] = 42;
        atom["Tc"] = 43;
        atom["Ru"] = 44;
        atom["Rh"] = 45;
        atom["Pd"] = 46;
        atom["Ag"] = 47;
        atom["Cd"] = 48;
        atom["In"] = 49;
        atom["Sn"] = 50;
        atom["Sb"] = 51;
        atom["Te"] = 52;
        atom["I"] = 53;
        atom["Xe"] = 54;
        atom["Cs"] = 55;
        atom["Ba"] = 56;
        atom["Lu"] = 71;
        atom["Hf"] = 72;
        atom["Ta"] = 73;
        atom["W"] = 74;
        atom["Re"] = 75;
        atom["Os"] = 76;
        atom["Ir"] = 77;
        atom["Pt"] = 78;
        atom["Au"] = 79;
        atom["Hg"] = 80;
        atom["Tl"] = 81;
        atom["Pb"] = 82;
        atom["Bi"] = 83;
        atom["Po"] = 84;
        atom["At"] = 85;
        atom["Rn"] = 86;
        atom["Fr"] = 87;
        atom["Ra"] = 88;
        atom["Lr"] = 103;
        atom["Rf"] = 104;
        atom["Db"] = 105;
        atom["Sg"] = 106;
        atom["Bh"] = 107;
        atom["Hs"] = 108;
        atom["Mt"] = 109;
        atom["Ds"] = 110;
        atom["Rg"] = 111;
        atom["Cn"] = 112;
        atom["Uut"] = 113;
        atom["Uuq"] = 114;
        atom["Uup"] = 115;
        atom["Uuh"] = 116;
        atom["Uus"] = 117;
        atom["Uuo"] = 118;
        atom["La"] = 57;
        atom["Ce"] = 58;
        atom["Pr"] = 59;
        atom["Nd"] = 60;
        atom["Pm"] = 61;
        atom["Sm"] = 62;
        atom["Eu"] = 63;
        atom["Gd"] = 64;
        atom["Tb"] = 65;
        atom["Dy"] = 66;
        atom["Ho"] = 67;
        atom["Er"] = 68;
        atom["Tm"] = 69;
        atom["Yb"] = 70;
        atom["Ac"] = 89;
        atom["Th"] = 90;
        atom["Pa"] = 91;
        atom["U"] = 92;
        atom["Np"] = 93;
        atom["Pu"] = 94;
        atom["Am"] = 95;
        atom["Cm"] = 96;
        atom["Bk"] = 97;
        atom["Cf"] = 98;
        atom["Es"] = 99;
        atom["Fm"] = 100;
        atom["Md"] = 101;
        atom["No"] = 102;
       
        int out, left;
        int i, j, n, m;
        int s, a[20];
        string readin;
        string b[20], c[20];
       
        scanf ( "%d %d", &n, &m );
        for ( i = 0; i < n; i ++ ){
                cin >> readin;
                b[i] = readin;
                a[i] = atom[ readin ];
        }
        sum[0] = 0;
        for ( i = 0; i < n; i ++ ){
                s = ( 1 << i );
                for ( j = 0; j < s; j ++ )
                        sum[ s + j ] = sum[j] + a[i];
        }
       
        memset ( dp, 0, sizeof ( dp ) );
        dp[m][0] = make_pair( 1, 0 );
        for ( i = 0; i < m; i ++ ){
                cin >> readin;
                c[i] = readin;
                a[i] = atom[ readin ];
        }
        while( m -- )
                for ( i = ( 1 << n ) - 1; i >= 0; i -- )
                        if ( dp[ m + 1 ][i].first == 1 ){
                                s = ( 1 << n ) - 1 - i;
                                for ( j = s; j > 0; j = ( j - 1 ) & s )
                                        if ( sum[j] == a[m] )
                                                dp[m][ i + j ] = make_pair( 1, j );
                        }
        m = 0;
        if ( dp[0][ ( 1 << n ) - 1 ].first == 1 ){
                printf( "YES\n" );
                left = ( 1 << n ) - 1;
                while( left ){
                        out = dp[m][left].second;
                        for ( i = 0; i < n; i ++ )
                                if ( out & ( 1 << i ) ){
                                        printf( "%s", b[i].c_str() );
                                        out -= ( 1 << i );
                                        if ( out )
                                                printf( "+");
                                }
                        printf( "->%s\n", c[m].c_str() );
                        left -= dp[m][left].second;
                        m ++;
                }
        }
        else
                printf( "NO\n" );
        return 0;
}
