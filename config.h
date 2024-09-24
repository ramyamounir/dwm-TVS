/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx    = 1.5;      /* border pixel of windows */
static const unsigned int gappx       = 20;       /* gaps between windows */
static const unsigned int snap        = 0;        /* snap pixel */
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

static const char bar_colour[]        = "#003A3E";
static const char bar_font_colour[]   = "#00E6B0";
static const char frame_colour[]      = "#E28743";
static const char frame_font_colour[] = "#003A3E";
static const char frame_border_colour[] = "#008080";
static const char bg_frame_colour[]   = "#003A3E";
static const char titlebgcolor[]      = "#003A3E";
static const char titlefgcolor[]      = "#009D7C";

static const char dmenu_height[]      = "10";         /* number of lines */
static const char dmenu_line_height[] = "25";         /* line height */

static const char dmenu_background[]    = "#003A3E";
static const char dmenu_font[]          = "#25BBAA";
static const char dmenu_highlight[]     = "#007169";
static const char dmenu_highlight_font[]= "#00E7B1";
static const char dmenu_search[]        = "#007169";
static const char dmenu_search_font[]   = "#003A3E";
static const char dmenu_highlight_search[]       = "#003739";
static const char dmenu_highlight_search_font[]  = "#E2D982";

static const char *colors[][3]        = {
	/*               fg         bg         border   */
    [SchemeNorm]  = { bar_font_colour, bar_colour, bg_frame_colour },
 	[SchemeSel]   = { frame_font_colour, frame_colour, frame_border_colour  },
 	[SchemeTitle] = { titlefgcolor, titlebgcolor, titlebgcolor  },
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
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
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
    { "󰍉",          monocle,                'V' },
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

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define TERMINAL "st"
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

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
	/*{ MODKEY,                               XK_h,           setmfact,                 {.f = -0.05} },*/
	/*{ MODKEY,                               XK_l,           setmfact,                 {.f = +0.05} },*/
	/*{ MODKEY,                               XK_z,           incrgaps,                 {.i = +3 } },*/
	/*{ MODKEY,                               XK_x,           incrgaps,                 {.i = -3 } },*/
	/*{ MODKEY,                               XK_a,           togglegaps,               {0} },*/
	/*{ MODKEY,                               XK_f,           togglefullscr,            {0} },*/



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

