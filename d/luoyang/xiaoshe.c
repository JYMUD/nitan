inherit ROOM;

void create()
{
        set("short", "����СԺ");
        set("long", @LONG
����һ�������ڱ��µ�����СԺ��Ժ���������С�ᣬ���������
���Դ����Ӽܳɡ����ϰ�����������������һ�������õ������ӡ�һ��
��������Ժ�������������������Ǹо������߽����ˣ�������ͷҲû��
̧һ̧��
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"zhulin3",
                "northeast"  :  __DIR__"youshe1",
                "northwest"  :  __DIR__"zuoshe1",
        ]));
        set("objects", ([
                __DIR__"npc/lvzhu" : 1,
                __DIR__"obj/zhudao" : 1,
        ]));
	set("coor/x", -6950);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}