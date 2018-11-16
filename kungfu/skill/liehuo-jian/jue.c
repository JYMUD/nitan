// This program is a part of NITAN MudLIB
// jue.c �һ�������

#include <ansi.h>

inherit F_SSERVER;

string name() { return "�һ�������"; }

int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int i;

        if (! me->is_fighting())
                return notify_fail("��"+HIR"�һ�������"NOR+"��ֻ����ս����ʹ�á�\n");

        if (me->is_busy())
                return notify_fail("����æ���أ�\n");

        if (! objectp(weapon = query_temp("weapon", me))
        || (string)query("skill_type", weapon) != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)query("neili", me) < 500)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("sword") < 100 ||
                me->query_skill_mapped("sword") != "liehuo-jian")
                return notify_fail("��ġ��һ𽣡��������ң��޷�ʹ�á�"+HIR"�һ�������"NOR+"����\n");

        msg = HIR "$N������������ʱ���б���������ˣ�������Է�������ȥ��\n" NOR;
        message_combatd(msg, me, target);

        me->clean_up_enemy();
        ob = me->select_opponent();
        addn("neili", -300, me);

        for(i = 0; i < 3; i++)
                if (me->is_fighting(ob) && ob->is_fighting(me) && query("eff_qi", ob)>0)
                {
                        set("action_msg", "������", me);
                        if (!query("equipped", weapon)) break;
                        COMBAT_D->do_attack(me, ob,weapon, 0);
                } else break;

        me->start_busy(1 + random(2));
        return 1;
}
