/*
 * WinDom: a high level GEM library
 * Copyright (c) 1997-2003 Dominique Bereziat & Arnaud Bercegeay
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * $Source: /cvsroot/windom/windom/include/windom.h,v $
 * WinDom header file
 *  
 * CVS info:
 *   $Author: bercegeay $
 *   $Date: 2004/11/23 18:59:27 $
 *   $Revision: 1.20 $
 */


#ifndef __WINDOM__
#define __WINDOM__

/*************************
 * Header files needed   *
 *************************/

#define __GEMLIB_OLDNAMES
#include <gem.h>
#include <gemx.h>

/* since GEMlib 43, both __GEMLIB__ and __MGEMLIB__ are defined */
#if !defined(__GEMLIB__)
# error This windom version require an up-to-date GEMLib
#endif
#if !defined(__MGEMLIB__)
# error This windom version require an up-to-date GEMLib
#endif

#ifdef __PUREC__
# define __MSHORT__
# include <stddef.h>
#endif

/*************************************************************
 *  WINDOM DEFINITIONS
 *************************************************************/

/* Macros functions 
 *************************/

#ifndef MIN
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

#define UNUSED( a)  ((void )(a))
#define IS_IN( xp, yp, x, y, w, h) (xp>=x && yp>=y && xp<x+w && yp<y+h)
#define FORM(win)   (((W_FORM*)DataSearch( win, WD_WFRM))->root)
#define TOOL( win) ((win)->tool.root)
#define GET_ICONBLK(t)	(((t)->ob_type==0x0D18)?(ICONBLK *)(t)->ob_spec.userblk->ub_parm:(t)->ob_spec.iconblk)
#define GET_CICONBLK(t)	(((t)->ob_type==0x0D18)?(CICONBLK *)(t)->ob_spec.userblk->ub_parm:(t)->ob_spec.ciconblk)

#ifndef ADR   /* Portab can defined this macro */
# define ADR(c)     (int)((long)(c)>>16), (int)(long)(c)
#endif
#define SET_BIT(field,bit,val) field = (val)?((field)|(bit)):((field) & ~(bit))

#ifndef TRUE
# define TRUE 1
# define FALSE 0
#endif

/* Structures
 ************************/
 
/* WinDom version */

#define __WINDOM_MAJOR__     1
#define __WINDOM_MINOR__     21
#define __WINDOM_REVISION__  3
#define __WINDOM_BETATAG__   ""

struct w_version {
    short patchlevel;
    short release;
    char *date;
    char *time;
    char *cc_name;
    short cc_version;
};

/* Application related definitions */

typedef INT16 W_COLOR[3];

#ifdef __GNUC__
struct _window;
#endif

typedef struct {
        /* Private variable */
        void   *conf;
        /* Public variable */
        int     id;             /* AES app id */
        INT16   handle;         /* VDI handle */
        INT16   aeshdl;         /* Screen VDI handle */
        INT16   x,y,w,h;        /* coord of desktop */
        int     color;          /* display # colors */
        int     nplanes;        /* display # planes (color=2^nplanes) */
        OBJECT  *menu;          /* desktop menu tree */
        W_COLOR *palette;       /* application color palette */
        INT16   work_in[11];    /* input of v_opnvwrk() */
        INT16   work_out[57];   /* output of v_opnvwrk() */
        int     aes4;           
        int     gdos;
        int     avid;
        int     ntree;
        char    *pipe;
        /* Private variables */
        void    *binding;
        void    *hilight;
        void    *mnbind;
        int		error;			/* Last error encoured */
    } APPvar;


/* Window related definitions */

typedef struct _grafport {
        INT16   handle;     /*  Handle station de travail virtuelle */
        W_COLOR *palette;   /*  Palette de couleur de la station    */
    } W_GRAFPORT;

typedef struct {
        OBJECT *root,*real; /* Le menu */
        int scroll;         /* gestion des scrollers */
        void *bind;
        void (*hilight)( struct _window *win, int title, int item);
#ifdef BETAMENU
        /* Activ menu */
        int ac_title, ac_item;
#endif
    } W_MENU;

