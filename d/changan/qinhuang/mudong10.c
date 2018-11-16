//mudong.c
// This is a room made by Wsl.
#include <room.h>
inherit ROOM;
int do_use(string arg);
int do_pull(string arg);
int do_enter(string arg);
void create()
{
        set("short", "ĹѨ");
        set("long", @LONG
����Լ�������ܵ�ǽ�ϲ���������ѡ�
LONG );
        setup();
}
void init()
{
        add_action("do_use", "use");
        add_action("do_pull", "pull");
        add_action("do_enter", "enter");
}
int do_use(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg=="" ) return 0;
        if (!present("fire",me)) return 0;
        if( arg=="fire" ) {
                remove_call_out("cls");
                call_out("cls", 30, this_object());
             write(
"��ȡ������һ�Σ�����ǰȥ��ȼ�����е�һֻ��ѣ�Ҳ��֪��ʲô���أ�
��������ֻ���һһȼ�����������㷢����������ȥ�������޾�ͷ���ѵ�
���л�����\n");
        set("long", @LONG
����һƬ���ң����ֿ��ױ���ɢ���ڵ��ϣ������Ͽ��˸��ָ���
��ͼ����������ͨ�˴Ҳ��֪������ʲô���ذ�����
LONG
        );
    set("item_desc", ([
"����" : "�ڻ�ѵ������£���������ϸ�۲���Χ�ľ��󣬵�ʼ�ղ��ܷ���ʲô��������\n",
"���" : "�㿴�˿�����ǽ�ϵĻ�ѣ������ƺ�......\n",
]));
        set("exits", ([
                "north" : __DIR__"mudong"+random(10),
                "south" : __DIR__"mudong"+random(10),
                "east" : __DIR__"mudong"+random(10),
                "west" : __DIR__"mudong"+random(10),
        ]));
        set_temp("dian", 1, me);
        return 1;
       }
        return notify_fail("�����ȼʲô��\n");
}
int do_pull(string arg)
{
    string p;
    p=sprintf("%d",query("passwd1", this_player()));
    if( !arg || arg == "" )
    if( !query_temp("dian", this_player()) )
    {
        write("ʲô����\n");
        return 1;
    }
    if( arg == p )
    {
        message_vision("$Nֻ����һ��ض�ɽҡ��\n", this_player());
        message_vision("�𶯹���������µ�һ��ʯ�建�������˿�����\n", this_player());
        set_temp("la1", 1, this_player());
        remove_call_out("close");
        call_out("close", 5, this_player());
        return 1;
    }
    else
    {
        write("�����в�������Ӧ������ֻ�ɣ�����\n");
        if (random(6) != 4)
                {
            message_vision("$N���������е�һֻ��ѣ���ʱ����֪ʲô�ط�ͻȻ���һֻ������ֱ����������š�\n", this_player());
            message_vision("$N��æ������ȥ�������Ǳ������������ֱۡ�\n", this_player());
            set_temp("die_for", "��������", this_player());
            addn("qi", -30000, this_player());
            addn("eff_qi", -20000, this_player());
            return 1;
        }
        else
        {
            if( this_player()->query_skill("dodge",1)<1000 )
            message_vision("$N���������е�һֻ��ѣ���ʱ����֪ʲô�ط�ͻȻ���һֻ������ֱ����������š�\n", this_player());
            message_vision("$N����������������������ŶԴ�����......\n",this_player());
            set_temp("die_for", "��������", this_player());
            this_player()->die();
            return 1;
        }
    }
}
int do_enter(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg=="" ) return 0;
        if( !query_temp("la1", me))return 0;
        if( !query("passwd1", me))return 0;
        if( arg=="��" ) {
             message_vision("$Nսս���������˽�ȥ��\n",me);
        me->move("/d/changan/qinhuang/mumen.c");
        delete_temp("dian", me);
        delete("passwd1", me);
        }       
          return 1;
}
void close(object me)
{
        message("vision","��¡¡���������֮��ʯ���ֺ����ˡ�\n", this_object());
        delete_temp("la1", me);
}

void cls(object room)
{
        message("vision","��һ�������Ѿ�Ϩ���ˡ�\n", room);
        set("long", @LONG
����Լ�������ܵ�ǽ�ϲ���������ѡ�
LONG
);
        delete("item_desc");
        delete("exits", room);
}
