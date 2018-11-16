#include <ansi.h>
#define BATTLEFIELD2_D     "/adm/daemons/battlefieldd2.c"

inherit ITEM;

void delay_destruct()
{
        destruct(this_object());
}

void init(object ob)
{
        if( !ob ) ob = this_player();
        if( !userp(ob) )
                return;

        if( !BATTLEFIELD2_D->in_battle(ob) )
                return;


        if( query_temp("used") )
                return tell_object(ob, name(1)+"��ǿ�������Ѿ������ա�\n");

        //ob->start_condition(BATTLEFIELD_GLORY);
        BATTLEFIELD2_D->add_bonus_score(ob, 100);
        tell_object(ob, "����Ϊ����"+name(1)+"����� "HIY"100"NOR" ��ս��������\n");

        call_out((: delay_destruct :), 0);

        set_temp("used", 1);
}

void create()
{
        set_name(WHT"ս����ҫʯ��"NOR, ({ "battlefield glory statue", "statue" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "��һ���������ʯ�����˿��Ի�ü�ǿ���������");
                set("value", 1000000);
                set("unit", "��");
                set("no_get", 1);
        }
}

