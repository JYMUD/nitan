#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�ʹ�ƫ��");
        set("long", @LONG
��������Ͻ��ǵ����ŵĴ�Ѱ�������ǵ������������ģ���
�����Բ�������;������������ǸϿ��뿪Ϊ�á�
LONG );
        set("exits", ([
                "east" : "/d/beijing/hg",
        ]));
        set("objects", ([
                "/d/beijing/npc/yuqian1" : 2,
        ]));
        set("coor/x", -200);
        set("coor/y", 4100);
        set("coor/z", 0);
        setup();
}
/* void init()
{
        add_action("do_body", "body");
}
int do_body(string arg)
{
        int max;
        object ob;
        ob = this_player();

        max=query("max_qi", ob);
        set("eff_qi", max, ob);
        set("qi", max*2, ob);
        max=query("max_jing", ob);
        set("eff_jing", max, ob);
        set("jing", max*2, ob);
        set("neili",query("max_neili",  ob)*2, ob);
        set("jingli",query("max_jingli",  ob), ob);
        max = ob->max_food_capacity();
        set("food", max+random(40), ob);
        max = ob->max_water_capacity();  
        set("water", max+random(40), ob);
        ob->clear_condition();
        return 1;
} */