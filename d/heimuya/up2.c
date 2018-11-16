// Room: carol/heimuya

#include <ansi.h>
inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();
void reset();
int do_insert(string arg);

void create()
{
        set("short", "����");
        set("long", @LONG
��һ�����͵����������������ǰ�������Ϸ·�������ɫ�Ľ�����
���������ƣ����������������ִ���һ������(rope)������ȥ������
�����»�ͨ��Ϣ�Ĺ��ߡ������������ƺ���Լ��һ������(basket)��
���µ�ǽ���ƺ���һ��ϻ��(xiazi)��
LONG );

    set("exits", ([
        "westdown" : __DIR__"up1",
    ]));
    set("item_desc", ([
        "basket": "����һ����������������Щ�Ź֡�\n",
        "rope"  : "���Ӿ������ӣ����������ϵĹ��ߡ�\n",
        "xiazi" : "����һ��ϻ�ӣ���������һ�����أ�ϻ�ӵĲ�����һ����ס�\n",
    ]));
    set("no_clean_up", 0);
    setup();
}

void init()
{
    add_action("do_insert", "insert");
}

void check_trigger()
{
    object room;

    if(!query("exits/enter") ) {
        if( !(room = find_object(__DIR__"basket")) )
            room = load_object(__DIR__"basket");
        if( room = find_object(__DIR__"basket") ) {
            if( query("insert_trigger", room) == 0){
                set("insert_trigger", 1, room);
                set("exits/enter", __DIR__"basket");
                set("exits/out", __FILE__, room);
                message("vision", "���ȡ���һ���������е������ѱ��۶ϣ�ֻ��һ��"
                        "����(basket)����������㲻��һ����\n", this_object() );
                set("item_desc", ([
                    "basket" : "����һ���������Ǵ�˵�еĽ�ͨ���ߡ�\n",
                ]));
                
                remove_call_out("on_board");
                call_out("on_board", 15);
            }
            else
                message("vision", "��������õ��²�����\n",this_object() );
        }
        else
            message("vision", "ERROR: basket not found\n", this_object() );
    }
}

void on_board()
{
    object room, me = this_player();

    if( !query("exits/enter") ) return;
    tell_object(me, HIG"ֻ�������������ϣ������������ã�\n"
                "���ƺ�������һ���˼��ɾ����졣\n"NOR);

    if( room = find_object(__DIR__"basket") )
    {
        delete("exits/out", room);
    }
    delete("exits/enter");
    remove_call_out("arrive");
    call_out("arrive",20);
}

void arrive()
{
    object room;
    if( room = find_object(__DIR__"basket") )
    {
        set("exits/out", __DIR__"up3", room);
        message("vision", "���һ�������ƺ�һ�´����ϵ��˵��ϡ�\n",room );
    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if( room = find_object(__DIR__"basket") ) {
        delete("exits/out", room);
        delete("insert_trigger", room);
    }
}

int do_insert(string arg)
{
    string dir;
    object ob;
    object me;

    me=this_player();

    if( !arg || arg=="" ) return 0;
    if( arg=="��" ) arg = "card2";   
    if( arg=="card2")
    {
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("������û������������\n");

        if( !query_temp("mark/cards", me) )
                set_temp("mark/cards", 1, me);

        if( query_temp("mark/cards", me) == 4 )
        {
                delete_temp("mark/cards", me);
                destruct(ob);
                check_trigger();
        }
        else    {
                addn_temp("mark/cards", 1, me);
                message("vision", "���һ�����㿴����������һ�ڡ�\n",me );
        }
    }
    else
    {
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("������û������������\n");
        else    return notify_fail(ob->name() + "�������ײ��ϣ���ôҲ�岻��ȥ��\n");
    }
    return 1;
}
