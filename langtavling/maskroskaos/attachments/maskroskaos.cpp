#include "maskroskaos.h"

void Solve(int N)
{
    // Pretty bad strategy
    int v = Query(1);
    for (int i = 0; i < N; ++i)
    {
        Answer(i*2+1, i*2+2);
    }
}
