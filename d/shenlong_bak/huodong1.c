inherit ROOM;

string show_bei();
string show_aoxian();

// 72Сʱֻ����սһ��
#define TIME_LIMIT 2

#include <ansi.h>

void create()
{
        set("short", HIR "���涴" NOR);
        set("long",@LONG
һ����˴�����֮��ϢͻȻ��һ���ޱȳ��ȵ���Ϣ�ڸǣ�ֻ����
���ұ�ʹ���ط��ź�⣬�ƺ��Ǿ�����ǧ������ĳ㿾������������
�ȣ�ǰ���ں�����һƬ��ֻ�н�������ʯ�����Ļ����ܿ��������
���¡���Զ������һ�鱮ʯ��bei���� Զ�����������һЩ���֡���
˵������������һֻ�Ѿ����������ε�Զ�Ż�����ޡ�
LONG);


        set("exits", ([
                "out"  : __DIR__"dong3.16",
        ]));

        set("item_desc", ([
                "bei"  : (: show_bei :),
                "aoxian":(: show_aoxian :),
        ]));

        set("no_rideto",1);
        set("no_flyto", 1);
        set("no_clean_up", 1);
        setup();

}

string show_bei()
{
        object ob;

        ob = find_living("huo qilin");
        if (objectp(ob) && environment(ob) == this_object())
        {
                return HIG "����һ�������Ż��صı�ʯ����ʯ���밼�ݵĲ��ֱ�ն��ѫ�����������������⣡\n" NOR;
        }
        return NOR + WHT "�������һЩ���صķ��ţ���δ�����������ڱ�ʯ������һ��ط��Ѿ���"
                         "��(aoxian)��ȥ���ƺ���һ������\n" NOR;
}

string show_aoxian()
{
        object ob;

        ob = find_living("huo qilin");
        if (objectp(ob) && environment(ob) == this_object())
        {
                return HIG "��ʯ���밼�ݵĲ��ֱ�ն��ѫ�����������������⣡\n" NOR;
        }

        if( query("no_putin", this_object()) )
                return HIG "��ʯ���밼�ݵĲ��ֱ�ն��ѫ�����������������⣡\n" NOR;

        return HIY "����ϸ�۲��ⰼ����ȥ��һ�飬�ƺ����Է�(putin)��һ����Ʒ�������еĻ��ء�\n" NOR;
}

// �������Ƿ��Ѿ��μӹ�����ս
void init()
{
        object me = this_player();

        add_action("do_putin", "putin");

        // TIME_LIMITСʱֻ�ܲμ�һ�Σ������ڼ����⣬Ϊ2Сʱ
        if (time() - query("boss/qilin", me) <  TIME_LIMIT * 3600 && userp(me) && ! wizardp(me))
        {
                tell_object(me, HIG "\n�Բ�����μӻ�����Կ�ս���ʱ����" +
                                sprintf("%d", TIME_LIMIT) + "Сʱ��\n");
                tell_object(me, HIC "������ϴβμӻ�����Կ�ս����� " + HIY +
                  sprintf("%d",(time()-query("boss/qilin", me))/3600)+HIC"Сʱ��\n\n"NOR);
                me->move(__DIR__"dong3.16");
                return;
        }

        // ���òμ�ʱ��
        tell_object(me, HIG "\n�������涴׼���μӶԿ�������ս�����벻Ҫ�뿪������" +
                        sprintf("%d", TIME_LIMIT) + "Сʱ���޷��ٴν��롣\n" NOR);
        tell_object(me, HIR "���Ѿ�����Ϊ����״̬���ڻ��涴��������Զ������������ʧ�κ���Ʒ�ͼ��ܡ�\n\n" NOR);
        set("boss/qilin", time(), me);

        // ����Ҫ���ã������Զ�����

        me->save();

        return;
}

// ����ն��ѫ��
int do_putin(string arg)
{
        object ob, env;
        object ob_qilin;

        object me = this_player();

        if (! arg)return notify_fail("��������ʲô��Ʒ��ʯ���а��ݲ��֣�\n");

        ob_qilin = find_living("huo qilin");
        if (objectp(ob_qilin))
        {
                if (environment(ob_qilin) == this_object() )
                        return notify_fail(HIG "ʯ���е�ն��ѫ�����������⣬͸������ض��������Ϣ��\n" NOR);
        }
        // �����峡������
        env = environment(me);
        if( query("doing", env) )
        {
                return notify_fail("Ŀǰ�����峡�����Ժ����ԣ�\n");
        }

        if( query("no_putin", env) )
                return notify_fail("��Ŀǰ��ʱ�޷���ɴ˲��������Ժ����ԡ�\n");

        if (objectp(ob = present(arg, me)))
        {

                // �ж��Ƿ�Ϊն��ѫ��
                if (base_name(ob) != "/clone/armor/zhanyao-xunzhang")
                        return notify_fail("��׼���ó�" + ob->name() + NOR "����ʯ����ȴ������ôҲ�Ų���ȥ��\n");

                /*
                // �����ڼ�������Կ�״򿪣����ݿ͵������ۣ�1COINһ��
                if (base_name(ob) != "/d/shenlong/obj/qilin_key")
                        return notify_fail("��׼���ó�" + ob->name() + NOR "����ʯ����ȴ������ôҲ�Ų���ȥ��\n");
                */
                message_vision(HIR "\n����~һ����$N��" + ob->name() + HIR "����ʯ���еİ��ݲ��֣�˲��" + ob->name() +
                             HIR "��ʯ����Ϊһ�壬��ɢ��������Ĺ�â ����\n" NOR, me);

                destruct(ob);

                set("no_putin", 1, env);
                remove_call_out("clear_no_putin");
                call_out("clear_no_putin", 10, env);

                // �����ӳٳ���
                remove_call_out("qilin_coming");
                call_out("qilin_coming", 5, me);

                return 1;
        }

        return notify_fail("������û��������Ʒ��\n");
}

void qilin_coming(object me)
{
        object ob_qilin, ob;

        ob = find_living("huo qilin");

        if (objectp(ob) && environment(ob))
        {
                if (base_name(environment(ob)) == __FILE__)
                        return ;
        }

        // �����峡�򷵻�
        ob = environment(me);
        if( query("doing", ob))return ;

        message_vision(HIY "\n��Ȼ�䣬ʯ�����ҵĲ���������ɽ��Ҳ��ʼ�ζ���������һ����죬һ�Ż����ɽ"
                       "����ܳ� ����\n" NOR, me);

        ob_qilin = new(__DIR__"npc/qilin");

        set("life_time", time(), ob_qilin);
        ob_qilin->move(__FILE__);

        delete("no_putin", ob);

        return;
}

void clear_no_putin(object env)
{
        delete("no_putin", env);
        return;
}

void start_move()
{
        object *ob;
        int i;
        object ob_out;

        ob = all_inventory(this_object());

        // ����峡��־
        delete("doing");

        if (! sizeof(ob))return;

        if (! objectp(ob_out = find_object(__DIR__"dong3.16")))
                ob_out = load_object(__DIR__"dong3.16");

        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character())
                {
                        destruct(ob[i]);
                        continue;
                }

                if( query("id", ob[i]) == "huoqilin" )
                        continue;

                ob[i]->move(ob_out);
        }

        return;
}

// ����BOSS�ĺ��У��������������ӳٽ����з����ڵ�ID
// �ƶ������涴�⣬��delay_time = 0 ���ӳ�
void move_all_player_out(int delay_time)
{
        if (! delay_time)
        {
                start_move();
        }
        else
        {
                remove_call_out("start_move");
                call_out("start_move", delay_time);
        }

        return;

}
