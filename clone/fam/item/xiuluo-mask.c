
// ��ߣ�Ϊ������������

#include <armor.h>
#include <ansi.h>

inherit MYMASK;
 
void create()
{
        string *sname = ({
                "��������",
                "��������",
                "��ɷ����",
                "������",
                "�߾�����",
                "��֫����",                
        });

        set_name(HIM "�������" NOR, ({ "xiuluo mianju", "xiuluo", "mianju" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "tian jing");
                set("unit", "ֻ");
                set("long", HIM "����һֻ��ߣ����������޹�����ģ�������Ϻ��û��֪�������ʵ����ˡ�\n" NOR);
                set("value", 1000000);
                /*
                set("armor_prop/mask_name", sname[random(sizeof(sname))]);
                set("armor_prop/mask_id",  ({ "masker xiuluo", "masker", "xiuluo"}) );
                set("armor_prop/mask_long", "���������������ߣ����Կ�������ʵ��ݡ�\n");
                set("armor_prop/mask_flag", 1);
                */
        }
        setup();
}

void init()
{
        add_action("do_exit", "exit");
        add_action("do_exit", "quit");
        add_action("do_exit", "save");
}

int do_exit()
{
        if (this_player()->query_temp("apply/mask_flag"))
        {
                return notify_fail("��ȡ����ߺ��ٽ��иò�����\n");
        }
}

int query_autoload()
{
        return 1;
}


