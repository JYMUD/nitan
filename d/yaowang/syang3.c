#include <ansi.h>
inherit ROOM;
string* npcs = ({
        __DIR__"npc/xiong",
        __DIR__"npc/he",
        __DIR__"npc/lu",
        __DIR__"npc/xie",
        __DIR__"npc/she",
});
void create()
{
        set("short", "������");
        set("long",@LONG
������ҩ���ȵ�����������������һЩ����ȡҩ�ĵĶ������԰Ѷ���
׽(zhuo)�����׳�ȥɱ��ȡҩ��
LONG );
        set("exits", ([
                "east" : __DIR__"syang",
        ]));
        set("objects", ([
        npcs[random(sizeof(npcs))] :random(2),
        npcs[random(sizeof(npcs))] :random(2),
        npcs[random(sizeof(npcs))] :random(2),
        npcs[random(sizeof(npcs))] :random(2),
        npcs[random(sizeof(npcs))] :random(2),
        ]) );
        setup();
}

void init()
{
        add_action("do_zhiliao", "zhuo");
}

int do_zhiliao(string arg)
{
        object me, ob;
          int lvl,exp,pot;
          exp=8+random(12);
          pot=2+random(6);
        me=this_player();
        lvl=me->query_skill("hunting");
        if( query("family/family_name", me) != "ҩ����"
         || lvl < 60 ) 
        {               return notify_fail("�㻹�������Լ����أ�׽�����ʲô��\n");
        }

        if( !arg || !objectp(ob = present(arg, environment(me))) )
                return notify_fail("ָ���ʽ��zhuo <ID> \n");

       if( query("owner", ob) == query("id", me) )
                   return notify_fail("���Ѿ�׽��"+ob->name()+"�ˣ�\n");

        if( query("owner", ob) && query("owner", ob) != query("id", me) )
                      return notify_fail(ob->name()+"�Ѿ����˼ҵ��ˣ�\n");
        if( !query("yaowang_zhuo", ob) )
                return notify_fail("�����������׽��\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("����æ���أ�\n");
          if (random(lvl)>lvl*2/3)
        {       
        ob->set_leader(me);
        me->start_busy(2);
        message_vision("$N��$n�ٻ���������$n�͹ԹԵø���$N��\n", me, ob);
                me->improve_skill("hunting",(query("int", me)/6));
                write(HIC "�����ٻ������ж������Լ�������Щ��ᡣ\n" NOR);
                   set("owner",query("id",  me), ob);
                     addn("combat_exp", exp, me);
                     me->improve_potential(pot);
                     tell_object(me, HIC "������" + chinese_number(exp) + 
                             "�㾭���" + chinese_number(pot) + "��Ǳ�ܡ�\n"NOR );
        }else 
        {       
        message_vision("$N��$n�ٻ���������$n�����Ͳ���$N��\n", me, ob);
          me->start_busy(random(2));
        }

        return 1;
}
