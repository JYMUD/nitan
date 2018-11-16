inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������һƬï�ܵ�����(wood)������ɫ�������ڸ�����գ�ż��
�������������������֪ʲôҰ�޵�˻�С��Ա�����һ��ľ��(pai
)��
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "west"  : __DIR__"shulin1",
                "south" : __DIR__"shanlu1",
        ]));
        set("quarrys", ([
                "tu"         : 100000,
                "ji"         : 80000,
                "pao"        : 50000,
                "caihuashe"  : 50000,
                "dushe"      : 20000,
                "hu"         : 5000,
                "bao"        : 2000,
                "laohu"      : 2000,
        ]));
        set("item_desc", ([
                "pai"  : "��������  ��������\n",
                "wood" :"һƬ�ɿ��������֡�\n",
        ]));        
         set("coor/x", -49990);
        set("coor/y", 20000);
        set("coor/z", 0);
        setup();
         // replace_program(ROOM);
}

void init()
{
        add_action("do_cut","cut");
}

int do_cut(string arg)
{
        object me = this_player();
        object ob;
 
        if (! arg || arg != "wood")
                return notify_fail("��Ҫ��ʲô��\n");
                
        if (present("chai dao", me))
                return notify_fail("û�в���ô����\n");
                
        if (query_temp("times") == 0)
                return notify_fail("������������\n");
 
        if( query("qi", me)<20 )
                return notify_fail("�����̫���������ܿ���\n");
 
        ob = new("/d/baituo/obj/chai");
        ob->move(environment(me));
        addn("qi", -20, me);
        addn_temp("times", -1);
        message_vision("$N����һ�����۵ù�Ǻ��\n", me);
        return 1;
}
