#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "��������������" NOR, ({ "hongbao2010"}) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "��һ�Ǹ��������������ý�ɫ������д��" HIY "��������֣�����������" HIR " ��\n"
                                "��(chai)������Ի������ѹ��Ǯ��СС�ľ���Ǳ�ܽ��������л����������Ʒһ����\n"
                                "*����2010��3��15��ǰʹ�ú����������ʹ����Ч������\n\n" NOR);
                set("value", 0);
                set("no_give", 1);
                set("no_sell", 1);
                set("no_store", 1);
                set("no_drop", 1);
                set("unit", "��"); 
        }
}

void init()
{
        add_action("do_chai", "chai");
}

int do_chai(string arg)
{
        object me = this_player();
        string msg;
        int i, exp, pot;
        object obgift;
        
        string *oblist = 
        ({
                "/clone/fam/gift/dex3",
                "/clone/fam/gift/con3",
                "/clone/fam/gift/int3",
                "/clone/fam/gift/str3",
                "/clone/fam/gift/dex2",
                "/clone/fam/gift/con2",
                "/clone/fam/gift/int2",
                "/clone/fam/gift/str2",                
                "/clone/fam/max/naobaijin",
                "/clone/fam/item/jintiao",
                "/clone/fam/item/moye-shengfu",
                "/clone/armor/fusang/shenxing-xue",
                "/clone/armor/qilin/jixing",
                "/clone/armor/fudai",
                "/clone/armor/shuixian-erhuan",
                "/clone/armor/dugu/jianmo-zhiyu",
                "/clone/armor/daojian/lengyue",
                "/clone/fam/item/xiling-hu",
                "/clone/fam/item/yuanshenjingyan-guo",
        });

        // ���ִ���ò���
        if (! objectp(me))return 0;

        if (! arg || arg != "hongbao2010")
                return notify_fail("��Ҫ��ʲô��\n");

        if (environment(this_object()) != me)
                return notify_fail("������û����������ѽ��\n");

        i = 12010;
        exp = 102010;
        pot = 102010;

        message_vision(HIR "$Nһ���˷ܣ��Ͻ�������𿪣����ޱ��ڴ������񳯺����һ����ɲ�Ǽ䣬һ��⻷"
                       "��$N���� ����\n" NOR, me);

        tell_object(me, HIG "��ϲ�㣬�����" HIY + chinese_number(exp) + HIG "��ʵս���顢" HIY + chinese_number(pot) + 
                        HIG "��Ǳ�ܼ�" HIY + chinese_number(i) + HIG "���ƽ�YSG����\n�׻�ף����������֣�������������\n" NOR);

        me->add("stocks/balance", i);
        me->add("combat_exp", exp);
        me->add("potential", pot);

        // 10%���ʻ�ȡ�����Ʒһ��
        if (random(10) == 1)
        {
                obgift = new(oblist[random(sizeof(oblist))]);
                if (obgift)
                {
                        tell_object(HIY "��ϲ�㣬�Ӻ���л��" + obgift->name() + HIY "����ϲ��ϲ����\n" NOR);
                        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name() + "���������������"
                                                                    "����Ʒ" + obgift->name() + HIM "������\n");  
                        obgift->move(me, 1);
                        log_file("hongbao2010", HIY + me->query("id") + "�Ӻ���л�� " + obgift->name() + "��\n" NOR);
                }
        }

        me->save();

        log_file("hongbao2010", me->query("id") + " �� " + ctime(time()) + " �򿪺����(/clone/misc/hongbao2010) \n");

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
