// room: mishi.c

#include <ansi.h>
#include <room.h>

inherit ROOM;
int do_press();
int valid_leave();
string look_hua();
string look_liang();

void create()
{
        set("short","����");
        set("long", @LONG
����һ��������С���䣬ǽ�ϵ�שͷ(zhuan) �Ѿ��������ˣ���
��(liang) Ҳ�Ѿ����ò�����ǽ�Ŵ���һ�������ӣ���������˳�����
���״�������һ����(hua)�����䴦б���ż����ɲ�
LONG );
        set("exits", ([
                "out" : __DIR__"midao",
        ]));
        set("item_desc", ([
                "hua"     : (: look_hua :),
                "liang"   : (: look_liang :),
                "zhuan": "שͷ�õ�һ����Ϳ��\n",
                //"liang": "�������Ϻõ��ľ���ģ���ϧ���̫�ã��Ѿ����õò��������ˡ�\n",
        ]) );
        set("objects", ([
                __DIR__"obj/tiexiang" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", 1820);
        set("coor/y", -6312);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

string look_hua()
{
        object me = this_player();

        if( query("score", me)<1000 )
                return HIR "\nһ���¾ɵĻ����������Ǵ�Ħ���棬û��ʲô��ͬ��\n" NOR;

        if( query("score", me)<3000 )
                return HIR "\nһ���¾ɵĻ������д�Ħ���������ո����������鰲�͡�\n" NOR;

        set_temp("marks/��1", 1, me);
        return HIR "\nһ���¾ɵĻ������д�Ħ���������ո���������ָ����(liang)����\n" NOR;
}

string look_liang()
{
        object me = this_player();

        if( !query_temp("marks/��1", me) )
                return "��Ҫ��ʲô��\n";

        if (query("move"))
                return WHT "һ���ľ���ķ�����������ո�µĹκۣ��ƺ�����ǰ�����˶�����\n" NOR;

        set_temp("marks/��2", 1, me);
        return WHT "һ���ľ���ķ�������ϧ���̫�ã��Ѿ����õò��������ˡ�\n" NOR;
}

int do_jump(string arg)
{
        object me, ob;
        me = this_player();

        if( !arg || arg=="" )
                return 0;
        if( arg=="liang")
        {
            if( query_temp("marks/��1", me)){
                if (me->query_dex()<20)
                    write("����ͼ���Ϸ������������������ݣ�ֻ�����ա�\n");
                else {
                    write("������Ծ���˷�����\n");
                    message("vision",
                             me->name() + "һ����Ծ���˷�����\n",
                             environment(me), ({me}) );
                    set("move", 1);
                    me->move(__DIR__"liang");
                    message("vision",
                             me->name() + "������Ծ��������\n",
                             environment(me), ({me}) );
                }
                return 1;
           }

           if( query_temp("marks/��2", me) )
           {
                if (me->query_dex() < 40)
                        write(HIC "����ͼ���Ϸ������������������ݣ�ֻ�����ա�\n" NOR);
                else
                {
                        foreach (ob in deep_inventory(me)) if (ob->is_character())
                        {
                                ob->move(environment(me));
                                message_vision("\n$N��" + ob->name() + "�ӱ��Ϸ�������"
                                               "�����ڵ��ϡ�\n\n" NOR, me);
                        }

                        message("vision", HIY "ֻ��" + me->name() + HIY "һ����Ծ���˷�"
                                          "����\n" NOR, environment(me), me);
                        set("move", 1);
                        write(HIY "\n����������һԾ�������˷�����\n\n" NOR);
                        me->move(__DIR__"liang");
                        message("vision", HIY "ֻ��" + me->name() + HIY "������Ĳ�Ծ"
                                          "��������\n" NOR, environment(me), me);
                }
                return 1;
            }
        }
}

int valid_leave(object me, string dir)
{
        delete_temp("marks/��1", me);
        delete_temp("marks/��2", me);
        delete_temp("marks/��1", me);
        return ::valid_leave(me, dir);
}