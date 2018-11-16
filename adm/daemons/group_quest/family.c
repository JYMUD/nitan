// group_quest:family Ⱥ�����񡪡���������

#include <ansi.h>
#include "family.h"

void create()
{
        seteuid(getuid());

        if (!select_quest())
        {
                // destruct(this_object());
                return;
        }
}

//string prompt() { return HIR "���������֡�" NOR; }
string prompt() { return HIR "�����ɡ�" NOR; }

int select_quest()
{
        int i;
        object *all_user;
        object ob,the_user;
        string p,*kp;
        mapping fam_map = ([]);

        // ��������������ң�ȡ��ÿ�����ɵ�������������������fam_map  family -> player_number
        foreach (object user in users())
        {
                if (! wizardp(user))
                {
                    p=query("family/family_name", user);
                    if (! stringp(p)) continue;
                    if (undefinedp(fam_map[p]))
                        fam_map[p] = ({ user });
                    else
                        fam_map[p] += ({ user });
                }
        }

        // MUD��û�������κ�һ�����ɵ����
        if (!sizeof(fam_map))
            return 0;

        // ȡ����������ߵ���������
        kp = keys(fam_map);
        kp -= ({ "�Ŵ�", "�����", "������", "��ɽ����" });
        if( !sizeof(kp) ) return 0;

        // �漴��ѡһ������
        p = kp[random(sizeof(kp))];

        // ��������������ߵ�������������������
        all = sizeof(fam_map[p]);
        if (all < 5) all = 5;
        if (all > 20) all = 30 - random(10);

        the_family = p;

        // ����������������ȡ������ҵ�������
        // ������һ�����⣬�������������ߵ����������3����ô�죿
        // ������Ҳû�з�������ʹ�õ���name1, name2, name3�������
        // �����ڰ����Ƿŵ�һ��name��������
        i = 3;
        while (i--)
        {
            if (sizeof(fam_map[p]))
            {
                name[i]=(query("name", fam_map[p][random(sizeof(fam_map[p]))]));
            }
            else
                name[i] = p + "����";
        }

        // ���ù���
        the_nation = "�й�";
        the_enemy = GROUP_QUEST_D->get_enemy(); 

        // ѡȡһ������
        story = all_story[random(sizeof(all_story))];

        return 1;
}

string create_tiaoxin()
{
        object ob;
        int i,lvl;
        string title;

        title = HIY + the_family + NOR + HIW + "���" + NOR + " " + HIY +
                        the_enemy + NOR;

        for (i = 0;i < all;i ++)
        {
                lvl = random(15) + 1;
                ob = GROUP_QUEST_D->create_npc(the_nation,lvl);
                GROUP_QUEST_D->place_npc(ob,"����",the_family,lvl);
                set("title", title, ob);
                ob->random_move();
                ob->random_move();
                ob->random_move();
                ob->random_move();
        }
        GROUP_QUEST_D->set_enemy(all);
        return "��С��޸ߺ�����" + HIY + "��" + the_family + "��" + NOR + WHT + "���˿���ҹ���������ү�ǽ���Ҫ���ǵĺÿ�������";
}

mixed query_quest_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (stringp(msg))
        {
                msg = replace_string(msg,"name1",name[0]);
                msg = replace_string(msg,"name2",name[1]);
                msg = replace_string(msg,"name3",name[2]);
                msg = replace_string(msg,"the_enemy",HIY + the_enemy + NOR + WHT);
                msg = replace_string(msg,"the_family",HIY + "��" + the_family + "��" + NOR + WHT);
        }
        return msg;
}
