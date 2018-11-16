// Room: /d/xingxiu/shanbi.c
// Last Modified by winder on Apr. 25 2001

inherit ROOM;

void create()
{
        set("short", "ɽ��");
        set("long", @LONG
һ���ݲ���ɽ�����˹����������᫵�С·���������޵���������
ͷ��ɡ�����������������������ƺư��﷽Բ�����޺�������ɽ��
�ϣ��������޵��������ҳ��ĿӰ�(ao)��
LONG
        );
        set("exits", ([
                "southdown" : __DIR__"xiaolu",
        ]));
        set ("item_desc", ([
                "ao" : "�����ù���ײ��(za)ɽ��(bi)���µĺۼ���\n"
        ])) ;
        set("objects", ([
                __DIR__"npc/gushou"  : 1,
        ]));
        set("outdoors", "xingxiu");
        set("coor/x", -49900);
        set("coor/y", 20300);
        set("coor/z", 100);
        setup();
}

void init()
{
        add_action("do_za", "za");
}

int do_za(string arg)
{
        object  weapon, me = this_player();
        int ging_cost, qi_cost, jingli_cost;
        weapon=query_temp("weapon", me);
        ging_cost=150/query("int", me);
        qi_cost=200/query("con", me);
 
        if (!living(me)) return 0;
        if ( arg != "bi" ) return notify_fail("��Ҫײ��ʲ�᣿\n");
        if (!weapon) return notify_fail("����ʲô��ɽ����������\n");  
        if( query("skill_type", weapon) == "staff" )
                if ((int)me->query_skill("staff", 1) >= 120) 
                        return notify_fail("���Ѿ�������������ѹ����ˡ�\n");  
        if( query("skill_type", weapon) == "hammer" )
                if ((int)me->query_skill("hammer", 1) >= 120) 
                        return notify_fail("���Ѿ�������������ѹ����ˡ�\n");  
        if( random(query("kar", me))<3 )
        {
                message_vision("$Nһ��С���ҵ��Լ����ϣ�ʹ�����˹�ȥ��\n",me);
                me->unconcious();
                return 1;
        }
        if( (query("jing", me)<ging_cost) || (query("qi", me)<qi_cost) )
        {
                message_vision("$N�͵�����ɽ���ϣ�����������ȣ�\n", me);
                me->unconcious();
                return 1;
        }
        message_vision("$Nʹ��ײ��ɽ�ڣ���ɽ�����ҳ�һ���Ӱ���\n", me);
        if( query("skill_type", weapon) == "staff" )
                me->improve_skill("staff", me->query_skill("staff", 1));
        else if( query("skill_type", weapon) == "hammer" )
        me->improve_skill("hammer", me->query_skill("hammer", 1));
        me->receive_damage("jing", ging_cost );
        me->receive_damage("qi", qi_cost );
        return 1;     
}