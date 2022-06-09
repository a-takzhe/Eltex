#ifndef DATA_H__
#define DATA_H__

#define HTOOL_MES "[Insert File Name]: "
#define MAXCOL 128
#define MAXCOL2 64
#define MAXROW 64

typedef struct PNT
{
    unsigned short x;
    unsigned short y;
    unsigned short max_X, max_y;
} point;

WINDOW *__MAINWND__;
WINDOW *__HTOOLWND__;
WINDOW *__TOOLSWND__;

char NOTE[MAXROW][MAXCOL];
char TROW[MAXCOL2];

point PN, PT, PW;

#endif