/*
  isbn.c

  https://ja.wikipedia.org/wiki/ISBN
*/

#include "isbn.h"

int DLL_EXPORT isbn_collect(int m, char *dst, char *src)
{
  int len = 0;
  for(char b, *p = src, *q = dst; (b = *p++) && len < m; ){
    if(b >= '0' && b <= '9') *q++ = b - '0', ++len;
  }
  return len;
}

int DLL_EXPORT isbn_check_digit(BOOL beep, int len, int m, char *buf, uchar b)
{
  if(len == m){ if(buf[m - 1] != b){ if(beep){ printf("\a"); } return 0; } }
  return 1;
}

uchar DLL_EXPORT isbn_mod_digit(ushort b, uchar n)
{
  return (n - (b % n)) % n;
}

char DLL_EXPORT isbn13(char *buf)
{
  char b[13];
  int len = isbn_collect(sizeof(b), b, buf);
  uchar s = 0;
  for(int i = 0; i < 6; ++i){
    s += b[i * 2] + b[i * 2 + 1] * 3;
  }
  uchar r = isbn_mod_digit(s, 10);
  isbn_check_digit(TRUE, len, sizeof(b), b, r);
  return r + '0';
}

char DLL_EXPORT isbn10(char *buf)
{
  char b[10];
  int len = isbn_collect(sizeof(b), b, buf);
  ushort s = 0;
  for(int i = 0; i < 9; ++i){
    s += b[i] * (10 - i);
  }
  uchar r = isbn_mod_digit(s, 11);
  isbn_check_digit(TRUE, len, sizeof(b), b, r);
  return r == 10 ? 'X' : (r + '0');
}

#ifdef __cplusplus
extern "C" {
#endif

BOOL DLL_EXPORT APIENTRY DllMain(HINSTANCE hInst, DWORD reason, LPVOID lpv);

#ifdef __cplusplus
}
#endif

BOOL DLL_EXPORT APIENTRY DllMain(HINSTANCE hInst, DWORD reason, LPVOID lpv)
{
  switch(reason){
  case DLL_PROCESS_ATTACH: break; // attach to process FALSE to fail DLL load
  case DLL_PROCESS_DETACH: break; // detach from process
  case DLL_THREAD_ATTACH: break; // attach to thread
  case DLL_THREAD_DETACH: break; // detach from thread
  default: break;
  }
  return TRUE; // success
}
