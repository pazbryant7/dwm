/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };


/* Autostart */
static const char *const autostart[] = {
		"sh", "-c", "slstatus", NULL,
		"sh", "-c", "~/.fehbg &", NULL,
		"sh", "-c", "xset s off -dpms &", NULL,
		"sh", "-c", "pgrep -x \"dunst\" >/dev/null || dunst &", NULL,
		"sh", "-c", "pgrep -x \"picom\" >/dev/null || picom &", NULL,
		"sh", "-c", "pgrep -x \"greenclip\" >/dev/null || greenclip daemon &", NULL,
    NULL
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     switchtotag    isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,             1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,             0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	  { "[\\]",     dwindle   },
 	  { "[@]",      spiral    },
    { "[]=",      tile      },    /* first entry is default */
    { "[M]",      monocle   },
    { "><>",      NULL      },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

/* Keys */

#include "movestack.c"
static const Key keys[] = {
    /* modifier             key                 function        argument */

    /* --- WM Control & Session --- */
    { MODKEY,               XK_q,               killclient,     {0} },
    { MODKEY|Mod1Mask,      XK_e,               quit,           {0} },

    /* --- Application Launchers --- */
    { MODKEY,               XK_t,               spawn,          {.v = termcmd } },

    /* --- Application Custom Launchers --- */
    { MODKEY,               XK_e,		            spawn,          SHCMD("st -e yazi") },
    { MODKEY|ShiftMask,     XK_t,               spawn,          SHCMD("alacritty") },
    { MODKEY,               XK_r,               spawn,          SHCMD("~/bin/wm/read") },
    { MODKEY,               XK_v,               spawn,          SHCMD("~/bin/wm/watch") },
    { MODKEY,               XK_d,               spawn,          SHCMD("rofi -show run") },
    { MODKEY,               XK_a,               spawn,          SHCMD("~/bin/wm/passmenu") },
    { MODKEY|ShiftMask,     XK_r,               spawn,          SHCMD("~/bin/wm/recording") },
    { MODKEY,               XK_s,               spawn,          SHCMD("~/bin/wm/screenkey") },
    { MODKEY,               XK_u,               spawn,          SHCMD("~/bin/wm/switch-sink") },
    { MODKEY,               XK_c,               spawn,          SHCMD("~/bin/wm/rofi-greenclip") },
    { MODKEY,               XK_b,               spawn,          SHCMD("~/bin/wm/set-brightness") },
    { MODKEY,               XK_o,               spawn,          SHCMD("~/bin/wm/passmenu --otp") },
    { MODKEY,               XK_space,		        spawn,          SHCMD("~/bin/wm/switch-keyboard") },
    { MODKEY,               XK_m,               spawn,          SHCMD("st -t ncmpcpp -e ncmpcpp") },
    { MODKEY,               XK_i,               spawn,          SHCMD("~/bin/wm/select-background") },
    { MODKEY|ShiftMask,     XK_Return,          spawn,          SHCMD("brave --profile-directory='work'") },
    { MODKEY,               XK_Return,          spawn,          SHCMD("brave --profile-directory='personal'") },

    /* --- Window Management --- */
    { MODKEY,		            XK_backslash,       setlayout,      {0} },
    { MODKEY,               XK_n,               viewnext,       {0} },
    { MODKEY|ShiftMask,     XK_w,               togglebar,      {0} },
    { MODKEY,               XK_w,               togglefloating, {0} },
	  { MODKEY,               XK_Tab,             zoom,           {0} },
    { MODKEY,               XK_Escape,		      view,           {0} },
    { MODKEY,               XK_f,               togglefullscr,  {0} },
    { MODKEY,               XK_p,               viewprev,       {0} },

    { MODKEY,               XK_F5,							xrdb,           {.v = NULL } },
    { MODKEY,               XK_h,               focusstack,     {.i = -1 } },
    { MODKEY,               XK_l,               focusstack,     {.i = +1 } },
    { MODKEY|Mod1Mask,      XK_l,               setmfact,       {.f = +0.05} },
    { MODKEY|Mod1Mask,      XK_h,               setmfact,       {.f = -0.05} },
    { MODKEY|ShiftMask,     XK_l,               movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,     XK_h,               movestack,      {.i = -1 } },

    /* --- Tags --- */
    TAGKEYS(XK_bracketleft, 0)
    TAGKEYS(XK_braceleft,   1)
    TAGKEYS(XK_parenleft,   2)
    TAGKEYS(XK_percent,     3)
    TAGKEYS(XK_equal,       4)
    TAGKEYS(XK_ampersand,   5)
    TAGKEYS(XK_parenright,  6)
    TAGKEYS(XK_braceright,  7)
    TAGKEYS(XK_bracketright,8)
    TAGKEYS(XK_exclam,      9)
    TAGKEYS(XK_1,           0)
    TAGKEYS(XK_2,           1)
    TAGKEYS(XK_3,           2)
    TAGKEYS(XK_4,           3)
    TAGKEYS(XK_5,           4)
    TAGKEYS(XK_6,           5)
    TAGKEYS(XK_7,           6)
    TAGKEYS(XK_8,           7)
    TAGKEYS(XK_9,           8)
    TAGKEYS(XK_0,           9)

    /* --- Screenshots --- */
    { ControlMask,XK_Print,   spawn, SHCMD("~/bin/wm/take-screenshots -m full -s save && notify-send 'Saved in disk'") },
    { Mod1Mask,   XK_Print,   spawn, SHCMD("~/bin/wm/take-screenshots -m select -s save && notify-send 'Saved in disk'") },
    { MODKEY,     XK_Print,   spawn, SHCMD("~/bin/wm/take-screenshots -m full -s clip && notify-send 'Saved in clipboard'") },
    { 0,          XK_Print,   spawn, SHCMD("~/bin/wm/take-screenshots -m select -s clip && notify-send 'Saved in clipboard'") },

    /* --- Hardware Keys --- */
    { 0, XF86XK_AudioRaiseVolume, spawn, SHCMD("~/bin/wm/volume-dunst up") },
    { 0, XF86XK_AudioLowerVolume, spawn, SHCMD("~/bin/wm/volume-dunst down") },
    { 0, XF86XK_AudioMute,        spawn, SHCMD("~/bin/wm/volume-dunst mute") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
	/* signum       function        argument  */
	{ 1,            setlayout,      {.v = 0} },
};
