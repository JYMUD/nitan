// Room: /city/biaojuhy.c

inherit ROOM;

void create()
{
        set("short", "��Ժ");
        set("long", @LONG
�������ھֻ��������֮�࣬��Ϣ���ɵ�Ժ�ӡ�Ժ�ӵ����������
�˵ļ��ż�����ͣ������������ɹ�·��ġ�Ժ�ӵ���Χ�м���С����
��ƽʱ��ʦ�������Ϣ�����ڡ�
LONG );
        set("exits", ([
                "south" : __DIR__"biaojuzt",
                "north" : __DIR__"biaojucf",
                "east"  : __DIR__"biaojuxf",
                "west"  : __DIR__"biaojuxf1",
        ]));
        set("objects", ([
                __DIR__"npc/zheng" : 1,
        ]));
        set("outdoors", "fuzhou");
	set("coor/x", -101);
	set("coor/y", -6151);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}