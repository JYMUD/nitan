inherit ROOM;

void create()
{
        set("short", "ҩ��");
        set("long", @LONG
����һ��ҩ�̣�һ��ŨŨ��ҩζ���㼸����Ϣ�����Ǵ�ҩ���ϵ�
���ٸ�С������ɢ�������ġ���ҽƽһָ���ڲ輸�Զ��Ժ��Ų裬��
Ҳ������һ�ۡ�
LONG );
        set("objects", ([
                "/d/city/npc/ping" : 1,
        ]));
        set("no_fight", 1);     
        set("no_sleep_room", 1);
        set("exits", ([
                "east" : __DIR__"road",
        ]));
	set("coor/x", -5060);
	set("coor/y", 2230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}