typedef struct {
        OBJECT *root, *real;
        int  *save;
        void *bind;
        int edit, nb_ob;
        INT16 cursor;
    } W_FORM;

typedef struct {
        char *name;
        INT16 x , y, w, h;  /* Coordonn‚es originale de la fenˆtre
                              * non-ic“nifi‚e. */
        void (*draw)(struct _window *);
    } W_ICON;

typedef struct _window {
        int         handle;
        int         attrib;
        int         status;
        W_GRAFPORT  graf;
        W_MENU      menu;
        W_FORM      tool;
        W_ICON      icon;
        GRECT       createsize;
		int         __rsvd[11];
        char        *name, *info;
        INT16       w_max, h_max;
        INT16       w_min, h_min;
        long        xpos, ypos;
        long        xpos_max, ypos_max;
        INT16       w_u, h_u;
        struct _window *next;
        int         type;
        void        *data;
        void        *binding;
    } WINDOW;

/* Window global variable */

typedef struct {
        WINDOW *first;
        WINDOW *front;
        WINDOW *appfront;
    } WINvar;

typedef struct {
        long timer;
        int bclick, bmask, bstate;
        int m1_flag, m1_x, m1_y, m1_w, m1_h;
        int m2_flag, m2_x, m2_y, m2_w, m2_h;
        INT16 buff[8];
        INT16 mx, my, mbut, mkstate;
        INT16 keybd, nb_click;
    } EVNTvar;


typedef struct {
    long        nobs;
    long        ntree;
    long        nted;
    long        ncib;
    long        nib;
    long        nbb;
    long        nfstr;
    long        nfimg;
    OBJECT      *object;
    TEDINFO     *tedinfo;
    ICONBLK     *iconblk;
    BITBLK      *bitblk;
    CICON       *cicon;
    CICONBLK    *ciconblk;
    char        **frstr;
    BITBLK      **frimg;
    OBJECT      **trindex;
}   rscHDR;

/* BubbleGEM */

typedef struct {
    unsigned short delay;       /* d‚lai de fermeture */
    unsigned short flag ;       /* voir constantes */
} BHLP;

/* Constants
 ***********************/

/* app.aes4 */
#define AES4_BOTTOM         0x0001
#define AES4_ICONIFY        0x0002
#define AES4_ICONIFYXYWH    0x0004
#define AES4_SMALLER        0x0008
#define AES4_BOTTOMER       0x0010
#define AES4_APPSEARCH      0x0020
#define AES4_FSLX           0x0040
#define AES4_BEVENT         0x0080
#define AES4_UNTOPPED       0x0100
#define AES4_TOOLBAR        0x0200
#define AES4_APPLCONTROL    0x0400
#define AES4_XGMOUSE        0x0800
#define AES4_MNSELECTED		0x1000
#define AES4_MENUBAR		0x2000

/* Definitions for ApplGet()/ApplSet() 
 */

/* modes */
#define APS_ICONSIZE        0
#define APS_FLAG            1
#define APS_WINBG           2
#define APS_KEYCOLOR        3
#define APS_STRSTYLE        4
#define APS_BUTSTYLE        5
#define APS_EXITSTYLE       6
#define APS_TITLESTYLE      7
#define APS_3DEFFECT        8
#define APS_MENUEFFECT      9
#define APS_BUBBLESTYLE     10
#define APS_POPUPSTYLE      11
#define APS_POPUPWIND       12
#define APS_WINDOWS         13
#define APS_XTEDINFOSTYLE   14
#define APS_XLONGEDITSTYLE  15
#define APS_XEDITTEXTSTYLE  16
#define APS_XEDITLABELSTYLE 17
#define APS_FRAMEWIDGETSIZE 18

/* values */
#define DEFVAL     -1
#define CENTER      0
#define WMOUSE      1
#define UP_RIGHT    2
#define UP_LEFT     3
#define DN_RIGHT    4
#define DN_LEFT     5
#define WFORM       6

