// special

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string  msg;
        mapping ss;
        string  skill;
        object ob;
        string pro;
        int i;
        string tmp_msg;

        if (wizardp(me) && stringp(arg) &&
            objectp(ob = find_player(arg)))
                // �鿴������ҵ����⼼��
                arg = 0;
        else
                ob = me;

        pro = (ob == me) ? "��" : ob->name(1);

        if( !query("born", ob) )
                return notify_fail(pro + "��û�г����ţ���ʲô�ؼ���\n");

        if( !mapp(ss=query("special_skill", ob)) || 
            ! sizeof(ss))
                return notify_fail(pro + "���ں���ʲô�ؼ�������Ŷ��\n");

        if (arg && (ob == me))
        {
                // �в����������ؼ���
                if (me->is_busy())
                        return notify_fail("������æ���أ�����ʹ���ؼ���\n");

                if (sscanf(arg, "%s %s", skill, arg) != 2)
                        skill = arg;

                if( !query("special_skill/"+skill, me) )
                        return notify_fail("�㲻�������ؼ�����\n");

                if (file_size(SPECIAL_D(skill) + ".c") < 0 
                    && file_size("/kungfu/special2/" + skill + ".c") < 0)
                        return notify_fail("����û�������ؼ�...\n");

                if (file_size("/kungfu/special2/" + skill + ".c") != -1)
                          return ("/kungfu/special2/" + skill)->perform(me, skill, arg);

                return SPECIAL_D(skill)->perform(me, skill, arg);
        }

        msg = pro + "���ڻ�������Щ�ؼ���\n";
        i = 1;
        foreach (skill in keys(ss))
        {
                if (file_size(SPECIAL_D(skill) + ".c") < 0
                    && file_size("/kungfu/special2/" + skill + ".c") < 0)
                {
                        write("�����ڼ��ܣ�" + skill + "\n");
                        continue;
                }
                // �������7����ÿ����ʾ�ĸ�                                
                if (file_size("/kungfu/special2/" + skill + ".c") != -1)
                {
                        if( sizeof(query("special_skill", ob)) >= 7 )
                        {
                                tmp_msg = ("/kungfu/special2/" + skill)->name() +  "(" YEL + skill + NOR ")";
                                msg += sprintf("%-28s", tmp_msg);
                                if (i % 4 == 0 && i > 1)msg += "\n";
                        }
                        else
                        {
                                msg += ("/kungfu/special2/" + skill)->name() +  "(" YEL + skill + NOR ")\n";
                        }
                }

                else
                {
                        if( sizeof(query("special_skill", ob)) >= 7 )
                        {
                                tmp_msg = SPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")";
                                msg += sprintf("%-28s", tmp_msg);
                                if (i % 4 == 0 && i > 1)msg += "\n";
                        }
                        else
                        {
                                msg += SPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")\n";
                        }
                }
                
                i += 1;
                
        }
        write(msg + "\n");
        return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : special <skill> | <���ID>

ʹ������������Բ鿴����ؼ������Ҫ��������ؼ�������Լ���
����ָ��ʹ��ʲô�ؼ������磺special hatred������ɱ����

��ʦ���Բ鿴���������������⼼�ܡ�

HELP );
    return 1;
}
