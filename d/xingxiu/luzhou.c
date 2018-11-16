// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short", "ɳĮ����");
        set("long", @LONG
��ɳĮ�ľ�ͷ������һ�����ޡ���ľ������һ�ۿ���������̨����һ��ľ��
ר���ڿʵ����˺�ˮ��������һ��ϵء�
LONG );
        set("resource/water", 1);

        set("exits", ([
                //"northeast" : __DIR__"shanjiao",
                "northeast" : __DIR__"tugu",
                "southeast" : __DIR__"nanjiang3",
                "south" : "/d/item/xuanbing",
        ]));

        set("objects", ([
                __DIR__"obj/donkey" : 1,
                __DIR__"obj/hamigua" : 2,
        ]));

        set("outdoors", "xiyu");
        set("no_map", "����ĵ��������Ի��޷����Ƶ�ͼ��\n");

        setup();
}

void init()
{
        add_action("do_drink", "drink");
}

int do_drink(string arg)
{
        int current_water;
        int max_water;
        object me;

        if (arg != "water")
                return notify_fail("��Ҫ��ʲô?\n");

        me = this_player();
        current_water=query("water", me);
        max_water=query("str", me)*10+100;
        if (current_water<max_water)
        {
                set("water", current_water+30, me);
                message("vision", me->name()+"ſ�ڿ������ľ�̨����ľ��Ҩ��һ��ˮ�ȡ�\n",
                        environment(me), ({me}) );
                write("�����һ�ھ��д���ɽ������������ѩˮ����ֱ���ۻ���\n");
        } else
                write("���Ų�ҪǮ��ˮ����ô�ȣ�������\n");

        return 1;
}
