#include "klib.h"

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t len;
  for(len=0; s[len]!='\0';len++);
  return len;
}

char *strcpy(char* dst,const char* src) {
  char *tmp=dst;
  while((*dst++=*src++) != '\0');
  //while(*dst++!=*src++);
  return tmp;
  /*size_t i;
  for(i=0;src[i]!='\0';i++) {
    dst[i]=src[i];
  }
  dst[i]='\0';*/
}

char* strncpy(char* dst, const char* src, size_t n) {
  size_t i;
  for(i=0;i<n && src[i]!='\0';i++) 
    dst[i]=src[i];
  for(;i<n;i++) 
    dst[i]='\0';
  return dst;
}

char* strcat(char* dst, const char* src) {
/*  size_t i,j;
  i=strlen(dst);
  for(j=0;src[j]!='\0';j++) {
    dst[i+j]=src[j];
  }
  dst[i+j]='\0';
  return dst;*/
  char *str=dst;
  assert(dst!=NULL &&src!=NULL);
  while(*dst!='\0') {
    dst++;
  }
  while((*dst++=*src++) != '\0');
  return str;
}

int strcmp(const char* s1, const char* s2) {
  int res=0;
  while(*s1 && *s2 && (res=(*s1-*s2))==0) {
    s1++,s2++;
  }
  return res;
}

int strncmp(const char* s1, const char* s2, size_t n) {
  int res=0;
  while(n-- && *s1 && *s2 && (res=(*s1-*s2))==0) {
    s1++,s2++;
  }
  return res;
}

void* memset(void* v,int c,size_t n) {
  unsigned char* p=v;
  while(n--)
    *p++ = (unsigned char)c;
  return v;
}

void* memcpy(void* out, const void* in, size_t n) {
  char *dp=out;
  const char *sp=in;
  while(n--) {
    *dp++ = *sp++;
  }    
  return out;
}

int memcmp(const void* s1, const void* s2, size_t n){
  const unsigned char *p1=s1,*p2=s2;
  while(n--) 
    if(*p1 != *p2)
      return *p1-*p2;
    else
      p1++,p2++;
  return 0;
}

#endif
