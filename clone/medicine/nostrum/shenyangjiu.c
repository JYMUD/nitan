// shenyangjiu.c �������
// Last Modified by winder on Jul. 15 2001

#include <ansi.h>
inherit ITEM;

void init()
{
        if (!wizardp(this_player()))
        {
                set("no_give","��ô���ľƣ����������ˣ�\n");
                set("no_drop","��ô��������ƣ����˶��ϧѽ��\n");
                set("no_sell","���������ƶ�Ҫ��,��̫��������˰ɡ�\n");
        }
        add_action("do_drink", "drink");
        add_action("do_drink", "he");
}

void create()
{
        set_name( YEL "�������" NOR , ({"shenyang yujiu", "jiu"}));
        set_weight(90);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","һ����Ƶ�ճ��ҩ�ƣ��������ǵ���أ���֮��ѧ��������档\n");
                set("value", 0);
                set("drug_type", "��Ʒ");
        }
        set("is_monitored",1);
        set("pour_type", "1");
        setup();
}

int do_drink(string arg)
{
        object me = this_player();

        if(!id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        if(!present(this_object(), this_player()))
                return notify_fail("��Ҫ��ʲô��\n");
        if( me->is_busy() )
                return notify_fail("�𼱣������ȣ�С�ı�Ǻ���ˡ�\n");

        if( query("eff_jing", me) >= query("max_jing", me) && 
                query("eff_qi", me) >= query("max_qi", me) )
        {
                write("��������ģ�������׵ľƲ����ϻ�\n");
                return 1;
        }
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        set("neili",query("max_neili",  me), me);
        message_vision(HIW "$N�ٱ����²�����ƣ�ֻ��С���������ϳ壬�����ؿڼ��\n����հ�����������ֻ��ͨ���ںͣ��ĺ���̩��\n" NOR, me);
        destruct(this_object());
        return 1;
}
