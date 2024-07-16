#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<utility>
#include<sstream>
#include<cstring>
#include<cassert>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define FORD(I,A,B) for(int I=(A);I>=(B);I--)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define SIZE(x) ((int)(x).size())

typedef pair<char,short> PII;

const int M=1010;

const int RIGHT=0;
const int LEFT=1; 
const int INCREASING=1;
const int DECREASING=0;

int n;
int t[2][M][3];
bool set=false; 

inline bool match(int &a,int b)
{
    if (set)
    {
        if (!a) a=b;
    }
    return !a || !b || (a==b);
}

void harmonize()
{
    REP(i,n) REP(j,3) match(t[RIGHT][i][j],t[LEFT][n-1-i][j]);
    REP(j,3) REP(i,n)
    {
        printf("%d",t[RIGHT][i][j]);
        if (i<n-1) putchar(' ');
        else puts("");
    }
}

// INCREASING: +1   DECREASING: -1
inline int mono_coeff(int monot)
{
    return 2*monot-1;
}
inline int mono_curr(int x,int monot)
{
    int curr=3*x+1;
    if (monot==DECREASING) curr=3*n+1-curr;
    return curr;
}

char hamilton_t[2][M][3][2];
PII hamilton_print[2][M][3][2];

short draws_t[2][M][3][3*M+1][2];

int draw(int direction,int x,int y,int val,int monot)
{
    if (x==n || val<1 || val>3*n) return 0;
    short &w=draws_t[direction][x][y][val][monot];
    if (w!=-1) return w;
    if (!match(t[direction][x][y],val)) return w=0;
    return w=1+draw(direction,x+1,y,val+mono_coeff(monot),monot);
}

bool sequence(int direction,int x1,int y,int curr,int x2,int monot)
{
    if (set)
    {
        int diff=mono_coeff(monot);
        FOR(i,x1,x2) {
            if (!match(t[direction][i][y],curr)) return false;
            curr+=diff;
        }
        return true;
    }
    return draw(direction,x1,y,curr,monot)>=x2-x1+1;
}

/* Can the subrectangle [x1,x2] x [0,2] be covered with one
   zigzag "there - back - there" from field (x1,y)
   to field (x2,2-y)? */
int zigzag(int direction,int x1,int y,int x2,int monot)
{
    int curr=mono_curr(x1,monot),diff=mono_coeff(monot);
    if (!sequence(direction,x1,y,curr,x2,monot)) return false;
    curr+=(x2-x1+1)*diff;
    curr+=(x2-x1)*diff;
    if (!sequence(direction,x1,1,curr,x2,1-monot)) return false;
    curr+=diff;
    if (!sequence(direction,x1,2-y,curr,x2,monot)) return false;
    return true;
}

int curl(int direction,int x1,int y1,int len,int y2,int monot)
{
    int curr=mono_curr(x1,monot),diff=mono_coeff(monot);
    int x2=x1+len-1;
    if (!sequence(direction,x1,y1,curr,x2,monot)) return false;
    if (monot==INCREASING) curr=3*n;
    else curr=1;
    diff=-diff;
    curr+=(x2-x1)*diff;
    if (!sequence(direction,x1,3-y1-y2,curr,x2,monot)) return false;
    curr+=diff;
    if (!sequence(direction,x1,y2,curr,x2,1-monot)) return false;
    return true;
}

int curl_handshake(int direction,int x1,int y,int y1,int x2,int y2)
{
    int curr=1;
    if (!sequence(direction,x1,y1,curr,x2,INCREASING)) return false;
    curr+=3*(n-x2-1)+2*(x2-x1+1)-1;
    if (!sequence(direction,x1,y,curr,x2,DECREASING)) return false;
    curr+=3*x1+1;
    if (!sequence(direction,x1,y2,curr,x2,INCREASING)) return false;
    return true;
}

char hamilton2_t[2][M][3][3*M+1][3];
char hamilton2_print[2][M][3][3*M+1][3]; // used only if y1,y2!=1 (otherwise there is no choice)
const int MOVE_Y1=0;
const int MOVE_Y2=1;

/* Can the subrectangle [x,n-1] x [0,2] be covered with a Hamiltonian path
   starting at (x,y1) and ending at (x,y2), with increasing values,
   starting from the value val1? */
char hamilton2(int direction,int x,int y1,int val1,int y2)
{
    if (x==n && abs(y1-y2)==1) return true;
    if (x==n) return false;
    char &w=hamilton2_t[direction][x][y1][val1][y2];
    if (!set && w!=-1) return w;
    char &wo=hamilton2_print[direction][x][y1][val1][y2];

    int val2=val1+3*(n-x)-1;
    if (!match(t[direction][x][y1],val1)) return w=false;
    if (!match(t[direction][x][y2],val2)) return w=false;
    if (y1==1)
    {
        if (!match(t[direction][x][2-y2],val1+1)) return w=false;
        if (hamilton2(direction,x+1,2-y2,val1+2,y2)) return w=true;
    } else if (y2==1)
    {
        if (!match(t[direction][x][2-y1],val2-1)) return w=false;
        if (hamilton2(direction,x+1,y1,val1+1,2-y1)) return w=true;
    } else
    {
        // we have a choice
        if (wo!=MOVE_Y2)
        {
            if (match(t[direction][x][1],val1+1) && hamilton2(direction,x+1,1,val1+2,y2)) {
                wo=MOVE_Y1;
                return w=true;
            }
        }
        if (wo!=MOVE_Y1)
        {
            if (match(t[direction][x][1],val2-1) && hamilton2(direction,x+1,y1,val1+1,1)) {
                wo=MOVE_Y2;
                return w=true;
            }
        }
    }
    return w=false;
}

