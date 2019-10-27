#include "klib.h"
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return 0;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap,fmt);
  int i=0;
  while(*fmt!='\0') {
    if(*fmt=='%') {
      fmt++;
      switch(*fmt) {
        case 'd': {
	  fmt++;
	  int j=va_arg(ap,int);
	  char ls[50]="";
  	  int m,s;
	  m=0;
	  if(j>0) {
 	    while(j>0) {
	      ls[m++]=(j%10)+'0';
	      j=j/10;
	    }
	    s=0;
	  }
	  else if(j==0) {ls[m++]='0';s=0;}
	  else if(j<0) {
	     while(j<0) {
                ls[m++]=(-(j%10))+'0';
                j=j/10;
             }
             s=1;
	  }
	  if(s==1) {*out='-';out++;i++;}
	  for(int n=m-1; n>=0;n--) {
	    *out=ls[n];
 	    i++;
	    out++;
	  }break;
        }
	case 's': {
	  fmt++;
	  char *src=va_arg(ap,char*);
	  while(*src!='\0') {
	    *out=*src;
	    i++;
	    out++;
	  }break;
	}
      }
    }
    else {
      *out=*fmt;
      i++;
      out++;
      fmt++;
    }
  }
  *out='\0';
  return i;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

#endif
