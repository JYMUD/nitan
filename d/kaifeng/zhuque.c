inherit ROOM;

void create()
{
        set("short", "��ȸ��");
        set("long", @LONG
�����ڳǵĳ��ţ��ߴ�ĳ�ǽ�ô���ש�ֺ���֭���ɣ�ʱ��ĳ�
ˢʹ��ǽש��Ϊ����ɫ�����������ǽ�¥�����治Զ�����Ǵ������
�İ˱������
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"road",
                  "north" : __DIR__"road2",
                  "westup" : __DIR__"jiaolou",
                  "eastup" : __DIR__"jiaolou2",
        ]));
        set("objects", ([
                  __DIR__"npc/guanbing" : 2,
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5050);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}