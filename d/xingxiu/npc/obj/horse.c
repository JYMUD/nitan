// item: /d/xingxiu/npc/obj/horse.c
// Jay 3/17/96

inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_ride", "ride");
}

void create()
{
        set_name("������", ({"horse", "yili ma", "ma"}));
        set_weight(35000);
        set_max_encumbrance(50000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ƥ");
                set("long", "һƥ���ֵ�������������(ride)��Ҳ�����Զ�����\n");
                set("value", 1000);
        }
}

int do_ride(string arg)
{
        object me = this_player();
        if (!id(arg))
                return notify_fail("��Ҫ��ʲô��\n");
        if( query_temp("marks/��", this_player())){
                       write("���Ѿ����������ˡ�\n");
                        return 1;
        }
        else {
               message("vision",this_player()->name() + "��������\n",
                        environment(me), ({me}) );
               write("��սս���������������ã�����û��������\n");
                set_temp("marks/��", 1, this_player());
        return 1;
        }
}