#include <ansi.h>
#include "pill.h"

void create()
{
        set_name(HIR "������" NOR, ({ "huolong guo", "huolong", "guo" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "����һöȭͷ��С�Ļ����������𵽵�Ϣ���������á�\n" NOR);
                set("base_unit", "ö");
                set("base_value", 8000);
                set("base_weight", 100);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int na, un;

        na = query("name");
        un = query("base_unit");

        if( time()-query_temp("last_eat/dan(D, me)")<400 )
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        if( query("neili", me) >= query("max_neili", me)*2 )
        {
                write("������������Ϊ�������" + name() + "��\n");
                return 1;
        }

        set_temp("last_eat/dan(D)", time(), me);

        message_vision(HIY "$N" HIY "����һ" + un + na + HIY "��˫Ŀ��ʱ��"
                       "�����䡣\n" NOR, me);

        set("neili",query("max_neili",  me)*2, me);

        me->start_busy(5);
        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}