// Room: /d/chengdu/ruyin1.c
// Last Modifyed by Winder on Jan. 4 2002

inherit ROOM;
void create()
{
        set("short", "�ƾɴ�լ");
        set("long", @LONG
������һ���ƾɴ�լ��ǰԺ�������Ѿ�������һ�룬���ڵ�������
ס�����ȥ·��ͥԺ���Ӳݴ����������Ѿ��ܾ�û����ס�ˣ���˵����
�����й����֣����ǵ�Ҳ��û��˵�����˱�������˸����ľ�����Ȼ
�ճ����
LONG        );
        set("outdoors", "chengdu");
        set("exits", ([ /* sizeof() == 1 */
                "west"  : __DIR__"ruin2",
                "east"  : __DIR__"westroad1",
        ]));
        set("objects", ([
                "/d/gaibang/npc/1dai" : 2,
                "/d/gaibang/npc/2dai" : 1,
        ]));
        set("coor/x", -15250);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}