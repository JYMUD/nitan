// Code of ShenZhou
// puti-zi.c ������

#include <ansi.h>

inherit ITEM;

void setup()
{}

int cure_ob(string);
void create()
{
        set_name("������", ({"puti zi", "zi"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�ž�Ө����������ӣ�������ɽ������ǰ����ϡ�ޱȣ�
������������֮ʵ�����ܻ��ٽ٣���ǧ�֣������ͬ�١�\n");
                set("value", 10000);
                set("no_sell", 1);
                set("medicine", 1);
                set("no_drop","�������������뿪�㡣\n");
                set("no_get", "�������������뿪�Ƕ���\n");
        }
        setup();
}
        
int cure_ob(object me)
{
        int force_limit, neili_limit, force_skill, add_skill, improve;


        force_limit=me->query_skill("force")*(query("con", me)*2/3);
        neili_limit=query("max_neili", me);
        force_skill = me->query_skill("force", 1);
        
        if ( (int)me->query_condition("bonze_drug" ) > 0 )
        {
                addn("max_neili", -(20+random(20)), me);
                message_vision(HIR "$N�ֳ���һ�������ӣ�ֻ���øγ���ϣ��������ѣ�ԭ����ʳ̫��̫�࣬ҩЧ�ʵ��䷴��\n" NOR, me);
        }
        else if ( neili_limit <= force_limit  )
        {
                addn("max_neili", 20+random(20), me);
                addn("neili", 100, me);

                message_vision(HIY "$N����һ�������ӣ���Ȼ��ֻ��һ�ɺƵ��ޱȵ�����ֱ�嶥��...\n" NOR, this_player());
                me->apply_condition("bonze_drug", 100);
        }

        me->unconcious();
        destruct(this_object());
        return 1;
}
