// Room: /d/suzhou/nandajie2.c
// Date: May 31, 98  Java

inherit BUILD_ROOM;

void create()
{
        set("short", "�ϴ��");
        set("long", @LONG
������һ�������Ľֵ��ϣ����ϱ���ͷ���졣����ͨ�����ϴ��
�����ĵضΣ�����������������������԰�������棬�����ݳǵ��ϳ�
�š���ν�������ã������պ������Ե�ȷ��������������������
���˼丣�ء�
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"tingyu",
                "west"  : __DIR__"liuyuan",
                "north" : __DIR__"nandajie1",
                "south" : __DIR__"nanmen",
        ]));
	set("coor/x", 1110);
	set("coor/y", -1080);
	set("coor/z", 0);
	setup();
}
