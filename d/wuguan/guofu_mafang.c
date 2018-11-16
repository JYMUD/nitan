inherit ROOM;
#include <ansi.h>

void create()
{
    set("short", "��");
    set("long", @LONG
�����ǹ����ڵ���������������ģ������˼�ʮƥ
���㿴��ȥ�������϶������ˣ����ϴϴ�ˣ������Ա���
��ˮ�أ�������Щ��ˮ��
LONG);
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"guofu_houyuan2",
        ]));
        set("objects", ([
           	__DIR__"npc/guanjia3" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_sao", "sao");        
}

int do_sao(string arg)
{     
        object me, weapon;
        int costj, costq;

        me = this_player();

        if( query_temp("mark/ɨ����", me) )
            	return notify_fail(CYN "���������µ���ιιι������ȥ����������"
                                   "��������\n" NOR);

        if( query_temp("job_name", me) != "��ɨ��" )
            	return notify_fail(CYN "�����¶���ȵ���û����Ϲ����ʲô��\n" NOR);

        if (me->is_busy())
		return notify_fail("��������æ���أ�\n");

        if (me->is_fighting())
		return notify_fail("������ս���У��޷�ר�ĸɻ\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("id", weapon) != "sao zhou" )
                return notify_fail(CYN "�����¼�Ц������������ʲô����ɨѽ����"
                                   "����\n" NOR);

        if (! arg || arg != "mafang")
		return notify_fail("��Ҫ��ɨʲô��\n");

        costj=random(query("con", me)/3)+1;
        costq=random(query("str", me)/3)+1;

        if( query("jing", me)<costj
	 || query("qi", me)<costq )
	{
             	message_vision(HIR "\n$N" HIR "��һ���������С�Ļ����ڷ�����"
                               "��һ�����ࡣ\n" NOR, me);
             addn("food", 100, 	me);
             	me->unconcious();
             	return 1;
        }
        
        me->receive_damage("jing", costj);
        me->receive_damage("qi", costq);       
        me->start_busy(1 + random(2));

        if (! (int)me->query_condition("wuguan_job")
            && query_temp("mark/ɨ", me)>10+random(10 )
           && present("mafang guanshi", environment(me)))
	{
              set_temp("mark/ɨ����", 1, 	me);
              	message_vision(CYN "\n�����¶�$N" CYN "˵���ɵĲ������ˣ����"
                               "��ȥ��Ү�ɴ�ү����(" HIY "fuming" NOR + CYN ")��"
                               "��\n" NOR, me);
              	return 1;
        }

        message_vision(HIM "$N" HIM "��ʼ��ɨ������ζʹ�㲻�ɱս��˺�����\n" NOR, me);
        addn_temp("mark/ɨ", 1, me);

        if ((int)me->query_skill("claw", 1) < 50
           && (int)me->query_skill("club", 1) < 50
           && me->can_improve_skill("claw")
           && me->can_improve_skill("club"))
	{
                write(HIC "����ɨ�ع����ж�צ����������Щ��ᡣ\n" NOR);
                me->improve_skill("claw",(query("int", me)/6));
                me->improve_skill("club",(query("int", me)/6));
        }
        return 1;
}