/* Bitfield for APS_FLAG */
#define FLG_KEYMOUSE  0x0001
#define FLG_BUTMOUSE  0x0002
#define FLG_NOPAL     0x0004
#define FLG_MNSCRL    0x0010
#define FLG_NOKEYMENU 0x0020
#define FLG_NOMGXFSEL 0x0040
#define FLG_MNSYSTEM  0x0080

/* app.key_color */
#define LTMFLY_COLOR  0x0010

/* RsrcXtype() mode */
#define RSRC_XTYPE 0x01   /* extended object type + color icons */
#define RSRC_X3D   0x02   /* standard 3D objects */
#define RSRC_XALL  0xFF   /* all (extended type + 3D objects)  */

/* WindFind() mode */
#define WDF_NAME  0
#define WDF_INFO  1
#define WDF_ID    2
#define WDF_MENU  3
#define WDF_FORM  4
#define WDF_TOOL  5
#define WDF_DATA  6

/* Cumulates window widgets */
#define WAT_ALL     0x4FFF  /* All widgets */
#define WAT_NOINFO  0x4FEF  /* All widget execpt the info bar */
#define WAT_FORM    0x400F  /* Formular: name, mover, closer, fuller, smaller */
#define WAT_MFORM   0x400D  /* Modal formular: name, mover, smaller, fuller */

/*  Windows status */
#define WS_OPEN         0x0001  /* window is opened */
#define WS_ICONIFY      0x0002  /* window is iconified */
#define WS_MENU         0x0004  /* window has menu */
#define WS_TOOLBAR      0x0008  /* window has toolbar */
#define WS_GROW         0x0010  /* window use graphic effects */
#define WS_UNTOPPABLE   0x0020  /* window is untoppable */
#define WS_FORM         0x0040  /* window is a formular */
#define WS_FORMDUP      0x0080  /* window is a duplicated formular */
#define WS_MODAL        0x0100  /* window is modal */
#define WS_FRAME_ROOT   0x0200  /* frame root window */
#define WS_FRAME        0x0400  /* framed window */
#define WS_ALLICNF      0x0800  /* all windows are iconified */
#define WS_FULLSIZE     0x1000  /* window has fulled size */
#define WS_PEXEC        0x2000  /* window is closed because of Pexec-call (reserved by ShelWrite) */

/*  WindSet() mode */
#define BEVENT_MODAL    0x1000
#define WF_ICONTITLE    1001
#define WF_ICONDRAW     1002
#define WF_HILIGHT      1003

/* FormWindDo() mode */ 
#define FORM_EVNT   0x8000
 
/* WindSlider() mode */
#define HSLIDER         0x0001
#define VSLIDER         0x0002

/* WinDom specific messages */
#define WM_DESTROY      0x4400    /* old value 1000 */
/*#define WM_MNSELECTED   0x4401 (deprecated) */
#define WM_FORM         0x4402
#define AP_LOADCONF     0x4403
#define AP_BUTTON       0x4404
#define AP_KEYBD        0x4405
#define AP_DEBUG        0x4410
#define WM_UPLINE       0x4411
#define WM_DNLINE       0x4412
#define WM_LFLINE       0x4413
#define WM_RTLINE       0x4414
#define WM_UPPAGE       0x4415
#define WM_DNPAGE       0x4416
#define WM_LFPAGE       0x4417
#define WM_RTPAGE       0x4418
#define WM_PREREDRAW	0x4419

/* EV_MSG extensions */
#define WM_XTIMER       1
#define WM_XKEYBD       2
#define WM_XBUTTON      3
#define WM_XM1          4
#define WM_XM2          5

/* EvntAdd() mode */
#define EV_BOT  0
#define EV_TOP  1

/* Reserved data magic number */
#define WD_WFRM 0x5746524DL /* 'WFRM' */
#define WD_WFRA 0x57465241L /* 'WFRA' */
#define WD_WFRI 0x57465249L /* 'WFRI' */
#define WD_WFNT 0x57464E54L /* 'WFNT' */
#define WD_WPOP 0x57504F50L /* 'WPOP' */

/* MenuPopUp() mode */
#define P_RDRW  0x0100
#define P_WNDW  0x0200
#define P_LIST  0x0400
#define P_CHCK  0x0800

