#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "���" NOR, ({ "hongbao"}) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "��һ�Ǹ��������������ý�ɫ������д��" HIY "�����꼪�� �������⡹" HIR " ��\n"
                                "��(chai)������Ի������ѹ��Ǯ��СС�ľ���Ǳ�ܽ�����\n"
                                "*����2007��4��28��ǰʹ�ú����������ʹ����Ч������\n\n" NOR);
                set("value", 1);
                set("unit", "��"); 
        }
}

void init()
{
        //add_action("do_chai", "chai");
}

int do_chai(string arg)
{
        object me = this_player();
        string msg;
        int i, exp, pot;
        
        // ���ִ���ò���
        
        if (! objectp(me))return 0;
        
        if (! arg || arg != "hongbao")
                return notify_fail("��Ҫ��ʲô��\n");
                
        if (environment(this_object()) != me)
                return notify_fail("������û����������ѽ��\n");
                
        i = 8000 + random(2000);
        exp = 80000 + random(20001);
        pot = 80000 + random(20001);

        message_vision(HIR "$Nһ���˷ܣ��Ͻ�������𿪣����ޱ��ڴ������񳯺����һ����ɲ�Ǽ䣬һ��⻷"
                       "��$N���� ����\n" NOR, me);
        
        tell_object(me, HIG "��ϲ�㣬�����" HIY + chinese_number(exp) + HIG "��ʵս���顢" HIY + chinese_number(pot) + 
                        HIG "��Ǳ�ܼ�" HIY + chinese_number(i) + HIG "���ƽ�YSG����\n�׻�ף�������꼪�� �������⡹��\n" NOR);
        
        me->add("stocks/balance", i);
        me->add("combat_exp", exp);
        me->add("potential", pot);
        
        me->save();
        
        log_file("hongbao", me->query("id") + " �� " + ctime(time()) + " �򿪺����(/clone/misc/hongbao) \n");

        destruct(this_object());
        return 1;
}
/*
int query_autoload()
{
        return 1;
}
*/