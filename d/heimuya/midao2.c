// Room /d/heimuya/midao2.c
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
         "northup"   : __DIR__"midao1",
         "southdown" : __DIR__"midao3",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