/* ObjcChange() mode */
#define OC_TOOLBAR  0
#define OC_FORM     1
#define OC_OBJC     2
#define OC_MENU     3
#define OC_MSG      0x1000

/* ObjcAttach() type */
#define BIND_VAR    1
#define BIND_FUNC   2
#define BIND_BIT    3

/* SlidCreat() parameters */
#define SLD_HORI 0
#define SLD_VERT 1
#define SLD_DIFF 0
#define SLD_IMME 1

/* constants for FormAlert() */
#define FA_NOICON   "[0]"
#define FA_ERROR    "[1]"
#define FA_QUESTION "[2]"
#define FA_STOP     "[3]"
#define FA_INFO     "[4]"
#define FA_DISK     "[5]"

/* FontSel() flags */
#define VSTHEIGHT   0x01
#define BITMAP      0x02
#define MONOSPACED  0x04

/* Values for FrameSet() */
#define FRAME_BORDER 1
#define FRAME_COLOR  2
#define FRAME_KEYBD  3
#define FRAME_SIZE   4
#define FRAME_FLAGS  5
#define FRAME_NOBG   6
#define FRAME_ACTIV  7
#define FRAME_TOPPED_ACTIV  8

/* Values for FrameGet() */
#define FRAME_CELL   10

/* Flags for FrameAttach() */
#define FRAME_WSCALE    0x0001
#define FRAME_HSCALE    0x0002
#define FRAME_WFIX      0x0004
#define FRAME_HFIX      0x0008
#define FRAME_NOBORDER  0x0010
#define FRAME_SELECT    0x0020

/* Values for BHLP.flag */
#define BGC_FONTCHANGED     0x01
#define BGC_NOWINSTYLE      0x02
#define BGC_SENDKEY         0x04
#define BGC_DEMONACTIVE     0x08
#define BGC_TOPONLY         0x10

/* AvStatus() return value */
#define V_SENDKEY       0x0001
#define V_ASKFILEFONT   0x0002
#define V_ASKCONFONT    0x0004  /* OPENCONSOLE */
#define V_ASKOBJECT     0x0008
#define V_OPENWIND      0x0010
#define V_STARTPROG     0x0020
#define V_ACCWINDOPEN   0x0040  /* ACCWINDCLOSED */
#define V_STATUS        0x0080  /* GETSTATUS */
#define V_COPY_DRAGGED  0x0100
#define V_PATH_UPDATE   0x0200  /* AV_PATH_UPDATE, WHAT_IZIT, DRAG_ON_WINDOW */
#define V_EXIT          0x0400
#define V_XWIND         0x0800
#define V_FONTCHANGED   0x1000
#define V_STARTED       0x2000
#define V_QUOTE         0x4000
#define V_FILEINFO      0x8000  /* FILECHANGED */

/* Valeur du mot 4 de VA_PROTOSTATUS
 * ou du mot 1 retourn‚ par av_status()
 */ 

#define V_COPYFILE      0x0001  /* FILECOPIED */
#define V_DELFILE       0x0002  /* FILEDELETED */
#define V_VIEW          0x0004  /* FILEVIEWED */
#define V_SETWINDPOS    0x0008

/* AvInit() mode */
#define A_SETSTATUS     0x0001
#define A_START         0x0002
#define A_STARTED       0x0004
#define A_FONTCHANGED   0x0008
#define A_QUOTE         0x0010
#define A_PATH_UPDATE   0x0020

/* vqt_xname() flags */
#define FNT_OUTLINE     0x1 /* 0=bitmap 1=vectorielle */
#define FNT_MONO        0x2 /* 0=non proportionnelle, 1=proportionnelle */
#define FNT_SPEEDO      0x4
#define FNT_TRUETYPE    0x8
#define FNT_TYPE1       0x10

/* vqt_xfntinfo() flags */
#define XFNT_NAME       0x1
#define XFNT_FAMILLY    0x2
#define XFNT_STYLE      0x4
#define XFNT_FILE       0x8
#define XFNT_NBPTS      0x100
#define XFNT_LISTPTS    0x200

