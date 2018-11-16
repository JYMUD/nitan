// Room: /d/xiangyang/westgate1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "白虎内门");
        set("long", @LONG
这里是襄阳城的西城门的内城门，城门高三丈，宽约二丈有余，尺许厚的城
门上镶满了拳头般大小的柳钉。门洞长约四丈，大约每隔两个时辰就换官兵把守。
洞侧帖满了悬赏捉拿之类的官府通谍。门洞西侧则是一条上城墙的窄梯。近年来
蒙古屡次侵犯襄阳城，故这儿把守相当严密，一些官兵们正在盘查要离襄阳城的
人。两边是上城头的石阶，向东进入城区。
                         s________________s         
                        /LLLLLLLLLLLLLLLLLL\        
    []__[]             ^^||======||======||^^             []__[] 
    []==[]_[]__[]__[]__[]||[]__[]||[]__[]||[]__[]__[]__[]_[]==[]
    []==[]|__|__|__|__|__|__|┏━━━┓_|__|__|__|__|__|__[]==[]      
    []==[]__|__|__|__|__|__|_┃白虎门┃__|__|__|__|__|__|_[]==[]   
    []==[]|__|__|__|__|__|__|┗━━━┛_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|__/      \|__|__|__|__|__|__|_[]==[]
    []==[]|__|__|__|__|__|__||        |_|__|缉|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_|        |__┌┐┌┐_|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|└┘└┘|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_|  西门  |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "southup" : __DIR__"wallw2",
                "northup" : __DIR__"wallw1",
                "east"    : __DIR__"westjie3",
                "west"    : __DIR__"westgate2",
        ]));
        set("objects", ([
                "/quest/quest5/job2/pi4"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7860);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}