#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

int count=0;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp() {
  if (count == 0) {
    init_wp_pool();
  }
  WP *p = free_;
  if (p != NULL) {
    free_ = free_->next;
    p -> next = head;
    head = p;
    count++;
    return p;
  }
  else {
    assert(0);
  }
}
/*
void free_wp(WP *wp) {
  WP *p = head;
  WP *q = p;
  if (p == NULL) {
    printf()
  }
}*/
