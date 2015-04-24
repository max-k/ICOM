#include <stdlib.h>

#include "sd.h"

static Tattribut* dtd_attNewI(char*id, TattributKind k)
{
    Tattribut* ret=calloc(1, sizeof *ret);
    ret->id = id;
    ret->kind=k;
    return ret;
}

Tattribut* dtd_attNewStr(char*id)
{
    Tattribut* ret=dtd_attNewI(id, A_STR);
    return ret;
}

Tattribut* dtd_attNewInt(char*id,int min, int max)
{
    Tattribut* ret=dtd_attNewI(id, A_INT);
    ret->u.ival.min=min;
    ret->u.ival.max=max;
    return ret;
}

Tattribut* dtd_attNewEnum(char*id, TstrSet* s)
{
    Tattribut* ret=dtd_attNewI(id, A_STR);
    ret->u.enumval=s;
    return ret;
}

TattributSet* dtd_attSetNew()
{
    TattributSet* ret=calloc(1, sizeof *ret);
    return ret;
}

void dtd_attSetAdd(TattributSet* s, Tattribut* a)
{
    s->t[s->nb++]=a;
}

