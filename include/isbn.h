/*
  isbn.h
*/

#ifndef __ISBN_H__
#define __ISBN_H__

// UNICODE and _UNICODE are defined in isbn.cbp
// #define UNICODE
// #define _UNICODE
#include <wchar.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

typedef unsigned char uchar;
typedef unsigned short ushort;

#ifdef BUILD_DLL
  #define DLL_EXPORT __declspec(dllexport)
#else
  #define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

int DLL_EXPORT isbn_collect(int m, char *dst, char *src);
int DLL_EXPORT isbn_check_digit(BOOL beep, int len, int m, char *buf, uchar b);
uchar DLL_EXPORT isbn_mod_digit(ushort b, uchar n);
char DLL_EXPORT isbn13(char *buf);
char DLL_EXPORT isbn10(char *buf);

#ifdef __cplusplus
}
#endif

#endif // __ISBN_H__
