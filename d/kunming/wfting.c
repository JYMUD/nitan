inherit ROOM;

void create()
{
        set("short", "����ͤ");
        set("long", @LONG
������ʯ����ߵ�һ���壬������һСͤ���治֪������
�ν�������ģ����ۿ�ȥ��ֻ������ʯ��������һʱ���۾���
�����ˡ�
LONG);
        set("outdoors", "kunming");
        set("exits", ([                
                "down" : __DIR__"lianhua",
        ]));
	set("coor/x", -16780);
	set("coor/y", -7200);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}