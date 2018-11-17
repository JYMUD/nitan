// Room: /d/baihuagu/tree1.c
// Last Modified by Winder on Mar. 5 2001

#include <ansi.h>;
inherit ROOM;
void create()
{
        set("short", "樹林");
        set("long", @LONG
叢林中一片黑暗。你瞪大眼睛，勉強看清楚了一點。一條細細
的光線(light)透過層疊的樹葉的縫中射下來，似乎預示着生的希望。
LONG);
        set("outdoors", "baihuagu");
        set("exits", ([ 
                "north": __DIR__"tree",  
                "west" : __DIR__"tree",
                "south": __DIR__"tree",
                "east" : __DIR__"tree",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -450);
        set("coor/y", -400);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_go","go");
        add_action("do_look","look");
}
int do_look(string arg)
{
        string *dirc = ({ "無","東","南","西","北"});
        int i;
        i=random(4)+1;
        if (!arg||!(arg=="light" || arg=="光線"))
                return notify_fail("你要看什麽？\n");
        message_vision(HIW "$N仔細觀察光線,發現它是從"+dirc[i]+"邊透過來的。\n" NOR,this_player());
        set_temp("marks/百花谷", i, this_object());
        return 1;
}
int do_go(string arg)
{
        string *dira=({"+-*/","east","south","west","north"});
        string *dirb=({"+-*/","e","s","w","n"});
        int a;
        a=query_temp("marks/百花谷", this_object());
        set_temp("marks/百花谷", 0, this_object());
        if (arg==dira[a]||arg==dirb[a])
        {
                this_player()->move(__DIR__"out");
        }
        else
                if(random(4)) this_player()->move(__DIR__"tree");
                else this_player()->move(__DIR__"bhgent");
        return 1;
}