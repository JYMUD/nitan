// Room /d/heimuya/midao6.c
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
         "northdown" : __DIR__"midao5",
         "southeast" : __DIR__"midao7",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
