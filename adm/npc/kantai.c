#include <ansi.h>
inherit ROOM;

int is_chat_room() { return 1; }

void create() {
        set("short", "���俴̨");
        set("long", @LONG
�����Ǳ��䳡�Ŀ�̨�������Ѿ����������У�Ⱥ�����۷׷ף����ڲ�
��˭���۹�������Щ���ӡ�
LONG
    );
        set("exits", ([
                "down"  : "/d/huashan/houzhiwangyu",
        ]));
        
        set("no_fight", 1);
        set("outdoors", "huashan" ); 

        setup();
}

