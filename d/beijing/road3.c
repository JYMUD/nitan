inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
������һ����������Ĵ�����ϡ��������������������ӵġ���
�̵ģ����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡���
ʱ����������������߷ɳ۶���������һ·��������·����������
����������֡�������������һ�������
LONG );
        set("exits", ([
                "northeast" : "/d/guanwai/laolongtou",
                "northwest" : "/d/beijing/road2",
                "south"     : "/d/beijing/road4",
        ]));
        set("objects",([
                "/d/taishan/npc/shu-sheng" : 1,
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2770);
	set("coor/y", 7590);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}