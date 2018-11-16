inherit ROOM;

void create()
{
        set("short", "��������");
        set("long", @LONG
��˵�������ºó�����û�뵽�����ϸ����졣��ô������治��
Ϊǧ����ľ����������Ҷ��ï������̧ͷ���Ͽ���ʱ���ƺ��и�Ӱ��
����֮���ƶ�������Ҳ���Ƿ紵������ɵĴ����
LONG
        );

        set("exits", ([
                "down": __DIR__"tree",
                "east"  : "/clone/game/mjroom",
                "west"  : "/clone/game/changan_dufang",
        ]));
        
        set("no_fight", 1);

        setup();
}

void init()
{
        add_action("do_jump","climb");
}

int do_jump(string arg)
{
        object me;
        
        me = this_player();
        if( !arg || arg != "down") 
                return notify_fail("��Ҫ���ĸ���������\n");

        if( query("gender", me) != "Ů��" )
                message("vision",
                        me->name() + "���������ץס���ɣ�ƨ��һŤһŤ��������ȥ��\n",
                        environment(me), ({me}) );
        else 
        if( query("age", me)<40 && query("per", me)>24 )
                message("vision",
                        me->name() + "�����Ӱ��������Ʈȥ��ת˲���š�\n",
                        environment(me), ({me}) );
        else 
                message("vision",
                        me->name() + "սս������ץס����������ȥ��\n",    environment(me), ({me}) );
        
        me->move(__DIR__"tree");
     
        if( query("gender", me) != "Ů��" )
                message("vision",
                        me->name() + "��������ش���������������\n",
                        environment(me), ({me}) );
        else 
        if( query("age", me)<40 && query("per", me)>24 )
                message("vision","һ������������㶨��һ����"+
                        me->name() + "�Ѿ���������������ǰ��\n",
                        environment(me), ({me}) );   
          
        else 
                message("vision", me->name() + "սս�����ش���������������\n", 
                        environment(me), ({me}) );   
        
        return 1;
}   

int valid_leave(object me, string dir)
{
        if ( dir=="down" && !wizardp(me))
                return notify_fail("����û��ֱ���ߣ�������ֻ����(climb)��ȥ��\n");

        return 1;
}
