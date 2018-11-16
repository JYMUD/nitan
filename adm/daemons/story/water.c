// story:witer ʥ��

#include <ansi.h>

inherit F_CLEAN_UP;

mixed random_gift();

nosave mixed *story = ({
        "�캢�������������²����ˣ���ɮ�������ǻ��ˡ�",
        "������Ŷ����������Ӧ������ׯ�ۣ�����ʲô�£�",
        "�캢����������������ׯ����͵������Ԫ���ɵ��˲ι���",
        "����������������£��������д���",
        "�캢�����������ǻ��Ʒ�����Ԫ���ɵ��˲ι�����",
        "�������Ҳ�Ҫ���������´λ㱨������ʱ���ܷ����Ҫ����������ǰ�棿",
        "�캢����Ŷ��",
        "���������ص��ģ�ֻҪ����ʥˮһ��أ���ľҲ���Իش���",
        "���δ�",
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
        mapping my, ips;
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
        
        if( query("gift/water", ob)>4 || random(5) )
        {
                msg = HIW "ֻ��" + ob->name(1) +
                      HIW "ȫ���â��ҫ��������ȣ��ƺ�û����ʲô���á�" NOR;
 
                my = ob->query_entire_dbase();
                my["jing"]   = my["eff_jing"]   = my["max_jing"];
                my["jingli"] = my["eff_jingli"] = my["max_jingli"];
                my["qi"]     = my["eff_qi"]     = my["max_qi"];
                my["neili"]  = my["max_neili"];
                my["food"]   = ob->max_food_capacity();
                my["water"]  = ob->max_water_capacity();
        } else
        {
                msg = HIC "���Ǽ�" + ob->name(1) +
                      HIC "ȫ����â���֣���̨��⻪��˸�����������" NOR;
                addn("int", 1, ob);
                addn("gift/water", 1, ob);
        }
        return msg;
}
