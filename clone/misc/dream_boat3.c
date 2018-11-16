
#include <ansi.h>
#define MEMBER_D "/adm/daemons/memberd"

inherit ITEM;

int last_update_boss;

string *nature_message = ({
        "Զ�������������������������ҡ���˼��£��漴��ƽ�˾���\n",
        "��մ�����������������ͻ�䣬���ƺ�ѹѹ��һƬ�������Ͽա�\n",
        "�������ȥ��һȺ����β���Ŵ���������Ծ��Ϸ�����沨�����ԣ�����������\n",
        "�������׹������ͻȻ�����������������죬������ҵ�ҡ���š�\n",
        "����������ͻȻ���磬һȺ��Ÿ����߷�����ӳ����Զ���Ĳʺ磬�����˼�������\n",
        "��վ�ڴ�ͷ��һ�󺣷紵�����������棬����˫�ۣ��о�������̩�ޱȡ�\n",
        "��Χ��Ȼ���ޱߵĺ��󣬺����Ĵ��ŷ��������紵���������ĵ������ء�\n",
        });

void start_heart_beat()
{
        // Ĭ��Ϊ����1
        set_heart_beat(1);
}

void create()
{
        set_name(HIW "�ɾ��ŷ���������δ֪�ص㣩" NOR, ({ "penglai boat"}));
        set_weight(2000);
        set_max_encumbrance(10000000);
        if (clonep())
        {
                set_default_object(__FILE__);
        }
        else
        {
                set("value", 1);
                                
                if (query("running"))
                           set("long", HIR "\n����(chuanfu)ߺ�ȵ������ǵĴ�������ʹ�У������ĵȺ�\n" NOR);
                else
                        set("long", HIC "\n����(chuanfu)ߺ�ȵ������ǵĴ����ڵȴ��У���������ڴ�����Ϣ��enter����\n" NOR);

                set("item_desc", ([
                        "chuanfu" : "����һλ����ḻ������æ�ò��ɿ�����\n",
                ]));
                set("no_flyto", 1);
                set("no_rideto", 1);
                set("no_clean_up", 1);

                set("stop_time", time()); // ������ʱ��
                set("waiting_time", 900); // Ĭ�ϵȴ�ʱ��
                set("running_time", 900); // Ĭ����ʹʱ��Ϊʮ�����

                set("source_place", "/d/xiakedao/haibin"); // ������
                set("dest_place", "/d/penglai/haitan"); // Ŀ�ĵ�
                set("dest_place_name", "�����ɵ�");
                set("source_place_name", "�Ϻ�֮��");

                set("unit", "��");
                set("material", "wood");
                set("no_get", "����(chuanfu)�ȵ����üһ����Ҳ�뿸�ڼ��ϣ�\n");

        }
        setup();        
        start_heart_beat();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_out", "out");
}

int do_enter ( string arg )
{
        object ob;
        string dir;
        object *inv;
        object horse, person;
        int i;

        ob = this_player();
        if (arg != this_object()->query("id"))
        {
                tell_object(ob , "��Ҫ enter �Ķ���\n");
                return 1 ;
        }

        if (ob->is_busy())
                return notify_fail("����æ��\n");
                
        // ����������˱�������
        if (objectp(horse = ob->query_temp("is_riding")))
        {
                if (objectp(person = horse->query_temp("is_rided_follow")))
                        person->delete_temp("is_riding_follow");

                horse->delete_temp("is_rided_follow");
                horse->delete_temp("is_rided_by");
                ob->delete_temp("is_riding_follow");
                ob->delete_temp("is_riding"); 
                

                message_vision(HIR "\n$N��" + horse->name() + HIR " �ƺ��޷�Ծ�Ϸ�����ǰ��һ�������"
                               "����������\n\n" NOR, ob);

                return 1;
        }

        // �ѱ�����û�������
        inv = deep_inventory(ob);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! playerp(inv[i])) continue;

                // ���˱�����û�
                inv[i]->move(environment(this_object()));                
        }

/*
        // ��ʱֻ��500��EXP���µķ�ת����Ա����
        if ((! MEMBER_D->is_valib_member(ob->query("id")) || 
            ob->query("scborn/ok")) && ! wizardp(ob))
                return notify_fail("����(chuanfu)�������������ڼ䣬�⴬��ʱֻ��Է�ת����Ա���š�\n");
*/                                
        if (environment(ob) == this_object())
                return notify_fail("����(chuanfu)�������Ѿ��ڴ����ˣ���ô�������º���\n");

        if (! ob->move(this_object()))return notify_fail("��λ�͹٣����Ѿ��������ˣ����°�ɣ�\n");

        tell_object(ob, HIG "����(chuanfu)����˵����Ҫ�´������� out ��\n" NOR);

        return 1 ;
}

