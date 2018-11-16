//recruit.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob, old_rec;
        mapping family;
        int i;
        string temp;
        int student_num;

        if (! arg) return notify_fail("ָ���ʽ��recruit|shou [cancel]|<����>\n");

        if (arg == "cancel")
        {
                old_rec=query_temp("pending/recruit", me);
                if (! objectp(old_rec))
                        return notify_fail("�����ڲ�û����¼�κ���Ϊ���ӵ���˼��\n");

                write("��ı����ⲻ����" + old_rec->name() + "Ϊ�����ˡ�\n");
                tell_object(old_rec, me->name() + "�ı����ⲻ������Ϊ�����ˡ�\n");
                delete_temp("pending/recruit", me);
                return 1;
        }

        if (! (ob = present(arg, environment(me))))
                return notify_fail("������˭�����ӣ�\n");

        if (ob == me) return notify_fail("���Լ�Ϊ���ӣ�������....����û���á�\n");

        if (ob->is_apprentice_of(me))
        {
                message_vision("$N����$n��ͷ��˵��������ͽ������\n", me, ob);
                return 1;
        }

        if( !query("family", me) )
                return notify_fail("�㲢�������κ����ɣ�������ȼ���һ��"
                                   "���ɣ����Լ���һ\n��������ͽ��\n");

        // If the target is willing to apprentice us already, we do it.
        if ((object)query_temp("pending/apprentice", ob) == me)
        {
                if (! living(ob))
                {
                        message_vision("$N������$nΪ���ӡ�\n\n"
                                       "����������$n��Ȼû�а취�а�ʦ֮��\n\n", me, ob);
                        return 1;
                }

                if( mapp(query("family", ob)) && 
                    stringp(query("family/family_name", ob)) && 
                    query("family/family_name", me) != 
                    query("family/family_name", ob) )
                {
                        message_vision("$n������ʦͶ��$N���£���\n\n"
                                       "$n����������$N���������ؿ����ĸ���ͷ��"
                                       "�е�����ʦ������\n\n", me, ob);
                        addn("betrayer/times", 1, ob);
                        if( query("family/family_name", ob) )
                            addn("betrayer/"+query("family/family_name", ob), 1, ob);
                } else
                        message_vision("$N������$nΪ���ӡ�\n\n"
                                       "$n����������$N���������ؿ����ĸ���ͷ��"
                                       "�е�����ʦ������\n", me, ob);
        
                me->recruit_apprentice(ob);
                delete_temp("pending/apprentice", ob);
        
                MYGIFT_D->check_mygift(ob, "newbie_mygift/baishi");   
                write("��ϲ��������һ�����ӣ�\n");
                family=query("family", ob);
                tell_object(ob, sprintf("��ϲ����Ϊ%s�ĵ�%s�����ӡ�\n",
                            family["family_name"],
                            chinese_number(family["generation"]) ));
                return 1;
        } else
        {
                old_rec=query_temp("pending/recruit", me);
                if (ob == old_rec)
                        return notify_fail("������" + ob->name() + "Ϊ���ӣ����ǶԷ���û�д�Ӧ��\n");
                else
                if (objectp(old_rec))
                {
                        write("��ı����ⲻ����" + old_rec->name() + "Ϊ�����ˡ�\n");
                        tell_object(old_rec, me->name() + "�ı����ⲻ������Ϊ�����ˡ�\n");
                }
                set_temp("pending/recruit", ob, me);
                message_vision("\n$N��Ҫ��$nΪ���ӡ�\n", me, ob);
                tell_object(ob, YEL "�����Ը���" + me->name() + "Ϊʦ����"
                                "�� apprentice ָ�\n" NOR);
                return 1;
        }
}


int help(object me)
{
        write(@HELP
ָ���ʽ : recruit|shou [cancel]|<����>

���ָ����������ĳ��Ϊ����, ����Է�Ҳ��ӦҪ����Ϊʦ�Ļ�.

See Also:       apprentice
HELP );
        return 1;
}
