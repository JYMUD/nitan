// /guanwai/shanhaiguan.c
inherit ROOM;

void create()
{
        set("short", "ɽ����");
        set("long", @LONG
����������ﳤ��������Ҫ�ؿ�--ɽ���ء����������Ҫ���Թž�
�ǹ���ͨ����ԭ�ıؾ�֮�ء�վ�ڹ�¥�ϱ�������ɽ���ű������̨������
Ŀ�����س���Զ����ֱ���뺣������ͷ��ϡ�ɼ�����¥��¥��������һ���
������(bian)��
LONG );
        set("exits", ([
                "northeast" : __DIR__"road1",
                "southeast" : __DIR__"laolongtou",
                "up"        : "/d/changcheng/shanhaiguan",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing"    : 2,
        ]));
        set("item_desc",([
                "bian" : 
"
    ��������������������������������������
    ��������������������������������������
    ������������  ��  ��  һ  ��  ��������
    ��������������������������������������
    ��������������������������������������\n",
        ]));
//        set("no_clean_up", 0);
         set("outdoors", "guanwai");
        set("coor/x", 3940);
	set("coor/y", 9120);
	set("coor/z", 0);
	setup();
//        replace_program(ROOM);
}
