#include <ansi.h>
inherit ROOM;

#define SCBORN_D       "/adm/daemons/scbornd"

void create()
{
        set("short", NOR + WHT "��ͨ�����⡿" NOR);
        set("long", HIW @LONG
�����������������ããһƬ�ƺ�����Զ����һ�����ţ���ǰվ
��һ�����ߣ��ƺ���ע�����㡣���ŵ�������������һյ���ɫ�ĳ���
�ƣ�changmingdeng for xueyi����
LONG NOR );
        set("exits", ([
                "enter" : __DIR__"tianmen",
]));
        set("sky", 1);
        set("objects", ([
                __DIR__"npc/xing": 1,
                "/clone/misc/changmingdeng" : 1,
        ]));

        set("no_fight", 1);
        setup();
}

void init()
{
        // this_player()->delete("yhjob");
}

int valid_leave(object me, string dir)
{
        object ob;
        object *inv;
        int i;

        //if (! wizardp(me))return notify_fail("�ݲ����ţ�\n");

        if (time() - me->query("last_enter_tianmen0") < 86400)                        
        {
                 return notify_fail("�Բ���������ϴν�����粻��24Сʱ���޷��ٴν�����硣\n");
        }

        // ����12���������
        if ( dir == "enter" && ! me->query("sky12/floor"))
        {
               ob = present("xingjun yan", environment(me));
               if (! objectp(ob))return notify_fail("�������\n");
               message_vision(HIC "�Ǿ�����ϸ�Ŀ���$N" HIC " ����\n" NOR, me);

               if (! SCBORN_D->check_data(me))
               {
                            message_vision(HIW "�Ǿ�������ض�$N" HIW "˵���������������"
                                           "�������ʮ�����졣\n" NOR, me);
                                         
                            return notify_fail("\n");  
               }
        }

        if (dir == "enter")
        {
                // ����������벻��
                inv = deep_inventory(me);
                for (i = 0; i < sizeof(inv); i++)
                {
                        if (! playerp(inv[i])) continue;
        
                        // ���˱�����û�
                        return notify_fail(HIW "�Ǿ�������ض�$N" HIW "˵�������ҿ��㻹���Ȱ�" + inv[i]->name() + 
                                           HIW "������˵�ɣ�\n" NOR);                
                }                
        }

        me->set("last_enter_tianmen0", time());

        return ::valid_leave(me, dir);
}
