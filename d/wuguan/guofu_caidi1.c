#include <ansi.h>
inherit ROOM;

void create()
{
    	set("short", "�˵�");
    	set("long", @LONG
�����ǿ�˵أ����ڳ��ڵò������õ��չˣ��˵����Ӳ�
�������ֵĲ˶����Ʋ��ã�����ģ��ض����ˡ�
LONG);
        set("no_fight", 1);
        set("exits", ([
             	"west" : __DIR__"guofu_houyuan3",
        ]));
        set("objects", ([
           	__DIR__"npc/guanjia5" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_chu", "chu");
}

int do_chu(string arg)
{
        object me, weapon;
        int costj, costq;

        me = this_player();

        if( query_temp("mark/������", me) )
            	return notify_fail(CYN "��԰�������µ���ιιι������ȥ����������"
                                   "��������\n" NOR);

        if( query_temp("job_name", me) != "����" )
            	return notify_fail(CYN "��԰���¶���ȵ���û����Ϲ����ʲô��\n" NOR);

        if (me->is_busy())
		return notify_fail("��������æ���أ�\n");

        if (me->is_fighting())
		return notify_fail("������ս���У��޷�ר�ĸɻ\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("id", weapon) != "chu tou" )
                return notify_fail(CYN "��԰���¼�Ц������������ʲô������ѽ����"
                                   "����\n" NOR);

        if (! arg || arg != "cao" )
		return notify_fail("��Ҫ��ʲô��\n");

        costj=random(query("con", me)/3)+1;
        costq=random(query("str", me)/3)+1;

        if( query("jing", me)<costj
	 || query("qi", me)<costq )
	{
        	message_vision(HIR "\n$N" HIR "���ų��ţ������С����һ��������"
                               "���Լ��Ľ��ϡ�\n" NOR, me);
                me->unconcious();
                return 1;
        }

        me->receive_damage("jing", costj);
        me->receive_damage("qi", costq);       
        me->start_busy(1 + random(2));

        if (! (int)me->query_condition("wuguan_job")
            && query_temp("mark/��", me)>10+(random(10) )
           && present("caiyuan guanshi", environment(me)))
	{
                set_temp("mark/������", 1, me);
                message_vision(CYN "\n��԰���¶�$N" CYN "˵���ɵĲ������ˣ����"
                               "��ȥ��Ү�ɴ�ү����(" HIY "fuming" NOR + CYN ")��"
                               "��\n" NOR, me);
                return 1;
        }

        message_vision(HIY "$N" HIY "�����ͷ�����ŵ��ϵ��Ӳݳ���������\n" NOR, me);
        addn_temp("mark/��", 1, me);

        if ((int)me->query_skill("staff", 1) < 50
           && (int)me->query_skill("cuff", 1) < 50
           && me->can_improve_skill("staff")
           && me->can_improve_skill("cuff"))
	{  
                write(HIC "���ڳ��ݹ����ж����ȷ���ȭ����Щ��ᡣ\n" NOR);
                me->improve_skill("staff",(query("int", me)/6));
                me->improve_skill("cuff",(query("int", me)/6));
        }
        return 1;
}
