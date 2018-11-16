inherit ITEM;
#include <ansi.h>

#define CMD_JD   HIY + "jianding " + query("id") + HIC

void create()
{
        set_name(HIC "��������" NOR, ({"wuming guyu", "wuming", "guyu"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIC "����һ�鲻֪���Ĺ��񣬿���ȥ�ǳ����ϣ���֪������һ�����\n" HIG
                                "��Ҫͨ�����������������Ŀ�������֣���������������������ʯ֮һ��\n" HIB
                                "������1������������2������������3����\n" HIW
                                "����ʯ��1����������ʯ��2����������ʯ��3����\n" HIR 
                                "����ǰ��ȷ����ı����еĸ�������ʣ��5% ��\n" HIC
                                "������³�ദ������ָ�� " + CMD_JD + " ������³�������������\n" NOR);
                        
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

void init()
{
        add_action("do_jianding", "jianding");
}

int do_jianding(string arg)
{
        object me, env;
        object yu;        
        int ran_point;
        
        me = this_player();
        
        
        if (! arg || arg != query("id"))
                return notify_fail("�������ʲô��\n");
                
                        
        env = environment(me);
        
        if (base_name(env) != "/d/room/xiaoyuan")
                return notify_fail("�����Ʒ����ֻ��³����ܼ������㻹��������ȥ�ɡ�\n");
                
        message_vision(HIY "$N�ó�" + name() + HIY "��³�������\n", me);
        
        
        // ��ʼ����
        /*40%���ʼ�����1����������1��
          35%���ʼ�����2����������1��
          25%���ʼ�����3����������1��
        */
        ran_point = 1 + random(100);
        if (ran_point > 60)
        {
                if (random(2))
                {
                        yu = new("/clone/fam/enchase/guxuan-yu1");
                }
                else
                {
                        yu = new("/clone/fam/enchase/xuanbing-shi1");
                }
        }
        else if (ran_point > 0 && ran_point <= 35)
        {
                if (random(2))
                {
                        yu = new("/clone/fam/enchase/guxuan-yu2");
                }
                else
                {
                        yu = new("/clone/fam/enchase/xuanbing-shi2");
                }                
        }
        else
        {
                if (random(2))
                {
                        yu = new("/clone/fam/enchase/guxuan-yu3");
                }
                else
                {
                        yu = new("/clone/fam/enchase/xuanbing-shi3");
                }                
        }

        tell_object(me, HIG "³�ཫ���������ʯ�����㡣\n" NOR);

        yu->move(me, 1);
        
        destruct(this_object());
        
        return 1;
}

