// apprentice.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob, old_app;
        mapping family, ob_family, skills;
        int i;
        string *skname;

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if (! arg)
                return notify_fail("ָ���ʽ��apprentice | bai [cancel]|<����>\n");

        if (query("reborn_offer", me))
                return notify_fail("ת���������޷���ʦ��\n");

        if (arg == "cancel")
        {
                old_app=query_temp("pending/apprentice", me);
                if( !objectp(old_app) )
                        return notify_fail("�����ڲ�û�а��κ���Ϊʦ����˼��\n");
                write("��ı����ⲻ���" + old_app->name() + "Ϊʦ�ˡ�\n");
                tell_object(old_app, me->name() + "�ı����ⲻ�����Ϊʦ�ˡ�\n");
                delete_temp("pending/apprentice", me);
                return 1;
        }

        if (! (ob = present(arg, environment(me))) ||
            ! ob->is_character())
                return notify_fail("�����˭Ϊʦ��\n");

        if (! living(ob))
                return notify_fail("������Ȱ�" + ob->name() + "Ū�ѡ�\n");

        if (ob == me)
                return notify_fail("���Լ�Ϊʦ��������....����û���á�\n");

        if (ob->is_baby())
                return notify_fail("�ݺ���Ϊʦ��������....����û���á�\n");

        if (me->is_apprentice_of(ob))
        {
                message_vision("$N������������$n��ͷ�밲���е�����ʦ������\n", me, ob);
                return 1;
        }

        if( !mapp(ob_family=query("family", ob)) )
                return notify_fail(ob->name() + "�Ȳ�����κ�"
                                   "���ɣ�Ҳû�п�ɽ���ɣ����ܰ�ʦ��\n");

        if (playerp(ob))
                return notify_fail("... ���ڲ��ܰ����Ϊʦ :)\n");

        family=query("family", me);
        if (mapp(family) && stringp(family["master_name"]) &&
            ob_family["family_name"] == family["family_name"] &&
            ob_family["generation"] >= family["generation"])
                return notify_fail(ob->name() + "����һ����æ��������ɲ��ҵ������ҵ�����\n");

        // betrayer ?
        if (mapp(family) && stringp(family["family_name"]) &&
            family["family_name"] != ob_family["family_name"] &&
            query_temp("pending/betrayer", me) != ob )
        {
                if( query("reborn_offer", me) )
                        return notify_fail("ת�������в�������ʦ��\n");
                write(HIR "���Ǵ�����ʦ���ܿ����⵽�����ͷ���Ŷ��\n" NOR
                      "��������˾��ģ���������һ���������\n");
                set_temp("pending/betrayer", ob, me);
                return 1;
        }

        // If the target is willing to recruit us already, we do it.
        if ((object)query_temp("pending/recruit", ob) == me)
        {
                if (mapp(family) && stringp(family["family_name"]) &&
                    family["family_name"] != ob_family["family_name"])
                {
                        message_vision(
                                "$N��������ʦ�ţ���Ͷ��$n���£���\n\n"
                                "$N����������$n���������ؿ����ĸ���ͷ���е�����ʦ������\n\n",
                                me, ob);
                        set("weiwang", 0, me);
                        addn("betrayer/times", 1, me);
                        delete("quest", me);
                        delete_temp("quest", me);
                        if (stringp(family["family_name"]))
                                addn("betrayer/"+family["family_name"], 1, me);
                } else
                        message_vision(
                                "$N������$nΪʦ��\n\n"
                                "$N����������$n���������ؿ����ĸ���ͷ���е�����ʦ������\n\n",
                                me, ob);
                ob->recruit_apprentice(me);
                delete_temp("pending/recruit", ob);

                tell_object(ob, "��ϲ��������һ�����ӣ�\n");
                printf("��ϲ����Ϊ%s�ĵ�%s�����ӡ�\n",
                        query("family/family_name", me),
                        chinese_number(query("family/generation", me)));
                return 1;

        } else
        {
                old_app=query_temp("pending/apprentice", me);
                if (ob == old_app)
                        return notify_fail("�����" + ob->name() +
                                           "Ϊʦ�����ǶԷ���û�д�Ӧ��\n");
                else
                if (objectp(old_app))
                {
                        write("��ı����ⲻ���" + old_app->name() + "Ϊʦ�ˡ�\n");
                        tell_object(old_app, me->name() + "�ı����ⲻ�����Ϊʦ�ˡ�\n");
                }

                message_vision("$N��Ҫ��$nΪʦ��\n", me, ob);
                set_temp("pending/apprentice", ob, me);
                if (userp(ob))
                {
                        tell_object(ob, YEL "�����Ը����" + me->name() +
                                    "Ϊ���ӣ��� recruit ָ�\n" NOR);
                } else
                        ob->attempt_apprentice(me);
                return 1;
        }
}


int help(object me)
{
        write(@HELP
ָ���ʽ : apprentice|bai [cancel]|<����>

���ָ���������ĳ��Ϊʦ������Է�Ҳ��ӦҪ����Ϊͽ�Ļ����ͻ�
�����а�ʦ֮�� ����Ҫ�ȵ��Է��� recruit ָ������Ϊ���Ӳ���
��ʽ��ʦ��

��ע�����Ѿ�����ʦ�����ֱ���ʦ��Ͷ��������£�����п��ܵ���
ԭ�����ɵ��˵�׷ɱ��һ��ʧ�֣������е������书���������˷ϵ���
�����书���롣

��������ʦ��ʹ�����ָ�������ʦ���밲��

��ͬ�ŵ�ʦ�����ܰݱ��Լ����ֵ͵Ļ��Ǻ��Լ�������ͬ���ˡ�

��ο����ָ�� expell��recruit
HELP );
        return 1;
}
