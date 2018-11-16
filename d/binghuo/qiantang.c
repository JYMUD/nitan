// Room: /binghuo/qiantang.c
// Date: Oct.28 1999 by Winder
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "Ǯ������");
        set("long", @LONG
Ǯ����������������תһ�����䣬Ȼ��ֱ�������ô��͸�����
�಻�������������������ϵ��һ�ұ���(zhou)���������з緫����
ͷ������յ��ɴ��������ɴ���£�һ����Ů������ͷ�����������ӡ�
LONG );
        set("outdoors", "wangpan");
        set("no_clean_up", 0);
        set("item_desc", ([
                "zhou" : "һ��С�ۣ�������ȥ(enter)������\n",
        ]));
        set("exits", ([
                "westup" : "/d/hangzhou/qiantang",
        ]));
        set("coor/x", 4080);
        set("coor/y", -1800);
        set("coor/z", -10);
        setup();
}

int do_enter(string arg)
{
        object me;
        mapping fam;

        me = this_player();
        if( !arg || arg=="" ) return 0;
        if( arg=="zhou" )
        {
               message("vision",
                        me->name() + "�����Ṧ��һ��������С�ۡ�",
                        environment(me), ({me}) );
               me->move(__DIR__"zhou");
               message("vision",
                        me->name() + "�Ӱ���Ծ��������\n",
                        environment(me), ({me}) );
                        return 1;
        }
        else  return notify_fail("���뵽��ȥ��\n");
}

void init()
{
        object me, dao, room, bai, ding;

        me = this_player();
        add_action("do_enter", "enter");
        room = get_object("/d/binghuo/wangpangu2");
        ding = present("chang jinpeng", room);

        if (objectp(ding)) 
                dao = present("tulong blade", ding);
        if (! dao)
        {
                ding = present("ding", room);
                if (objectp(ding)) 
                dao = present("tulong blade", ding);
        }

        if (objectp(dao))
        {
                room = get_object("/d/binghuo/wangpanshan");
                bai = present("bai guishou",room);
                if (objectp(bai)) tell_object(me, HIC "\nֻ�������ϲ����˺��������еĺ���ȫ���������ӥ�̵ı�־��\n" NOR);

                if (objectp(bai)
                    && !query_temp("broadcast", bai )
                    && query("combat_exp", me)>1000000
                    && query("weiwang", me)>100000 )
                {
                        message("vision", HIR"\n������������" NOR+WHT "�׹�������һ����Ц��\n" NOR, all_interactive());
                        message("vision", HIR"\n������������" NOR+WHT "�׹��٣�����ӥ�̵õ�����������"
                                          WHT"��������ɽ�������ﵶ������ᡣ\n" NOR, all_interactive());
                        set_temp("broadcast", 1, bai);
                }
        }
}
