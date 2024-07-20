/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int scalepreview       = 4;        /* preview scaling (display w and h / scalepreview) */
static const int previewbar         = 1;        /* show the bar in the preview window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
#define ICONSIZE 18   /* icon size */
#define ICONSPACING 10 /* space between icon and title */
static const char *fonts[]          = { "MesloLGS Nerd Font Mono:size=14", "NotoColorEmoji:pixelsize=12:antialias=true:autohint=true"  };
static const char dmenufont[]       = "MesloLGS Nerd Font Mono:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
// static const char col_gray4[]       = "#eeeeee"; 
static const char col_gray4[]       = "#1c1f24"; 
static const char col_cyan1[]        = "#0993b3";
static const char col_cyan[]        = "#e6a709";
// static const char col_cyan[]        = "#d98116";#e6a709
static const char col_blue[]        = "#005577";
static const char col_col1[]        = "#51afef";
static const char col_col2[]        = "#c678dd";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_blue },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan1  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm",	"-g",	"200x44", NULL };
const char *spcmd2[] = {"st", "-n", "splf",	"-g",	"200x44", "-e", "lfub", NULL };
const char *spcmd3[] = {"st", "-n", "spnvim",	"-g",	"200x44", "-e", "nvim", NULL };
const char *spcmd4[] = {"keepassxc", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"splf",	spcmd2},
	{"spnvim",	spcmd3},
	{"keepassxc",   spcmd4},
};

static const char *const autostart[] = {
	"dwmblocks", NULL,
	"picom", NULL,
	"variety", NULL,
	// "st", NULL,
	NULL /* terminate */
};

