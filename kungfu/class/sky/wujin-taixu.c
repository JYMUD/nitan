
#include <ansi.h>

inherit ITEM;

void setup()
{

        set("no_clean_up", 1);
        set("no_roar", 1);
        set("no_flyto", 1);    // ���������MISS������Ѿ���horse.c������
        set("no_rideto", 1);   // ���������MISS������Ѿ���horse.c������
        set("no_obsend", 1);
        set("no_paimai", 1);

        ::setup();

}

void create()
{
        set_name(HIW "�޾�̫��" NOR, ({ "wujin taixu" }));
        set_weight(200000);
        set_max_encumbrance(2000000000);

        if (clonep())
        {
                set_default_object(__FILE__);
        }
        else
        {
                set("value", 1);
                set("long",
                HIY "����������֮��Ԩ���޾���̫�飬���ܰ�ããһƬ���ƺ�û��ǰ��֮·��\n"
                    "Ҳû�б߼ʡ���ʱ�������������������Ŷ�����ζ������㲻����������\n"
                    "һ���������˶��ٶ�Թ��𣬾����˶���Ѫ����ɱ¾���������ޱ߼ʵ���\n"
                    "��֮�У���ֻ������һ��ϸС�ĳ������������������������ֻ������һֻ\n"
                    "΢����������� ���� ����ʱ��ί��ʱ���߿����������������������˼\n"
                    "����ǧ ����\n"NOR);
                set("unit", "��");
                set("material", "air");
                set("no_rideto", 1);
                set("no_flyto", 1); 
                set("exits", ([ "out" : "/kungfu/class/sky/sky13" ]));
             
                set("no_get", "!@#$!@#%%^@!^\n");
        }
        setup();
}
/*
void init()
{
        object me = this_player();
        
        add_action("do_start", "start");
        
        CHANNEL_D->do_channel("rumor", this_object(), HIY + me->name() + "(" + me->query("id") + ")" HIM "���׻����������޾�̫�飬��ս��ת�ػ���\n" NOR);                
}
*/


int valid_leave(object me, string arg)
{
        return 1;
}
