#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dtd.h"

extern FILE * yyin;
char * errormsg;

void failure ( char * progname )
{
    printf( "usage : %s <file> [exe] \n", progname );
    exit( EXIT_FAILURE );
}

void manage_args ( int argc, char ** argv, FILE ** fichier )
{
    if( argc > 3 ) failure( argv[0] );

    if( argc == 3 )
    {
        FILE* fichierExe = NULL;
        fichierExe = fopen( argv[2], "w" );
        if (fichierExe == NULL) failure( argv[0] );
        fputs( "code executable", fichierExe );
        fclose( fichierExe );
    }


    *fichier=NULL;
    if( argc == 2 )
    {
    	if( strcmp( argv[1], "-" ) != 0 )
    	{
	    *fichier = fopen( argv[1], "r" );
	    if( *fichier == NULL ) failure( argv[0] );
	    yyin = *fichier;
    	}
    }
}

int main ( int argc, char ** argv )
{
    FILE * fichier;
    manage_args( argc, argv, &fichier );
    yyparse();
    if( fichier != NULL ) fclose( fichier );
    return 0;
}
