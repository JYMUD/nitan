inherit ROOM;

void create()
{
        set("short", "��Ժ");
        set("long", @LONG
������ҩ���ȵ���Ժ��������Ժ��ׯ�����£����ܵĽ�����
���ڷ��Ÿ��ָ�����ҩ�ޡ�Ժ�����붫����ڷ�������ʯ�⣬
�����ҩ���ȸ����ӽ�ѧ�õġ�
LONG
        );
        set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"yitong",
  "south" : __DIR__"gd5",
  "east" : __DIR__"ssl2",
  "west" : __DIR__"ssl1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
