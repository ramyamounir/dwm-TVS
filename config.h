/* See LICENSE file for copyright and license details. */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define TERMINAL "st"
#define TERMCLASS "St"
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* appearance */
static const unsigned int borderpx    = 1.5;      /* border pixel of windows */
static const unsigned int gappx       = 20;       /* gaps between windows */
static const unsigned int snap        = 0;        /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int minwsz      = 25;       /* Minimal heigt of a client for smfact */
static const int showbar              = 1;        /* 0 means no bar */
static const int topbar               = 1;        /* 0 means bottom bar */
static const unsigned int cornerrad   = 0;        /* window cornder radius */ 
static const int bar_height           = 30;
static const double activeopacity     = 1.0f;     /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity   = 0.9f;     /* Window opacity when it's inactive (0 <= opacity <= 1) */
static       Bool bUseOpacity         = False;    /* Starts with opacity on any unfocused windows */
static const char *fonts[]            = {
    "SF Mono:size=10:style=SemiBold",
    "SF Pro Display Medium:size=11",
    "Symbols Nerd Font:size=12",
    "Symbols Nerd Font Mono:size=12"
};
static const char dmenufont[]         = "SF Mono:size=10:style=SemiBold";




/*
fields                        background-turquoise        background-green

# dwm
bar_colour                    "#002B33"                   "#003A3E"
bar_font_colour               "#25BBAA"                   "#00E6B0"
frame_colour                  "#25BBAA"                   "#E28743"
frame_border_colour           "#25BBAA"                   "#008080"
frame_font_colour             "#002B33"                   "#003A3E"
bg_frame_colour               "#002B33"                   "#003A3E"
titlebgcolor                  "#002B33"                   "#003A3E"
titlefgcolor                  "#25BBAA"                   "#009D7C"

# dmenu
background (nb)               "#003A3E"                   "#003A3E"
font (nf)                     "#25BBAA"                   "#25BBAA" 
highlight (sb)                "#007169"                   "#007169" 
highlight font (sf)           "#00E7B1"                   "#00E7B1"
search (nhb)                  "#007169"                   "#007169"
search font (nhf)             "#003A3E"                   "#003A3E"
highlight search bg (shb)     "#003739"                   "#003739"
highlight search font (shf)   "#E2D982"                   "#E2D982"
*/



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
static const char dmenu_font[]          = "#25BBAA";
static const char dmenu_highlight[]     = "#007169";
static const char dmenu_highlight_font[]= "#00E7B1";
static const char dmenu_search[]        = "#007169";
static const char dmenu_search_font[]   = "#1E2127";
static const char dmenu_highlight_search[]       = "#003739";
static const char dmenu_highlight_search_font[]  = "#E2D982";


static const char *colors[][3]        = {
	//               fg         bg         border  
    [SchemeNorm]  = { bar_font_colour, bar_colour, bg_frame_colour },
 	[SchemeSel]   = { frame_font_colour, frame_colour, frame_border_colour  },
 	[SchemeTitle] = { titlefgcolor, titlebgcolor, titlebgcolor  },
};




/*
// colors
static char col_black[]       = "#1E2127";
static char col_white[]       = "#abb2bf";
static char col_blue[]       = "#61AFEF";
static char col_red[]       = "#E45649";
static char col_purple[]       = "#C678DD";
static char col_green[]       = "#1DB954";
static char col_yellow[]       = "#D19A66";

static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#770000";
static char selbgcolor[]            = "#005577";

static char *colors[][3]      = {
	//               fg         bg         border   
	[SchemeNorm] = { col_white, col_black, col_black},
	[SchemeSel]  = { col_white, col_black,  col_blue},
};
*/





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
	{ NULL,      "spcalc",    NULL,       	    SPTAG(1),     1,           1,         0,        -1 }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const float smfact    = 0.00; /* factor of tiled clients [0.00..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

/* { symbol, arrange function, direction } */
static const Layout layouts[] = {
    { "󰯌",          tile,                   'V' },
    { "󰨦",          NULL,                   'V' },
    { "󰼀",          centeredmaster,         'V' },
    { "󱂩",          bstack,                 'H' },
    { "󰯋",          bstackhoriz,            'H' },
    { "",          centeredfloatingmaster, 'H' }
};

static const int default_layout = 5;

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } },
	/*{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \*/
	/*{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \*/
	/*{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \*/
	/*{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \*/
	/*{ MOD, XK_x,     ACTION##stack, {.i = -1 } },*/


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

/* { modifier, key, function, argument } */
static const Key keys[] = {

    // Navigation 
	{ MODKEY,                               XK_t,           setlayout,                {.v = &layouts[0]} },
	{ MODKEY,                               XK_y,           setlayout,                {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,                     XK_t,           setlayout,                {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,                     XK_y,           setlayout,                {.v = &layouts[5]} },
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
	{ MODKEY,                               XK_h,           setmfact_ls,                 {.f = -0.05} },
	{ MODKEY,                               XK_l,           setmfact_ls,                 {.f = +0.05} },
	/*{ MODKEY,                               XK_z,           incrgaps,                 {.i = +3 } },*/
	/*{ MODKEY,                               XK_x,           incrgaps,                 {.i = -3 } },*/
	/*{ MODKEY,                               XK_a,           togglegaps,               {0} },*/
	{ MODKEY,                               XK_f,           togglefullscr,            {0} },



    // Applications and Scripts
	{ MODKEY,                               XK_d,           spawn,                    {.v = dmenucmd }},                                 // dynamic menu (dmenu)
	{ MODKEY,  	                            XK_Return,      spawn,                    SHCMD(TERMINAL) },	                             // open the terminal
	{ MODKEY,                               XK_w,           spawn,                    SHCMD("$BROWSER") },                               // open Browser
	{ MODKEY|ShiftMask,                     XK_w,           spawn,                    SHCMD(TERMINAL " -e sudo nmtui") },                // Wifi Gui
	{ MODKEY,                               XK_p,           spawn,                    SHCMD("passmenu") },                               // open passmenu
	{ MODKEY|ShiftMask,                     XK_p,           spawn,                    SHCMD("maimpick") },                               // open passmenu
	{ MODKEY,                               XK_m,           spawn,                    SHCMD("dmenumount") },                             // open passmenu
	{ MODKEY|ShiftMask,                     XK_m,           spawn,                    SHCMD("dmenuumount") },                            // open passmenu
	{ MODKEY,                               XK_BackSpace,	spawn,                    SHCMD("sysact") },                                 // Script for logging out
	{ MODKEY,                               XK_r,           spawn,                    SHCMD(TERMINAL " -e lf") },
	{ MODKEY|ShiftMask,                     XK_r,           spawn,                    SHCMD(TERMINAL " -e htop") },
	{ MODKEY,                               XK_minus,       spawn,                    SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,                     XK_minus,       spawn,                    SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,                               XK_equal,       spawn,                    SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,                     XK_equal,       spawn,                    SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks)") },
                                                                                                                                        
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD(TERMINAL) },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

