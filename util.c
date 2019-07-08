#include "9cc.h"

// 入力プログラム
char *user_input;

// エラーを報告するための関数
// printfと同じ引数を取る
void error(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

// エラー箇所を報告する
void error_at(char *loc, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  int pos = loc - user_input;
  fprintf(stderr, "%s\n", user_input);
  fprintf(stderr, "%*s", pos, "");  // pos個の空白を出力
  fprintf(stderr, "^ ");
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

void print_tokens(Token *cur) {
  while(cur->kind != TK_EOF) {
   fprintf(stderr, "kind: %d, val: %d ", cur->kind, cur->val);
   fprintf(stderr, "str: %.*s\n", cur->len, cur->str);
   cur = cur->next;
  }
}

void print_tree(Node *node) {
  fprintf(stderr, "kind: %d, val: %d\n", node->kind, node->val);
  if (node->kind == ND_NUM)
    return;
  print_tree(node->lhs);
  print_tree(node->rhs);
}
