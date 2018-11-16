inherit DEMONROOM;

void create()
{
        set("short", "��ľ��");
        set("long",@LONG
����һƬ��ľ�֡���û���뵽����һ���µ��Ͼ���������һƬ��
ľ��(bush)�����ɸе��ǳ��Ծ���ǰ�����û��·�����ܵ������г�
�����Ӳݡ�
LONG);

	set("exits", ([
	    "south" : __DIR__"haitan",
		"east"  : __DIR__"lin1.1", 
	]));

	set("item_desc", ([
	    "bush" : "��Ƭ��ľ��̫����,Ҫ���ȥ����ֻ�п���һ��·��(kan)��\n",
	]));
		
		set("n_time", 30); 
		set("n_npc", 1); 
                set("n_max_npc", 10);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/snake");

        set("outdoors", "shenlong");
        setup();
}

void init()
{
        add_action("do_kan", "kan");
}

int do_kan(string arg)
{
        object weapon;
        object me;

        if (arg != "bush")
                return notify_fail("��Ҫ��ʲô��\n" ) ;

        me = this_player();
	if( !objectp(weapon=query_temp("weapon", me)) )
		return notify_fail("�����������²��аɣ�\n");

        if( query("skill_type", weapon) != "blade" && 
            query("skill_type", weapon) != "sword" )
                return notify_fail(weapon->name() + "Ҳ��������������\n");

	message_vision("$N������У����Ź�ľ�Ծ���һ���ҿ���\n", me);

        if( query("neili", me)>100 )
        {
                set("exits/north", __DIR__"lin2");
                message_vision("$N�۵���������,���ڿ���һ��С·��\n", me);
                addn("neili", -50, me);
                remove_call_out("close");
                call_out("close", 20);
	} else	
	{
                message_vision("$N�۵���������,Ҳû����һ��·����\n", me);
                set("neili", 0, me);
	}
        return 1;
}

void close()
{
        message("vision", "��ľ�Խ�����£����,�����ָֻ���ԭ״��\n",
                this_object());
        delete("exits/north");
}
