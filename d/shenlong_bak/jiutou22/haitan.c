#include <ansi.h>
inherit ROOM;

void home(object ob);

void create()
{
        set("short", "��̲");
        set("long", @LONG
�㱻һ��紵��ͷ��Ŀѣ���ƺ��ֻص��˺�̲��
LONG);


        setup();
}

void init()
{

	this_player()->move("/d/shenlong/haitan");
}
