
#include <stdlib.h>
#include <string.h>
#include <search.h>

#include "sd.h"

/**********************************************************************/
/**** marker tree handler                                          ****/

extern void         dtd_baltreeSetSuff(TbaliseTree* t, TbaliseTreeSuff s)
{
    t->suffixe = s;
}

extern TbaliseTree* dtd_baltreeOpe(TbaliseTree* l, TbaliseTreeKind k, TbaliseTree* r)
{
    TbaliseTree* ret  = calloc(1,sizeof *ret);
    ret->suffixe.kind = SF_ExactelyN;
    ret->suffixe.n    = 1;
    ret->kind         = k;
    ret->left         = l;
    ret->right        = r;
    return ret;
}

extern TbaliseTree* dtd_baltreeLeaf(char* n, TbaliseTreeSuff s)
{
    TbaliseTree* ret=calloc(1,sizeof *ret);
    ret->name    = n;
    ret->suffixe = s;
    ret->kind    = BT_BALISE;
    return ret;
}

/**********************************************************************/
/**** maker handler                                                ****/

static void* dtd_balises=0;
static int   dtd_NbBaliseWithData=0;
static int   dtd_NbBaliseWithRawdata=0;


extern Tcontent* dtd_contNew(TcontentKind k)
{
    Tcontent* ret=calloc(1,sizeof *ret);
    ret->kind = k;
    return ret;
}

static int      balise_cmp(const void *l, const void *r)
{
    return strcmp(((Tbalise*)l)->name,((Tbalise*)r)->name);
}

extern Tbalise* dtd_balise_search(char* n)
{
    Tbalise b; b.name=n;
    Tbalise** ret = (Tbalise**)tfind(&b,&dtd_balises,balise_cmp);
    return ret==0 ? 0 : *ret;
}

extern Tbalise* dtd_balise_add(char* n, TattributSet* a, Tcontent* c)
{
    Tbalise* b=calloc(1,sizeof *b);
    b->name     = n;
    b->attribut = a;
    b->content  = c;
    if (c->kind==C_DATA)
        dtd_NbBaliseWithData += 1;
    else if (c->kind==C_RAWDATA)
        dtd_NbBaliseWithRawdata += 1;
    Tbalise** ret = (Tbalise**)tsearch(b,&dtd_balises,balise_cmp);
    return ret==0 ? 0 : *ret;
}

static void (*dtd_walk_func)(Tbalise* b, void* param);
static void* dtd_walk_param;

static void     dtd_balise_walk_I(const void* b, const VISIT order, const int depth)
{
    if ( order!=preorder && order!=leaf ) return;
    dtd_walk_func(*(Tbalise**)b, dtd_walk_param);
}

extern Tbalise* dtd_balise_walk(void (*func)(Tbalise* b, void* param),void*param)
{
    dtd_walk_func = func;
    dtd_walk_param = param;
    twalk(dtd_balises,dtd_balise_walk_I);
}
