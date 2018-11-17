inherit ROOM;


void create ()
{
  set ("short","安南錢莊");
  set ("long", @LONG
這裡是安南的錢莊。這裡的信譽很好，有很多人來這裡存錢。老闆
正在那裡打着算盤，夥計在門前熱情地招呼着客人。
LONG);

  set("exits", ([ 

 "south":__DIR__"dongjie2",
      ]));
 
  set("objects",([
          __DIR__"npc/wu":1,
          ]));
  
  set("valid_startroom", 1);
  setup();
 
}
