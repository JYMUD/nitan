// Room /d/heimuya/midao7.c
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
         "northwest" : __DIR__"midao6",
         "out"       : "/d/city/yaopu",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
