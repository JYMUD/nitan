inherit ROOM;

void create()
{
        set("short", "��ٵ�");
        set("long", @LONG
����һ��������ֱ����������Ĵ�ٵ����������˶���������������
�����ٵ����ǿ�㣬����ݵ���ʮ���ۡ�����ֱ�ﳤ���Ķ��ţ�������
�߲�Զ���Ƕ��������ųǵ����Ǳ��ˡ�
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "eastup" : __DIR__"wbridge",
                  //"west" : __DIR__"guandaow2",
                  "west" : "/d/changan/road1",
        ]));

	set("coor/x", -7070);
	set("coor/y", 2180);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}