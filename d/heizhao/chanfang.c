//Cracked by Kafei
// yideng10.c

inherit ROOM;
void create()
{
        set("short", "����");
        set("long", @LONG
������һ������������һ���Ǵ����붨�ĵط���ż��Ҳ�����Ӵ�
���Ÿ�ɮ��̽�����ڡ�
LONG );

        set("no_sleep_room",1);
        set("exits", ([
                "out" : __DIR__"houyuan",
        ]));
        set("invalid_startroom", 1);
        setup();
}

int valid_leave(object me, string dir)
{
        object yd;
        if (objectp(yd=present("yideng dashi", environment(me)))) {
                message_vision("һ�ƴ�ʦ��$N΢΢Ц��Ц������ı����ⲻ��Ҫ�ҵ������ˣ��ðɡ���\n˵��ת���뿪��������\n", me);
                delete_temp("yideng_waitreward", me);
                yd->move("/d/heizhao/yideng9");
        }
    return ::valid_leave(me, dir);
}