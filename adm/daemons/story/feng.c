// story:feng ����

#include <ansi.h>

mixed random_gift();

inherit F_CLEAN_UP;

nosave mixed *story = ({
        "·�ˣ���λ��磬�⸽�������ʲô��ֵ����鷢����",
        "�Է���˵������ߵĺ��Ͼ��������һֻ��ˡ�",
        "·�ˣ�ԭ����������....",
        "�Է򣺰������Ǹ��������ġ�",
        "·�ˣ���˵�ϻ����忴���˷�����裬��������ǣ�����Ѱ���˶��򲻹����ˡ�",
        "......",
        "���ߣ���˿���ˮ�еĵ�Ӱ���������Լ��������У��������衣",
        "��Χ���ŷ�����������硣",
        "����������",
        (: random_gift :),
});

void create()
{
        seteuid(getuid());
}

string prompt() { return HIR "���񻰡�" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

mixed random_gift()
{
        object *obs;
        object ob, pob;
        string msg;
        mapping ips;
        string ip, *ks;

        ips = ([ ]);
        /*
        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 environment($1) &&
                                                 query("outdoors", environment($1)) && 
                                                 !query("env/no_story", $1) && 
                                                 !query("doing", $1):));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        */

        foreach (pob in all_interactive())
        {
                if( wizardp(pob) || !query("born", pob) || 
                    ! living(pob) || ! environment(pob) ||
                    !query("outdoors", environment(pob)) || 
                    pob->is_ghost() ||
                    query("env/no_story", pob) || 
                    query("doing", pob) || 
                    environment(pob)->is_chat_room())
                        continue;

                ip = query_ip_number(pob);
                if (undefinedp(ips[ip])) ips[ip] = ({ pob }); else ips[ip] += ({ pob });
        }

        if (! sizeof(ips))
                return 0;

        // �漴��һ��IP
        ks = keys(ips);
        ip = ks[random(sizeof(ks))];

        // �ڸ�IP��ַ���漴��ȡһ�����
        ob = ips[ip][random(sizeof(ips[ip]))];

        if( query("gift/feng", ob)>4 || random(5) )
        {
                msg = HIR + ob->name(1) + "��һ�������������ˤ���˵��ϡ�" NOR;
                if( query("combat_exp", ob)<1000000 || 
                    query("qi", ob)<1000 )
                        ob->unconcious();
                else
                {
                        set("qi", 10, ob);
                        set("eff_qi", 10, ob);
                        set("jing", 1, ob);
                        set("eff_jing", 1, ob);
                }
        } else
        {
                msg = HIG "��˵" + ob->name(1) +
                      HIG "�����п����˷�����衣" NOR;
                addn("dex", 1, ob);
                addn("gift/feng", 1, ob);
        }
        return msg;
}

