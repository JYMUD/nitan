// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;
#include <localtime.h>

string* dirs = ({
        "east", "southeast", "southeast", "southwest", "northeast", "northeast",
        "west", "south", "south", "northwest", "north", "north",
});

string* dirs2 = ({
        "e", "se", "se", "sw", "ne", "ne",
        "w", "s", "s", "nw", "n", "n",
});

void create()
{

        set("short", "�һ���");
        set("long", @LONG
��һ�߽����֣�������һ���һ�����һ�����������ʱĿѣ���ԣ���
ʧ�˷���������и����˳�����ͷһ�ƣ���·���ڻ�������ʧ����Ӱ��
�٣�����ֻ��Ӳ��ͷƤ��ǰ���ˡ�
LONG );

        set("exits", ([
                "east"      : __DIR__"thzhen1",
                "south"     : __DIR__"thzhen1",
                "west"      : __DIR__"thzhen1",
                "north"     : __DIR__"thzhen1",
                "northeast" : __DIR__"thzhen3",
                "southeast" : __DIR__"thzhen3",
                "southwest" : __DIR__"thzhen3",
                "northwest" : __DIR__"thzhen3",
        ]));

        set("objects", ([
                // CLASS_D("taohua") + "/feng" : 1,
        ]) );

        set("outdoors", "taohua");

        set("coor/x", 9000);
        set("coor/y", -2500);
        set("coor/z", 0);
        setup();

}
/*
void init()
{
        set_temp("die_reason", "�����һ������һ�������", this_player());
        this_player()->receive_damage("qi", 15);
        this_player()->receive_wound("qi",  15);
        message_vision(HIR "ͻȻһ���һ��������㼲��$N��\n" NOR, this_player());
}
*/

int valid_leave(object me, string dir)
{
        mixed local;
          int   count, gain;
          mapping myfam;

        myfam=query("family", me);

          local = localtime(time()*60);

          count = ((local[LT_HOUR] + 1) % 24) / 2;
          gain = random((me->query_skill("qimen-wuxing", 1)) / 30) + 1;
          if (dirs[count] == dir || dirs2[count] == dir)
          {
                me->move("/d/taohua/thzhen2");
                if (! myfam || myfam["family_name"] == "�һ���")
                {
                        if( query("combat_exp", me)<20000+random(10000) )
                        {
                                addn("combat_exp", gain, me);
                        }
                }
                  me->start_busy(random(3));
                return 1;
          }
          return ::valid_leave(me, dir);
}
