/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
X */

static const unsigned int tagpad =
    4; /* left/right padding around each tag, in px */
static const unsigned int systrayonleft =
    0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int showbar = 1;     /* 0 means no bar */
static const int topbar = 0;      /* 0 means bottom bar */
static const char *fonts[] = {
    "Annotation Mono:pixelsize=15:style:DemiBold:antialias=true:autohint=true",
    "Noto Color Emoji:pixelsize=15:antialias=true:autohint=true",
};
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#bbbbbb";
static char selfgcolor[] = "#eeeeee";
static char selbordercolor[] = "#005577";
static char selbgcolor[] = "#005577";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

static const char *const autostart[] = {
    "mpd",
    NULL,
    "dunst",
    NULL,
    "picom",
    NULL,
    "pipewire",
    NULL,
    "slstatus",
    NULL,
    "wireplumber",
    NULL,
    "pipewire-pulse",
    NULL,
    "/home/bryant/.fehbg",
    NULL,
    "xset",
    "s",
    "off",
    "-dpms",
    NULL,
    NULL /* terminate array */
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"feh", NULL, NULL, 0, 1, -1},
    {"Nsxiv", NULL, NULL, 0, 1, -1},
    {"ffplay", NULL, NULL, 0, 1, -1},
    {"mpv", NULL, NULL, 1 << 6, -1, -1},
    {"steam", NULL, NULL, 1 << 7, 0, -1},
    {"Zathura", NULL, NULL, 1 << 6, 0, -1},
    {"calibre", NULL, NULL, 1 << 4, 0, -1},
    {"qBittorrent", NULL, NULL, 1 << 5, 0, -1},
    {"st-256color", NULL, "ncmpcpp", 0, -1, -1},
    {"st-256color", NULL, "bitwarden", 0, -1, -1},
    {"st-256color", NULL, "Calculator", 0, -1, -1},
};

/* layout(s) */
static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int attachbelow =
    1; /* 1 means attach after the currently active window */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */
static const int refreshrate =
    60; /* refresh rate (per second) for client move/resize */

#include "fibonacci.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[\\]", dwindle},
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
    {MODKEY, KEY, view, {.ui = 1 << TAG}},                                     \
        {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
    {                                                                          \
        .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                   \
    }

static const Key keys[] = {
    /* --- WM Control & Session --- */
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY | Mod1Mask, XK_e, quit, {0}},

    /* --- Window Focus & Manipulation --- */
    {MODKEY, XK_f, togglefullscr, {0}},
    {MODKEY, XK_h, focusstack, {.i = -1}},
    {MODKEY, XK_l, focusstack, {.i = +1}},

    {MODKEY | Mod1Mask, XK_h, setmfact, {.f = -0.05}},
    {MODKEY | Mod1Mask, XK_l, setmfact, {.f = +0.05}},

    {MODKEY, XK_Tab, zoom, {0}},
    {MODKEY, XK_w, togglefloating, {0}},

    /* --- Layouts & Master Stack Control --- */
    {MODKEY, XK_backslash, setlayout, {0}},

    /* --- Tag & Workspace Navigation (Views) --- */
    {MODKEY, XK_n, viewnext, {0}},
    {MODKEY, XK_p, viewprev, {0}},

    {MODKEY, XK_Escape, view, {0}},

    /* --- UI & Bar --- */
    {MODKEY | ShiftMask, XK_w, togglebar, {0}},
    {MODKEY, XK_F5, xrdb, {.v = NULL}},

    /* --- System Core & App Launchers --- */
    {MODKEY, XK_t, spawn, SHCMD("st")},
    {MODKEY, XK_e, spawn, SHCMD("st -e lf")},
    {MODKEY, XK_s, spawn, SHCMD("~/bin/wm/sk")},
    {MODKEY, XK_d, spawn, SHCMD("rofi -show run")},
    {MODKEY | ShiftMask, XK_t, spawn, SHCMD("alacritty")},

    /* --- Web Browsers --- */
    {MODKEY | ShiftMask, XK_Return, spawn,
     SHCMD("brave-origin --profile-directory='Work'")},
    {MODKEY, XK_Return, spawn,
     SHCMD("brave-origin --profile-directory='Personal'")},

    /* --- System & Desktop Tools --- */
    {MODKEY, XK_u, spawn, SHCMD("~/bin/wm/uitool")},
    {MODKEY, XK_a, spawn, SHCMD("~/bin/wm/bw-menu")},
    {MODKEY, XK_b, spawn, SHCMD("~/bin/wm/set-brightness")},
    {MODKEY, XK_i, spawn, SHCMD("~/bin/wm/select-background")},
    {MODKEY | ShiftMask, XK_b, spawn, SHCMD("~/bin/wm/warmth")},
    {MODKEY, XK_space, spawn, SHCMD("~/bin/wm/switch-keyboard")},

    /* --- Utility Apps (Translation, Calc, Reader) --- */
    {MODKEY, XK_r, spawn, SHCMD("~/bin/wm/reader")},
    {MODKEY, XK_o, spawn, SHCMD("~/bin/wm/calculator")},
    {MODKEY, XK_c, spawn, SHCMD("~/bin/wm/transl es:en")},
    {MODKEY | ShiftMask, XK_c, spawn, SHCMD("~/bin/wm/transl en:es")},

    /* --- Media & Recording --- */
    {MODKEY, XK_m, spawn, SHCMD("st -t ncmpcpp -e ncmpcpp")},
    {MODKEY | ShiftMask, XK_r, spawn, SHCMD("~/bin/wm/recording")},

    {MODKEY, XF86XK_Tools, spawn, SHCMD("~/bin/wm/take-screenshots -m menu")},
    {0, XF86XK_Tools, spawn,
     SHCMD("~/bin/wm/take-screenshots -m select -s clip")},

    {0, XF86XK_AudioMute, spawn, SHCMD("~/bin/wm/volume-dunst mute")},
    {0, XF86XK_AudioRaiseVolume, spawn, SHCMD("~/bin/wm/volume-dunst up")},
    {0, XF86XK_AudioLowerVolume, spawn, SHCMD("~/bin/wm/volume-dunst down")},

    TAGKEYS(XK_bracketleft, 0) TAGKEYS(XK_braceleft, 1) TAGKEYS(XK_parenleft, 2)
        TAGKEYS(XK_percent, 3) TAGKEYS(XK_equal, 4) TAGKEYS(XK_ampersand, 5)
            TAGKEYS(XK_parenright, 6) TAGKEYS(XK_braceright, 7)
                TAGKEYS(XK_bracketright, 8) TAGKEYS(XK_exclam, 9)};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
    /* signum       function        argument  */
    {1, xrdb, {.v = 0}},
};
