// Code of ShenZhou
// kurong.c �����ķ�
// Modify By Scatter

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("�����ķ������˺������ã�\n");

        if( query_temp("kurong", me) )
                return notify_fail("��������ת�����ķ��ˡ�\n");

        if (me->query_skill("kurong-changong",1) < 100
                || me->query_skill("force",1) < 100
                || me->query_skill("buddhism",1) < 100 )
                return notify_fail("�����δ��ͨ��������ǿ�˿����ķ������洦��\n");

        if( query("max_neili", me)<2000
                 || query("neili", me)<query("max_neili", me)/10 )
                return notify_fail("�������������ת�����ķ���\n");

        skill=me->query_skill("kurong-changong",1)+me->query_skill("buddhism",1);

        message("vision",HIW"\n"+query("name", me)+"˫�ƺ�ʮ����Ϣ��ת�£�һ����Ƭ�̼���Ѫ��ȫ��ֻʣ�ݹǣ���Ƭ�̣��ֻظ�Ѫ���ӯ��ģ����\n\n"NOR,environment(me),me);
        tell_object(me, HIW "\n��˫�ƺ�ʮ����ת�����ķ���һ�������Ե����������������ת��Ϣ������һ��һ�����֣�Ƭ�̼��ظ�������\n\n" NOR);

        set_temp("kurong", skill*4*query("max_neili", me)/2000, me);

        call_out("checking", 1, me);
        addn("neili", -query("max_neili", me)/10, me);

        return 1;
}

void checking(object me)
{
        int maxqi, amount;

        if (!me) return;

        if (!living(me))
        {
                delete_temp("kurong", me);
                return;
        }

        if( !query_temp("kurong", me)){
                tell_object(me, HIW "��е������������ǣ���ת�Ŀ����ķ�����ɢȥ��\n" NOR);
                return;
        }

        if (me->query_skill_mapped("force") != "kurong-changong")
        {
                delete_temp("kurong", me);
                return;
        }

        if (!me->is_fighting()) {
                if( query_temp("kurong", me) <= 50 )
                        delete_temp("kurong", me);
                else addn_temp("kurong", -50, me);
        }

        maxqi=query("eff_qi", me);

        if (me->is_ghost()) {
                delete_temp("kurong", me);
                return;
        }

        if( living(me) && (maxqi<query("max_qi", me)*95/100 && query("neili", me)>150)){
                amount=(me->query_skill("kurong-changong",1)+me->query_skill("buddhism",1))/4+query("con", me);
                addn("neili", -100, me);
                me->receive_curing("qi", amount);
                message_vision("$N�������˼���������Ϣ��ת���˿ڵ�Ѫ���Զ�ֹס�ˡ�\n", me);
        }

        if( living(me) && (query("qi", me)<(maxqi*2/3))){
                amount=maxqi-query("qi", me);
                if( amount>query_temp("kurong", me))amount=query_temp("kurong", me);
                addn_temp("kurong", -amount, me);
                me->receive_heal("qi", amount);
                message_vision("$N�������˼���������ɫ�������ö��ˡ�\n", me);
        }

        call_out("checking", 2, me);
        return;
}