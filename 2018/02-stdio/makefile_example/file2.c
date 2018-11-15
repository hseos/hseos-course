#include "heads.h"
/* Second include of the same file has no effect due to
   header guard or 'pragma once' */
#include "heads.h"
#include <stdio.h>

int main() {

    /* These functions implemented in separate files
       For ANSI C it is not required to explicitly declare
       them, but for C99 and later - required (see separate
       headers file "heads.h" */
    f();   
    g(); /* _Z1gv(); /* -- without extern "C"  */

    char c;
    /* Read characters and put it back (shifted by 1)
       until there are some data in redirected input file
       or user presses Ctrl+D in terminal */
    while ((c=getchar())!=EOF) {
        putchar(c+1);
    }

    /* This next statement will be executed in case of EOF
       (user pressed Ctrl+D), but not program terminated
       (user pressed Ctrl+C) */
    printf("\nGoodbye!\n");
    
    /* getchar() keeps error in a special global variable
       on EOF event, so do not forget to explicitly return 0 */
    return 0;
}
