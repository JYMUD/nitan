#include <ansi.h>
inherit ROOM;

void home(object ob);

void create()
{
        set("short", "��̲");
        set("long", @LONG
��������������ˡ��ϱ���һ���޼ʵĴ󺣣���������Ƭ
��ľ�֡����ϵĿ����ƺ��������ƣ���ʪ�ĺ����д���һ����
�����ּ�����һ�����صĻ��㣬����������ʮ�ֹ��졣���߲�
��һ�Ҵ�(chuan)��
LONG);

        set("item_desc", ([
                "chuan" : "�������ߵ�������ϵ�Ĵ󴬡����ϵĿ��˻����ֻҪ\n"
                          "�ϴ�(enter)�Ϳ��Ի���ԭ��\n",
        ]));
        set("exits",([
                "north" :__DIR__"lin1",
                "south" :__DIR__"jiutou1.1", 
                "west"  :__DIR__"jiutou11/jiutou1.1", 
                "east"  :__DIR__"jiutou22/jiutou1.1", 
                "southeast"  :__DIR__"jiutou3/jiutou1.1", 
                "southwest"  :__DIR__"jiutou4/jiutou1.1", 
        ]));
        set("outdoors", "shenlong");
        set("valid_startroom", 1);
        set("no_clean_up", 1);
        /*
	set("objects", ([
		"/clone/dream_npc/shenlongdao/nianshou" : 1,
	]));
	*/
        setup();
}

void init()
{
        set("startroom", base_name(this_object()), this_player());
	add_action("do_enter", "enter");
}

int do_enter ( string arg )
{
        object ob ;
        string dir;
        if( !arg || arg !="chuan" ) 
        {
                tell_object(this_player() , "��Ҫ enter �Ķ���\n" ) ;
                return 1 ;
        }
        ob = this_player () ;
        message_vision("����һ�������ϴ���æ����һ��������ඣ�\n", ob);
        message_vision("�������𷫣��������������С�\n", ob);
        ob->move(__DIR__"dahai") ;
        tell_object(ob, BLU "���ں��Ϻ����˺ܾúܾ�.......\n" NOR ) ;
        call_out("home", 10 , ob );
        return 1 ;
}
void home( object ob )
{
        if (! objectp(ob))
	        return;
        if (base_name(environment(ob)) != "/d/shenlong/dahai")
                return;
        tell_object(ob , "�����ڵִ�����ԭ��һ���������С������´�����\n" ) ;
        ob->move ("/d/beijing/haigang") ;
}