/* Global variables
 ***********************/

extern struct w_version WinDom;
extern APPvar           app;
extern WINvar           wglb;
extern EVNTvar          evnt;
extern GRECT            clip;
extern short*           _AESglobal;

/* Function Prototypes
 ***********************/

/* Application Library */

/* int     ApplInit    ( void); */
int		ApplInit	( void);
int     ApplInit_   ( short *global);
int     ApplReInit  ( short *global);
int     ApplExit    ( void);
int     ApplGet     ( int mode, ...);
int     ApplSet     ( int mode, ...);
int     ApplName    ( char *name, int handle);
int     ApplWrite   ( int to, int msg, ...);
int     ApplControl ( int ap_cid, int ap_cwhat);

/* AV library */

int     AvInit      ( char *name, int status, long idle);
void    AvExit      ( void);
INT16*  AvStatus    ( void);
char*   AvStrfmt    ( int mode, char *src);
char*   AvServer    ( void);
int     AvWaitfor   ( int, INT16 *, long);

/* Cookies library */

long*   get_cookiejar( void);
int     new_cookie  (long cookie, long value);
int     get_cookie  (long cookie, long *value);
int     set_cookie  (long cookie, long value);

/* BubbleGEM library */ 

int     BubbleCall  ( char *help, int x, int y);
int     BubbleModal ( char *help, int x, int y);
int     BubbleDo    ( OBJECT *tree, int __index);
int     BubbleAttach( OBJECT *tree, int __index, char *help);
void    BubbleFree  ( void);
int     BubbleFind  ( OBJECT *tree, int __index, char **help);
int     BubbleEvnt  ( void);
void    BubbleConf  ( BHLP conf);
int     BubbleGet   ( void);
 
/* Configuration library */

int     ConfRead    ( void);
int     ConfInquire ( char *keyword, char *fmt, ...);
int     ConfGetLine ( char *line);
int     ConfWrite   ( char *keyword, char *fmt, ...);
int		ConfWindom	( void);

/* Data library */

int     DataAttach  ( WINDOW *win, long magic, void *data);
int     DataDelete  ( WINDOW *win, long magic);
void*   DataSearch  ( WINDOW *win, long magic);

/* Event library */

int     EvntWindom  ( int __evnt);
int     EvntAdd     ( WINDOW *win, int msg, void *proc, int mode);
int     EvntAttach  ( WINDOW *win, int msg, void *proc);
int     EvntDataAdd ( WINDOW *win, int msg, void *proc, void *data, int mode);
int     EvntDataAttach
					( WINDOW *win, int msg, void *proc, void *data);
int     EvntDelete  ( WINDOW *win, int msg);
void*   EvntFind    ( WINDOW *win, int msg);
int     EvntExec    ( WINDOW *win, int msg);
void    EvntClear   ( WINDOW *win);
int     EvntRemove  ( WINDOW *win, int msg, void *proc);
void    EvntDisable ( WINDOW *win, int msg);
void    EvntEnable  ( WINDOW *win, int msg);
void    EvntRedraw  ( WINDOW *win);

/* Formular library */

WINDOW* FormWindBegin( OBJECT *dial, char *nom);
void    FormWindEnd  ( void);
int     FormWindDo   ( int __evnt);

int     FormAttach  ( WINDOW *win, OBJECT *tree, void *func);
void 	FormResize	( WINDOW *win, INT16 *x, INT16 *y, INT16 *w, INT16 *h);
WINDOW* FormCreate  ( OBJECT *tree, int attrib, void *func, char *name, GRECT *coord, int grow, int dup);
int     FormSave    ( WINDOW *win, int mode);
int     FormRestore ( WINDOW *win, int mode);
void    FormBegin   ( OBJECT *tree, MFDB *bckgrnd);
void    FormEnd     ( OBJECT *tree, MFDB *bckgrnd);
#define FormDo(a,b) form_do(a,b)
int     FormAlert   ( int but, char fmt[], ...);
void*   FormThumb   ( WINDOW *win, int *idxthb, int *idxbut, int nb);
void    FormThbSet  ( WINDOW *win, int but);
int     FormThbGet  ( void   *thb, int mode);

