// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����֮��");
        set("long", @LONG
����������ֻ�з紵���Σ�������ɣ����Ӳ��죬ע��Ⱥɽ����
�˲�����Ȼ����˼��֮���飡��ǰ����ֻ��һ��ܴ�ı��ڣ����پ�
�£�����ڱ��漫��⻬����ͬ����һ�㣬ɢ��������Ĺ�â������
�����ͱ��絶�����ƾ���ӿ������ס�
LONG );
        set("exits", ([
                "down" : __DIR__"kunlun5",
        ]));

        set("outdoors", "kunlun");
        setup();
}

void init()
{
        add_action("do_throw", "throw");
        add_action("do_enter", "enter");
}

int do_throw(string arg)
{
        object me, ob;
        
        me = this_player();
        if( !objectp( ob = present("contract", me) ) ||
            query("owner", ob) != query("id", me) )
                return 0;
        
        if( !query("reborn_offer", me) || query("reborn_offer", me) != "finish" )
                return 0;
                         
        if( !arg || arg != "contract" ) 
                return notify_fail("��Ҫ��ʲô�����Ǳ��ڣ�\n");      
                    
        message_vision( HIW "$N" HIW "�����Ϲ��������(Contract)�����Ǳ��ڣ�������û�����С�������ʧ������\n"
                        HIW "ֻ������ƽ���Ĵ����������ࡢ���󽥽�͸��������������ˮ�������ģ����\n"
                        HIW "ԭ��������ͨ��������ͨ����" HIR "�����ؾ���" HIW "(enter mirror)��\n" NOR, me );
        set_temp("throw_contract", 1, me);
        destruct(ob);
        return 1; 
}

int do_enter(string arg)
{
        object me, *inv;
        int i;
        
        me = this_player();
        if( !query_temp("throw_contract", me) )
                return 0;
                
        if( !arg || arg != "mirror" ) 
                return notify_fail("����Ҫȥ���\n");      
        
        inv = deep_inventory(me);
        for( i=sizeof(inv)-1; i>=0; i-- ) {
                if( objectp(inv[i]) && inv[i]->is_character() ) {
                        tell_object(me, "�㲻���Խ�������һ���NPC(��������)�������ؾ��С�\n");
                        return 0;
                }
        }
        
        message_vision( HIW "$N" HIW "�����ٲ����������������ؾ��С�\n" NOR, me );
        tell_object(me, HIM "ֻ�����ܾ�����ʹ������������ɾ����ð��κ���Żع����߳������������ڤ�硣\n" NOR);
        delete_temp("throw_contract", me);
        me->move("/d/death/youmingjie");
        set("startroom", "/d/death/youmingjie", me);
        message("vision",HBRED"��ת���������ظ���"+query("name", me)+"("+query("id", me)+")"
                HBRED "������ڤ�磬����ս��ڤ�ظ����飬��ȡת����Ե��\n" NOR, users());
        return 1;
}