/* Can the subrectangle [x,n-1] x [0,2] be covered with a Hamiltonian path,
   starting from field (x,y) and ending with value 1 or 3n? */
char hamilton(int direction,int x,int y,int monot)
{
    if (x==n) return true;
    char &w=hamilton_t[direction][x][y][monot];
    if (!set && w!=-1) return w;
    PII &wo=hamilton_print[direction][x][y][monot];

    // option 1: zigzag
    if (y!=1)
    {
        FOR(i,x,n-1)
        {
            if (wo.FI!=-1 && !(wo.FI==1 && wo.SE==i)) continue;
            if (zigzag(direction,x,y,i,monot) && hamilton(direction,i+1,2-y,monot))
            {
                wo=MP(1,i);
                return w=true;
            }
        }
    }
    // option 2: hamilton2
    REP(y2,3) if (y2!=y)
    {
        if (wo.FI!=-1 && !(wo.FI==2 && wo.SE==y2)) continue;
        int curr=mono_curr(x,monot);
        if (monot==DECREASING) curr-=3*(n-x)-1;
        if ((monot==INCREASING &&  hamilton2(direction,x,y,curr,y2)) ||
                (monot==DECREASING && hamilton2(direction,x,y2,curr,y)))
        {
            wo=MP(2,y2);
            return w=true;
        }
    }
    // option 3: hamilton2 with a curl
    if (y!=1)
    {
        REP(y2,3) if (y2!=y) FOR(len,1,n-x-1)
        {
            if (wo.FI!=-1 && !(wo.FI==3 && wo.SE/n==y2 && wo.SE%n==len)) continue;
            int curr=mono_curr(x,monot),diff=mono_coeff(monot);
            if (!curl(direction,x,y,len,y2,monot)) continue;

            curr+=len*diff;
            int x1=x+len;
            if (monot==DECREASING) curr-=3*(n-x1)-1;
            if ((monot==INCREASING &&  hamilton2(direction,x1,y,curr,y2)) ||
                    (monot==DECREASING && hamilton2(direction,x1,y2,curr,y)))
            {
                wo=MP(3,n*y2+len);
                return w=true;
            }
        }
    }

    return w=false;
}

// the hook in the task - configuration of a different form
int wdirection=-1,wx1=-1,wx2=-1,wy=-1,wy1=-1;
int hook()
{
    REP(direction,2) FOR(x1,1,n-2) FOR(x2,x1,n-2) REP(y,3) REP(y1,3) if (y1!=y)
    {
        if (wdirection!=-1 && !(wdirection==direction && wx1==x1 && wx2==x2 && wy==y && wy1==y1)) continue;
        int y2=3-y-y1;
        if (!curl_handshake(direction,x1,y,y1,x2,y2)) continue;
        if (hamilton2(direction,x2+1,y1,x2-x1+2,y) && hamilton2(1-direction,n-1-(x1-1),y,2*(x2-x1+1)+3*(n-x2-1)+1,y2))
        {
            wdirection=direction;
            wx1=x1;
            wx2=x2;
            wy=y;
            wy1=y1;
            return true;
        }
    }
    return false;
}

int main()
{
    scanf("%d",&n);
    REP(j,3) REP(i,n) scanf("%d",t[RIGHT][i]+j);
    REP(i,n) REP(j,3) t[LEFT][i][j]=t[RIGHT][i][j];
    REP(i,n/2) REP(j,3) swap(t[LEFT][i][j],t[LEFT][n-1-i][j]);

    memset(hamilton_t,-1,sizeof(hamilton_t));
    memset(hamilton2_t,-1,sizeof(hamilton2_t));
    memset(hamilton_print,-1,sizeof(hamilton_print));
    memset(hamilton2_print,-1,sizeof(hamilton2_print));
    memset(draws_t,-1,sizeof(draws_t));

    // when configurations can be divided into two parts
    FOR(i,0,n) REP(y,3) REP(monot,2)
    {
        bool can=true;
        can &= hamilton(RIGHT,i,y,monot);
        can &= hamilton(LEFT,n-1-(i-1),y,1-monot);
        if (can)
        {
            set=true;
            hamilton(RIGHT,i,y,monot);
            hamilton(LEFT,n-1-(i-1),y,1-monot);
            harmonize();
            exit(0);
        }
    }
    if (hook())
    {
        set=true;
        hook();
        harmonize();
        exit(0);
    }
    return 0;
}
