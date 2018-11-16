inherit ROOM;

protected void refresh_table()
{
        object *inv,zhuozi;
        int i = 15;

        if(!objectp(zhuozi = present("wood table", this_object())))
                return;

        call_out("refresh_table",300);

        if( sizeof( (inv = all_inventory(zhuozi)) ) )
                foreach( object one in inv )
                        if(!one->is_food())
                        {
                                if(one->is_character())
                                        one->move(this_object());
                                else
                                        destruct(one);
                        }
                        else
                                i--;

        if(i > 0)
                while(i--)
                {
                        object food = new("/clone/food/jitui");
                        food->move(zhuozi);
                }
}

void create()
{
        set("short", "����");
        set("long", @LONG
������ǳ��������������۵ľ���һ�ھ޴��ˮ�ס�������
��Ĳ����Ϸ��Ÿ��ֳ�ʳ������������������ȥ��æ���ţ�����
������ˮ����Ҩ(drink)��ˮ�ȡ�
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"gd4",
]));

        set("objects", ([
                __DIR__"obj/table": 1,
]));

        setup();
        refresh_table();
}

void init()
{
        add_action("do_drink", "drink");
}

int do_drink(string arg)
{
          object me;
          me=this_player();

              if( query("water", me) >= me->max_water_capacity() )
     {
                     write("���Ѿ���̫���ˣ���Ҳ�಻��һ��ˮ�ˡ�\n"); 
                    return 1; 
             } 

        message_vision("$N��ˮ�ױ��ñ���Ҩ��ˮ���˼��ڡ�\n", me);
        addn("water", 20, me);
        if( (query("family/family_name", me) != "ҩ����" )
        && (random(10) < 3) )
                me->apply_condition("scorpion_poison", 10);
        return 1;
}
