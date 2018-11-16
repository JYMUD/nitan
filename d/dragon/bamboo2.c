// room: well.c
// Jay 4/8/96

#include <ansi.h>
inherit ROOM;

int do_use(string arg);
int do_tui(string arg);

void create()
{
        set("short", "��");
        set("long",
"�������Ӻ�ï�ܣ����߼������������е��������ӵ����㡣��������\n"
"�ط�����������ʲô��\n"
);
        set("exits", ([
                "east" : __DIR__"bamboo",
        ]));
        set("no_clean_up", 0);
        set("no_magic", 1);
        setup();
}

void init()
{
        add_action("do_use", "use");
        add_action("do_tui", "tui");
}

int do_use(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("moonsoul", me))  return 0;
        if( arg=="moonsoul" ) {
             write(
             "���ͳ����е�"+HIC"����"NOR+"��"+HIC"����"NOR+"���������Ĺ�â���ұ����ƺ��е����ţ�Ҳ�����������(tui)һ�¡�\n"
             );
             set_temp("marks/��1", 1, this_player());
             return 1;
       }
}

int do_tui(string arg)
{
        object me;
        me = this_player();

        if( query_temp("marks/��1", me)){
            message("vision", me->name() + "һ���ӾͲ����ˡ�\n",
                    environment(me), ({me}) );
            me->move(__DIR__"moonroom");
            message("vision", me->name() + "���ҷ찵������˳�����\n",
                    environment(me), ({me}) );
            delete_temp("marks/��1", this_player());

            return 1;
        }
        else {
            write("������ʲô��?!\n");
            return 1;
        }
}
