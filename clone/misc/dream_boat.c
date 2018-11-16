
#include <ansi.h>

inherit ITEM;

void start_heart_beat()
{
        // Ĭ��Ϊ����1
                set_heart_beat(1);
}

void create()
{
        set_name(HIW "���ͷ���������δ֪�ص㣩" NOR, ({ "large boat"}));
        set_weight(200000);
        set_max_encumbrance(1000000);
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
                                set("no_clean_up", 1);

                                set("stop_time", time()); // ������ʱ��
                                set("waiting_time", 600); // Ĭ�ϵȴ�ʱ��
                                set("running_time", 600); // Ĭ����ʹʱ��Ϊʮ����

                                set("source_place", "/d/shenlong/haitan"); // ������
                                set("dest_place", "/b/tulong/haigang"); // Ŀ�ĵ�
                                set("dest_place_name", "����֮��");
                                set("source_place_name", "������");

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

        ob = this_player();
        if (arg != this_object()->query("id"))
        {
                tell_object(ob , "��Ҫ enter �Ķ���\n");
                return 1 ;
        }

                if (environment(ob) == this_object())
                        return notify_fail("����(chuanfu)�������Ѿ��ڴ����ˡ�\n");
                
        ob ->move(this_object());

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
                object ob;
                string now_place_name;
                int left_time;

                if (! environment(this_object()))return;

                set_name(HIW "���ͷ���������" + query("dest_place_name") + "��" NOR, query("id"));

                left_time = query("waiting") - (time() - query("stop_time"));
                left_time /= 60;
                if (query("running"))
                {
                        if (time() - query("start_time") >= query("running_time") / 2 )                        
                                set("long", HIR "\n����(chuanfu)ߺ�ȵ������ǵĴ�������ʹ�У�����ʹ����·�̵�һ�룬�����ĵȺ�\n" NOR);                        
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
                                        foreach(ob in obs)
                                        {
                                                ob->move(environment(this_object()));                                                
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
