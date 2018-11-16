// ͭ��

#include <ansi.h>

inherit ITEM;

#define TONGREN_D        "/adm/daemons/tongrend2"

int is_wmtongren() { return 1; };

void create()
{
        set_name(HIY "������ͭ��" NOR, ({ "dazhoutian tongren" }) );
        set_weight(50);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "����һ���ƾɵ�ͭ�ˣ����������һЩͼ���������Ѿ��޷���ʶ��\n" HIG
                                "ʹ��ָ�� kg dazhoutian tongren ������Ѩͭ�ˡ�\n" NOR);
                set("value", 1);
                set("unit", "��");
                set("skill", ([
                        "name" : "jingluo-xue",
                        "exp_required" : 50000,
                        "jing_cost"  : 20,
                        "difficulty" : 80,
                        "max_skill"  : 120,
                        "min_skill"  : 0,                        
                ]));

        }

        setup();
}

void init()
{
        add_action("do_kg", "kg");        
}

int do_kg(string arg)
{
        object ob, me;
        
        me = this_player();
        
        if (! me)return 0;
        
        if (! arg || arg != "dazhoutian tongren")
                return notify_fail("��Ҫ��ʲô���п��������\n");
                
        if (! objectp(ob = present("dazhoutian tongren", me)))
                return notify_fail("������û��������Ʒ��\n");        
                
        TONGREN_D->open_tongren(me, ob);
        
        return 1;                        
}

int query_autoload()
{
         return 1;
}
