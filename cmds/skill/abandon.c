// abandon.c

#include <ansi.h>

inherit F_CLEAN_UP;

int help();
int main(object me, string arg)
{
        mapping smap, pmap;
        int skill_lvl, lvl, i;
        int jingcost;
        string skill;
        string name;
        int level;
        int lost;

        if (! arg || arg == "")
                return help();

        if (sscanf(arg, "%s to %d", skill, lvl) != 2)
                return help();

        if (me->is_fighting())
                return notify_fail("����æ�Ŵ���أ�����ʱ���������£�\n");

        if (me->is_busy())
                return notify_fail("����æ��û������������\n");

        jingcost=query("int", me)+random(query("int", me));
        if( jingcost>query("jing", me) )
                return notify_fail("���޷����о�����\n");

        if (skill == "exp")
        {
                lost=query("combat_exp", me);
                if (lost < 100)
                        return notify_fail("�㷢���Լ����ڶ���ѧ��ֱ����һ����֪��\n");

                if (lvl > lost || lvl < 0)
                        return notify_fail("�㷢���Լ����ڶ���ѧ��⻹û����ô�ߡ�\n");

                if (lvl == lost)
                        return notify_fail("���ǲ���ͷ�Խ�ˮ�ˣ����ڻ��÷�����\n");

                level = sqrt3(lvl/100) * 10 + 1;
                while ((level + 1)*(level + 1)*(level + 1) <= lvl*10 )
                        level++;

                tell_object(me, HIR "�㽫����EXP�� " + lvl + " �㣬����֧�� " +
                                chinese_number(level) + " ����ѧ���ܡ�\n\n" NOR);

                tell_object(me, "����ؿ��������ȷ���Ļ����������Ĺ����������ͨ���룺");
                input_to("check_password", 1, me, skill, lvl);
                return 1;

                message("vision", me->name() + "����������˼��ʲô��\n",
                        environment(me), me);
                tell_object(me, "�㲻����ȭ�ű����Ṧ�ڹ���ֻ��һ����˼�����书��\n");
                me->start_busy(3 + random(5));
                if( random(query("int", me))>15 )
                {
                        tell_object(me, "�����㷢���Լ��ƺ�����̫�ã�û�а��Ч����\n");
                        return 1;
                }

                // lost = random(lost / 100) + 1;
                // addn("combat_exp", -lost, me);
                set("combat_exp", lvl, me);
                switch (random(6))
                {
                case 0:
                        tell_object(me, HIR "���������˺ܶ���ܰ"
                                    "�����£����ɵó������С�\n" NOR);
                        break;
                case 1:
                        tell_object(me, HIR "���ƺ��ֿ�����ңԶ"
                                    "��ͯ�꣬һʱ��ȴ�˳�����ķ��ա�\n" NOR);
                        break;
                case 2:
                        tell_object(me, HIR "����Ȼһ����̾��ֻ��"
                                    "���Լ�Ϊ����ѧ�ķ�һ����ʵ����ν��\n" NOR);
                        break;
                case 3:
                        tell_object(me, HIR "������ֹˮ�����е�"
                                    "�书���·����Լ�Զȥ�ˡ�\n" NOR);
                        break;
                case 4:
                        tell_object(me, HIR "��̧ͷ������գ���"
                                    "��������͸����˵�����Ľ��ģ��������ľ㻯��\n" NOR);
                        break;
                default:
                        tell_object(me, HIR "���Ժ��лι�������"
                                    "���̿����������ӣ����ɵð��Կ�Ц��\n" NOR);
                        break;
                }

                // UPDATE_D->check_user(me);
                return 1;
        }

        smap = me->query_skill_map();
        pmap = me->query_skill_prepare();

        name = to_chinese(skill);
        if (name[0] < 160) name = "�����";
        skill_lvl = (int)me->query_skill(skill, 1);

        if (! skill_lvl)
        {
                me->delete_skill(skill);
                write("���ˡ�\n");
                return 1;
        }

        if (lvl > skill_lvl || lvl < 0)
                return notify_fail("�㷢���Լ����ڶԸ����书��⻹û����ô�ߡ�\n");

        if (lvl == skill_lvl)
                return notify_fail("���ǲ���ͷ�Խ�ˮ�ˣ����ڻ��÷�����\n");

        tell_object(me, HIR "�㽫�������� " + name + " �� " + chinese_number(lvl) + " ����\n\n" NOR);

        tell_object(me, "����ؿ��������ȷ���Ļ����������Ĺ����������ͨ���룺");
        input_to("check_password", 1, me, skill, lvl, name, smap, pmap);
        return 1;

        me->start_busy(1+random(query("int", me)/7));
        if( random(query("int", me))>24 )
                return notify_fail("�㼯�о���������" + name + "��������ֺ��޽����\n");

        // skill_lvl = random(skill_lvl);
        if (lvl < 1)
        {
                for (i = sizeof(smap)-1; i >= 0; i --)
                        if ((string)smap[keys(smap)[i]] == skill)
                                me->map_skill(keys(smap)[i]);

                for (i = sizeof(pmap)-1; i >= 0; i -- )
                        if ((string) values(pmap)[i] == skill)
                                me->prepare_skill(keys(pmap)[i]);

                SKILLS_D->remove_id_from_abandon(me, skill);
                me->delete_skill(skill);
                me->reset_action();
                write("�㼯�о���������" + name + "��������ڽ������������ˡ�\n");
        } else
        {
                me->set_skill(skill, lvl);
                write("�㼯�о���������" + name + "���������Ч����\n");
        }
        return 1;
}

