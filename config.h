#define TERMINAL    "alacritty"
#define EDITORTERM  "nvim"
#define EDITOR      "neovide"
#define BROWSER     "firefox"
#define BROWSERTWO  "chromium"
#define FILEMANAGER "pcmanfm"

/* See LICENSE file for copyright and license details. */
/* appearance */
static const int horizpadbar    = 2;        /* horizontal padding for statusbar */
static const int vertpadbar     = 0;        /* vertical padding for statusbar */
static const char dmenufont[]   = "Ubuntu:size=10";
static const char *fonts[]      = {
    "monospace:weight=bold:size=10:antialias=true:hinting=true",
    "JoyPixels:size=11:antialias=true:autohint=true",
    "FontAwesome:size=11:antialias=true:autohint=true",
};
static unsigned int borderpx    = 1;        /* border pixel of windows */
static unsigned int snap        = 32;       /* snap pixel */
static int showbar              = 1;        /* 0 means no bar */
static int topbar               = 1;        /* 0 means bottom bar */
static char normbgcolor[]       = "#222222";
static char normbordercolor[]   = "#444444";
static char normfgcolor[]       = "#bbbbbb";
static char selfgcolor[]        = "#eeeeee";
static char selbordercolor[]    = "#005577";
static char selbgcolor[]        = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "🐧", "", "📰", "🎵", "🔍", "💀", "➐", "➑", "➒" };
// static const char *tags[] = { "➊", "➋", "➌", "➍", "➎", "➏", "➐", "➑", "➒" };

#define TAGPOS(POS) (1 << (POS - 1))
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title                    tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,                    0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,                    TAGPOS(2),    0,           -1 },
    { "Firefox",  NULL,       "Firefox Preferences",   TAGPOS(2),    1,           -1 },
	{ "Chromium", NULL,       NULL,                    TAGPOS(4),    0,           -1 },
	{ "Pcmanfm",  NULL,       NULL,                    TAGPOS(3),    0,           -1 },
};

/* layout(s) */
static float mfact              = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster              = 1;    /* number of clients in master area */
static int resizehints          = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "grid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",              tile },    /* first entry is default */
	{ "><>",              NULL },    /* no layout function means floating behavior */
	{ "HHH",              grid },
	{ "[M]",              monocle },
	{ NULL,               NULL },
};

/* key definitions */
#define MODKEY Mod4Mask

#define TAGKEYS(KEY,TAG)												        \
	{1, {{MODKEY, KEY}},						view,       {.ui = 1 << TAG} },	\
	{1, {{MODKEY|ControlMask, KEY}},			toggleview, {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ShiftMask, KEY}},				tag,        {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ControlMask|ShiftMask, KEY}},	toggletag,  {.ui = 1 << TAG} },

#define SPECIALFNKEYS(FNKEY, FNCMD) {1, {{0, FNKEY}},  spawn,  FNCMD},
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SPWNCMD(cmd)        { .v = cmd }
#define SHCMD(cmd)          { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define SPWNTERM(name, cmd) { .v = (const char*[]){ TERMINAL, "-t", name, "-e", cmd, NULL } }
#define MEDIACMD(cmd)       { .v = (const char*[]){"/bin/sh", "-c", cmd";", "kill -44 $(pidof dwmblocks)", NULL} }

#include <X11/XF86keysym.h>
/* commands */
static char dmenumon[2]         = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]    = { TERMINAL, NULL };

