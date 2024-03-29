/* See LICENSE file for copyright and license details. */

#define TERMINAL "urxvt"        /* Default terminal emulator */
#define TERMCLASS "URxvt"       /* Terminal emulator window class */

/* appearance */
static const unsigned int borderpx          = 1; /* border pixel of windows */
static const unsigned int gappx             = 6; /* gaps between windows */
static const unsigned int snap              = 2; /* snap pixel */
static const unsigned int systraypinning    = 1; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing    = 2; /* systray spacing */
static const int systraypinningfailfirst    = 1; /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray                = 1; /* 0 means no systray */
static const int showbar                    = 1; /* 0 means no bar */
static const int topbar                     = 1; /* 0 means bottom bar */
static const int focusonwheel               = 0;
static const char *fonts[]                  = { "hack:size=10" };
static const char dmenufont[]               = "hack:size=10";
static const char col_gray1[]               = "#1c1c1c";
static const char col_gray2[]               = "#444444";
static const char col_gray3[]               = "#bbbbbb";
static const char col_gray4[]               = "#eeeeee";
static const char col_cyan[]                = "#005577";
static const char col_pink[]                = "#ff00aa";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_gray2, col_pink  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class                                    instance    title       tags mask     isfloating   monitor */
    { "Steam",                                  NULL,       NULL,       0,            1,           -1 },
    { "Lutris",                                 NULL,       NULL,       0,            1,           -1 },
    { "UnityHub",                               NULL,       NULL,       0,            1,           -1 },
    { "steam_app_489830",                       NULL,       NULL,       0,            1,           -1 },
    { "Microsoft Teams Notification",           NULL,       NULL,       0,            1,           -1 },
    { "Microsoft Teams - Preview",              NULL,       NULL,       0,            1,           -1 },
    { "VirtualBox Manager",                     NULL,       NULL,       0,            1,           -1 },
    { "EDialog_popup",                          NULL,       NULL,       0,            1,           -1 },
    { "Wfica_ErrorOrInfo",                      NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int mainmon = 0; /* xsetroot will only change the bar on this monitor */

#include "layouts.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "HHH",      grid },
};

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
static char dmenumon[2]         = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]    = { TERMINAL, NULL };
static const char *screenshot[] = { "screenshot.sh", NULL };

/* Playerctl commands */
#define playerctl(cmd) { .v = (const char*[]){ "playerctl", cmd, NULL } }

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
    /* modifier         key                 function        argument */
    { MODKEY,           XK_Return,          spawn,          {.v = termcmd } },
    { MODKEY,           XK_b,               togglebar,      {0} },
    { MODKEY,           XK_j,               focusstack,     {.i = +1 } },
    { MODKEY,           XK_k,               focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask, XK_h,               setmfact,       {.f = -0.05} },
    { MODKEY|ShiftMask, XK_l,               setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask, XK_Return,          zoom,           {0} },
    { MODKEY,           XK_Tab,             view,           {0} },
    { MODKEY|ShiftMask, XK_q,               killclient,     {0} },
    { MODKEY,           XK_t,               setlayout,      {.v = &layouts[0]} },
    { MODKEY,           XK_f,               setlayout,      {.v = &layouts[1]} },
    { MODKEY,           XK_m,               setlayout,      {.v = &layouts[2]} },
    { MODKEY,           XK_g,               setlayout,      {.v = &layouts[3]} },
    { MODKEY|ShiftMask, XK_space,           togglefloating, {0} },
    { MODKEY|ShiftMask, XK_f,               togglefullscr,  {0} },
    { MODKEY,           XK_0,               view,           {.ui = ~0 } },
    { MODKEY|ShiftMask, XK_0,               tag,            {.ui = ~0 } },
    { MODKEY,           XK_h,               focusmon,       {.i = -1 } },
    { MODKEY,           XK_l,               focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask, XK_j,               tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask, XK_k,               tagmon,         {.i = +1 } },
    { MODKEY|ShiftMask, XK_n,               shiftview,      {.i = +1 } },
    { MODKEY|ShiftMask, XK_b,               shiftview,      {.i = -1 } },
    { MODKEY,           XK_e,               spawn,          SHCMD(TERMINAL " -e ranger") },
    { MODKEY,           XK_c,               spawn,          SHCMD("rofi -show calc -show-icons") },
    { MODKEY,           XK_space,           spawn,          SHCMD("rofi -show drun -show-icons") },
    { MODKEY,           XK_Print,           spawn,          {.v = screenshot } },
    { MODKEY|ShiftMask, XK_Escape,          spawn,          SHCMD("powermenu") },
    /* Audio control */
    { 0, XF86XK_AudioMute,                  spawn,          SHCMD("pulsemixer --toggle-mute && volume-indicator") },
    { 0, XF86XK_AudioRaiseVolume,           spawn,          SHCMD("pulsemixer --change-volume +5 && volume-indicator") },
    { 0, XF86XK_AudioLowerVolume,           spawn,          SHCMD("pulsemixer --change-volume -5 && volume-indicator") },
    /* Player controls */
    { 0, XF86XK_AudioPlay,                  spawn,          playerctl("play-pause") },
    { 0, XF86XK_AudioStop,                  spawn,          playerctl("stop") },
    { 0, XF86XK_AudioNext,                  spawn,          playerctl("next") },
    { 0, XF86XK_AudioPrev,                  spawn,          playerctl("previous") },
    
    TAGKEYS( XK_1, 0 )
    TAGKEYS( XK_2, 1 )
    TAGKEYS( XK_3, 2 )
    TAGKEYS( XK_4, 3 )
    TAGKEYS( XK_5, 4 )
    TAGKEYS( XK_6, 5 )
    TAGKEYS( XK_7, 6 )
    TAGKEYS( XK_8, 7 )
    TAGKEYS( XK_9, 8 )
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* event            mask        button      function        argument */
    { ClkLtSymbol,      0,          Button1,    setlayout,      {0} },
    { ClkLtSymbol,      0,          Button3,    setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,      0,          Button2,    zoom,           {0} },
    { ClkStatusText,    0,          Button2,    spawn,          {.v = termcmd } },
    { ClkClientWin,     MODKEY,     Button1,    movemouse,      {0} },
    { ClkClientWin,     MODKEY,     Button2,    togglefloating, {0} },
    { ClkClientWin,     MODKEY,     Button3,    resizemouse,    {0} },
    { ClkTagBar,        0,          Button1,    view,           {0} },
    { ClkTagBar,        0,          Button3,    toggleview,     {0} },
    { ClkTagBar,        MODKEY,     Button1,    tag,            {0} },
    { ClkTagBar,        MODKEY,     Button3,    toggletag,      {0} }
};
