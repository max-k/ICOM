
#ifndef FILE_SD_H
#define FILE_SD_H

// un ensemble de string (taille maximale fixe: TSTRSET_MAXSIZE) 
#define TSTRSET_MAXSIZE 100
typedef struct _TstrSet {
    int   nb;
    char* t[TSTRSET_MAXSIZE];
} TstrSet;

// --------------------------------------------------------
// attribut et ensemble d'attributs
typedef enum _TattributKind { A_STR, A_INT, A_ENUM } TattributKind;

typedef struct _Tattribut {
    char*         id;
    TattributKind kind;
    union {
        struct { int min,max; } ival;
        TstrSet*                enumval;
    } u;
} Tattribut;

extern Tattribut* dtd_attNewStr(char* id);
extern Tattribut* dtd_attNewInt(char* id,int min, int max);
extern Tattribut* dtd_attNewEnum(char* id,TstrSet* s);

#define TATTSET_MAXSIZE 10
typedef struct _TattributSet {
    int        nb;
    Tattribut* t[TATTSET_MAXSIZE];
}TattributSet;

extern TattributSet* dtd_attSetNew();
extern void          dtd_attSetAdd(TattributSet* s, Tattribut* a);


// --------------------------------------------------------
// le contenu d'une balise

typedef enum _TcontentKind {
    C_EMPTY, C_DATA, C_RAWDATA, C_INT, C_TREE
} TcontentKind;
typedef struct _Tcontent {
    TcontentKind kind;
    union {
        char*                 rawdata;
        struct _TbaliseTree*  tree;
    } u;
} Tcontent;

extern Tcontent* dtd_contNew(TcontentKind k);

// --------------------------------------------------------
// balise et ensemble de balise

typedef struct _Tbalise {
    char*         name;
    TattributSet* attribut;
    Tcontent*     content;
} Tbalise;

// if the marker named n exists in the marker set, the function
// returns a pointer to it, otherwise it returns the null pointer.
extern Tbalise* dtd_balise_search(char* m);

// The function builds the marker named m with the a attribut set,
// the c content and then adds it to the marker set.
// The function returns a pointer to the built marker.
extern Tbalise* dtd_balise_add(char* m, TattributSet* a, Tcontent* c);

// return the number of markers with DATA content
extern int      dtd_balise_getNbData();
// return the number of markers with RAWDATA content
extern int      dtd_balise_getNbRawdata();
// run func(m,param) for every maker in the marker set.
extern Tbalise* dtd_balise_walk(void (*func)(Tbalise* b, void* param),void*param);

// --------------------------------------------------------
// expression de balise
typedef enum TbaliseTreeSuffKind {
    SF_ExactelyN, SF_ZeroOrOne, SF_ZeroOrMore, SF_AtLeastOne
} TbaliseTreeSuffKind;

typedef struct _TbaliseTreeSuff  {
    TbaliseTreeSuffKind kind;
    int                 n;
} TbaliseTreeSuff;

typedef enum TbaliseTreeKind {
    BT_BALISE, BT_CAT, BT_OR
} TbaliseTreeKind;

typedef struct _TbaliseTree  {
    char*                name;
    TbaliseTreeSuff      suffixe;
    TbaliseTreeKind      kind;
    struct _TbaliseTree* left;
    struct _TbaliseTree* right;
} TbaliseTree;

extern void         dtd_baltreeSetSuff(TbaliseTree* t, TbaliseTreeSuff s);
extern TbaliseTree* dtd_baltreeOpe(TbaliseTree* l, TbaliseTreeKind k, TbaliseTree* r);
extern TbaliseTree* dtd_baltreeLeaf(char* n, TbaliseTreeSuff s);

#endif
