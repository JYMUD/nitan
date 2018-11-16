
#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "���̽���" NOR; }

int perform( object me, object target)
{
        int lvl, str, dex, skill;
        string weapon;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("���̽���ֻ�ܶ�ս���еĶ���ʹ�ã�\n");

        if( query_temp("canshang", me) )
                return notify_fail("���Ѿ���ʹ�ò��̽����ˣ�\n");

        if( objectp(query_temp("weapon", me)) )
                        return notify_fail("���̽�����Ҫ����ֲ���ʩչ��\n");

        if( me->query_skill_mapped("finger") != "canhe-zhi" )
                return notify_fail("����ʹ�õĲ��ǲκ�ָ������ʩչ���̽�����\n");

        if( me->query_skill_prepared("finger") != "canhe-zhi" )
                return notify_fail("�������Ĳ��ǲκ�ָ������ʩչ���̽�����\n");

        if( me->query_skill_mapped("force") != "shenyuan-gong" )
                return notify_fail("�����������ڹ�������Ԫ����ʩչ�������̽�����\n");

        if( me->query_skill("force") < 140 )
                return notify_fail("����ڹ���򲻵����޷�ʩչĽ�ݼҴ���ѧ��\n");

        if( me->query_int() < 22 )
                return notify_fail("�������̫�����ʩչ����Ľ�ݼҴ���ѧ��\n");

        if( (lvl=me->query_skill("finger")) < 100 )
                return notify_fail("���̽�����Ҫ�����ָ��������Ч��\n");

        if( query("neili", me) <= lvl*3/2 )
                return notify_fail("�������������ʹ��Ľ�ݾ�ѧ����ָ����\n");

        if( query("jingli", me)<lvl )
                return notify_fail("��ľ���������ʹ��Ľ�ݾ�ѧ����ָ����\n");

        message_combatd(HIM "$N" HIM "����Ĭ���������̡���������ת������������ֻ���������ƿ�֮���������죡\n"
                        HIM "��������һ�ɽ���ֱ��$n" HIM "��ȥ��\n" NOR, me, target);
        str = me->query_str()/2;
        dex = me->query_dex()/3;
        addn_temp("apply/str", str, me);
        addn_temp("apply/dex", dex, me);
        set_temp("canshang", 1, me);

        skill = (me->query_skill("canhe-zhi",1)+me->query_skill("beidou-xianzong" ,1)) / 2;

        me->start_call_out( (: call_other, __FILE__, "end_perform", me, str, dex :),skill/8);

        addn("neili", -lvl, me);
        addn("jingli", -lvl, me);
        return 1;
}

void end_perform( object me, int str, int dex)
{
        addn_temp("apply/str", -str, me);
        addn_temp("apply/dex", -dex, me);
        delete_temp("canshang", me);

        tell_object(me, HIY "�㻺����ס���Σ�����һ�������������ջص��\n" NOR);
}