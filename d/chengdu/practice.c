// Room: practice
// Date: Feb.14 1998 by Java

#include <room.h>
inherit ROOM;

void create()
{
      set("short", "��ݲ�����");
        set("long", @LONG
���������ʯ���������󵶳�����ɳ�����ȵȣ����м���������
���ľ�ˣ�����ݵ����ճ������ĵط���
LONG );

      set("exits", ([ /* sizeof() == 1 */
          "down"   : __DIR__"wuguan",
      ]));

      set("objects", ([
          "/clone/npc/mu-ren" : 4,
      ]));

        set("coor/x", -15200);
	set("coor/y", -1800);
	set("coor/z", 10);
	setup();
      replace_program(ROOM);
}