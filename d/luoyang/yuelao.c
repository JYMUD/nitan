inherit ROOM;

void create()
{
        set("short", "һ��ǣ");
        set("long", @LONG
���������ط���һ��ǣ��������ר�����˵޽��Լ�ͽ����Լ�ĵط���
�����������еķ򸾶���������ϲ����Ե�ģ�������������Ҳ�����Ľ��
�����������ˡ�
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"eroad2",
        ]));
        set("objects", ([
                "/adm/npc/hongniang" : 1,
        ]));
	set("coor/x", -6970);
	set("coor/y", 2140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}