#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "xml.h"

extern FILE * yyin;
char * errormsg;

void failure ( char * progname )
{
    printf( "usage : %s [file]\n", progname );
    exit( EXIT_FAILURE );
}

void manage_args ( int argc, char ** argv, FILE ** fichier )
{
    if( argc > 2 ) failure( argv[0] );

    *fichier=NULL;
    if( argc == 2 )
    {
	*fichier = fopen( argv[1], "r" );
	if( *fichier == NULL ) failure( argv[0] );
	yyin = *fichier;
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
