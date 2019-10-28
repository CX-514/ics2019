#include "klib.h"
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

char* my_itoa(char* dest, int n, int base){
	/*transfer int into char[]*/
	//int outn = n;
	char number[20];
	for(int i = 0; i <= 9; ++i) number[i] = i + '0';
	number[10] = 'a'; number[11] = 'b'; number[12] = 'c';
	number[13] = 'd'; number[14] = 'e'; number[15] = 'f';
	if(n == 0) {
		dest[0] = '0';
		dest[1] = '\0';
		return dest;
	}
	
	int len = 0;
	int neg = 0;
	if(n < 0) {
		neg = 1;
		len ++;
		n = -n;
	}
	int temp = n;
	while(temp > 0){
		len ++;
		temp /= base;
	}
	
	for(int i = 0; i < len; ++i){
		int x = n % base;
		assert(x < 16);
		dest[len - i - 1] = number[x];
		//printf("dest[%d] = %c\n", len-i-1,dest[len-i-1]);
		n /= base;
	}
	if(neg) dest[0] = '-';
	dest[len] = '\0';
	//printf("%d -> %s\n",outn,dest);
	return dest;
}

int printf(const char *fmt, ...) {
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return 0;
}

int sprintf(char *out, const char *fmt, ...) {
/*  va_list ap;
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
  va_end(ap);
  return i; */
  //return 0;
  int len = strlen(fmt);
	int i = 0;
	int in_size = 0;
	va_list var_arg;
	va_start(var_arg, fmt);
	out[0] = '\0';

	while(i < len){
		if(fmt[i] == '%'){
			int in_num = 0;
			char in_char[50] = "";
			switch(fmt[i+1]){
				case 'd'://%d 
					in_num = va_arg(var_arg,int);
					my_itoa(in_char, in_num, 10);
					strcat(out, in_char);
					in_size += strlen(in_char);
					break;
				case 's'://%s
				 	strcpy(in_char,va_arg(var_arg, char*));
					strcat(out,in_char);
					in_size += strlen(in_char);
					break;
				default: printf("Not implememted argument type!\n");
			}
			i += 2;
		}
		else {
			char temp[2];
			temp[0] = fmt[i];
			temp[1] = '\0';
			strcat(out, temp);
			in_size ++;
			i ++;
		}
	}
		va_end(var_arg);
return in_size;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

#endif
