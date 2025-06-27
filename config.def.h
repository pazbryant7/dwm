/* Includes for media keys */
#include <X11/XF86keysym.h>

/* Appearance */
static const unsigned int snap                = 32;       /* snap pixel */
static const unsigned int borderpx            = 2;        /* border pixel of windows */

/* Bar */
static const int topbar                       = 0;
static const int showbar                      = 1;
static const int hiddenbar_tags[]             = { 1, 7 };

/* Fonts */
static const char *fonts[] = {
    "National Park SemiBold:size=10.5:weight=SemiBold:antialias=true:autohint=true",
    "Noto Color Emoji:pixelsize=10:antialias=true:autohint=true",
};

/* XRDB Colors */
static char selfgcolor[]            = "#eeeeee";
static char selbgcolor[]            = "#005577";
static char normbgcolor[]           = "#222222";
static char normfgcolor[]           = "#bbbbbb";
static char selbordercolor[]        = "#005577";
static char normbordercolor[]       = "#444444";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
    [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
};

/* Autostart */
static const char *const autostart[] = {
    "sh", "-c", "slstatus", NULL,
    "sh", "-c", "~/.fehbg &", NULL,
    "sh", "-c", "xset s off -dpms &", NULL,
    "sh", "-c", "pgrep -x \"dunst\" >/dev/null || dunst &", NULL,
    "sh", "-c", "pgrep -x \"picom\" >/dev/null || picom &", NULL,
    "sh", "-c", "pgrep -x \"unclutter\" >/dev/null || unclutter &", NULL,
    NULL
};

/* Tagging */
static const char *tags[] = {
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
};


/* WM Class Rules */
static const Rule rules[] = {
    /* class                 instance    title       tags mask  switchtotag   isfloating   monitor    */
    { "jetbrains-datagrip",  NULL,       NULL,       1 << 3,    0,             0,           -1 },
    { "Postman",             NULL,       NULL,       1 << 3,    0,             0,           -1 },
    { "bruno",               NULL,       NULL,       1 << 3,    0,             0,           -1 },
    { "calibre",             NULL,       NULL,       1 << 4,    1,             0,           -1 },
    { "Anki",                NULL,       NULL,       1 << 4,    0,             0,           -1 },
    { "qBittorrent",         NULL,       NULL,       1 << 5,    0,             0,           -1 },
    { "Zathura",             NULL,       NULL,       1 << 6,    1,             0,           -1 },
    { "mpv",                 NULL,       NULL,       1 << 6,    1,            -1,           -1 },
    { "vesktop",             NULL,       NULL,       1 << 7,    0,             0,           -1 },
    { "st-256color",         NULL,       "ncmpcpp",  0,         0,            -1,           -1 },
    { "st-256color",         NULL,       "numbat",   0,         0,            -1,           -1 },
    { "Nsxiv",               NULL,       NULL,       0,         0,             1,           -1 },
    { "feh",		             NULL,       NULL,       0,         0,             1,           -1 },
    { "ffplay",		           NULL,       NULL,       0,         0,             1,           -1 },
};

/* Layouts */
static const int nmaster             = 1;
static const int resizehints         = 1;
static const float mfact             = 0.50;
static const int floatuserwidth      = 700;
static const int floatuserheight     = 430;
static const int lockfullscreen      = 1;


#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
    { "[\\]",     dwindle   },
    { "[M]",      monocle   },
    // { "><>",      NULL      },    /* no layout function means floating behavior */
};

/* Key Definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* Utility to run sh commands */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Keys */

