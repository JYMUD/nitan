inherit ROOM;

void create()
{
        set("short", "�ܵ�");
        set("long", @LONG
������ڵ��ܵ����������ɽ����Ϊ��ֱ����ԭ������ġ�
LONG );
        set("region", "baituo");
        set("exits" , ([
                "east" : "/d/city/guangchang",
                "up"   : __DIR__"neishi",
        ]));
        set("objects",([
                __DIR__"obj/shenshe" : 1 ,
        ]));

        setup();
        replace_program(ROOM);
}