inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "�����");
        set("long",
"[1;32m��ˮ�峺͸������ʱ���Կ�����β������ˮ�档��ˮ��ͷ��\n"
"һ�����ٲ�����������������ٲ���ɽ��ֱ����£������ĺ����������\n"
"��һ���ʯ����д�����������������һҶ���ۡ�\n"
);
        set("exits", ([ 
  "north" : __DIR__"village",
  "east" : __DIR__"lake1",
]));
        set("resource/water",1);
         set("no_magic", 1);
        setup();
}
void init()
{
    add_action("do_yell", "yell");
}

void check_trigger()
{
    object room;

    if(!query("exits/enter") ) {
        if( !(room = find_object(__DIR__"duchuan")) )
            room = load_object(__DIR__"duchuan");
        if( room = find_object(__DIR__"duchuan") ) {
            if( query("yell_trigger", room) == 0){
                set("yell_trigger", 1, room);
                set("exits/enter", __DIR__"duchuan");
                set("exits/out", __FILE__, room);
                message("vision", "һҶ���ۻ�����ʻ�˹�����������һ��̤��"
                    "����ϵ̰����Ա�˿�\n���¡�\n", this_object() );
                message("vision", "������һ��̤�Ű���ϵ̰����γ�һ������"
                    "�Ľ��ݡ�\n", room);
                remove_call_out("on_board");
                call_out("on_board", 15);
            }
            else
                message("vision", "ֻ���ú��������������������"
                    "�����æ���š�����\n",this_object() );
        }
        else
            message("vision", "ERROR: boat not found\n", this_object() );
    }
    else 
        message("vision", "����һֻ�ɴ��ϵ�������˵�������������أ������ɡ�\n",
            this_object() );
}
void on_board()
{
    object room;

    if( !query("exits/enter") ) return;

    message("vision", "������̤�Ű��������������һ�㣬���������ʻȥ��\n",
        this_object() );

    if( room = find_object(__DIR__"duchuan") )
    {
        delete("exits/out", room);
        message("vision", "������̤�Ű���������˵��һ��������ඡ���"
            "���һ�㣬������\n����ʻȥ��\n", room );
    }
    delete("exits/enter");

    remove_call_out("arrive");
    call_out("arrive", 20);
}
void arrive()
{
    object room;
    if( room = find_object(__DIR__"duchuan") )
    {
        set("exits/out", __DIR__"spirit9", room);
        message("vision", "����˵���������ϰ��ɡ����漴��һ��̤�Ű�"
            "���ϵ̰���\n",room );
    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if( room = find_object(__DIR__"duchuan") ) {
        delete("exits/out", room);
        message("vision","������̤�Ű����������ѱ���ʻ����ġ�\n", room);
        delete("yell_trigger", room);
    }
}
int do_yell(string arg)
{
    string dir;

    if( !arg || arg=="" ) return 0;

    if( arg=="boat" ) arg = "����";
    if( query("age", this_player())<16 )
        message_vision("$Nʹ�����̵���������һ������" + arg + "��\n",
            this_player());
    else if( query("neili", this_player())>500 )
        message_vision("$N���˿�����һ����" + arg + "������������ƽ�͵�ԶԶ��"
            "�˳�ȥ��\n", this_player());
    else
        message_vision("$N������������Хһ������" + arg + "����\n",
            this_player());
    if( arg=="����")
    { 
     if( !query_temp("m_success/����", this_player()))return notify_fail("������ô���ģ���ʦץ�ģ��ǿɲ��á�\n");

     if( !query_temp("m_success/��Ӱ", this_player()))return notify_fail("��û�������⿪��ӡ�����ܶ����ȥ�ء�\n");

     if( !query_temp("m_success/����", this_player()))return notify_fail("��μ��������𣿻�����û����ɱ�����������ǲ��еġ�\n");
        check_trigger();
        return 1;
    }
    else
        message_vision("������ԶԶ����һ���������" + arg +
            "��������\n", this_player());
    return 1;
}

void reset()
{
    object room;

    ::reset();
    if( room = find_object(__DIR__"duchuan") )
        delete("yell_trigger", room);
}