static Keychord keychords[] = {
	/* Keys                                         function        argument */
	{1, {{MODKEY,                       XK_p}},		spawn,          SPWNCMD(dmenucmd)},
	{1, {{MODKEY,                  XK_Return}},		spawn,          SPWNCMD(termcmd)},
	{2, {{MODKEY, XK_e}, {MODKEY,       XK_e}},		spawn,          SPWNCMD(termcmd)},
    {1, {{MODKEY|ShiftMask,             XK_s}},     spawn,          SHCMD("maimsave")},
    {1, {{0,              XF86XK_ScreenSaver}},     spawn,          SHCMD("maimsave""-save")},

    // Application keys
	{2, {{MODKEY|ShiftMask, XK_b},  {0, XK_1}},	    spawn,          SHCMD(BROWSER) },
	{2, {{MODKEY|ShiftMask, XK_b},  {0, XK_2}},	    spawn,          SHCMD(BROWSERTWO) },
	{1, {{MODKEY|ShiftMask,             XK_m}},	    spawn,          SHCMD(FILEMANAGER) },
	{1, {{MODKEY,                       XK_v}},	    spawn,          SPWNTERM("Programming Env", EDITORTERM) },
	{1, {{MODKEY|ShiftMask,             XK_v}},	    spawn,          SPWNTERM("Programming Env", EDITOR) },
	{1, {{MODKEY|ShiftMask,         XK_slash}},	    spawn,          SPWNTERM("ResourceInfo", "htop") },

    // Dwm stuff keys
	{1, {{MODKEY,                       XK_b}},		togglebar,      {0} },
	{1, {{MODKEY,                       XK_j}},		focusstack,     {.i = +1 } },
	{1, {{MODKEY,                       XK_k}},		focusstack,     {.i = -1 } },
	{1, {{MODKEY,                       XK_i}},		incnmaster,     {.i = +1 } },
	{1, {{MODKEY,                       XK_d}},		incnmaster,     {.i = -1 } },
	{1, {{MODKEY,                       XK_h}},		setmfact,       {.f = -0.05} },
	{1, {{MODKEY,                       XK_l}},		setmfact,       {.f = +0.05} },
	{1, {{MODKEY|ShiftMask,        XK_Return}},	    zoom,           {0} },
	{1, {{MODKEY,                     XK_Tab}},		view,           {0} },
	{1, {{MODKEY|ShiftMask,             XK_c}},		killclient,     {0} },
	{1, {{MODKEY,                       XK_t}},		setlayout,      SPWNCMD(&layouts[0]) },
	{1, {{MODKEY,                       XK_f}},		setlayout,      SPWNCMD(&layouts[1]) },
	{1, {{MODKEY,                       XK_m}},		setlayout,      SPWNCMD(&layouts[2]) },
    {1, {{MODKEY|ShiftMask,		        XK_j}},     cyclelayout,    {.i = -1 } },
    {1, {{MODKEY|ShiftMask,             XK_k}},     cyclelayout,    {.i = +1 } },
    {1, {{MODKEY|ShiftMask,             XK_l}},      rotatestack,    {.i = +1 } },
    {1, {{MODKEY|ShiftMask,             XK_h}},      rotatestack,    {.i = -1 } },
	{1, {{MODKEY,                   XK_space}},		setlayout,      {0} },
	{1, {{MODKEY|ShiftMask,         XK_space}},		togglefloating, {0} },
    {1, {{MODKEY|ShiftMask,             XK_f}},     togglefullscr,  {0} },
	{1, {{MODKEY,                       XK_0}},		view,           {.ui = ~0 } },
	{1, {{MODKEY|ShiftMask,             XK_0}},		tag,            {.ui = ~0 } },
	{1, {{MODKEY,                   XK_comma}},		focusmon,       {.i = -1 } },
	{1, {{MODKEY,                  XK_period}},		focusmon,       {.i = +1 } },
	{1, {{MODKEY|ShiftMask,         XK_comma}},		tagmon,         {.i = -1 } },
	{1, {{MODKEY|ShiftMask,        XK_period}},		tagmon,         {.i = +1 } },
	{1, {{MODKEY|ShiftMask,             XK_q}},		quit,           {0} },
    {1, {{MODKEY|ControlMask,           XK_q}},     quit,           {1} },
    /* Media Keys */
    SPECIALFNKEYS(XF86XK_MonBrightnessUp,           SHCMD("xbacklight -inc 5"))
    SPECIALFNKEYS(XF86XK_MonBrightnessDown,         SHCMD("xbacklight -dec 5"))
    SPECIALFNKEYS(XF86XK_AudioMute,                 MEDIACMD("amixer set Master toggle"))
    SPECIALFNKEYS(XF86XK_AudioRaiseVolume,          MEDIACMD("amixer set Master 5%+"))
    SPECIALFNKEYS(XF86XK_AudioLowerVolume,          MEDIACMD("amixer set Master 5%-"))
    SPECIALFNKEYS(XF86XK_AudioPrev,                 MEDIACMD("mpc prev"))
    SPECIALFNKEYS(XF86XK_AudioNext,                 MEDIACMD("mpc next"))
    SPECIALFNKEYS(XF86XK_AudioPlay,                 MEDIACMD("mpc pause"))
    /* Tag Keys */
	TAGKEYS(XK_1        ,0)
	TAGKEYS(XK_2        ,1)
	TAGKEYS(XK_3        ,2)
	TAGKEYS(XK_4        ,3)
	TAGKEYS(XK_5        ,4)
	TAGKEYS(XK_6        ,5)
	TAGKEYS(XK_7        ,6)
	TAGKEYS(XK_8        ,7)
	TAGKEYS(XK_9        ,8)
};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    {"color0",          STRING,     &normbordercolor},
    {"color4",          STRING,     &selbordercolor},
    {"color0",          STRING,     &normbgcolor},
    {"color4",          STRING,     &normfgcolor},
    {"color0",          STRING,     &selfgcolor},
    {"color4",          STRING,     &selbgcolor},
    {"borderpx",        INTEGER,    &borderpx},
    {"snap",            INTEGER,    &snap},
    {"showbar",         INTEGER,    &showbar},
    {"topbar",          INTEGER,    &topbar},
    {"nmaster",         INTEGER,    &nmaster},
    {"resizehints",     INTEGER,    &resizehints},
    {"mfact",           FLOAT,      &mfact},
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
