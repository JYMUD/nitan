#include <ansi.h>
#define BATTLEFIELD2_D     "/adm/daemons/battlefieldd2.c"
inherit COMBINED_ITEM;

void create()
{
        set_name(HIC"ս"NOR CYN"��"HIC"ѫ"NOR CYN"��"NOR, ({ "battle insigne"}) );
        set_temp("status", HIG"��"NOR GRN"��");

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "��ս���л�õ�ս��ѫ�£����������һ�ϡ�е���Ʒ��Ҳ����\n"
                            "ʹ��(use)�����½���ս����\n");
                set("unit", "��");
                set("base_unit", "ö");
                set("base_value", 100);
                set("no_sell", 1);
                set("no_drop", 1);
                set("no_give", 1);
        }
        setup();
        set_amount(1);
}

void init()
{
        add_action("do_use", "use");
}

int do_use(string arg)
{
        object me;
        object env;

        me = this_player();

        if( !BATTLEFIELD_D->is_battle_open() && !BATTLEFIELD2_D->is_battle_start() )
                return notify_fail("ս����û�п�ʼ������\n");

        if( !BATTLEFIELD_D->is_battle_start() && !BATTLEFIELD2_D->is_battle_start() )
                return notify_fail("ս����û�п�ʼ��\n");
        
        if( !BATTLEFIELD_D->in_battle(me) && !BATTLEFIELD2_D->in_battle(me) )
                return notify_fail("�����ʹ��battle join���μ�ս����\n");        
                
        if( BATTLEFIELD_D->inside_battlefield(me) || BATTLEFIELD2_D->inside_battlefield(me) )
                return notify_fail("���Ѿ���ս�����ˣ�Ϊ������ս�ɡ�\n");

        if( BATTLEFIELD_D->in_battle(me) ) BATTLEFIELD_D->init_player(me);
        else BATTLEFIELD2_D->init_player(me);
        add_amount(-1);
        return 1;
}

