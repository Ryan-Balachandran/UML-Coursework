#ifndef scan_h
#define scan_h

typedef enum {t_read, t_write, t_id, t_literal, t_gets, t_add, t_sub, t_mult, t_div, t_lparen, t_rparen, t_eof,
              t_equiv, t_notEquiv, t_lt, t_gt, t_ltEquiv, t_gtEquiv, t_if, t_fi, t_do, t_od, t_check} token;

extern char token_image[100];
extern token scan();
//typedef void(*NR) ();

#endif /* scan_h */
