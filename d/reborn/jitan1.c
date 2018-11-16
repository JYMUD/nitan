// This program is a part of NITAN MudLIB
// Jitan1.c

#include <ansi.h>
inherit ROOM;

void start_worship(object who, int n);

void create()
{
        set("short", "̩ɽ��̳");
        set("long", @LONG
����֮����̩ɽ��̳������̳������ͭ����¯һ�������������
�����������������������㣬����ٻ���̩ɽ���������֡���
LONG );
        set("exits", ([
                "down" : "/d/taishan/dongtian",
        ]));
        set("objects", ([
                __DIR__"obj/xianglu" : 1,
        ]));
        set("outdoors", "taishan");
        set("worship", 1);        
        setup();
}

void init()
{
        add_action("do_put", "put");
}

int do_put(string arg)
{
        object me, ob, obj, env;
        string what, where;
        int n;
        
        me = this_player();
        env = environment(me);
        if( !objectp(ob = present("xiang lu", env)) )
                return 0;    
                
        if( !arg || sscanf(arg, "%s in %s", what, where) != 2)
                return 0;       
                
        if( where == "xiang lu" ) {
                if( what != "magic xiang" ) {
                        tell_object(me, "��ͭ����¯��ɲ������Ӷ�����\n");
                        return 1;
                }  
                             
                if( !objectp(obj = present(what, me)) &&
                    !objectp(obj = present(what, env)) ) {
                        tell_object(me, "�����Ϻ͸���û��������������\n");
                        return 1;
                }

                if( present("taishan fujun", this_object()) ) {
                        tell_object(me, "̩ɽ�����Ѿ�������ǰ�ˣ����û�������Ҫ�˰ɡ�\n");
                        return 1;
                }
                                        
                message_vision( MAG "$N" MAG "����������ͭ����¯���������ζ���������ܡ�\n" NOR, me);
                obj->move(ob);
                set("no_get", 1, obj);
                obj->start_borrowing();  
                n=query("worship", env);
                if ( n ) start_worship(me, n);
                return 1;
        }
        return 0;
}

void start_worship(object who, int n)
{
        object ob;

        if( !objectp( ob = present("contract", who) ) ||
            query("owner", ob) != query("id", who) )
                return;
        
        ob = new("/d/reborn/npc/fujun" + n);
        set("worship",query("id",  who), ob);
        ob->move(this_object());
        ob->start_borrowing(); 
        ob->command("say ���η����ˣ�������������������");
}