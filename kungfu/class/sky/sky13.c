#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "�������졿" NOR);
        set("long", HIW @LONG

                ��         ��         ��

    �����������ľ�ͷ������һƬ��ʣ�ãã�ޱߡ�Զ����ʱ����
һ������â������������ԭ���԰׵���ʡ����ȥ������ãã����
���������Ĵ����ӣ��ƺ�����ֹ����ż������������Ʈ��������ȴ��
ʹ�����������������Զ��վ��һλ���ߺ�һλ�����ˣ��ƺ���ע��
���㡣

LONG NOR );

        set("sleep_room", 1);
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/tongtian": 1,
                __DIR__"npc/tianshen": 1,
        ]));

        set("exits", ([
                "out" : "/d/city/wumiao",
        ]));
        set("sky", 1);
        setup();
}

void init()
{
        object me = this_player();
        
        if (! me->query("sky12/tianmen") && userp(me))
        {
                tell_object(me, HIG "ͨ�����ɶ���˵������û��ʹ�ù������ӣ�����ô��������ģ��ߣ�\n" NOR);

                me->delete("sky12");
                me->save();
                me->move("/d/city/wumiao");
                
                //destruct(me);                
        }
        return ;        
}
