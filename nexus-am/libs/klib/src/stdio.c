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
  int sum=0;
  int i=0;
  int len=strlen(fmt);
  while(i<len) {
    if(fmt[i]=='%') {
      int num=0;
      char ls[50]="";
      switch(fmt[i+1]) {
        case 'd': {
	  		num=va_arg(ap,int);
	  		char number[20];
	  		for (int j=0;j<10;j++) {number[j]=j+'0';}
			number[10] = 'a'; number[11] = 'b'; number[12] = 'c'; number[13] = 'd'; number[14] = 'e'; number[15] = 'f';
	  		int l=0;
	  		int neg=0;
			if(num==0) {
	    		ls[0]='0';
	    		ls[1]='\0';
	  		}
	  		if(num<0) {
	    		neg=1;
	    		l++;
	    		num=-num;
	  		}
	  		int temp=num;
	  		while(temp>0) {
	    		l++;
	    		temp=temp/10;
	  		}
	  		for (int a=0; a<l; a++) {
	    		int x=num%10;
				assert(x<16);
	    		ls[l-a-1]=number[x];
	    		num=num/10;
	  		}
	  		if(neg) ls[0]='-';
	  		ls[l]='\0';
	  		strcat(out,ls);
	  		sum+=strlen(ls);	
        } break;
		case 's': {
	  		strcpy(ls,va_arg(ap, char*));
	  		strcat(out,ls);
	  		sum += strlen(ls);
		}break;
	  } 
    	i+=2;
	}
    else {
      	sum++;
      	char s[2];
      	s[0]=fmt[i];
      	s[1]='\0';
      	strcat(out,s);
      	i++;
  	}
 }
  va_end(ap);
  return sum; 
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

#endif
