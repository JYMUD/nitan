// blade.c
// Last Modified by winder on May. 25 2001
#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
         set_name(HIG"С¥һҹ������"NOR, ({ "springrain blade", "blade" }) );
         set_weight(4000);
         if( clonep() )
                 set_default_object(__FILE__);
         else {
                 set("unit", "��");
                 set("value", 500);
                 set("material", "iron");
                 set("long",
                        "��С¥һҹ�����꣢������С¥���꣢�����������������������֮һ��\n"
                        "�˵���а�����������ࡣ\n");
                 set("wield_msg", "$N���һ�����λε�$n�������С�\n");
                 set("unequip_msg", "$N�����е�$n��������ĵ��ʡ�\n");
         }
         init_blade(300);
         setup();
}