/* Mouse library */

void    MouseObjc   ( OBJECT *tree, int __index);
void    MouseWork   ( void);
void    MouseSprite ( OBJECT *tree, int __index);

/* Frame library */

void    FrameInit   ( void);
void    FrameExit   ( void);
WINDOW* FrameCreate ( int attrib);
void    FrameAttach ( WINDOW *win, WINDOW *src, int line, int col, int w, int h, int mode);
WINDOW* FrameRemove ( WINDOW *win, WINDOW *child, int line, int col);
void    FrameSet    ( WINDOW *win, int mode, ...);
void 	FrameGet	( WINDOW *win, int mode, ...);
WINDOW* FrameFind   ( WINDOW *win, int x, int y);
WINDOW* FrameSearch ( WINDOW *win, int line, int col);
int     FrameCalc   ( WINDOW *win, int mode, INT16 *x, INT16 *y, INT16 *w, INT16 *h);

/* Font  library */

int     FontName2Id ( char *name);
int     FontId2Name ( int id, char *name);
int     VstLoadFonts( int vh, int res);
void    VstUnloadFonts
                    ( int vh, int res); 
int     VstFont     ( int vh, int id) ;
int     VqtName     ( int vh, int elem, char *name) ;
int     VqtXname    ( int vh, int id, int __index, char *name, int *fl);

/* Selector library */

int     file_select ( char *pfname, char *pname, char *fname, const char *ext, char *title);
int     FselInput   ( char *path, char *fname, char *ext, char *title, char *lpath, char *lext);
int     FontSel     ( char *title, char *example, int flags, int *id, int *size, char *name);

/* Menu library */

int     MenuBar     ( OBJECT *menu, int mode);
int     MenuTnormal ( WINDOW *win, int title, int mode);
int     MenuIcheck  ( WINDOW *win, int title, int mode);
int     MenuText    ( WINDOW *win, int title, char *txt);
int     MenuDisable ( void);
int     MenuEnable  ( void);
int     MenuPopUp   ( void *data, int x, int y, int max, int size, int item, int mode);
void    MenuScroll  ( WINDOW *win, int dir);
int		MenuAttach	( int flag, OBJECT *tree, short item, MENU *mdata);

/* Object library */

int     ObjcAttach      ( int mode, WINDOW *win, int __index, int type, ...);
int     ObjcChange      ( int mode, void *data, int __index, int state, int redraw);
int     ObjcDraw        ( int mode, void *win, int __index, int depth);
OBJECT* ObjcDup         ( OBJECT *tree, WINDOW *win);
int     ObjcEdit        ( int mode, WINDOW *win, int obj, int val, INT16 *idx, int kind);
void    ObjcFree        ( OBJECT *tree);
char*   ObjcString      ( OBJECT *tree, int __index, char *put);
#define ObjcStrCpy(tree,index,str)  strcpy(ObjcString(tree,index,NULL),str)
void    ObjcStrFmt      ( char *dest, char *src, int size);
void    ObjcStr3d       ( OBJECT *tree);
int     ObjcWindDraw    ( WINDOW *win, OBJECT *tree, int __index, int depth, int xclip, int yclip, int wclip, int hclip);
int     ObjcWindChange  ( WINDOW *win, OBJECT *tree, int __index, int xclip, int yclip, int wclip, int hclip, int state);
OBJECT *ObjcTree		( int mode, WINDOW *win);

/* Window library */

WINDOW* WindCreate  ( int GemAttrib, int x, int y, int w, int h);
int     WindOpen    ( WINDOW *win, int x, int y, int w, int h);
int     WindClose   ( WINDOW *win);
int     WindDelete  ( WINDOW *win);
WINDOW* WindHandle  ( int handle);
#ifdef __MSHORT__
int     WindSet     ( WINDOW *win, int mode, ...);
int     WindGet     ( WINDOW*, int, ...);
#define WindSetStr  WindSet
#define WindSetPtr  WindSet
#else
int     WindSet     ( WINDOW *win, int mode, int x, int y, int w, int h);
int     WindGet     ( WINDOW*, int, INT16*, INT16*, INT16*, INT16*);
#define WindSetStr(w,m,s) \
        WindSet(w,m,(long)(s)>>16,(long)(s)&0xFFFFL,0,0)
