// sangong.c

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        if( query("max_neili", me)<1 )
                return notify_fail("���Ѿ�������ɢ����ûʲô��Ҫ��ɢ���ˡ�\n");

        tell_object(target, HIY "��ĬĬ�İ������Ǵ󷨵ľ��Ͻ�����ɢ���澭������\n" NOR);
        message("vision", HIY + me->name() + "�������أ�ȴ�ֲ������˵���"
                          "�ӣ���֪��������ʲô�����Ĺ���\n" NOR,
                environment(me), ({ me }));

        me->start_busy(1);
        addn("max_neili", -100, me);
        if( query("max_neili", me)<0 )
                set("max_neili", 0, me);

        return 1;
}

void del_sucked(object me)
{
        delete_temp("sucked", me);
}