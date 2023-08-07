/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx     = 7;        /* gaps between windows */
static const unsigned int snap      = 42;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "White Rabbit:size=16" };
static const char dmenufont[]       = "White Rabbit:size=18";
static const char col_gray1[]       = "#2e2f2f";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#97961a";
static const char col_gray4[]       = "#000000";
static const char col_cyan[]        = "#97961a";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", " ", " ", "", " ", " ", "", "", "" };//    
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance    title       tags mask     isfloating   monitor */
	{ "Gimp",            NULL,       NULL,       0,            0,           -1 },
	{ "Brave",           NULL,       NULL,       1 << 1,       0,           -1 },
    { "Virt-manager",    NULL,       NULL,       1 << 7,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};
#include </usr/include/X11/XF86keysym.h>
/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browser[]  = { "brave", NULL };
//static const char *virtmanager[] = {"virt-manager", NULL};
static const char *virtualbox[] = {"virtualbox", NULL};
static const char *zathura[] = {"zathura", NULL};
static const char *pavucontrol[] = {"pavucontrol", NULL};
static const char *passmenu[] = {"passmenu",  "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4,NULL};

#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } }, 
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = passmenu } }, 
	{ MODKEY,                       XK_w,      spawn,          {.v = browser } },
	{ MODKEY,   	                XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_v,      spawn,          {.v = virtualbox}  },
    { 0,                            XK_Print,  spawn,          SHCMD("/home/dil/suckless/dwm/screenshot.sh") },
    { ShiftMask,                    XK_Print,  spawn,          SHCMD("/home/dil/suckless/dwm/screenshotsel.sh") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY, 	                    XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    //{ MODKEY|ShiftMask,             XK_s,      spawn,           SHCHD("sudo poweroff")},
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
   // { MODKEY,			            XK_z, 	   shiftview,      {.i=-1   } },
    { MODKEY,			            XK_z, 	   spawn,      {.v = zathura   } },
    { MODKEY,			            XK_p, 	   spawn,      {.v = pavucontrol   } },


   // { MODKEY,			            XK_x, 	   shiftview,      {.i=+1   } },
    { 0, XF86XK_AudioMute,                     spawn,          SHCMD("amixer set Master toggle")},
	{ 0, XF86XK_AudioRaiseVolume,              spawn,          SHCMD("amixer set Master 10%+") },
	{ 0, XF86XK_AudioLowerVolume,              spawn,          SHCMD("amixer set Master 10%-") },
	{ 0, XF86XK_MonBrightnessUp,    	       spawn,          SHCMD("sudo light -A 10") },
	{ 0, XF86XK_MonBrightnessDown,             spawn,          SHCMD("sudo light -U 10") },
//{ 0, XF86XK_TouchpadToggle,                 spawn,          }
	{ 0, XF86XK_AudioPlay, 		               spawn, 	       SHCMD("cmus-remote --server /run/user/1000/cmus-socket -p ")	 },
	{ 0, XF86XK_AudioNext, 		               spawn,    	   SHCMD("cmus-remote --server /run/user/1000/cmus-socket -n ")	 },
	{ 0, XF86XK_AudioPrev, 		               spawn,   	   SHCMD("cmus-remote --server /run/user/1000/cmus-socket -r ")	 },
//	{ 0, XF86XK_AudioPause,         spawn, 	   SHCMD("cmus-remote --server /run/user/1000/cmus-socket -u ")	 },
	{ 0, XF86XK_AudioStop, 		spawn,     SHCMD("cmus-remote --server /run/user/1000/cmus-socket -u ")  },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

