// train.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob,where;
        mapping fam;
        int sp, dp;
        int i, cost, train_level;

        seteuid(getuid());

        if (me->query_skill("training", 1) < 10)
                return notify_fail("���Ԧ�����������죬�޷�ѵ��Ұ�ޣ�\n");

        if (! arg)
                return notify_fail("��Ҫѵ��ʲôҰ�ޣ�\n");

        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("����û����ֻҰ�ްɣ�\n");

        if (playerp(ob)) 
                return notify_fail("�˼�Ҳ����ң����ʲô�㰡��\n");

        if( query("race", ob) != "Ұ��" )
                return notify_fail("�ⲻ��Ұ�ޣ�����ͷ�˰ɣ�\n");

        if( query_temp("owner", ob) && 
            (query_temp("owner", ob) == query("id", me)) )
                return notify_fail(ob->name() + "������ѱ�����ģ��㻹���ڸ�ɶ�����أ�\n");

        if( query_temp("owner", ob) && 
            (query_temp("owner", ob) != me) )
                return notify_fail(ob->name() + "�类�˼�ѱ���ˣ��㻹���ڸ�ɶ�����أ�\n");

        if (ob == me)
                return notify_fail("��û��ô���ɣ����Լ������ˣ�\n");

        if (! living(ob)) 
                return notify_fail("��ֻҰ���ε��ˣ�������ѵ�������أ�\n");

        if (me->is_busy())
                return notify_fail("����æ���Ȼ����˵�ɡ�\n");

        cost=query("max_jing", me)/(me->query_skill("training",1)/10)-10;
        if( cost < 1 ) cost = 1;

        if( query("jing", me) <= cost )
                return notify_fail("������̫���ˣ��޷�ѵ��Ұ�ޡ�\n");

        message_vision("ֻ��$N����" + ob->name() +
                       "�ֽ��Ұڣ������ƶ�������ϸ�\n\n",me);

        sp=me->query_skill("training",1)+query("int", me);
        dp=query("combat_exp", ob)/100;
        
        if (random(sp) < random(dp) / 2)
        {
                ob->kill_ob(me);
                me->start_busy(1);
                return notify_fail("��Ԧ�����������Ƕ���Ұ"
                                   "�Բ�����������ʹ��˹�����\n");
        }

        me->receive_damage("jing", cost);
        message_vision("��ʱ" + ob->name() + "����$Nҡ��ҡβ�ͣ�����ѱ�����ӡ�\n\n", me);

        train_level = me->query_skill("training", 1);
        if (me->can_improve_skill("training"))
                me->improve_skill("training",random(query("int", me)));

        set("attitude", "peace", ob);
        ob->remove_all_enemy(1);
        set_temp("owner", me, ob);
        set_temp("owner_name",query("name",  me), ob);
        set_temp("owner_id",query("id",  me), ob);
        if( (strsrch(query("name", ob),"��") >= 0) || 
            (strsrch(query("name", ob),"¿") >= 0) || 
            (strsrch(query("name", ob),"��") >= 0) || 
            (strsrch(query("name", ob),"��") >= 0) || 
            (strsrch(query("name", ob),"ţ") >= 0) || 
            (strsrch(query("name", ob),"��") >= 0) || 
            (strsrch(query("name", ob),"ʨ") >= 0) || 
            (strsrch(query("name", ob),"��") >= 0) || 
            (strsrch(query("name", ob),"��") >= 0) || 
            (strsrch(query("name", ob),"¹") >= 0) || 
            (strsrch(query("name", ob),"��") >= 0) || 
            (strsrch(query("name", ob),"��") >= 0) )
                set("ridable", 1, ob);
        me->remove_all_enemy();
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : train <����>

��ָ�������ѱ��ĳ��������Ѿ�ѱ���Ķ�����Խ�������ָ�

����ָ�
        come <������>:                  �ö�����������ж���
        stay:                           ֹͣ����ĸ���״̬��
        attack <ĳ��>:                  �ö��﹥�����ˡ�
        stop <������>:                  �ö���ֹͣ���˵Ĺ�����
        release:                        ������ū״̬����������롣

����ָ���ֻ��ĳЩ�������ã�
        qi(ride) <������>:              ���������������ȡ�
        xia(unride) <������>:           �£��뿪���
        wei(feed) <������>:             �涯��ιʳ��
        yin <������>:                   ��������ˮ��

HELP
        );
        return 1;
}
