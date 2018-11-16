// This program is a part of NITAN MudLIB
// hup.c ������Ԫ

#include <ansi.h>

#define HUP "��" HIR "������Ԫ" NOR "��"

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        string msg;
        mapping my;
        int rp;
        int neili_cost;

        if( userp(me) && !query("can_perform/xiantian-gong/hup", me) )
                return notify_fail("��δ�ø���ָ�㣬��֪�����ʩչ" HUP "��\n"); 

        if ((int)me->query_skill("xiantian-gong", 1) < 200)
                return notify_fail("�����칦�����������ʩչ" HUP "��\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" HUP "��\n");

        if( query("neili", me)<200 )
                return notify_fail("�����ڵ���������������ʩչ" HUP "��\n");

        my = me->query_entire_dbase();
        if ((rp = (my["max_qi"] - my["eff_qi"])) < 1)
                return (SKILL_D("force") + "/recover")->exert(me, target);

        if (rp >= my["max_qi"] / 10)
                rp = my["max_qi"] / 10;

        skill = me->query_skill("force");
        msg = HIW "$N" HIW "�����³�һ��������ʱ����ͨ������ɫ�����ı�"
              "��ƽ�͡�\n" NOR;
        message_combatd(msg, me);

        neili_cost = rp + 100;
        if (neili_cost > my["neili"])
        {
                neili_cost = my["neili"];
                rp = neili_cost - 100;
        }
        me->receive_curing("qi", rp);
        me->receive_healing("qi", rp * 3 / 2);
        addn("neili", -neili_cost, me);

        me->start_busy(3);
        return 1;
}