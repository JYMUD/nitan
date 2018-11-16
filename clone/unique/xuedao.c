//Cracked by Kafei
// xuedao.c  Ѫ��
//updated by weer@1.NT

#include <weapon.h>
#include <ansi.h>
inherit F_UNIQUE;
inherit BLADE;

void create()
{
        set_name(RED"Ѫ��"NOR, ({ "xue dao", "dao" }));
        set_weight(7000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", RED"һ���������嵶������ס�������������һ�㡣������ȥ��������һƬ��
��֮ɫ��\n" NOR);
                set("value", 7000000);
                set("material", "steel");
                set("rigidity", 200);
                set("replica_ob","/d/shaolin/obj/jiedao");
                set("wield_msg", RED "ֻ����ৡ���һ����Ѫ�����ʷɳ���$N����������סһ�����߷��ź�⣬������һƬѪ����\n" NOR);
                set("unwield_msg", RED " �߽����ʡ�\n" NOR);
                set("clone_ob", "/clone/weapon/xuedao");
        }
//      ::create();
        init_blade(100);
        setup();
}

void init()
{
        add_action("do_lian","lian");
        add_action("do_lian","practice");
}

int do_lian(string arg)
{
        object weapon, me = this_player();

        if (arg != "blade") return 0;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
        return notify_fail( "��ʹ�õ��������ԡ�\n");

        if ( weapon != this_object() ) return 0;
        
        if ( arg == "blade" && !me->is_fighting()
         && query("combat_exp", me) >= 50000
        && present("xuedao book", me)
        && ((int)me->query_skill("xuedao-daofa",1) >= 50
        && (int)me->query_skill("xuedao-daofa",1) <= 200
         && query("family/master_id", me) == "xuedaolaozu")){
                me->receive_damage("jingli",10);
                me->receive_damage("qi", 5);
                me->improve_skill("xuedao-daofa",query("int", me)+10);
        if( me->query_skill("xuedao-daofa",1) > 150 ) 
        me->receive_damage("jingli", 5 );
        me->receive_damage("qi", 5);

        if( me->query_skill("xuedao-daofa",1) > 180 ) 
        me->receive_damage("jingli", 10);
        me->receive_damage("qi", 5);

        if( me->query_skill("xuedao-daofa",1) > 200 ) 
        me->receive_damage("jingli", 15);
        me->receive_damage("qi", 5);
                tell_object(me,"���Ѫ�����������ˣ�\n", me);
        return 1;
        }
        else
        return notify_fail("Ѫ���������ˣ�������ûʲô��չ��\n");
}
