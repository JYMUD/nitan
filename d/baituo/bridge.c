inherit ROOM;

void create()
{
        set("short", "С��");
        set("long", @LONG
����һ��С���ţ�����ɽ�ϵı�ѩ�ڻ��γ�һ���峺��СϪ����
���»�����������ʱ����Ƥ��С��Ծ��ˮ�棬�������»���һ������
ɫ�Ļ��ߡ�
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "north" : __DIR__"guangchang",
                "east"  : __DIR__"xijie",
        ]));
        set("objects",([
                __DIR__"npc/cungu" : 1,
        ]));
        set("coor/x", -49980);
        set("coor/y", 19970);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}