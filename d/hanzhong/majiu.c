#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short","���");
        set("long", @LONG
�����书�����ǣ���Ϊƽʱ�������˲��࣬�Ե���Щ�ƾɡ���
�������µ���ľ���϶���һ����ľ�� (paizi)�����жѷ������Ѳ��ϣ�
������һ����ۡ�
LONG );
      set("outdoors", "hanzhong");
      set("no_fight", 1);
      set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
                "/clone/npc/mafu": 1,
      ]));
      set("exits",([ /* sizeof() == 1 */
                "west" : __DIR__"kedian1",
      ]));
        set("coor/x", -12230);
	set("coor/y", 820);
	set("coor/z", 0);
	setup();
      replace_program(TRANS_ROOM);
}
