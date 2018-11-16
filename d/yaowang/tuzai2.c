#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���׳�");
        set("long", @LONG
������ҩ���ȵ����׳�����ר����������ҩ���������Ķ��
ȡҩ���õģ�����԰Ѷ���׽�������������(sha)��
LONG );
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"tuzai1",
        ]));
        setup();
}

void init()
{
        add_action("do_sha", "sha");
}

int do_sha(string arg)
{
        object me, ob;
        int exp,pot;
        exp=8+random(12);
        pot=2+random(2);
        me=this_player();

        if( query("family/family_name", me) != "ҩ����" || me->query_skill("medical",1)<60 )
        {
                return notify_fail("�㻹����ȡҩ�أ�����ɱ���\n");
        }

        if( !arg || !objectp(ob = present(arg, environment(me))) )
                return notify_fail("ָ���ʽ��sha <ID> \n");

        if( !query("yaowang_zhuo", ob) )
                return notify_fail("�����������������ɱ��\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("����æ���أ�\n");

        if(random(3))
        {
              message_vision(HIR"$N��$n�������ײ��ϣ�һ��������ȥ��\n"NOR, me, ob);
              message_vision(HIR"�������$n���ϻ���������$N��������Լ���\n"NOR, me, ob);
                 me->start_busy(1+random(2));
              return 1;
            }
        me->improve_skill("medical", ((int)me->query_skill("healing",1)/10));
        message_vision(HIR"$N��$n�������ײ��ϣ�һ��������ȥ��\n"NOR, me, ob);
        ob->die();
        addn("combat_exp", exp, me);
        me->improve_potential(pot);
      tell_object(me,HIC "�����׹�������ԡ�����ҽ���������µ���ʶ��\n" NOR);
              tell_object(me, HIC "������" + chinese_number(exp) + 
                      "�㾭���" + chinese_number(pot) + "��Ǳ�ܡ�\n"NOR ); 
         me->start_busy(2);
        return 1;
}
