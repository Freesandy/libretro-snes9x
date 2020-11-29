#ifndef LIBRETRO_CORE_OPTIONS_H__
#define LIBRETRO_CORE_OPTIONS_H__

#include <stdlib.h>
#include <string.h>

#include <libretro.h>
#include <retro_inline.h>

#ifndef HAVE_NO_LANGEXTRA
#include "libretro_core_options_intl.h"
#endif

/*
 ********************************
 * VERSION: 1.3
 ********************************
 *
 * - 1.3: Move translations to libretro_core_options_intl.h
 *        - libretro_core_options_intl.h includes BOM and utf-8
 *          fix for MSVC 2010-2013
 *        - Added HAVE_NO_LANGEXTRA flag to disable translations
 *          on platforms/compilers without BOM support
 * - 1.2: Use core options v1 interface when
 *        RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION is >= 1
 *        (previously required RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION == 1)
 * - 1.1: Support generation of core options v0 retro_core_option_value
 *        arrays containing options with a single value
 * - 1.0: First commit
*/

#ifdef __cplusplus
extern "C" {
#endif

/*
 ********************************
 * Core Option Definitions
 ********************************
*/

/* RETRO_LANGUAGE_ENGLISH */

/* Default language:
 * - All other languages must include the same keys and values
 * - Will be used as a fallback in the event that frontend language
 *   is not available
 * - Will be used as a fallback for any missing entries in
 *   frontend language definition */

struct retro_core_option_definition option_defs_us[] = {

   /* These variable names and possible values constitute an ABI with ZMZ (ZSNES Libretro player).
    * Changing "Show layer 1" is fine, but don't change "layer_1"/etc or the possible values ("Yes|No").
    * Adding more variables and rearranging them is safe. */

   {
      "snes9x_region",
      "系统制式（需要重启）",
      "指定系统制式。'PAL'制是50hz，'NTSC'制是60hz。\n"
      "如果选择了不正确的制式，游戏可能会运行偏快或者偏慢。",
      {
         { "auto", "自动" },
         { "ntsc", "NTSC" },
         { "pal",  "PAL" },
         { NULL, NULL},
      },
      "auto"
   },
   {
      "snes9x_aspect",
      "显示宽高比",
      "选择期望的显示宽高比。\n"
      "此项设置只有当RetroArch的宽高比设为‘内核提供’时有效。",
      {
         { "4:3",         NULL },
         { "uncorrected", "未修正的" },
         { "auto",        "自动" },
         { "ntsc",        "NTSC" },
         { "pal",         "PAL" },
         { NULL, NULL},
      },
      "4:3"
   },
   {
      "snes9x_overscan",
      "切除过扫描区域",
      "移除屏幕上下边缘的大约8个像素，这些像素通常并未被游戏使用，在标准电视上被边框隐藏了。\n"
      "'自动'表示根据当前游戏自动检测和切除过扫描区域。",
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { "auto",     "自动" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_gfx_hires",
      "启用高分辨率模式",
      "允许游戏切换到高分比率模式（512x448）或者强制所有游戏以256x224输出（会有破损像素）。",
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_hires_blend",
      "高分辨率混合",
      "当游戏切换到高分辨率模式时（512x448），混合相邻像素。\n"
      "某些有些需要此方法产生透明效果（例如Kirby's Dream Land, Jurassic Park...）",
      {
         { "disabled", "禁用" },
         { "merge",    "融合" },
         { "blur",     "模糊" },
         { NULL, NULL},
      },
      "disabled"
   },
   {
      "snes9x_blargg",
      "Blargg NTSC滤镜",
      "使用一个视频滤镜来模拟不同的NTSC TV信号。",
      {
         { "disabled",   "禁用" },
         { "monochrome", "单色" },
         { "rf",         "射频" },
         { "composite",  "复合视频" },
         { "s-video",    "S-Video" },
         { "rgb",        "RGB" },
         { NULL, NULL},
      },
      "disabled"
   },
   {
      "snes9x_audio_interpolation",
      "音频插值",
      "使用音频滤镜。'Gaussian'产生比原始硬件加强的低音效果。\n"
	  "'Cubic'和'Sinc'精确度较低，但是保留更多高频。",
      {
         { "gaussian", "Gaussian" },
         { "cubic",    "Cubic" },
         { "sinc",     "Sinc" },
         { "none",     "None" },
         { "linear",   "Linear" },
         { NULL, NULL},
      },
      "gaussian"
   },
   {
      "snes9x_up_down_allowed",
      "允许同时按下相反方向键",
      "启用此项允许同时按下/快速切换/按住左右或者上下方向键。\n"
      "这可能会引起移动问题。",
      {
         { "disabled", "禁用" },
         { "enabled",  "启用" },
         { NULL, NULL },
      },
      "disabled"
   },
   {
      "snes9x_overclock_superfx",
      "SuperFX超频",
      "SuperFX协处理器倍频。可以提高帧率也可能引起时序错误。\n"
      "低于100%的值可以提高在低端设备上的游戏性能。",
      {
         { "50%",  NULL },
         { "60%",  NULL },
         { "70%",  NULL },
         { "80%",  NULL },
         { "90%",  NULL },
         { "100%", NULL },
         { "150%", NULL },
         { "200%", NULL },
         { "250%", NULL },
         { "300%", NULL },
         { "350%", NULL },
         { "400%", NULL },
         { "450%", NULL },
         { "500%", NULL },
         { NULL, NULL},
      },
      "100%"
   },
   {
      "snes9x_overclock_cycles",
      "减少拖慢（Hack，不安全）",
      "超频SNES的CPU。可能导致游戏崩溃！\n"
      "'轻度'可以缩短游戏载入时间。\n"
      "'兼容方式'可以解决绝大部分游戏的拖慢。\n"
      "'最大'只针对某些绝对需要的游戏（例如Gradius 3, Super R-type...）",
      {
         { "disabled",   "禁用" },
         { "light",      "轻度" },
         { "compatible", "兼容方式" },
         { "max",        "最大" },
         { NULL, NULL},
      },
      "disabled"
   },
   {
      "snes9x_reduce_sprite_flicker",
      "减少闪烁（Hack，不安全）",
      "增加屏幕上可以同时绘制的活动块数量。",
      {
         { "disabled", "禁用" },
         { "enabled",  "启用" },
         { NULL, NULL},
      },
      "disabled"
   },
   {
      "snes9x_randomize_memory",
      "随机内存初始值（不安全）",
      "启动时随机化内存值。\n"
      "有些游戏例如'Super Off Road'使用系统内存\n"
      "作为随机数生成器来随机化物品放置或者AI行为，\n"
      "以使游戏更加难以预测。",
      {
         { "disabled", "禁用" },
         { "enabled",  "启用" },
         { NULL, NULL},
      },
      "disabled"
   },
   {
      "snes9x_block_invalid_vram_access",
      "阻止无效的VRAM访问",
      "有些自制程序/修改版ROM需要禁用此项才能正确运行。",
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "disabled"
   },
   {
      "snes9x_echo_buffer_hack",
      "回声缓存Hack（不安全，只对旧式添加音乐修改版ROM启用）",
      "有些自制程序/修改版ROM需要启用此项才能正确运行。",
      {
         { "disabled", "禁用" },
         { "enabled",  "启用" },
         { NULL, NULL},
      },
      "disabled"
   },
   {
      "snes9x_show_lightgun_settings",
      "显示光枪设置",
      "启用对Super Scope / Justifier / M.A.C.S.步枪输入设备的设置选项。\n"
      "注意：必须重新切换快速菜单以生效。",
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "disabled"
   },
   {
      "snes9x_lightgun_mode",
      "光枪模式",
      "使用鼠标控制的‘光枪’或者使用触屏输入。",
      {
         { "Lightgun",    "光枪" },
         { "Touchscreen", "触屏" },
         { NULL, NULL},
      },
      "Lightgun"
   },
   {
      "snes9x_superscope_reverse_buttons",
      "交换Super Scope的扳机按钮",
      "交换Super Scope的‘开火’键和‘光标’键的位置。",
      {
         { "disabled", "禁用" },
         { "enabled",  "启用" },
         { NULL, NULL},
      },
      "disabled"
   },
   {
      "snes9x_superscope_crosshair",
      "Super Scope准心大小",
      "改变屏幕上的准心大小。",
      {
         { "0",  NULL },
         { "1",  NULL },
         { "2",  NULL },
         { "3",  NULL },
         { "4",  NULL },
         { "5",  NULL },
         { "6",  NULL },
         { "7",  NULL },
         { "8",  NULL },
         { "9",  NULL },
         { "10", NULL },
         { "11", NULL },
         { "12", NULL },
         { "13", NULL },
         { "14", NULL },
         { "15", NULL },
         { "16", NULL },
         { NULL, NULL},
      },
      "2"
   },
   {
      "snes9x_superscope_color",
      "Super Scope准心颜色",
      "改变屏幕上的准心颜色。",
      {
         { "White",            "白色" },
         { "White (blend)",    "白色（混合）" },
         { "Red",              "红色" },
         { "Red (blend)",      "红色（混合）" },
         { "Orange",           "橙色" },
         { "Orange (blend)",   "橙色（混合）" },
         { "Yellow",           "黄色" },
         { "Yellow (blend)",   "黄色（混合）" },
         { "Green",            "绿色" },
         { "Green (blend)",    "绿色（混合）" },
         { "Cyan",             "青色" },
         { "Cyan (blend)",     "青色（混合）" },
         { "Sky",              "天蓝色" },
         { "Sky (blend)",      "天蓝色（混合）" },
         { "Blue",             "蓝色" },
         { "Blue (blend)",     "蓝色（混合）" },
         { "Violet",           "蓝紫色" },
         { "Violet (blend)",   "蓝紫色（混合）" },
         { "Pink",             "粉红色" },
         { "Pink (blend)",     "粉红色（混合）" },
         { "Purple",           "紫红色" },
         { "Purple (blend)",   "紫红色（混合）" },
         { "Black",            "黑色" },
         { "Black (blend)",    "黑色（混合）" },
         { "25% Grey",         "25%灰度" },
         { "25% Grey (blend)", "25%灰度（混合）" },
         { "50% Grey",         "50%灰度" },
         { "50% Grey (blend)", "50%灰度（混合）" },
         { "75% Grey",         "75%灰度" },
         { "75% Grey (blend)", "75%灰度（混合）" },
         { NULL, NULL},
      },
      "White"
   },
   {
      "snes9x_justifier1_crosshair",
      "Justifier 1准心大小",
      "改变屏幕上的准心大小。",
      {
         { "0",  NULL },
         { "1",  NULL },
         { "2",  NULL },
         { "3",  NULL },
         { "4",  NULL },
         { "5",  NULL },
         { "6",  NULL },
         { "7",  NULL },
         { "8",  NULL },
         { "9",  NULL },
         { "10", NULL },
         { "11", NULL },
         { "12", NULL },
         { "13", NULL },
         { "14", NULL },
         { "15", NULL },
         { "16", NULL },
         { NULL, NULL},
      },
      "4"
   },
   {
      "snes9x_justifier1_color",
      "Justifier 1准心颜色",
      "改变屏幕上的准心颜色。",
      {
         { "Blue",             "蓝色" },
         { "Blue (blend)",     "蓝色（混合）" },
         { "Violet",           "蓝紫色" },
         { "Violet (blend)",   "蓝紫色（混合）" },
         { "Pink",             "粉红色" },
         { "Pink (blend)",     "粉红色（混合）" },
         { "Purple",           "紫红色" },
         { "Purple (blend)",   "紫红色（混合）" },
         { "Black",            "黑色" },
         { "Black (blend)",    "黑色（混合）" },
         { "25% Grey",         "25%灰度" },
         { "25% Grey (blend)", "25%灰度（混合）" },
         { "50% Grey",         "50%灰度" },
         { "50% Grey (blend)", "50%灰度（混合）" },
         { "75% Grey",         "75%灰度" },
         { "75% Grey (blend)", "75%灰度（混合）" },
         { "White",            "白色" },
         { "White (blend)",    "白色（混合）" },
         { "Red",              "红色" },
         { "Red (blend)",      "红色（混合）" },
         { "Orange",           "橙色" },
         { "Orange (blend)",   "橙色（混合）" },
         { "Yellow",           "黄色" },
         { "Yellow (blend)",   "黄色（混合）" },
         { "Green",            "绿色" },
         { "Green (blend)",    "绿色（混合）" },
         { "Cyan",             "青色" },
         { "Cyan (blend)",     "青色（混合）" },
         { "Sky",              "天蓝色" },
         { "Sky (blend)",      "天蓝色（混合）" },
         { NULL, NULL},
      },
      "Blue"
   },
   {
      "snes9x_justifier2_crosshair",
      "Justifier 2准心大小",
      "改变屏幕上的准心大小。",
      {
         { "0",  NULL },
         { "1",  NULL },
         { "2",  NULL },
         { "3",  NULL },
         { "4",  NULL },
         { "5",  NULL },
         { "6",  NULL },
         { "7",  NULL },
         { "8",  NULL },
         { "9",  NULL },
         { "10", NULL },
         { "11", NULL },
         { "12", NULL },
         { "13", NULL },
         { "14", NULL },
         { "15", NULL },
         { "16", NULL },
         { NULL, NULL},
      },
      "4"
   },
   {
      "snes9x_justifier2_color",
      "Justifier 2准心颜色",
      "改变屏幕上的准心颜色。",
      {
         { "Pink",             "粉红色" },
         { "Pink (blend)",     "粉红色（混合）" },
         { "Purple",           "紫红色" },
         { "Purple (blend)",   "紫红色（混合）" },
         { "Black",            "黑色" },
         { "Black (blend)",    "黑色（混合）" },
         { "25% Grey",         "25%灰度" },
         { "25% Grey (blend)", "25%灰度（混合）" },
         { "50% Grey",         "50%灰度" },
         { "50% Grey (blend)", "50%灰度（混合）" },
         { "75% Grey",         "75%灰度" },
         { "75% Grey (blend)", "75%灰度（混合）" },
         { "White",            "白色" },
         { "White (blend)",    "白色（混合）" },
         { "Red",              "红色" },
         { "Red (blend)",      "红色（混合）" },
         { "Orange",           "橙色" },
         { "Orange (blend)",   "橙色（混合）" },
         { "Yellow",           "黄色" },
         { "Yellow (blend)",   "黄色（混合）" },
         { "Green",            "绿色" },
         { "Green (blend)",    "绿色（混合）" },
         { "Cyan",             "青色" },
         { "Cyan (blend)",     "青色（混合）" },
         { "Sky",              "天蓝色" },
         { "Sky (blend)",      "天蓝色（混合）" },
         { "Blue",             "蓝色" },
         { "Blue (blend)",     "蓝色（混合）" },
         { "Violet",           "蓝紫色" },
         { "Violet (blend)",   "蓝紫色（混合）" },
         { NULL, NULL},
      },
      "Pink"
   },
   {
      "snes9x_rifle_crosshair",
      "M.A.C.S.步枪准心大小",
      "改变屏幕上的准心大小。",
      {
         { "0",  NULL },
         { "1",  NULL },
         { "2",  NULL },
         { "3",  NULL },
         { "4",  NULL },
         { "5",  NULL },
         { "6",  NULL },
         { "7",  NULL },
         { "8",  NULL },
         { "9",  NULL },
         { "10", NULL },
         { "11", NULL },
         { "12", NULL },
         { "13", NULL },
         { "14", NULL },
         { "15", NULL },
         { "16", NULL },
         { NULL, NULL},
      },
      "2"
   },
   {
      "snes9x_rifle_color",
      "M.A.C.S.步枪准心颜色",
      "改变屏幕上的准心颜色。",
      {
         { "White",            "白色" },
         { "White (blend)",    "白色（混合）" },
         { "Red",              "红色" },
         { "Red (blend)",      "红色（混合）" },
         { "Orange",           "橙色" },
         { "Orange (blend)",   "橙色（混合）" },
         { "Yellow",           "黄色" },
         { "Yellow (blend)",   "黄色（混合）" },
         { "Green",            "绿色" },
         { "Green (blend)",    "绿色（混合）" },
         { "Cyan",             "青色" },
         { "Cyan (blend)",     "青色（混合）" },
         { "Sky",              "天蓝色" },
         { "Sky (blend)",      "天蓝色（混合）" },
         { "Blue",             "蓝色" },
         { "Blue (blend)",     "蓝色（混合）" },
         { "Violet",           "蓝紫色" },
         { "Violet (blend)",   "蓝紫色（混合）" },
         { "Pink",             "粉红色" },
         { "Pink (blend)",     "粉红色（混合）" },
         { "Purple",           "紫红色" },
         { "Purple (blend)",   "紫红色（混合）" },
         { "Black",            "黑色" },
         { "Black (blend)",    "黑色（混合）" },
         { "25% Grey",         "25%灰度" },
         { "25% Grey (blend)", "25%灰度（混合）" },
         { "50% Grey",         "50%灰度" },
         { "50% Grey (blend)", "50%灰度（混合）" },
         { "75% Grey",         "75%灰度" },
         { "75% Grey (blend)", "75%灰度（混合）" },
         { NULL, NULL},
      },
      "White"
   },
   {
      "snes9x_show_advanced_av_settings",
      "显示高级音频/视频设置",
      "显示图层/GFX特效/音频通道的底层设置。\n"
      "注意：必须重新切换快速菜单以生效。",
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "disabled"
   },
   {
      "snes9x_layer_1",
      "显示图层1",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_layer_2",
      "显示图层2",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_layer_3",
      "显示图层3",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_layer_4",
      "显示图层4",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_layer_5",
      "显示角色层",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_gfx_clip",
      "启用图形剪切窗口",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_gfx_transp",
      "启用透明特效",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_sndchan_1",
      "启用声音通道1",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_sndchan_2",
      "启用声音通道2",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_sndchan_3",
      "启用声音通道3",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_sndchan_4",
      "启用声音通道4",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_sndchan_5",
      "启用声音通道5",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_sndchan_6",
      "启用声音通道6",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_sndchan_7",
      "启用声音通道7",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   {
      "snes9x_sndchan_8",
      "启用声音通道8",
      NULL,
      {
         { "enabled",  "启用" },
         { "disabled", "禁用" },
         { NULL, NULL},
      },
      "enabled"
   },
   { NULL, NULL, NULL, {{0}}, NULL },
};

/*
 ********************************
 * Language Mapping
 ********************************
*/

#ifndef HAVE_NO_LANGEXTRA
struct retro_core_option_definition *option_defs_intl[RETRO_LANGUAGE_LAST] = {
   option_defs_us, /* RETRO_LANGUAGE_ENGLISH */
   NULL,           /* RETRO_LANGUAGE_JAPANESE */
   NULL,           /* RETRO_LANGUAGE_FRENCH */
   NULL,           /* RETRO_LANGUAGE_SPANISH */
   NULL,           /* RETRO_LANGUAGE_GERMAN */
   NULL,           /* RETRO_LANGUAGE_ITALIAN */
   NULL,           /* RETRO_LANGUAGE_DUTCH */
   NULL,           /* RETRO_LANGUAGE_PORTUGUESE_BRAZIL */
   NULL,           /* RETRO_LANGUAGE_PORTUGUESE_PORTUGAL */
   NULL,           /* RETRO_LANGUAGE_RUSSIAN */
   NULL,           /* RETRO_LANGUAGE_KOREAN */
   NULL,           /* RETRO_LANGUAGE_CHINESE_TRADITIONAL */
   NULL,           /* RETRO_LANGUAGE_CHINESE_SIMPLIFIED */
   NULL,           /* RETRO_LANGUAGE_ESPERANTO */
   NULL,           /* RETRO_LANGUAGE_POLISH */
   NULL,           /* RETRO_LANGUAGE_VIETNAMESE */
   NULL,           /* RETRO_LANGUAGE_ARABIC */
   NULL,           /* RETRO_LANGUAGE_GREEK */
   option_defs_tr, /* RETRO_LANGUAGE_TURKISH */
};
#endif

/*
 ********************************
 * Functions
 ********************************
*/

/* Handles configuration/setting of core options.
 * Should be called as early as possible - ideally inside
 * retro_set_environment(), and no later than retro_load_game()
 * > We place the function body in the header to avoid the
 *   necessity of adding more .c files (i.e. want this to
 *   be as painless as possible for core devs)
 */

static INLINE void libretro_set_core_options(retro_environment_t environ_cb)
{
   unsigned version = 0;

   if (!environ_cb)
      return;

   if (environ_cb(RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION, &version) && (version >= 1))
   {
#ifndef HAVE_NO_LANGEXTRA
      struct retro_core_options_intl core_options_intl;
      unsigned language = 0;

      core_options_intl.us    = option_defs_us;
      core_options_intl.local = NULL;

      if (environ_cb(RETRO_ENVIRONMENT_GET_LANGUAGE, &language) &&
          (language < RETRO_LANGUAGE_LAST) && (language != RETRO_LANGUAGE_ENGLISH))
         core_options_intl.local = option_defs_intl[language];

      environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_INTL, &core_options_intl);
#else
      environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS, &option_defs_us);
#endif
   }
   else
   {
      size_t i;
      size_t option_index              = 0;
      size_t num_options               = 0;
      struct retro_variable *variables = NULL;
      char **values_buf                = NULL;

      /* Determine number of options
       * > Note: We are going to skip a number of irrelevant
       *   core options when building the retro_variable array,
       *   but we'll allocate space for all of them. The difference
       *   in resource usage is negligible, and this allows us to
       *   keep the code 'cleaner' */
      while (true)
      {
         if (option_defs_us[num_options].key)
            num_options++;
         else
            break;
      }

      /* Allocate arrays */
      variables  = (struct retro_variable *)calloc(num_options + 1, sizeof(struct retro_variable));
      values_buf = (char **)calloc(num_options, sizeof(char *));

      if (!variables || !values_buf)
         goto error;

      /* Copy parameters from option_defs_us array */
      for (i = 0; i < num_options; i++)
      {
         const char *key                        = option_defs_us[i].key;
         const char *desc                       = option_defs_us[i].desc;
         const char *default_value              = option_defs_us[i].default_value;
         struct retro_core_option_value *values = option_defs_us[i].values;
         size_t buf_len                         = 3;
         size_t default_index                   = 0;

         values_buf[i] = NULL;

         /* Skip options that are irrelevant when using the
          * old style core options interface */
         if ((strcmp(key, "snes9x_show_lightgun_settings") == 0) ||
             (strcmp(key, "snes9x_show_advanced_av_settings") == 0))
            continue;

         if (desc)
         {
            size_t num_values = 0;

            /* Determine number of values */
            while (true)
            {
               if (values[num_values].value)
               {
                  /* Check if this is the default value */
                  if (default_value)
                     if (strcmp(values[num_values].value, default_value) == 0)
                        default_index = num_values;

                  buf_len += strlen(values[num_values].value);
                  num_values++;
               }
               else
                  break;
            }

            /* Build values string */
            if (num_values > 0)
            {
               size_t j;

               buf_len += num_values - 1;
               buf_len += strlen(desc);

               values_buf[i] = (char *)calloc(buf_len, sizeof(char));
               if (!values_buf[i])
                  goto error;

               strcpy(values_buf[i], desc);
               strcat(values_buf[i], "; ");

               /* Default value goes first */
               strcat(values_buf[i], values[default_index].value);

               /* Add remaining values */
               for (j = 0; j < num_values; j++)
               {
                  if (j != default_index)
                  {
                     strcat(values_buf[i], "|");
                     strcat(values_buf[i], values[j].value);
                  }
               }
            }
         }

         variables[option_index].key   = key;
         variables[option_index].value = values_buf[i];
         option_index++;
      }

      /* Set variables */
      environ_cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);

error:

      /* Clean up */
      if (values_buf)
      {
         for (i = 0; i < num_options; i++)
         {
            if (values_buf[i])
            {
               free(values_buf[i]);
               values_buf[i] = NULL;
            }
         }

         free(values_buf);
         values_buf = NULL;
      }

      if (variables)
      {
         free(variables);
         variables = NULL;
      }
   }
}

#ifdef __cplusplus
}
#endif

#endif
