// Room /d/heimuya/midao02.c
// By haiyan

#include <room.h>
inherit ROOM;

void create()
{
     set("short", "�ص�");
        set("long", @LONG
����������̼������ܵ�ͨ������������书��Ϊ�����칦��Ϊ
�����˴��ţ��ʽ��е��Ӷ��ڴ˵�������
LONG );
     set("exits", ([
         "west"    : __DIR__"midao01",
         "east"    : __DIR__"lwchang1",
         "south"   : __DIR__"lwchang2",
         "north"   : __DIR__"lwchang3",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
