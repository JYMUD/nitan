// Room /d/heimuya/midao3.c
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
         "northup"   : __DIR__"midao2",
         "southeast" : __DIR__"midao4",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
