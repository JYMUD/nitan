inherit ROOM;

void create()
{
	set("short", "С��");
        set("long", @LONG
������һ����������Ĵ�����ϡ��������������������ӵġ���
�̵ġ����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡���
ʱ����������������߷ɳ۶���������һ·��������·����������
����������֡����߾��Ǵ�֮���ˡ�
LONG );
        set("exits", ([
                "east"  : __DIR__"haigang",
                "south"  : "/d/ruzhou/beimen",
                "north" : __DIR__"road9",
        ]));
        set("objects",([
                "/d/taishan/npc/tiao-fu" : 1,
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2770);
	set("coor/y", 7550);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
