// mtxiaowu.c 木屋

inherit ROOM;

void create()
{
        set("short", "木屋");
        set("long", @TEXT
这里是一个很小的木屋，室中放着一些乱七八遭的家具，墙角
边还有一张破烂的小床，有一个英俊的少年在屋内走来走去，似乎
有什么心事，不时的发出几声长叹...... 
TEXT );
       set("exits", ([
           "west" : __DIR__"mtdating",
       ]));
       set("objects",([
           __DIR__"npc/shizhongyu" : 1,
       ]));
        set("coor/x", -2090);
        set("coor/y", -1700);
        set("coor/z", 30);
        setup();
       replace_program(ROOM);
}