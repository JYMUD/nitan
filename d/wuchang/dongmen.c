inherit ROOM;

void create ()
{
        set ("short","����");
        set ("long", @LONG
�����Ƕ����ˡ��кܶ����˶����������ߡ���ս�ҵ�������人��
Ȼ��������֡��м����ٱ���ҫ��������վ�������������������ˡ�
LONG);

        set("exits", ([
                "west":__DIR__"zhongxin",
        ]));
        set("objects",([
                "/d/city/npc/bing":2,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5080);
	set("coor/y", -1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}