int do_out()
{
        object me = this_player();

        if (environment(me) != this_object())return 0;
                
        if (query("running"))
                return notify_fail("�Ѿ������ˣ�\n");
                
        me->move(environment(this_object()));
                
        return 1;
}

void heart_beat()
{
                //object me = find_player("rcwiz");
                object *inv, *obs;
                object ob, ob_boss;
                string now_place_name;
                int left_time;

                //keep_heart_beat(1);

                if (! environment(this_object()))return;

                set_name(HIW "�ɾ��ŷ���������" + query("dest_place_name") + "��" NOR, query("id"));

                left_time = query("waiting") - (time() - query("stop_time"));
                left_time /= 60;
                if (query("running"))
                {
                        // �����������
                        if (random(30) == 1)
                        {
                                message_vision(HIC + nature_message[random(sizeof(nature_message))] + NOR, this_object()); 
                        }
                        
                        if (time() - query("start_time") >= query("running_time") / 2 )        
                        {                
                                set("long", HIR "\n����(chuanfu)ߺ�ȵ������ǵĴ�������ʹ�У�����ʹ����·�̵�һ�룬�����ĵȺ�\n" NOR);                        
                                if ((time() - last_update_boss >= 1800) && random(4) == 7 )
                                {
                                        ob_boss = new("/d/penglai/npc/qingmianshou");
                                        if (ob_boss->move(this_object()))        
                                        {
                                                message_vision(HIB "ͻȻ��������ӿ��ֻ�����һ�ź���Ʈ����������һζ�����㱼䣬һֻ�����Ѿ�վ��"
                                                               "����ǰ��\n" NOR, this_object()); 
                                                       CHANNEL_D->do_channel(this_object(), "rumor", "��˵" HIG "������" + HIM "�������ɵ��ӳ��������ɾ��ŷ�����" NOR);
                                        }
                                        last_update_boss = time();
                                }
                                
                        }
                        else
                                set("long", HIR "\n����(chuanfu)ߺ�ȵ������ǵĴ�������ʹ�У������ĵȺ�\n" NOR);
                }
                else
                        set("long", HIC "\n����(chuanfu)ߺ�ȵ������ǵĴ����ڵȴ���(����ʣ��" + sprintf("%d", left_time) + "����)����������ڴ�����Ϣ��enter����\n" NOR);
                
                inv = all_inventory(this_object());
                obs = filter_array(inv, (: userp($1) :)); // ���˵���������

                // ������ʹ�м��㿿��ʱ���Ƿ�ﵽ
                if (query("running"))
                {
                        // ��վ��
                        if (time() - query("start_time") >= query("running_time"))
                        {
                                        set("stop_time", time()); // ���õ�վʱ��
                                        this_object()->move(query("dest_place"));
                                        delete("running");
                                        message_vision(HIC "����(chuanfu)ߺ�ȵ����͹���С��Ӵ���������� ����\n" NOR, this_object());
/*
                                        if (ob_boss = find_living("qingmian shou"))
                                        {
                                                destruct(ob_boss);
                                        }
*/
                                        // �������������startroom
                                        foreach(ob in obs)
                                        {
                                                //if (ob->query("id") == "qingmian shou")destruct(ob);
                                                ob->move(environment(this_object()));
                                                ob->set("startroom", base_name(environment(this_object())));        
                                                ob->save();
                                        }
                                        // �����������ƺ�Դ��Ŀ�ĵص�
                                        now_place_name = query("dest_place_name");
                                        set("dest_place", query("source_place"));
                                        set("dest_place_name", query("source_place_name"));

                                        set("source_place", base_name(environment(this_object())));
                                        set("source_place_name", now_place_name);

                                        
                                        // ����ʱ��
                                        set("stop_time", time());                                        
                                        
                        }
                        return;
                }
                else // ! running
                {
                        // ������
                        if (time() - query("stop_time") >= query("waiting_time"))
                        {
                                set("start_time", time());
                                set("running", 1);
                                message_vision(HIC "����(chuanfu)ߺ�ȵ���С������������ ����\n" NOR, this_object());
                                this_object()->move("/clone/misc/sea");
                        }
                        return;
                }
                

}
