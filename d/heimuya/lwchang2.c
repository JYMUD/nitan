// lwchang2.c
// By haiyan

inherit ROOM;

void create()
{
        set("short", "���䳡");
        set("long", @LONG
������������̵����䳡���������ż���ľ�ˣ������ڵ��ӳ���
�˴�����а�������ܳ����Ź���ɫ�ʡ�
LONG );
        set("exits", ([
            "north"    : __DIR__"midao02",
        ]));
        set("objects", ([
            "/clone/npc/mu-ren" : 3,
        ]));

        setup();
        replace_program(ROOM);
}