#include "movestack.c"
static const Key keys[] = {
    /* modifier             key                 function        argument */

    /* --- WM Control & Session --- */
    { MODKEY,               XK_q,                    killclient,     {0} },
    { MODKEY|Mod1Mask,      XK_e,                    quit,           {0} },

    /* --- Application Launchers --- */
    { MODKEY,               XK_t,                    spawn,          SHCMD("st") },
    { MODKEY|ShiftMask,     XK_t,                    spawn,          SHCMD("alacritty") },

    { MODKEY,               XK_Return,               spawn,          SHCMD("helium-browser") },
    { MODKEY|ShiftMask,     XK_Return,               spawn,          SHCMD("waterfox") },

    { MODKEY,               XK_e,		                 spawn,          SHCMD("st -e yazi") },
    { MODKEY,               XK_d,                    spawn,          SHCMD("rofi -show run") },
    { MODKEY,               XK_c,                    spawn,          SHCMD("st -t numbat -e numbat") },
    { MODKEY,               XK_m,                    spawn,          SHCMD("st -t ncmpcpp -e ncmpcpp") },

    { MODKEY,               XK_v,                    spawn,          SHCMD("~/bin/wm/watch") },
    { MODKEY,               XK_r,                    spawn,          SHCMD("~/bin/wm/reader") },
    { MODKEY|ShiftMask,     XK_b,                    spawn,          SHCMD("~/bin/wm/warmth") },
    { MODKEY,               XK_a,                    spawn,          SHCMD("~/bin/wm/passmenu") },
    { MODKEY,               XK_s,                    spawn,          SHCMD("~/bin/wm/screenkey") },
    { MODKEY|ShiftMask,     XK_r,                    spawn,          SHCMD("~/bin/wm/recording") },
    { MODKEY,               XK_o,                    spawn,          SHCMD("~/bin/wm/passmenu otp") },
    { MODKEY,               XK_b,                    spawn,          SHCMD("~/bin/wm/set-brightness") },
    { MODKEY,               XK_space,		             spawn,          SHCMD("~/bin/wm/switch-keyboard") },
    { MODKEY,               XK_i,                    spawn,          SHCMD("~/bin/wm/select-background") },

    /* --- Hardware Keys --- */
    { MODKEY|Mod1Mask,      XF86XK_Tools,            spawn,          SHCMD("~/bin/wm/take-screenshots -m full -s save && notify-send 'Saved in disk'") },
    { MODKEY|ShiftMask,     XF86XK_Tools,            spawn,          SHCMD("~/bin/wm/take-screenshots -m select -s save && notify-send 'Saved in disk'") },
    { MODKEY,               XF86XK_Tools,            spawn,          SHCMD("~/bin/wm/take-screenshots -m full -s clip && notify-send 'Saved in clipboard'") },
    { 0,                    XF86XK_Tools,            spawn,          SHCMD("~/bin/wm/take-screenshots -m select -s clip && notify-send 'Saved in clipboard'") },

    /* --- Hardware Keys --- */
    { 0,                    XF86XK_AudioRaiseVolume, spawn,          SHCMD("~/bin/wm/volume-dunst up") },
    { 0,                    XF86XK_AudioLowerVolume, spawn,          SHCMD("~/bin/wm/volume-dunst down") },
    { 0,                    XF86XK_AudioMute,        spawn,          SHCMD("~/bin/wm/volume-dunst mute") },

    /* --- Window Management --- */
    { MODKEY|ShiftMask,     XK_w,                    togglebar,      {0} },
    { MODKEY,               XK_w,                    togglefloating, {0} },
    { MODKEY,		            XK_backslash,            setlayout,      {0} },

    { MODKEY,               XK_f,                    togglefullscr,  {0} },
    { MODKEY,               XK_Tab,                  zoom,           {0} },
    { MODKEY,               XK_Escape,		           view,           {0} },

    { MODKEY,               XK_n,                    viewnext,       {0} },
    { MODKEY,               XK_p,                    viewprev,       {0} },

    { MODKEY,               XK_F5,		               xrdb,           {.v = NULL } },

    { MODKEY,               XK_h,                    focusstack,     {.i = -1 } },
    { MODKEY,               XK_l,                    focusstack,     {.i = +1 } },

    { MODKEY|Mod1Mask,      XK_l,                    setmfact,       {.f = +0.05} },
    { MODKEY|Mod1Mask,      XK_h,                    setmfact,       {.f = -0.05} },

    { MODKEY|ShiftMask,     XK_l,                    movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,     XK_h,                    movestack,      {.i = -1 } },

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
};

/* Mouse buttons */
static const Button buttons[] = {
    { ClkTagBar,    0,			Button1, view,        {0} },
    { ClkLtSymbol,  0,			Button1, setlayout,   {0} },
    { ClkClientWin, MODKEY,             Button3, resizemouse, {0} },
    { ClkClientWin, MODKEY,             Button1, movemouse,   {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
    /* signum       function            argument  */
    { 1,            xrdb,	        {.v = 0} },
};
