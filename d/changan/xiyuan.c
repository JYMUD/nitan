//Room: xiyuan.c

inherit ROOM;

void create ()
{
        set ("short", "ϷԺ");
        set("long", @LONG
���������İ����������˴���һ�����ɵ����е���ɫ��Ϸ̨��Ϸ
̨���߹�����յ�����ĵ�����ǰ������Щ���ʣ�������һЩ���Ͳ���
�Ϳ������Ρ�������ǰ�ǹ�ս�����ڵ����и���ڵĶ������洫������
���У��о��ܹ��죬����ԣ�down������ȥ̽��̽�顣
LONG );
        set("exits", ([
                "south" : "/d/changan/liande-beikou",
                "down" : "/d/migong/shanlu",   
        ]));
        set("objects", ([
                "/d/changan/npc/xizi" : 1,
        ]));

        set("coor/x", -10680);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}