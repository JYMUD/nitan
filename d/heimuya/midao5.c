// Room /d/heimuya/midao5.c
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
         "north"     : __DIR__"midao4",
         "southup"   : __DIR__"midao6",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
