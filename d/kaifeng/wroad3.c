inherit ROOM;

void create()
{
 set("short", "�����");
        set("long", @LONG
���⸮���������Ҫ��ͨҪ�����ֵ����ߵ������������˳�����
���̷���ߺ�ȣ�������С�����ּۻ��ۣ������ޱȡ��ϱ߲�Զ������
��ۡ���������ͤ԰��
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"wroad2",
                  "east" : __DIR__"tinyuan",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5070);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}