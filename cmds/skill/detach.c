// detach.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        mapping family, skills;
        int i;
        string *skname;
        int lvl = 0;

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if (! arg)
                return notify_fail("ָ���ʽ��detach <����>\n");

        if (! (ob = present(arg, environment(me))) ||
            ! ob->is_character())
                return notify_fail("�����˭�Ͼ�ʦͽ��ϵ��?\n");

        if (! living(ob))
                return notify_fail("������Ȱ�" + ob->name() + "Ū�ѡ�\n");

        if( query("reborn_offer", me) )
                return notify_fail("ת�������в������������ɡ�\n");

        if( query_temp("pending/detach", me) != ob )
        {
                write(HIR "����Ĵ����" + ob->name(1) + "˵��Ҫ�뿪ʦ����������"
                      "���뿪�ˣ��㽫��ʧȥ���еĸ߼��书Ŷ��\n" NOR);
                write(YEL "�����������˾��ģ�����������һ��������\n" NOR);
                set_temp("pending/detach", ob, me);
                me->start_busy(1);
                return 1;
        }

        if (! me->is_apprentice_of(ob))
        {
                if( query("family/family_name", ob) == query("family/family_name", me) )
                {
                    message_vision("\n$N���һ������$n����ʲ��ʲô����Ҫ����ʦ�ţ�"
                                   "���¿ɵ�����ʦ��ȥ��\n", ob, me);
                    return 1;
                }
        }

        message_vision("\n$N��$n����һ��ͷ������ʦ������... ��������ʦ�š�\n", me, ob);
        if( intp(query("family/beggarlvl", me)) && 
            query("family/beggarlvl", me)>0 )
                lvl=query("family/beggarlvl", me);
        set_temp("pending/detach", 1, me);
        tell_object(ob, me->name() + "������ʦ�š�\n");
        ob->attempt_detach(me);
        if (lvl) set("gaibang/beggarlvl", lvl, me); 
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : detach|tuoli <����>
 
���ָ�������������ʦ����������ʦ�ţ���Ϊһ��Ĵ����ɲ�Ը���
����ʦ���ˣ�������������Ͷ�������ɣ���ð��չ������ʦ�ţ�Ȼ
��һ������ʦ�ţ�ʦ����׷��������ѧ���ı�����ѧ����׷�ز�������
�书��֪ʶ�����ܵ��κ�Ӱ�졣

��ο����ָ�� expell
HELP );
        return 1;
}
