// This program is a part of NT MudLIB

#include <ansi.h>

#define ZHOUTIAN_D      "/adm/daemons/zhoutiand"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object tongren_ob;

        if( me->is_busy() || me->is_fighting() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg || arg == "" )
                return notify_fail("ָ���ʽ : chongxue <Ѩλͭ��ID>\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("����ڹ���Ϊ���㣬�޷���ϸС����Ѩλ��ͨ��\n");

        if( (int)me->query_skill("jingluo-xue", 1) < 100 )
                return notify_fail("��Ծ���ѧ���ղ������޷���ϸС����Ѩλ��ͨ��\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("�����ڵ���̫���ˣ��޷����ĳ�Ѩ��\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("�����ڵľ�̫���ˣ��޷����ĳ�Ѩ��\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("������������в��㣬�޷���ϸС����Ѩλ��ͨ��\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("�����ڵ�����̫���ˣ��޷��˹���Ѩ��\n");

        if( arg == "all" )
        {
                if( !query("jingmai/finish", me) )
                        return notify_fail("�㲢û��ȫ���С���쾭��Ѩ����ͨ����\n");

                set("breakup", 1, me);
                message_vision( HIC "ͻȻ$N" HIC "���һ����һ����������" 
                                HIC "��Ȼɢ�����������ܿ�����ʱ������ȡ�\n" NOR, me); 
                tell_object(me, HIG "���ʱ���û���һ�����ɣ�һ������֮����Ȼ" 
                                HIG "��������һƬ����������û��˿�����ͣ�ȫ������Ȼ��ͨ����̩֮����\n" NOR); 
                return 1;
        }

        if( query("jingmai/finish", me) )
                return notify_fail("���Ѿ���ͨȫ���С���쾭���������ٴγ�Ѩ��\n");

        if( !objectp(tongren_ob = present(arg, me)) )
                return notify_fail("������û�����ͭ�ˣ�\n");

        if( !tongren_ob->is_tongren() )
                return notify_fail("���޷�ʹ��������Ѩ��\n");

        if( query("jingmai/"+query("jingmai_name", tongren_ob)+"/"+arg, me) )
                return notify_fail("���Ѿ���ͨ�����Ѩλ��\n");

        message_vision(HIW "$N" HIW "����ͭ�������صĳ�Ѩ��ʽ������ͭ��֮������ڹ�����ʼ��Ѩ��\n" NOR, me);
        message_vision(HIW "ֻ��$N" HIW "ͷ�ϰ������ڡ�������ͬ���������С�\n" NOR, me);

        tell_object(me, HIG "����������ڵ���ԴԴ���������ٷ�����������Ԫ��תԽ��Խ�죬\n"
                        HIG"���������ѵ���һ������������"+query("xuewei_name", tongren_ob)+"��ȥ��\n"NOR);


        ZHOUTIAN_D->do_chongxue(me, tongren_ob);

        me->start_busy(1);

        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : chongxue <Ѩλͭ��ID>
           chongxue all    �������������С���쾭��Ѩ����ͨ����ʹ�ø�ָ���Ѩ

��ָ�����ϸС������ͨ�����ӳ�����������

HELP
);
        return 1;
}


