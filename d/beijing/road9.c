inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
������һ����������Ĵ�����ϡ��������������������ӵġ���
�̵ġ����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡���
ʱ����������������߷ɳ۶���������һ·���������ϵ��˸�����
�ž�װ���¼��������еĻ���������ŵ�������������Щϰ��Ľ���
�ˡ���·��������������������֡�
LONG );
        set("exits", ([
                "north" : "/d/beijing/road8",
                "south" : "/d/beijing/road10",
        ]));
        set("objects",([
                "/d/taishan/npc/tangzi" : 2,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2770);
	set("coor/y", 7560);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}