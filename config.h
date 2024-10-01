/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"

/* appearance */
static unsigned int borderpx  = 3;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 20;       /* horiz inner gap between windows */
static unsigned int gappiv    = 10;       /* vert inner gap between windows */
static unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
/*static char *fonts[]          = { "monospace:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true"  };*/
static char *fonts[]            = {
    "SF Mono:size=10:style=SemiBold",
    "SF Pro Display Medium:size=11",
    "Symbols Nerd Font:size=12",
    "Symbols Nerd Font Mono:size=12"
};
static const char dmenufont[]         = "SF Mono:size=10:style=SemiBold";


// colors
static const char bar_colour[]        = "#1E2127"; 
static const char bar_font_colour[]   = "#abb2bf";
static const char frame_colour[]      = "#E28743";
static const char frame_font_colour[] = "#1E2127";
static const char frame_border_colour[] = "#E28743";
static const char bg_frame_colour[]   = "#1E2127";
static const char titlebgcolor[]      = "#1E2127";
static const char titlefgcolor[]      = "#abb2bf";

static const char dmenu_height[]      = "10";         // number of lines
static const char dmenu_line_height[] = "25";         // line height

static const char dmenu_background[]    = "#1E2127";
static const char dmenu_font[]          = "#abb2bf";
static const char dmenu_highlight[]     = "#abb2bf";
static const char dmenu_highlight_font[]= "#1E2127";
static const char dmenu_search[]        = "#abb2bf";
static const char dmenu_search_font[]   = "#1E2127";
static const char dmenu_highlight_search[]       = "#1E2127";
static const char dmenu_highlight_search_font[]  = "#abb2bf";


