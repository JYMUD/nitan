#include <ansi.h>

inherit ITEM;

int do_use(string arg);

void create()
{
        set_name(HIM "�����ɹ�" NOR, ({"penglai xianguo", "penglai", "xianguo", "guo"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "\n����һ�ž�Ө��͸���ɹ�����˵���ú��ܹ���������\n"
                                      "*����(fuyong xianguo)��������������ɻ��30���飬25��Ǳ�ܣ�1000�㹱�׼�20����ᣨ˫����������ӱ�����\n"
                                      "*ÿ����һ�������ɹ�������һ���������������ɴ��̳ǹ���\n" NOR);
                set("unit", "��");
                set("value", 1);
        }
}

int query_autoload()
{
        return 1;
}


void init()
{
        add_action("do_use", "fuyong");       
}

int do_use(string arg)
{
        object me, ob;
        int exp, ys_exp, pot, tihui, gongxian;
                
        me = this_player();
        
        if(! objectp(present("penglai xianguo", me)))return 0;
        
        if(! objectp(ob = present("xiling hu", me)))
        {
                return notify_fail("������û����������޷����������ɹ���\n");
        }
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ�أ�\n");
                 
        // ʹ������
        message_vision(HIY + "\n$N" HIY "һ̧ͷ����һ�������ɹ����������������������� ����\n" NOR, me);

        exp = 300000;
        pot = 250000;
        tihui = 200000;
        gongxian = 1000;
        
        // ��ڼ�
        if( query("service/double_gift", me) )
        {
                exp *= 2;
                pot *= 2;
                tihui *= 2;
                gongxian *= 2;
        }
        
        tell_object(me, HIG "����������ɹ�������" + chinese_number(exp) + "���飬" + chinese_number(pot) + "Ǳ"
                            "�ܣ�" + chinese_number(gongxian) + "���ɹ��׼�" + chinese_number(tihui) + "��ᡣ���������һ����\n\n" NOR);

        // ���������
        destruct(ob);
        
        // Ԫ�����Ӿ���
        if( query("yuanshen/exp", me)<2000000000 )
        {
                ys_exp = exp / 5;
                exp -= ys_exp;
                addn("yuanshen/exp", ys_exp, me);
        }
        
        if( query("potential", me)>2000000000 || query("learned_points", me)>2000000000 )
        {
                set("potential",query("potential",  me)-query("learned_points", me), me);
                set("learned_points", 0, me);
        }
        if( query("experience", me)>2000000000 || query("learned_experience", me)>2000000000 )
        {
                set("experience",query("experience",  me)-query("learned_experience", me), me);
                set("learned_experience", 0, me);
        }
        if( query("combat_exp", me) <= 2000000000 )
        {
                addn("combat_exp", exp, me);
        }
        if( query("potential", me)<2000000000 )
        {
                addn("potential", pot, me);
        }
        if( query("experience", me)<2000000000 )
        {
                addn("experience", tihui, me);
        }
        
        addn("gongxian", gongxian, me);
        
        me->save();
        
        log_file("xianguo",query("id", me)+"at"+ctime(time())+"usepenglaixianguo.\n");
        
        destruct(this_object());
        
        return 1;
}