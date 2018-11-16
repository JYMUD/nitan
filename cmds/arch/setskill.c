// setskill.c
// Smallfish@Huaxia

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int i,j,level;
        mapping skill_status;
        object ob;
        string skill,obj;
        string *skills;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if( !arg )
                return notify_fail("setskill <ĳ��> <����>/all <������>��\n");

        if( !arg || sscanf(arg, "%s %s %d", obj, skill, level)!=3 )
                return notify_fail("setskill <ĳ��> <����>/all <������>��\n");

        ob = find_player(obj);

        if( !ob )
                ob = find_living(obj);
        if( !ob )
                ob = present(obj, environment(me));
        if( !ob )
                return notify_fail("�Ҳ����������.\n");

        if( (wiz_level(me) < wiz_level(ob)) && userp(ob) )
                return notify_fail("��û������" + ob->name() + "���ܵ�Ȩ����\n");

/*
        if( level == 0 && wizardp(ob) )
                return notify_fail("�����ô������ʦ�Ĺ���ɾ����\n");
*/

        if (! me->is_admin())
        {
                switch (SECURITY_D->query_site_privilege("call"))
                {
                case "all":
                        break;

                case "self":
                        if (ob != me)
                                return notify_fail("��ֻ��ʹ�ø������������ĺ�����\n");
                        break;

                case "npc":
                        if (playerp(ob) || ! ob->is_character())
                                return notify_fail("��ֻ�ܺ��� NPC �ĺ�����\n");
                        break;

                case "user":
                        if (! playerp(ob))
                                return notify_fail("��ֻ�ܶ����ʹ��������\n");
                        break;

                case "nonechar":
                        if (ob->is_character())
                                return notify_fail("��ֻ�ܶԷǽ�ɫ����ʹ��������\n");
                        break;

                case "wizard":
                        if (! wizardp(ob))
                                return notify_fail("��ֻ�ܶ���ʦʹ��������\n");
                        break;

                default:
                        return notify_fail("�㲻��ʹ�ø����\n");
                }
        }

        write(WHT"begin setting skills for "NOR + ob->short(1) + WHT"��\n"NOR);
        if( skill == "all" ) {
                if ( !(skill_status = ob->query_skills()) || !sizeof(skill_status) )
                        return notify_fail("�����û��ѧ���κμ��ܣ������� all ���������\n");
                skills  = keys(skill_status);
                j = sizeof(skill_status);
                for(i=0; i<j; i++) {
                        if( level ==0 ) {
                                ob->delete_skill(skills[i]);
                                write("deleting->" + to_chinese(skills[i]) + 
                                        "(" + skills[i] + ")\n");
                        }
                        else {
                                ob->set_skill(skills[i], level);
                                printf("setting-> %-36s%d\n", to_chinese(skills[i]) + 
                                        "(" + skills[i] + ")", level);
                        }
                }
        }
        else {
                if( level ==0 ) {
                        ob->delete_skill(skill);
                        write("deleting->" + to_chinese(skill) + "(" + skill + ")\n");
                }
                else    {
                        ob->set_skill(skill, level);
                        printf("setting-> %-36s%d\n", to_chinese(skill) + 
                                "(" + skill + ")", level);
                }
        }
        if( userp(ob) && ob!=me ) log_file("static/setskill",
                sprintf("%s(%s) setskill %s(%s) %s to level %d at %s.\n", me->name(),
                        query("id", me),ob->name(),query("id", ob),skill,level,
                        ctime(time()) ) );
        write(WHT"Done.\n"NOR);
        return 1;
}

int help()
{
        write(@LONG
ָ���ʽ��setskill  <ĳ��> <����>/all <������>��

�����趨ĳ�˵�ĳ�ּ��ܵļ�����, ����ڶ����� all �������е�
���ܸ�Ϊ�趨�ļ����������ѡ���˼�����Ϊ 0 ��ɾ�����˴���ܡ�

���棺�����ô����
LONG    );
        return 1;
}
