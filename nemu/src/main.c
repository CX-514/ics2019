#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<monitor/expr.h>


int init_monitor(int, char *[]);
void ui_mainloop(int);
uint32_t expr(char *e, bool *success);

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
  int is_batch_mode = init_monitor(argc, argv);

  char buf[1000];
  int count=0,suc=0;
  FILE *fp = fopen("/home/cx/ics2019/nemu/tools/gen-expr/input","r");
  while(fgets(buf,1000,fp)) {
    char *arg1 = strtok(buf, " ");
    char *arg2 = strtok(NULL, "/n");
    bool success = true;
    int n;
    sscanf(arg1,"%d", &n);
    int result=expr(arg2,&success);
    if (success) {
      if (result==n)
        suc++;
    }
    count++; 
  }
  fclose(fp);
  float acc = suc/count;
  printf("%.3f",acc);
  
  /* Receive commands from user. */
  ui_mainloop(is_batch_mode);

  
  return 0;
}
