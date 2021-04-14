/* Include this file once, if compiler supports 'pragma once' */
#pragma once

/* Classic header guard, suppoerted by any compiler */
#ifndef HEADS_H
#define HEADS_H

#ifdef _WIN32
/* Crazy Windows programmers should use these definitions.... */
/* Macro __MYLIBRARY_BUILD should be passed to
   compiler via command line argument:
   -D__MYLIBRARY_BUILD
*/
   
    #ifdef __MYLIBRARY_BUILD
        #define _OS_SPECIFIC __declspec(dllexport)
    #else
        #define _OS_SPECIFIC __declspec(dllimport)
    #endif
#else
/* *nix-like programmers are not so crazy like M$ */
    #define _OS_SPECIFIC /* just empty definition */
#endif

#ifdef __cplusplus
    #define MyLibAPI extern "C" _OS_SPECIFIC
#else
    #define MyLibAPI extern     _OS_SPECIFIC
#endif

MyLibAPI void f();
MyLibAPI void g();

#endif
