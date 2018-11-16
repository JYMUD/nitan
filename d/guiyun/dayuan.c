// Room: /guiyun/qianyuan.c
// Date: Nov.18 1998 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "��Ժ");
        set("long", @LONG
�����ǹ���ׯ�Ĵ�Ժ������Ժ���൱�������ҿ�ǽ�����м����
����ƽ�������Ǽ��˵�ס������ǰ��������ľ��������紵������Ҷ��
�����¡���ľ��������һ�������
LONG );
        set("outdoors", "guiyun");
        set("no_clean_up", 0);
        set("valid_startroom", 1);
/*
������һ�԰׵�(diao)��ԭ���������һ���Ϊ������ӻص��ġ�
        set("item_desc", ([
                "diao" : "һ�԰׵���չ�����ɡ�������һ����ĵ��ӣ�\n"
                "����(ride)�Ϳ��Էɻ��һ�����\n",
        ]));
*/
        set("exits", ([
                "out"   : __DIR__"damen",
                "west"  : __DIR__"qianting",
        ]));
        set("coor/x", 280);
        set("coor/y", -830);
        set("coor/z", 0);
        setup();
        "/clone/board/guiyun_b"->foo();
}

void init()
{
//        add_action("do_ride", "ride");
}
int do_ride ( )
{
        mapping myfam;
        object room;
        object ob = this_player () ;
        myfam=query("family", ob);
        if(!myfam || myfam["family_name"] != "�һ���")
        {
                message_vision("$NһԾ������˰׵�ֻ���׵����쳤ণ�ͻȻ��Ȼһ��......\n"
                HIR "���$Nˤ�˸��������ף�\n" NOR
                "�����׵��$N��������Ȥ����ֻ��ʶ�һ����ĵ��ӡ�\n" , ob ) ;
                ob -> receive_damage ("qi",50) ;
                ob -> receive_wound  ("qi",50) ;
                return 1;
        }
        if( !(room = find_object("/d/taohua/lantian")) )
                room = load_object("/d/taohua/lantian");
        if( room = find_object("/d/taohua/lantian") ) 
        if( query_temp("tian_trigger", room) == 1 )
        {
                message_vision("���ڰ׵���æ��,���һ���ٳ���!\n" , ob) ;
                return 1 ;
        }
        set_temp("tian_trigger", 1, room);
        message_vision("$NһԾ������˰׵�ֻ���׵����쳤ণ�ͻȻչ��߷ɡ�\n\n"
                "����һ��һ�����ν�����С������������\n" , ob );
        ob->move(room) ;
        tell_object(ob, CYN  "\n�㲻�ϵط�ѽ�ɣ���ˮǧɽ����Ʈ�� ......\n\n" NOR ) ;
        call_out("taohua", 3 , ob );
        delete_temp("tian_trigger", room);
        return 1 ;
}
void taohua( object ob )
{
        tell_object(ob, "�����ڷɵ����һ�ɽׯ���׵�����������\n\n"  ) ;
        ob -> move ("/d/taohua/damen") ; 
}
void reset()
{
        object room;

        ::reset();
        if( room = find_object("/d/taohua/lantian") )
                delete("tian_trigger", room);
}