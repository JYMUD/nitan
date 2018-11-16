#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + HIC "���߸�" NOR, ({ "guiling gao", "guiling", "gao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIC "����һ�����ڹ�׺��������óɵĹ���"
                            "�࣬�����������١�\n" NOR);
                set("value", 3000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int na, un;
        mapping my = me->query_entire_dbase();

        na = this_object()->name();
        un=query("unit", this_object());

        if ((int)me->query_condition("pill_drug") > 0)
        {
                write("�����������Ϣδ���������������ܸе������嵴����"
                      "��óȻ��ʳ��\n");
                return 1;
        }

        me->apply_condition("pill_drug", 2000);

        message_vision(HIC "$N" HIC "����һ" + un + na + HIC "����æ��ʼ�˹���"
                       "��ҩ����\n" NOR, me);

        if( query("max_jingli", me)<1000 )
        {
                tell_object(me, HIC "��ֻ���þ�����֮��������ֱ�����ڶ�����\n" NOR);
                me->improve_jingli(5 + random(5));
        } else
                tell_object(me, HIC "��ֻ��������֮����ȫ���ƣ��һɨ���ա�\n" NOR);

        if( query("jingli", me)<query("max_jingli", me) )
                my["jingli"]  = my["max_jingli"];

        me->start_busy(random(5) + 5);
        destruct(this_object());
        return 1;
}