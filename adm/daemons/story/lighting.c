// story:lighting ���

#include <ansi.h>

mixed random_gift();

nosave mixed *story = ({
        "��ĸ����...����ɶ��",
        "�׹�����ô���㣿",
        "��ĸ��ĿԲ�������д�����˵���㱳���ﶼ�����Ҹ�Щʲô��",
        "�׹�����̬��",
        "��ĸ����...",
        "...",
        "��...",
        "����...",
        "���ƣ�������������������������������",
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
        object ob;
        string msg;

        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 environment($1) &&
                                                 query("outdoors", environment($1)) &&
                                                 !query("env/no_story", $1) &&
                                                 !query("doing", $1):));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        
        if( query("gift/lighting", ob) || random(5) )
        {
                msg = HIR + ob->name(1) + "һ���ҽУ�����ĵ�����ȥ��" NOR;
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
                msg = HIC "���Ǽ�" + ob->name(1) + "��������䣬��������һ�㣬�������ݡ�" NOR;
                addn("con", 1, ob);
                addn("gift/lighting", 1, ob);
        }
        return msg;
}
