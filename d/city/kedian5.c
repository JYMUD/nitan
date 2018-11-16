// Room: /city/kedian4.c
// SMALLFISH 1995/12/04

#include <ansi.h>
#include <room.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create() 
{
        set("short", "������");
        set("long", @LONG
[1��33m   ��  ��  ��  ��  ��  ��  ��  ��  ��  ң  ��  ң   ��  
��  ��  ��  ��  ��  ��  ��  ��  Զ  ��  Զ   Զ  ��  ��  �� 
 ȫ  ��  ��  ��  ��  ��  ��  ��   Զ  ��  ��  ��  ��  ��  ��
  ��  ��  ��  ��  ��   ��  ͷ  ��  ��  ��  ��  ��  ��  ��  ��
  ��  ��   ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��   
��  ��  ��  ��  ��  һ  ��  һ  ��  һ  ��  һ   ��  Ƥ  �� 
 ��  ��  Ⱥ  ��  ��  ��  ��  ��  ��   ��  ��  ��      ��  ��
      ��      ��      ��[2��37��0m
LONG );

        set("no_fight", 1);
        set("no_steal", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);

        set("exits", ([
                "up"   : "/d/city/kedian",
        ]));

        setup();

        "/clone/board/kedian_b"->foo();
}