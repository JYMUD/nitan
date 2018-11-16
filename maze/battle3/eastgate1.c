// Room: /d/xiangyang/eastgate1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "青龙内门");
        set("long", 
"这里是襄阳城的东城门的内城门，只见城门上方是三个大字。近年来
蒙古屡次侵犯襄阳城，故这儿把守相当严密，一些官兵们正在盘查要离襄
阳城的人。两边是上城头的石阶，向西进入城区。\n\n"
"                         s________________s         
                        /LLLLLLLLLLLLLLLLLL\\      
    []__[]             ^^||======||======||^^             []__[] 
    []==[]_[]__[]__[]__[]||[]__[]||[]__[]||[]__[]__[]__[]_[]==[]
    []==[]|__|__|__|__|__|__|┏━━━┓_|__|__|__|__|__|__[]==[]    
    []==[]__|__|__|__|__|__|_┃"HIY"襄阳城"NOR"┃__|__|__|__|__|__|_[]==[]  
    []==[]|__|__|__|__|__|__|┗━━━┛_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|__/      \\|__|__|__|__|__|__|_[]==[]
    []==[]|__|__|__|__|__|__||        |__|__|__|__|__|__|_[]==[]
    []==[]__|__|__|__|__|__|_|        |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__| "HIG"青龙门"NOR" |__|__|__|__|__|__|_[]==[]
    []==[]__|__|__|__|__|__|_|        |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]\n\n"
);
        set("outdoors", "xiangyang");

        set("exits", ([
                "east"    : __DIR__"eastgate2",
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 2,
        ]));
        set("coor/x", -7780);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
}
