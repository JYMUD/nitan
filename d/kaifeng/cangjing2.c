inherit ROOM;

void create()
{
        set("short", "�ؾ�¥����");
        set("long", @LONG
С¥���ĸ������з���ʯ�Ұ����������տ����е�ˮ�ݸ���ʱ�䣬
�����еĺ��л���ղ��ں��еķ𾭷ŵ�����ȥɹ�Է��վñ�������
�ˣ�������ɹ�𾭵�ʯͷ�ͳ�Ϊɹ��ʯ����˵�з�����
LONG );
        set("objects", ([
                  __DIR__"npc/obj/jing4" : 1,
                  __DIR__"npc/obj/jing3" : 1,
                  __DIR__"npc/obj/jing2" : 1,
                  __DIR__"npc/obj/jing1" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "down" : __DIR__"cangjing",
        ]));

	set("coor/x", -5030);
	set("coor/y", 2220);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}