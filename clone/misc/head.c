// head.c �Դ�

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;
inherit F_CUTABLE;
inherit F_SILENTDEST;

void eat_effect();
int is_head() { return 1; }

void create()
{
        set_name(NOR + RED "ͷ­" NOR, ({ "head" }));
        set_weight(1500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 1);
                set("no_store", 1);
                set("no_sell", "�ҵ��졭�⡭����Ҳ���������١��ٸ��أ�");
                set("food_supply", 10);
                set("food_remaining", 4);
                set("long", RED "����һ����Ѫ���ܵ��׼�����Ѫ������������\n" NOR);
        }
}

int set_from(object owner)
{
        apply_effect((: eat_effect :));
        set("owner_id",query("owner_id", owner));
        set("victim_name",query("victim_name", owner));
        set("is_player",query("is_player", owner));
        set("killed_by",query("killed_by", owner));
        set("defeated_by",query("defeated_by", owner));
        set("defeated_by_who",query("defeated_by_who", owner));
        set("assist",query("assist", owner));
        set("gender",query("gender", owner));

        if( !stringp(query("victim_name", owner)) )
        {
                set("name", "���õ���ͷ");
                set("name", "���õ���ͷʬ��", owner);
        } else
        {
                set("name",query("victim_name", owner)+"����ͷ");
                set("name", "��ͷʬ��", owner);
        }

        if( query_temp("clawed_by_jiuyin", owner) )
        {
                set_temp("clawed_by_jiuyin", 1);
                set("long", query("long") +
                            "�����Ȼ�����С��������һ̽���պÿ��Բ��롣\n");
        }

        set_name(NOR + RED + query("name") + NOR, ({ "head" }));
        return 1;
}

int do_cut(object me, string part)
{
        if (! query("food_remaining"))
                return 0;

        return ::do_cut(me, part);
}

int finish_eat()
{
        set_name(NOR + WHT "����ͷ" NOR, ({ "bone" }));
        set_weight(150);
        set("long", WHT "����һ����ɭɭ������ͷ��\n" NOR);
        return 1;
}

void eat_effect()
{
        object me;

        me = this_player();
        addn("combat/eatman", 1, me);
        if( query("shen", me)>-1000 )
                set("shen", -1000, me);
}
