// Room: /d/nanyang/yidao3.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;

void create()
{
        set("short", "��ٵ�");
        set("long", @LONG
������һ����������Ĵ�ٵ��ϡ��������������������ӵ����̣�
���Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡���ʱ������
����������߷ɳ۶���������һ·��������·�������������������
�֡�
LONG );
        set("exits", ([
                "south" : __DIR__"beimen",
                "west" : "/d/kaifeng/tonanyang",
                "northeast" : "/d/ruzhou/xiaozheng",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "nanyang");
	set("coor/x", -6940);
	set("coor/y", 800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}