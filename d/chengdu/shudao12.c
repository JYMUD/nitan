#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
�����������������µ�����ϣ���·ʮ����խ�����ﲻʱ����ǿ
����û���������˺��٣���Ŀ��ȥ����Բ��������û�����̣��㻹��
�ӿ첽���߰ɡ�
LONG );
        set("exits", ([
                  "east" : __DIR__"shudao11",
                  "west" : __DIR__"shudao13",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15090);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}