// Room /d/heimuya/midao4.c
// By haiyan

#include <room.h>
inherit ROOM;

void create()
{
     set("short", "�ص�");
        set("long", @LONG
����������̼������ܵ�ͨ�����Ǻ�ľ������ԭ����ȡ����ϵ��
�ݾ���
LONG );
     set("exits", ([
         "northwest" : __DIR__"midao3",
         "south"     : __DIR__"midao5",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
