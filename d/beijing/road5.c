inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
������һ����������Ĵ�����ϡ��������������������ӵġ���
�̵ġ����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡���
ʱ����������������߷ɳ۶���������һ·��������·����������
����������֡����߾����������ˡ�
LONG );
        set("exits", ([
                "north" : "/d/beijing/yongdingmen",
                "west"  : "/d/xueshan/bieyuan",
                "southeast" : "/d/beijing/road6",
        ]));
        set("objects",([
                "/d/taishan/npc/seng-ren" : 1,
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7600);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}