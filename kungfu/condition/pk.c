#include <ansi.h>

int dispel() { return 0; }

int update_condition(object me, int duration)
{
        if (duration < 1)
        {
                tell_object(me, HIR "ִ����������㣺�����ѱ����ն�"
                                "ʮ��Сʱ�������������ˣ���\n");
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "��˵" + me->name(1) + HIM + "�����ͷ��ˡ�");
                me->set("combat/WPK", 0);
                me->set("combat/PKS", 0);
                return 0;
        }
        // �ƻ��в����ٳͷ�ʱ��
        if (! me->query("doing"))me->apply_condition("pk", duration - 1);
        return 1;
}
