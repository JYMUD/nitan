// Room: /d/ruzhou/xiaozheng.c С��
// llm 99/02

inherit ROOM;

void create()
{
        set("short", "����С��");
        set("long", @LONG
�����Ѿ��������ݵؽ��ˡ�С�򲻴󣬵���λ����ԭ����ԣ���
�������Ŀ��˱�ʹ�������������������ˡ�����ʹ������ı����˿�
���٣�����������ɫ�ҴҵĽ������ˡ�
LONG
        );

        set("exits", ([
                "southwest" : "/d/nanyang/yidao3",
                "north" : __DIR__"nanmen",
                "east" : __DIR__"shang_road3",
        ]));

        set("objects",([
                __DIR__"npc/xiao-fan" : 1,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
