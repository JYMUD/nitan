// vote command..
// Modified by Marz, 04/18/96

#include <net/dns.h>
#include <ansi.h>

inherit F_CLEAN_UP;

int valid_voters(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object victim;
        string act_name, victim_name;
        string file;
        object file_ob;

        if( (query("age", me)<18) && !wizardp(me) )
                return notify_fail("�������Ƕ�Ϸ��С����һ����ȥ��\n");

        if( query("vote/deprived", me) )
        {
                // �Ƿ񱻰���ͶƱȨ����û�лָ��أ�
                if( time()-query("vote/deprived", me) >= 86400 )
                        delete("vote/deprived", me);
                else
                        return notify_fail("�����𵱳���Ū������������ͶƱȨ���£�׷��Ī����\n");
        }

            if (! arg || sscanf(arg, "%s %s", act_name, victim_name) != 2)
                return notify_fail("����ʥ��һƱ��Ҫ������˲���Ͷ��\n");
    
        victim = find_player(victim_name);
        if (! objectp(victim))
        {
                string temp;
                temp = victim_name;
                victim_name = act_name;
                act_name = temp;
                victim = find_player(victim_name);
        }

        if (! victim) return notify_fail("��ҪͶ˭��Ʊ��\n");
        if (wizardp(victim)) return notify_fail("��ҪͶ��ʦ��Ʊ��\n");
                
        if (! stringp(file = (string)"/cmds/std/vote/" + act_name) ||
            file_size(file + ".c") <= 0)
                return notify_fail("��ҪͶƱ��ʲô��\n");

        call_other(file, "???");
        file_ob = find_object(file);

        if ((int)file_ob->vote(me, victim) <= 0)
        {
                if( query("vote/abuse", me)>50 )
                {
                        write(HIG "����Ϊ����ͶƱ��ͶƱȨ����ʱ����24Сʱ��\n" NOR);
                        set("vote/deprived", time(), me);
                        delete("vote/abuse", me);
                }
                return 0;
        }

        log_file("static/vote", sprintf("%s %s vote: %s %s\n",
                                        log_time(), log_id(me),
                                        act_name, victim_name));

        return 1;
}

int valid_voters(object me)
{
        object *list;
        int d = 0;
        int j;

            list = users();
            j = sizeof(list);
            while (j--)
        {
                // Skip those users in login limbo.
                if (! environment(list[j])) continue;
                if (! me->visible(list[j])) continue;
                if( (query("age", list[j])<18) && !wizardp(list[j]))continue;
                if( query("vote/deprived", list[j]))continue;

                d++;
        }
        
        return d;
}


int help(object me)
{
        write(@HELP
ָ���ʽ : vote <����> <ĳ��> 

�����������ĳ�˲�ȡ�ж����ɴ��ͶƱ��������������������û���˸��飬
ͶƱ���Զ�ȡ������ǰ����������<����>��

chblk:   �ر�ĳ��Ƶ��������Ʊ���ϣ�ʮ����ͬ����Ǽ򵥶���ͬ�⣬���
                       ����������14�꣬��ôֻ��Ҫ����ͬ�⼴�ɡ�
unchblk: ��ĳ��Ƶ��������Ʊ���ϣ�ʮ�����ͬ����Ǽ򵥶���ͬ�⡣

ע�⣺ͶƱ����ʹ���κβ�ͬ IP ����ĺϷ� ID�� �����������ͶƱ����ɧ
��������ң��򽫵��¼������ PURGE �������ͽ䣬���Ҵ˳ͽ佫������ ID
������������С��ʹ��ͶƱȨ�������κ�û��Υ����Ϸ�������ң�����
ʹ��ͶƱ��������Ϊ����ͶƱȨ��

HELP );
        return 1;
}