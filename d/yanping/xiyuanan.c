// Room: /d/yanping/xiyuanan.c
// Date: Sep 28, 2002  Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "溪源庵");
        set("long", @LONG
雄渾的鳳山為底座，朝南突兀聳起，岩冠嶙剛，凌空而立。溪源庵窩
在鳳山南麓，兩側危岩壁立，四面層巒翠。沿鳳冠岩蜿蜒前行數百米，忽
然豁然開朗，滿目田園風光。古人“策杖問真源”，沿溪流自十里游廊到
此，一路山嵐水響，“別後三日，夢中猶作飛濤聲”。庵內留有不少古人
墨寶(poem)，南宋大儒朱熹大書“溪山第一”於此。
LONG );
        set("exits", ([
                "southdown" : __DIR__"xiagu",
        ]));
        set("item_desc", ([
                "poem" : HIY"
  和謝石氍別駕游溪源詩                     訪溪源"HIG"
               僧智永                               林世壁(明)"HIC"

香閣依危嶂， 悠然列翠屏。       溪源一派玉為流， 錦樹紅霞爛素秋。
鳥啼千樹碧， 人坐數峰青。       兩岸垂蘿雲嶂合， 數聲啼鳴石林幽。
得句皆春草， 無山不幔亭。       幽源何處可棲真， 流水桃花此避秦。
茲游良不俗， 自是慰山靈。       日暮清溪看曬網， 隔船時問打漁人。

寂歷峰頭寺， 藤蘿掩石扉。       沙岸紆迴碧浦通， 仙蹤縹緲自難窮。
聊將消白晝， 何幸接玄暉。       便應一葦臨滄海， 直訪蓬萊王蕊宮。
入竹逢僧話， 聞香悟道機。       溪上橫橋十四門， 煙霞杳藹入溪源。
涼風生木末， 幾片暮雲歸。       定知此夕遊仙夢， 一枕清風白鶴騫。
\n"NOR
        ]));
        set("outdoors", "yanping");
        set("no_clean_up", 0);
        set("coor/x", 1420);
        set("coor/y", -6120);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}