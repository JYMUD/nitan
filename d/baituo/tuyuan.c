//room: tuyuan.c
inherit ROOM;

void create()
{
        set("short","��Է");
        set("long", @LONG
���Ǹ��������Է����ֻ����þ����ض����̲ݵ��ϳԲݡ�����
������԰�����洫���������޵ĺ��У�������һ����԰��
LONG );
        set("exits",([
                "east"      : __DIR__"sheyuan",
                "west"      : __DIR__"shoushe",
                "southwest" : __DIR__"zhuyuan",
        ]));
        set("outdoors", "baituo");
        set("objects",([
                __DIR__"npc/baitu" : 2,
        ]));
        set("coor/x", -49970);
        set("coor/y", 20070);
        set("coor/z", 30);
        setup();
}