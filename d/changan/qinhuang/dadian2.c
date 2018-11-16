// This is a room made by wsl.
inherit ROOM;
void create()
{
    set("short", "大殿");
        set("long", @LONG
而更使人感到这个空间像旷野的，是在河流两旁，虽然实际上没
有青草，可是叫人一看就知道，那是一片草原，是一片水草丰美，最
适合放牧的地方，因为在整个空间之中，至少有超过两百匹的『马』
那些马，完全和实在的马一样大小，它们神态生动，有的在俯首饮水，
有的在地上打滚，有的在追逐，有的在踢蹄，每一匹马，都有它不同
的神态，一个眼花之下，会以为那些马全是活的。
LONG );
    set("exits", ([
        "south" :__DIR__"dadian",
        "north" :__DIR__"dadian3",
]));
        set("item_desc", ([
  "马" : "那些马，全是陶制的，每一匹马的位置，显然也曾经过一艺术的精心
安排，疏密有致，一点也不觉得拥挤，反倒衬得整个空间更加空旷。
",
]));
    setup();
    replace_program(ROOM);
}
