// Room /d/heimuya/midao1.c
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
         "out"       : __DIR__"house1",
         "southdown" : __DIR__"midao2",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