static char *colors[][3]        = {
	//               fg         bg         border  
        [SchemeNorm]  = { bar_font_colour, bar_colour, bg_frame_colour },
 	[SchemeSel]   = { frame_font_colour, frame_colour, frame_border_colour  },
 	[SchemeTitle] = { titlefgcolor, titlebgcolor, titlebgcolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};


static const unsigned int OPAQUE = 0xD0U;
static const unsigned int baralpha = 0xE0U;
static const unsigned int borderalpha = 0xA0U;

static const unsigned int alphas[][3]      = {
         /*               fg      bg        border*/
        [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeTitle]  = { OPAQUE, baralpha, borderalpha  },
};



/* tagging */
static const char *tags[] = { "󰲠", "󰲢", "󰲤", "󰲦", "󰲨", "󰲪", "󰲬", "󰲮", "󰲰", "󰿬" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    instance      title       	 tags mask    isfloating   isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,       	    1 << 8,       0,           0,         0,        -1 },
	{ TERMCLASS,  NULL,       NULL,       	    0,            0,           1,         0,        -1 },
	{ NULL,       NULL,       "Event Tester",   0,            0,           0,         1,        -1 },
	{ NULL,      "spterm",    NULL,       	    SPTAG(0),     1,           1,         0,        -1 },
	{ NULL,      "spcalc",    NULL,       	    SPTAG(1),     1,           1,         0,        -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
    { "󰯌",          tile                   },  /* Default: Master on left, slaves on right */
    { "󱂩",          bstack                 },  /* Master on top, slaves on bottom */
    { "󰼀",          centeredmaster         },  /* Master in middle, slaves on sides */
    { "",          centeredfloatingmaster }   /* Same but master floats */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */


/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run",
        "-c",
        "-l", dmenu_height,
        "-h", dmenu_line_height,
        "-m", dmenumon,
        "-fn", dmenufont,
        "-nb", dmenu_background,
        "-nf", dmenu_font,
        "-sb", dmenu_highlight,
        "-sf", dmenu_highlight_font,
        "-nhb", dmenu_search,
        "-nhf", dmenu_search_font,
        "-shb", dmenu_highlight_search,
        "-shf", dmenu_highlight_search_font,
        NULL
};

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */

static char normbgcolor[]           = "#FF0000";
static char normbordercolor[]       = "#00FF00";
static char normfgcolor[]           = "#0000FF";
static char selfgcolor[]            = "#FFFF00";
static char selbordercolor[]        = "#FF00FF";
static char selbgcolor[]            = "#00FFFF";

ResourcePref resources[] = {
		{ "color0",		STRING,	&normbordercolor },
		{ "color8",		STRING,	&selbordercolor },
		{ "color0",		STRING,	&normbgcolor },
		{ "color4",		STRING,	&normfgcolor },
		{ "color0",		STRING,	&selfgcolor },
		{ "color4",		STRING,	&selbgcolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include "shiftview.c"

/* { modifier, key, function, argument } */
static const Key keys[] = {

    // Navigation 
	{ MODKEY,                               XK_t,           setlayout,                {.v = &layouts[0]} },
	{ MODKEY,                               XK_y,           setlayout,                {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,                     XK_t,           setlayout,                {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,                     XK_y,           setlayout,                {.v = &layouts[3]} },
	{ MODKEY,                               XK_o,           incnmaster,               {.i = +1 } },
	{ MODKEY|ShiftMask,                     XK_o,           incnmaster,               {.i = -1 } },
	{ MODKEY,                               XK_space,       zoom,                     {0} },
	STACKKEYS(MODKEY,                                                                 focus)
    STACKKEYS(MODKEY|ShiftMask,                                                       push)

    // Tabs Navigation
	TAGKEYS(                                XK_1,                                                0)
	TAGKEYS(                                XK_2,                                                1)
	TAGKEYS(                                XK_3,                                                2)
	TAGKEYS(                                XK_4,                                                3)
	TAGKEYS(                                XK_5,                                                4)
	TAGKEYS(                                XK_6,                                                5)
	TAGKEYS(                                XK_7,                                                6)
	TAGKEYS(                                XK_8,                                                7)
	TAGKEYS(                                XK_9,                                                8)
	{ MODKEY,                               XK_0,           view,                     {.ui = ~0 } },
	{ MODKEY|ShiftMask,                     XK_0,           tag,                      {.ui = ~0 } },


    // Windows
	{ MODKEY,                               XK_q,           killclient,               {0} },                        // quits the focused window
	{ MODKEY|ShiftMask,                     XK_q,           quit,                     {0} },			            // quit this window manager
	{ MODKEY,                               XK_Left,        focusmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,                     XK_Left,        tagmon,                   {.i = -1 } },
	{ MODKEY,                               XK_Right,       focusmon,                 {.i = +1 } },
	{ MODKEY|ShiftMask,                     XK_Right,       tagmon,                   {.i = +1 } },
	{ MODKEY,                               XK_b,           togglebar,                {0} },
	{ MODKEY,                               XK_h,           setmfact,                 {.f = -0.05} },
	{ MODKEY,                               XK_l,           setmfact,                 {.f = +0.05} },
	{ MODKEY,                               XK_z,           incrgaps,                 {.i = +3 } },
	{ MODKEY,                               XK_x,           incrgaps,                 {.i = -3 } },
	{ MODKEY,                               XK_a,           togglegaps,               {0} },
	{ MODKEY,                               XK_f,           togglefullscr,            {0} },



    // Applications and Scripts
	{ MODKEY,                               XK_d,           spawn,                    {.v = dmenucmd }},                                 // dynamic menu (dmenu)
	{ MODKEY,  	                            XK_Return,      spawn,                    SHCMD(TERMINAL) },	                             // open the terminal
	{ MODKEY,                               XK_w,           spawn,                    SHCMD("$BROWSER") },                               // open Browser
	{ MODKEY|ShiftMask,                     XK_w,           spawn,                    SHCMD(TERMINAL " -e sudo nmtui") },                // Wifi Gui
	{ MODKEY,                               XK_p,           spawn,                    SHCMD("dm-pass") },                               // open passmenu
	{ MODKEY|ShiftMask,                     XK_p,           spawn,                    SHCMD("maimpick") },                               // open passmenu
	{ MODKEY,                               XK_m,           spawn,                    SHCMD("dmenumount") },                             // open passmenu
	{ MODKEY|ShiftMask,                     XK_m,           spawn,                    SHCMD("dmenuumount") },                            // open passmenu
	{ MODKEY,                               XK_BackSpace,	spawn,                    SHCMD("sysact") },                                 // Script for logging out
	{ MODKEY,                               XK_r,           spawn,                    SHCMD(TERMINAL " -e lf") },
	{ MODKEY|ShiftMask,                     XK_r,           spawn,                    SHCMD(TERMINAL " -e htop") },
	{ MODKEY|ShiftMask,                     XK_b,           spawn,                    SHCMD(TERMINAL " -e bluetuith") },
	{ MODKEY,                               XK_equal,       spawn,                    SHCMD("pulsemixer --change-volume +5") },
	{ MODKEY,                               XK_minus,       spawn,                    SHCMD("pulsemixer --change-volume -5") },
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
};

