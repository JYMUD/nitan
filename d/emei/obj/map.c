// map.c 峨嵋地圖
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( HIC "『峨嵋旅遊圖』" NOR, ({ "luyou tu","tu","map"}) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long",
"\n                 『峨嵋旅遊圖』\n\n"
"　　　【地圖一】　　　　　　　　　＾　　　＜　ｕｐ\n"
" 　　　　　　　　　　　　　　　　北\n"
"\n"
"　　　白　　　　　　　　　　　　　　　　　　　　　　　 　≌≌≌\n"
"　　　龍　　　　　　　　　　　　　　　　　　　　　　　 　≌保≌　山\n"
"　　　洞＼清　　　　　　　　　　　　　　　　　　　　　 　≌國≌<―\n"
"　　　　　音　　　　　　　　　　　　　　　＋＋＋＋＋＋ ／≌寺≌　門\n"
"　　　　／閣＼中　神　純　歸　觀　解　密＋ 伏 ＋密　≌≌≌\n"
"　黑龍江　　　峰―水―陽―雲―音―脫― <―虎―\n"
"　棧道　　　　寺　閣　殿　閣　堂　坡　林＋ 寺 ＋林\n"
"　　　　 　　　　 ｜　　　　｜　　　　　 ＋＋＋＋＋＋＋\n"
"　　　　 　　　　 福 靈 　　玉\n"
"　　　　 　　　　 壽 文 　　女\n"
"　　　　 　　　　 庵 閣 　　峰\n"
"\n"
"\n"
"　　　【地圖二】　\n"
"\n"
"                  　　　　　　　　　　　　　　　　十二盤<-萬年庵≌\n"
"　　　　　　　　　　　　　　　　　　　　　　　　　／　　　≌≌≌≌\n"
"　　　　　＾　　　　　　　　　　　　　　　　　　／　　　　　＾\n"
"　　　　　北　　　　　　　　　　　　　　　　　／　　　古＋＋｜＋＋\n"
"　　　　　　　　　　　　　　　　十二盤―十二盤　　　　德＋白龍洞\n"
"　　　　　　　　　　　　　　　／　　　　　　　　　　　林＋＋＋＋＼\n"
"　　　　　　　　　　　　　　／　　　　　　　　　　　　　　　　　　清音閣\n"
"　＊＊<-―華嚴頂<-―十二盤　　　　　　　　　　　　　　　　　　　　／\n"
"　＊蓮＊　　　　　　　　　　　　　　　　　　　　　　　　　黑龍江棧道\n"
"　＊　＊　　　　　　　　　　　　　　　　　　　　　　　　　　　｜\n"
"　＊花＊　　　　　　　 　　　　　　　　　　　 　　≌≌≌≌≌\n"
"　＊　＊　　　　　　　　　　　　　　　　　　　　　　　　　≌千佛庵≌\n"
"　＊石＊　　　　　　　　　　　　　　九十九道拐<-九十九道拐　≌≌≌≌\n"
"　　　＼　　　九十九道拐<-九十九道拐\n"
"　　　　＼　　／\n"
"　　　∴九老洞口∴\n"
"　　　∴∴∴∴∴∴\n"
"\n"
"\n"
"\n"
"\n"
"　　　　　　　　　　　　　　　≈洗象池<-坡道<-坡道<-＊蓮花石＊\n"
"　　　【地圖三】　　　　　　　≈≈≈≈　　　　　　　＊＊＊＊＊\n"
"　　　　　　　　　　　　　　　　　｜　　　　　　　　　　　　　＼∴∴∴∴∴\n"
"　　　　　　　　　　　　　　　　凌雲梯　　　　　　　　　　　　　∴九老洞∴\n"
"　　　　　＾　　　　　　　　　　　｜　　　＋　　　　　　　　　　∴∴∴∴∴\n"
"　　　　　北　　　　　　　　　　雷洞坪　＋＋＋\n"
"　　　　　　　　　　　　　　　　　｜　　＋＋＋＋\n"
"　　　　　　　　　　　　　　　　八十四盤＋　冷＋＋\n"
"　　　　　　　　　　　　　　　／　＋＋＋＋　　＋＋\n"
"　　　　　　　　　　　　八十四盤　＋＋＋＋杉　＋＋\n"
"　　　　　　　　　　　　　｜　　＋＋＋＋　　　＋＋\n"
"　　　　　　　　　　　　　ˇ　　＋＋＋＋林　＋＋\n"
"　　　　　　　　　　　　　　　八十四盤　＋＋＋＋＋＋＋\n"
"　　　　　　　　　　　　　　＼　＋＋＋＋＋＋\n"
"　　　　　　　　　≌≌≌≌≌　＼\n"
"　　　　　　　　　≌萬行庵≌<-接引殿\n"
"　　　　　　　　　≌≌≌≌≌\n"
"　　　　　　　　　　　｜\n"
"　　　　　　　　　　　ˇ\n"
"　　　　　 　　　金頂\n"
"　　　　　　　　　　／\n"
"　　　　　≌≌≌≌≌　｜\n"
"　　　　　≌卧雲庵≌　｜\n"
"　　　　　≌≌≌≌　≌≌≌≌≌\n"
"　　　　　　　｜　　≌華藏庵≌\n"
"　　　　　　　｜　　≌≌≌≌≌\n"
"　　　　　　　｜　　　　｜\n"
"　　　　　　∽∽∽∽∽∽∽∽∽\n"
"　　　　　　∽　　　　　　　∽\n"
"　　　　　　∽　睹　光　台　∽\n"
"　　　　　　∽　　　　　　　∽\n"
"　　　　　　∽∽∽∽∽∽∽∽∽\n");
                set("value", 50);
                set("material", "paper");
        }
        setup();
}