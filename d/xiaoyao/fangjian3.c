// fangjian3.c
// Modified by Winder June.25 2000

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
��ֻ������ǰ��Ȼһ����һ����װ����Ů��������һ�ѳ�������׼
��������ţ���������һ���龪֮����ŷ���ԭ��ֻ�Ǹ������ɵ�
���񣬵��ǿ���ȥȴ������һ�����졣�����һ˫����ӨȻ�й⣬���
������ʱֻ�������Ŀѣ��������ħ��а���۹���Ҳ�벻������
������
LONG );
        set("exits", ([
                "east"    : __DIR__"tongmen",
                "northup" : __DIR__"shiji4",
        ]));
        set("objects",([
                __DIR__"obj/putuan" : 1,
        ]));
//        set("no_clean_up", 0);
        set("book_count",1);
        set("coor/x", -50010);
        set("coor/y", -21020);
        set("coor/z", -40);
        setup();
}

void init()
{
        set_temp("ketou_times", 50, this_player());
        add_action("do_kneel", "kneel");
        add_action("do_ketou", "ketou");
}

int do_kneel(string arg)
{
        object me,room,weapon;
        me = this_player();
        if ( !arg || arg == "") return 0;
        if ( arg != "putuan") return 0;
        if (!present("putuan",environment(me))) return 0;
        if( query_temp("marks/kneel", me) == 1 )
                return notify_fail("���Ѿ��������ˡ�\n");
        message_vision("$N˫ϥһ��������������\n", me);
        addn_temp("marks/kneel", 1, me);
        return 1;
}

int do_ketou()
{
        object me, ob;

        me = this_player();
        if( !query_temp("marks/kneel", me))return 0;
        if (!present("putuan",environment(me))) return 0;
        if( query_temp("ketou_times", me) == 0 )
        {
                message_vision("$N��ͷ̫ƴ���ˡ�\n", me);
                set_temp("ketou_times", random(50), me);
                me->unconcious();
                return 1;
        }

        addn_temp("ketou_times", -1, me);

        message_vision("$N���������ظ������ͷ���ˡ��ˡ��ˡ�������\n", me);

        if ( random(100) == 37 
        && !present("bojuan", me)
        && query("book_count") >= 1)
        {
                addn("book_count", -1);
                ob=new("/clone/book/bojuan");
                if (ob->violate_unique()) {destruct(ob);return 1;}
                ob->move(me);
message("channel:rumor",MAG"��ҥ�ԡ�ĳ�ˣ�"+query("name", this_player())+"ȡ���˱�ڤ�񹦲�������\n"NOR,users());
                tell_object(me, "ͻȻ���㷢��С�������ϵ�һ�㱡�����Ѳ���Ȼ���ѣ�¶���������\n");
                tell_object(me, "�㼱æ�������˳�����\n");
        }

        return 1;

}

int valid_leave(object me, string dir)
{
        if( query_temp("ketou_times", me) >= 0)delete_temp("ketou_times", me);
        if( query_temp("marks/kneel", me))delete_temp("marks/kneel", me);
        return ::valid_leave();
}