varargs void check_password(string passwd, object me, string skill, int lvl, string name, mapping smap, mapping pmap)
{
        int i;
        object link_ob;
        string old_pass;

        link_ob=query_temp("link_ob", me);
        old_pass=query("ad_password", link_ob);
        if (! stringp(old_pass) || crypt(passwd, old_pass) != old_pass)
        {
                old_pass=query("password", link_ob);
                if (! stringp(old_pass) || crypt(passwd, old_pass) != old_pass)
                {
                        write(HIR "���������ע�⣬������ѧ������������������ͨ���롣\n");
                        return;
                }
        }

        if (skill == "exp")
        {
                message("vision", me->name() + "����������˼��ʲô��\n",
                        environment(me), me);
                tell_object(me, "�㲻����ȭ�ű����Ṧ�ڹ���ֻ��һ����˼�����书��\n");
                me->start_busy(3 + random(5));
                /*
                if( random(query("int", me))>15 )
                {
                        tell_object(me, "�����㷢���Լ��ƺ�����̫�ã�û�а��Ч����\n");
                        return;
                }
                */

                set("combat_exp", lvl, me);
                switch (random(6))
                {
                case 0:
                        tell_object(me, HIR "���������˺ܶ���ܰ"
                                    "�����£����ɵó������С�\n" NOR);
                        break;
                case 1:
                        tell_object(me, HIR "���ƺ��ֿ�����ңԶ"
                                    "��ͯ�꣬һʱ��ȴ�˳�����ķ��ա�\n" NOR);
                        break;
                case 2:
                        tell_object(me, HIR "����Ȼһ����̾��ֻ��"
                                    "���Լ�Ϊ����ѧ�ķ�һ����ʵ����ν��\n" NOR);
                        break;
                case 3:
                        tell_object(me, HIR "������ֹˮ�����е�"
                                    "�书���·����Լ�Զȥ�ˡ�\n" NOR);
                        break;
                case 4:
                        tell_object(me, HIR "��̧ͷ������գ���"
                                    "��������͸����˵�����Ľ��ģ��������ľ㻯��\n" NOR);
                        break;
                default:
                        tell_object(me, HIR "���Ժ��лι�������"
                                    "���̿����������ӣ����ɵð��Կ�Ц��\n" NOR);
                        break;
                }

                UPDATE_D->check_user(me);
                return;
        }

        me->start_busy(1+random(query("int", me)/7));
        /*
        if( random(query("int", me))>24 )
        {
                tell_object(me, "�㼯�о���������" + name + "��������ֺ��޽����\n");
                return;
        }
        */

        if (lvl < 1)
        {
                for (i = sizeof(smap)-1; i >= 0; i --)
                        if ((string)smap[keys(smap)[i]] == skill)
                                me->map_skill(keys(smap)[i]);

                for (i = sizeof(pmap)-1; i >= 0; i -- )
                        if ((string) values(pmap)[i] == skill)
                                me->prepare_skill(keys(pmap)[i]);

                SKILLS_D->remove_id_from_abandon(me, skill);
                me->delete_skill(skill);
                me->reset_action();
                write("�㼯�о���������" + name + "��������ڽ������������ˡ�\n");
        } else
        {
                int add;

                add=query_temp("apply/add_skill", me);
                lvl -= add;
                if (lvl < 1)
                {
                        tell_object(me, "����������ȫ������" + name + "������ָ������Ϊ�㡣\n");
                        return;
                }
                me->set_skill(skill, lvl);
                write("�㼯�о���������" + name + "���������Ч����\n");
        }
        return;
}

int help()
{
        write(@TEXT
ָ���ʽ��abandon|fangqi <��������> | exp to <��ֵ>

�������ʵս�������ĳһ������ѧ���ļ��ܵ�ָ������ֵ���ɹ���
������츳�йأ�ֻ���ܹ���Ϣ�ĵط����ܹ��������������书��

��ʱ����Ϊ�书��˻����㲻�ٴ�����ĳ��������¹��򣬾Ϳ���
ʹ������ָ���������
TEXT );
        return 1;
}
