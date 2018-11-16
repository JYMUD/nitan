// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ITEM;

string *valid_types = ({
        "sword",
        "blade",
        "staff",
        "hammer",
        "club",
        "whip",
        "throwing",
});

int do_washto(string arg);

void create()
{
        set_name(HIR "ϴ�츳��" NOR, ({"wash gift", "gift"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", @LONG
�����ṩ����Щ����ʱ��ѡ���츳����һ�����·��������츳��ϴ�츳����
ϴ�츳��ÿ��ֻ��ʹ��һ�Σ���ʽΪ washto <����> <����> <����> <��>
���磺washto 20 20 20 20 ��ϴ�츳ʱ��Ҫ��������м�������Լ���ȫ��
�м�����ĵ���ʹ����mygift������ĵ����졣
LONG );
                set("value", 1);
                set("no_sell", 1);
        }
        setup();
}

void init()
{
        object me = this_player();

        if (me == environment())
                add_action("do_washto", "washto");
}


int do_washto(string arg)
{
        int i, j, points;
        int tmpstr, tmpint, tmpcon, tmpdex;
        int str, wux, con, dex;
        object me, weapon;
        mapping my;
        array sname;
        mixed skill_status;

        me = this_player();

        if (! arg || sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon, tmpdex) != 4)
                return notify_fail("ָ���ʽ��washto <����> <����> <����> <��>\n" +
                                   "��    �磺washto 20 20 20 20\n");

        /*
        if( query("age", me) > 20 )
                return notify_fail("���Ѿ����������ڣ���ת��ǰ����ӵ�е����츳�Ļ��ᡣ\n");

        if( query("gift/washed", me) )
                return notify_fail("���Ѿ�ʹ�ù�ϴ�츳���ˣ�ÿ��ֻ��һ�λ��ᡣ\n");

        if (query("reborn/times", me))
                return notify_fail("ϴ�츳��ֻ��û��ת�������ʹ�ã��������Ѿ������Ե�ˡ�\n");
        */

        //if (tmpstr > 43 || tmpstr < 21)
        if (tmpstr > 100 || tmpstr < 13)
                return notify_fail("����ѡ���������ֵҪ�������21��43֮�䡣\n");

        //if (tmpint > 43 || tmpint < 21)
        if (tmpint > 100 || tmpint < 13)
                return notify_fail("����ѡ���������ֵҪ�������21��43֮�䡣\n");

        //if (tmpcon > 46 || tmpcon < 24)
        if (tmpcon > 100 || tmpcon < 13)
                return notify_fail("����ѡ��ĸ�����ֵҪ�������24��46֮�䡣\n");

        //if (tmpdex > 43 || tmpdex < 21)
        if (tmpdex > 100 || tmpdex < 13)
                return notify_fail("����ѡ�������ֵҪ�������21��43֮�䡣\n");

        my = me->query_entire_dbase();
        str = copy(my["str"]);
        wux = copy(my["int"]);
        con = copy(my["con"]);
        dex = copy(my["dex"]);

        points = str + wux + con + dex;
        if (tmpstr + tmpint + tmpcon + tmpdex != points)
                return notify_fail("��������ѡ����츳��ֵ���Լ��츳��" + points + "��ֵ��һ�¡�\n");
        /*

        write(HIW "��ʼ��������츳����ѧ�����Ƿ�������������...\n" NOR);

        skill_status = me->query_skills();
        if (mapp(skill_status) && sizeof(skill_status))
        {
                int ob;

                if( objectp(ob=query_temp("weapon", me)) )
                        ob->unequip();

                delete_temp("handing", me);

                sname  = keys(skill_status);

                for (i = 0; i < sizeof(sname); i++)
                {
                        if (SKILL_D(sname[i])->type() != "martial")
                                continue;

                        if (sname[i] == "zuoyou-hubo")
                                continue;

                        if (sname[i] == "martial-cognize" || sname[i] == "sword-cognize")
                                continue;

                        if (sname[i] == "count" && tmpint >= 30)
                                continue;

                        for (j = 0; j < sizeof(valid_types); j++)
                        {
                                if (SKILL_D(sname[i])->valid_enable(valid_types[j]))
                                {
                                        switch(valid_types[j])
                                        {
                                        case "sword" :
                                                weapon = new("/clone/weapon/changjian");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "blade" :
                                                weapon = new("/clone/weapon/changjian");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "staff" :
                                                weapon = new("/clone/weapon/zhubang");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "whip" :
                                                weapon = new("/clone/weapon/changbian");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "club" :
                                                weapon = new("/clone/weapon/qimeigun");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "hammer" :
                                                weapon = new("/clone/weapon/hammer");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "throwing" :
                                                weapon = new("/d/tangmen/obj/qinglianzi");
                                                weapon->move(me, 1);
                                                set_temp("handing", weapon, me);
                                                break;
                                        default :
                                                break;
                                        }
                                        break;
                                }
                        }
                        if (! SKILL_D(sname[i])->valid_learn(me))
                        {
                                if (objectp(weapon))
                                        destruct(weapon);

                                return notify_fail(HIR "������ yanjiu " + sname[i] + " 1��ȷ�Ͽ����о�����ϴ���츳��\n" NOR);
                        }

                        if (objectp(weapon))
                                destruct(weapon);
                }
        }
        */

        write("�����·�����츳Ϊ\n"
              "����[" + tmpstr + "]\n"
              "����[" + tmpint + "]\n"
              "����[" + tmpcon + "]\n"
              "��[" + tmpdex + "]��\n");

        my["str"] = tmpstr;
        my["int"] = tmpint;
        my["con"] = tmpcon;
        my["dex"] = tmpdex;
        
        /*
        write(HIW "��ʼ������츳����ѧ�����Ƿ�����ѧϰ����...\n" NOR);
        
        if (mapp(skill_status) && sizeof(skill_status))
        {
                int ob;

                if( objectp(ob=query_temp("weapon", me)) )
                        ob->unequip();

                delete_temp("handing", me);

                sname  = keys(skill_status);

                for (i = 0; i < sizeof(sname); i++)
                {
                        if (SKILL_D(sname[i])->type() != "martial")
                                continue;

                        if (sname[i] == "zuoyou-hubo")
                                continue;

                        if (sname[i] == "martial-cognize" || sname[i] == "sword-cognize")
                                continue;

                        if (sname[i] == "count" && tmpint >= 30)
                                continue;

                        for (j = 0; j < sizeof(valid_types); j++)
                        {
                                if (SKILL_D(sname[i])->valid_enable(valid_types[j]))
                                {
                                        switch(valid_types[j])
                                        {
                                        case "sword" :
                                                weapon = new("/clone/weapon/changjian");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "blade" :
                                                weapon = new("/clone/weapon/changjian");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "staff" :
                                                weapon = new("/clone/weapon/zhubang");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "whip" :
                                                weapon = new("/clone/weapon/changbian");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "club" :
                                                weapon = new("/clone/weapon/qimeigun");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "hammer" :
                                                weapon = new("/clone/weapon/hammer");
                                                weapon->move(me, 1);
                                                weapon->wield();
                                                break;
                                        case "throwing" :
                                                weapon = new("/d/tangmen/obj/qinglianzi");
                                                weapon->move(me, 1);
                                                set_temp("handing", weapon, me);
                                                break;
                                        default :
                                                break;
                                        }
                                        break;
                                }
                        }
                        if (! SKILL_D(sname[i])->valid_learn(me))
                        {
                                if (objectp(weapon))
                                        destruct(weapon);
                                        
                                my["str"] = str;
                                my["int"] = wux;
                                my["con"] = con;
                                my["dex"] = dex;
                                return notify_fail(HIR "���츳��������" + to_chinese(sname[i]) + "ѧϰ�������޸�ʧ�ܡ�\n" NOR);
                        }

                        if (objectp(weapon))
                                destruct(weapon);
                }
        }
        */
        addn("gift/washed", 1, me);

        write("�����·�������츳�ɹ���������ָ��(hp -g)�鿴��\n");
        destruct(this_object());
        return 1;
}
