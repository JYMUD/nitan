
#include <armor.h>
#include <ansi.h>

inherit ARMOR;

void create()
{
        set_name(HIR "�����" NOR, ({ "potian jia" }) );
        set_weight(1000);
                set("long", HIW "����һ������ͨͨ�Ļ��ף�������Χɢ��������������������������"
                        "ʲôҲ�����塣\n" HIC
                    HIC "��Ч�м�������+ 100        ��Ч�Ṧ������+ 100\n" NOR
                    HIC "����Ч��������+ 20%        ����Ч���ȼ���  300\n" NOR
                    HIC "�����ر�������+ 40%\n" NOR);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "steel");
                                set("value", 800000);
                set("armor_prop/armor", 300);
                        set("armor_prop/dodge", 100);
                                set("armor_prop/parry", 100);
                        set("armor_prop/reduce_poison", 20);
                                set("armor_prop/avoid_poison", 40);
                }
                set("material", "tian jing");
                set("wear_msg", HIR "������ƿն��죬����������֮������ȴ������$N" HIC "�϶�Ϊһ��[2;37;0m\n" NOR);
                set("remove_msg", HIR "$N" HIC "���쳤Х������׶������죬ɲ�Ǽ���Χ������ɢ�������������"
                                                        "��ʧ����ʡ�\n" NOR);

        setup();
}

int query_autoload()
{
        return 1;
}
/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;  

        if ((int)me->query_skill("force", 1) < 260
           || (int)me->query("neili") < 500
           || ! living(me) || random(4) != 1)
                return;

        cost = damage / 2;

        if (cost > 300) cost = 300;

        ap = ob->query_skill("force") * 12 + ob->query("max_neili");
        dp = me->query_skill("force") * 12 + me->query("neili");

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "ƽ���ؿ���$N" HIR "��$N" HIR "��"
                                            "��һƬãȻ�����룺�ѵ���С������ǧ��\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$n" HIR "ƽ���ؿ���$N" HIR "��$N" HIR "��"
                                            "��һƬãȻ�����룺�ѵ���С������ǧ��\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIR "$n" HIR "ƽ���ؿ���$N" HIR "��$N" HIR "��"
                                            "��һƬãȻ�����룺�ѵ���С������ǧ��\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "$n" HIR "ƽ���ؿ���$N" HIR "��$N" HIR "��"
                                            "��һƬãȻ�����룺�ѵ���С������ǧ��\n" NOR]);
                        break;
                }
                return result;
        }
}
*/