static const char *tagsel[][2] = {
   /*   fg         bg    */
  { col_gray3, col_gray1 }, /* norm */
  { col_gray1, col_cyan1  }, /* sel */
  // { col_gray4, col_cyan1  }, /* sel */
  { col_gray1, col_col2 }, /* occ but not sel */
  // { col_cyan,  col_gray1 }, /* occ but not sel */
  // { col_cyan,  col_gray3 }, /* has pinned tag */
  { col_cyan,  col_gray3 }, /* has pinned tag */
};
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class	     instance	      title             tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",            NULL,            NULL,             0,         1,          0,           0,        -1 },
	{ "firefox",         NULL,            NULL,             1 << 1,    0,          0,          -1,        -1 },
	{ "thunderbird",     NULL,            NULL,             1 << 2,    0,          0,          -1,        -1 },
	{ "Emacs",           NULL,            NULL,             1 << 3,    0,          0,          -1,        -1 },
	{ "Code",            NULL,            NULL,             1 << 0,    0,          0,          -1,        -1 },
	{ "st",		     NULL,            NULL,             0,         0,          1,           0,        -1 },
	{ "alacritty",       NULL,            NULL,             0,         0,          1,           0,        -1 },
	{ NULL,              NULL,            "Event Tester",   0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,	             "spterm",        NULL,		SPTAG(0),  1,	       1,	    0,	      -1 },
	{ NULL,	             "splf",          NULL,	       	SPTAG(1),  1,	       1,	    0,	      -1 },
	{ NULL,	             "spnvim",        NULL,	       	SPTAG(2),  1,	       0,	    0,	      -1 },
	{ NULL,	             "keepassxc",     NULL,	       	SPTAG(3),  1,	       0,	    0,	      -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	// { "===",      bstackhoriz },
	// { "HHH",      grid },
	// { "###",      nrowgrid },
	// { "---",      horizgrid },
	// { ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#include <X11/XF86keysym.h>
#define PrintScreenDWM 0x0000ff61
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)                                                                                               \
       &((Keychord){1, {{MODKEY, KEY}},                                        view,           {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask, KEY}},                            toggleview,     {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ShiftMask, KEY}},                              tag,            {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask, KEY}},                  toggletag,      {.ui = 1 << TAG} }),

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"
#include "exitdwm.c"
static Keychord *keychords[] = {
       /* Keys												function        argument */
       &((Keychord){1, {{MODKEY|ShiftMask,				XK_Return}},                    spawn,           {.v = dmenucmd } }),
       &((Keychord){1, {{MODKEY,					XK_Return}},                    spawn,           {.v = termcmd } }),
       &((Keychord){1, {{Mod1Mask,					XK_b}},				togglebar,       {0} }),
       &((Keychord){1, {{MODKEY,					XK_j}},                         focusstack,      {.i = +1 } }),
       &((Keychord){1, {{MODKEY,					XK_k}},                         focusstack,      {.i = -1 } }),
       &((Keychord){1, {{MODKEY, 					XK_i}},                         incnmaster,      {.i = +1 } }),
       &((Keychord){1, {{MODKEY, 					XK_d}},                         incnmaster,      {.i = -1 } }),
       &((Keychord){1, {{MODKEY, 					XK_h}},                         setmfact,        {.f = -0.05} }),
       &((Keychord){1, {{MODKEY, 					XK_l}},                         setmfact,        {.f = +0.05} }),
       &((Keychord){1, {{MODKEY|ShiftMask,				XK_j}},				movestack,       {.i = +1 } }),
       &((Keychord){1, {{MODKEY|ShiftMask, 				XK_k}},                         movestack,       {.i = -1 } }),
       &((Keychord){1, {{MODKEY,					XK_space}},                     zoom,            {0} }),
       &((Keychord){1, {{MODKEY, 					XK_Tab}},                       view,            {0} }),
       &((Keychord){1, {{MODKEY, 					XK_q}},                         killclient,      {0} }),

	/* Keybindings gaps. */
       &((Keychord){1, {{MODKEY,					XK_u}},                         incrgaps,        {.i = +1 } }),
       &((Keychord){1, {{MODKEY|ControlMask,				XK_u}},                         incrgaps,        {.i = -1 } }),
       &((Keychord){1, {{MODKEY,					XK_i}},                         incrigaps,       {.i = +1 } }),
       &((Keychord){1, {{MODKEY|ControlMask,				XK_i}},                         incrigaps,       {.i = -1 } }),
       &((Keychord){1, {{MODKEY|ControlMask, 				XK_i}},                         incrogaps,       {.i = +1 } }),
       &((Keychord){1, {{MODKEY|ControlMask, 				XK_o}},                         incrogaps,       {.i = -1 } }),
       &((Keychord){1, {{MODKEY|ControlMask, 				XK_egrave}},                    incrihgaps,      {.i = +1 } }),
       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask,			XK_egrave}},			incrihgaps,      {.i = -1 } }),
       &((Keychord){1, {{MODKEY|ControlMask,				XK_exclam}},                    incrivgaps,      {.i = +1 } }),
       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask,			XK_exclam}},			incrivgaps,      {.i = -1 } }),
       &((Keychord){1, {{MODKEY|ControlMask,				XK_ccedilla}},                  incrohgaps,      {.i = +1 } }),
       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask,			XK_ccedilla}},			incrohgaps,	 {.i = -1 } }),
       &((Keychord){1, {{MODKEY|ControlMask,				XK_agrave}},			incrovgaps,      {.i = +1 } }),
       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask,			XK_agrave}},			incrovgaps,      {.i = -1 } }),
       &((Keychord){1, {{MODKEY|ControlMask,				XK_a}},				togglegaps,      {0} }),
       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask,			XK_a}},				defaultgaps,     {0} }),
       &((Keychord){1, {{Mod1Mask,					XK_s}},                         togglesticky,    {0} }),

       /* Keybindings layout */
       &((Keychord){2, {{Mod1Mask, XK_w}, {0,				XK_t}},                          setlayout,      {.v = &layouts[0]} }),
       &((Keychord){2, {{Mod1Mask|ShiftMask, XK_w}, {0,			XK_b}},				 setlayout,      {.v = &layouts[1]} }),
       &((Keychord){2, {{Mod1Mask, XK_w}, {0,				XK_g}},                          setlayout,      {.v = &layouts[2]} }),
       &((Keychord){2, {{Mod1Mask, XK_w}, {0,				XK_m}},                          setlayout,      {.v = &layouts[3]} }),
       &((Keychord){2, {{Mod1Mask, XK_w}, {0,				XK_d}},                          setlayout,      {.v = &layouts[4]} }),
       &((Keychord){2, {{Mod1Mask, XK_w}, {0,				XK_b}},                          setlayout,      {.v = &layouts[5]} }),
       &((Keychord){2, {{Mod1Mask, XK_w}, {0,				XK_c}},                          setlayout,      {.v = &layouts[6]} }),
       &((Keychord){2, {{Mod1Mask|ShiftMask, XK_w}, {0,			XK_c}},				 setlayout,      {.v = &layouts[7]} }),
       // &((Keychord){2, {{Mod1Mask|ShiftMask, XK_l}, {0, XK_g}},                setlayout,     {.v = &layouts[8]} }),
       // &((Keychord){2, {{Mod1Mask, XK_l}, {0, XK_h}},                          setlayout,     {.v = &layouts[9]} }),
       // &((Keychord){3, {{Mod1Mask|ShiftMask, XK_l}, {0, XK_h}},                setlayout,     {.v = &layouts[10]} }),
       // &((Keychord){2, {{Mod1Mask, XK_l}, {0, XK_c}},                          setlayout,     {.v = &layouts[11]} }),
       // &((Keychord){2, {{Mod1Mask|ShiftMask, XK_l}, {0, XK_c}},                setlayout,     {.v = &layouts[12]} }),
       &((Keychord){2, {{Mod1Mask, XK_w}, {0,				XK_f}},                          setlayout,      {.v = &layouts[8]} }),
       &((Keychord){1, {{Mod1Mask,					XK_space}},                      setlayout,      {0} }),

       &((Keychord){1, {{MODKEY|ShiftMask,				XK_space}},                      togglefloating, {0} }),
       // &((Keychord){1, {{MODKEY|ShiftMask, XK_f}},                             togglefullscr,  {0} }),
       &((Keychord){1, {{MODKEY|ControlMask,				XK_f}},                          fullscreen,     {0} }),
       &((Keychord){1, {{MODKEY,					XK_f}},                          fullscreen,	 {0} }),
       &((Keychord){1, {{MODKEY, 					XK_x}},                          view,           {.ui = ~0 } }),
       &((Keychord){1, {{MODKEY|ShiftMask,				XK_v}},                          tag,            {.ui = ~0 } }),
       &((Keychord){1, {{MODKEY,					XK_comma}},                      focusmon,       {.i = -1 } }),
       &((Keychord){1, {{MODKEY, 					XK_period}},                     focusmon,       {.i = +1 } }),
       &((Keychord){1, {{MODKEY|ShiftMask,				XK_comma}},                      tagmon,         {.i = -1 } }),
       &((Keychord){1, {{MODKEY|ShiftMask, 				XK_period}},                     tagmon,         {.i = +1 } }),

       /* Scratchpad keys */
       &((Keychord){1,    {{Mod1Mask,					XK_t}},                          togglescratch,  {.ui = 0 } }),
       &((Keychord){1,    {{Mod1Mask, 					XK_f}},                          togglescratch,  {.ui = 1 } }),
       &((Keychord){1,    {{Mod1Mask,					XK_e}},                          togglescratch,  {.ui = 2 } }),
       &((Keychord){1,    {{Mod1Mask, 					XK_p}},                          togglescratch,  {.ui = 3 } }),
       // &((Keychord){1,    {{Mod1Mask, XK_h}},                                  togglescratch,  {.ui = 3 } }),
       // &((Keychord){1,    {{Mod1Mask|ShiftMask, XK_m}},	                       togglescratch,  {.ui = 5 } }),
       // &((Keychord){1,    {{Mod1Mask|ShiftMask, XK_n}},                        togglescratch,  {.ui = 6 } }),

       /* Exit keys */
       &((Keychord){1,    {{MODKEY|ShiftMask,				XK_q}},				 exitdwm,        {0} }),
       &((Keychord){1,    {{MODKEY|ControlMask|ShiftMask,		XK_q}},				 quit,           {0} }),
       &((Keychord){1,    {{MODKEY|ShiftMask,				XK_r}},				 quit,           {1} }), 

       /* keybindings audio */	
       &((Keychord){1,    {{0,						XF86XK_AudioMute}},		 spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") }),
       &((Keychord){1,    {{0, 						XF86XK_AudioRaiseVolume}},       spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +2%") }),
       &((Keychord){1,    {{0, 						XF86XK_AudioLowerVolume}},       spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -2%") }),
       &((Keychord){1,    {{0, 						XF86XK_AudioPrev}},              spawn,          SHCMD("playerctl previous") }),
       &((Keychord){1,    {{0, 						XF86XK_AudioNext}},              spawn,          SHCMD("playerctl next") }),
       &((Keychord){1,    {{0, 						XF86XK_AudioPlay}},              spawn,          SHCMD("playerctl play-pause") }),
       &((Keychord){1,    {{0, 						PrintScreenDWM,}},               spawn,          SHCMD("flameshot gui") }),
   
       /* Launch program keys */
       &((Keychord){2,    {{MODKEY, XK_b},   {0,			XK_f}},				 spawn,          SHCMD("firefox") }),
       &((Keychord){2,    {{MODKEY, XK_b},   {0, 			XK_q}},				 spawn,          SHCMD("qutebrowser") }),
       &((Keychord){2,    {{MODKEY, XK_c},   {0, 			XK_e}},                       	 spawn,          SHCMD("emacs") }),
       &((Keychord){2,    {{MODKEY, XK_c},   {0, 			XK_m}},                       	 spawn,          SHCMD("thunderbird") }),
       &((Keychord){2,    {{MODKEY, XK_c},   {0, 			XK_c}},                       	 spawn,          SHCMD("code") }),
       &((Keychord){2,    {{MODKEY, XK_c},   {0, 			XK_t}},                       	 spawn,          SHCMD("thunar") }),
       &((Keychord){2,    {{Mod1Mask, XK_d}, {0, 			XK_r}},                       	 spawn,          SHCMD("dm-radio") }),
       &((Keychord){2,    {{Mod1Mask, XK_d}, {0, 			XK_u}},                       	 spawn,          SHCMD("dmenuunicode") }),

       /* Keybindings variety */
       &((Keychord){2,    {{Mod1Mask, XK_n}, {0, 			XK_n}},				 spawn,          SHCMD("variety -n") }),
       &((Keychord){2,    {{Mod1Mask, XK_n}, {0, 			XK_p}},                       	 spawn,          SHCMD("variety -p") }),
       &((Keychord){2,    {{Mod1Mask, XK_n}, {0, 			XK_t}},                       	 spawn,          SHCMD("variety -t") }),
       &((Keychord){2,    {{Mod1Mask, XK_n}, {0, 			XK_f}},                       	 spawn,          SHCMD("variety -f") }),

       /* Keybindings change workspaces (Azerty) */
       TAGKEYS(								XK_ampersand,							     0)
       TAGKEYS(                        					XK_eacute,                 					     1)
       TAGKEYS(                        					XK_quotedbl,               					     2)
       TAGKEYS(                        					XK_apostrophe,             					     3)
       TAGKEYS(                        					XK_parenleft,              					     4)
       TAGKEYS(                        					XK_section,                					     5)
       TAGKEYS(                        					XK_egrave,                 					     6)
       TAGKEYS(                        					XK_exclam,                 					     7)
       TAGKEYS(                        					XK_ccedilla,               					     8)
       TAGKEYS(                        					XK_agrave,                 					     9)
 };

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