#define WindSetPtr(w,m,p,q) \
        WindSet(w,m,(long)(p)>>16,(long)(p)&0xFFFFL,(long)(q)>>16,(long)(q)&0xFFFFL)
#endif
int     WindCalc    ( int type, WINDOW *wind, int xin, int yin,
                      int win, int hin, INT16 *xout, INT16 *yout, 
                      INT16 *wout, INT16 *hout);
void    WindSlider  ( WINDOW *win, int mode);
void    WindClear   ( WINDOW *win);
WINDOW* WindAttach  ( int handle);
WINDOW* WindFind    ( int mode, ...);
void    WindTop     ( WINDOW *win);
void	WindNew		( void);
void    add_windowlist   ( int);
void    remove_windowlist( int);
int 	bottom_windowlist( void);

/* Slider library (for window formular) */
void*	SlidCreate	( float min, float max, float sinc, float linc, float value, int ori, int upd);
void  	SlidAttach	( void *slid, int mode, WINDOW *win, int up, int bsld, int sld, int dn);
float 	SlidGetValue( void *slid);
void  	SlidSetFunc ( void *slid, void *func, void *data);
void  	SlidSetSize ( void *slid, int size);
void  	SlidSetValue( void *slid, float value);
void  	SlidSetUpdat( void *slid, int upd);

/* Ressource library */

int     RsrcLoad        ( const char *name);
void    RsrcXtype       ( int mode, OBJECT **rs_trindex, int num_tree);
void    RsrcFixCicon    ( OBJECT *object, int num_obs, int num_cib, INT16 palette[][4], void *fix);
void    RsrcFreeCicon   ( void *fix);
int     RsrcUserDraw    ( int mode, WINDOW *win, int __index, void *draw, void *data);
#define RsrcFree    rsrc_free
void*   RsrcXload       ( const char *name);
void    RsrcXfree       ( void *rsc);
int     RsrcGaddr       ( void *rsc, int type, int __index, void *addr);
rscHDR* RsrcGhdr        ( void *rsc);


/* Inquire library */

int     has_appl_getinfo( void);
int     vq_tos      ( void);
int     vq_magx     ( void);
int 	vq_mint		( void);
int     vq_nvdi     ( void);
int     vq_naes     ( void);
int     vq_winx     ( void);
int		vq_xaaes	( void);
int     vq_extfs    ( char *);
int     vqt_extname ( int handle, int __index, char *name, int *speedo, INT16 *format, INT16 *flags);
int     vqt_xname   ( int handle, int id, int __index, char *name, int *flags);

/* Utility library */

void    give_iconifyxywh
                    ( INT16 *x, INT16 *y, INT16 *w, INT16 *h);
void    snd_rdw     ( WINDOW *win);
void    snd_arrw    ( WINDOW *win, int msg);
void    rc_set      ( GRECT *, int, int, int, int);
void    rc_clip_on  ( int handle, GRECT *r);
void    rc_clip_off ( int handle);
void    w_getpal    ( W_COLOR *palette);
void    w_setpal    ( W_COLOR *palette);
void    w_get_bkgr  ( int of_x, int of_y, int of_w, int of_h, MFDB *img);
void    w_put_bkgr  ( int of_x, int of_y, int of_w, int of_h, MFDB *img);
int     keybd2ascii ( int keybd, int shift);
char*   conv_path   ( char *);

int     CallStGuide ( char *);
int     ShelWrite   ( char *prg, char *cmd, void *env, int av, int single);
void    DebugWindom ( const char *format, ...);
void*   Galloc      ( long size);
void    GrectCenter ( int w, int h, INT16 *x, INT16 *y );

void    form_close  ( WINDOW *win, int __index, int mode);

#endif /* __WINDOM__ */
