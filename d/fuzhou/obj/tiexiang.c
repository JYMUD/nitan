// tiexiang.c

inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_climb", "climb");
}

void create()
{
        set_name("����", ({"tie xiang", "xiang", "box"}));
        set_weight(200000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һֻ�д��ֱ��������ӣ���Щ�����ˡ�\n");
                set("unit", "ֻ");
                set("material", "steal");
        }
        setup();
}

int do_climb(string arg)
{
        object me = this_player();
        if (!id(arg))
                return notify_fail("��Ҫ���Ķ�����\n");
        if( query_temp("marks/��1", this_player())){
                       write("����ô����û��û�ˣ�\n");
                        return 1;
        }
        else {
               message("vision",this_player()->name() + "�������ӡ�\n",
                        environment(me), ({me}) );
               write("���������ӡ�\n");
                set_temp("marks/��1", 1, this_player());
        return 1;
        }
}
