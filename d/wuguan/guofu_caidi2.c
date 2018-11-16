#include <ansi.h>
inherit ROOM;

void create()
{
    	set("short", "�˵�");
        set("long", @LONG
�����ǿ�˵أ��˵����м��ڴ�ף�����ʢ����ˮ������
�˵ؿ������������ˣ����ò�����ĳ��ţ�����������Ϊȱˮ
̫���Ե�ʰɡ�
LONG);
        set("no_fight", 1);
        set("exits", ([
            	"east" : __DIR__"guofu_houyuan3",
        ]));
        set("objects", ([
           	__DIR__"npc/guanjia6" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_jiao", "jiao");
}

int do_jiao(string arg)
{      
        object me, weapon;
        int costj, costq;

        me = this_player();

        if( query_temp("mark/������", me) )
            	return notify_fail(CYN "��԰�������µ���ιιι������ȥ����������"
                                   "��������\n" NOR);

        if( query_temp("job_name", me) != "���˵�" )
            	return notify_fail(CYN "��԰���¶���ȵ���û����Ϲ����ʲô��\n" NOR);

        if (me->is_busy())
		return notify_fail("��������æ���أ�\n");

        if (me->is_fighting())
		return notify_fail("������ս���У��޷�ר�ĸɻ\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("id", weapon) != "shui piao" )
                return notify_fail(CYN "��԰���¼�Ц����������ʲô��Ҩˮ��ѽ����"
                                   "����\n" NOR);

        if (! arg || arg != "shui" )
		return notify_fail("��Ҫ��ʲô��\n");

        costj=random(query("con", me)/3)+1;
        costq=random(query("str", me)/3)+1;

        if( query("jing", me)<costj
	 || query("qi", me)<costq )
	{
              	message_vision(HIR "\n$N" HIR "�����������Ҩˮ�����һʧ���Խ��˸�"
                               "�\n" NOR, me);
              set("water", 600, 	me);
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

        message_vision(HIG "$N" HIG "��ư�Ӹ���Ҩ��ˮ���ڲ˵��ｽ��ˮ����\n" NOR, me);
        addn_temp("mark/��", 1, me);

        if ((int)me->query_skill("whip", 1) < 50
           && (int)me->query_skill("finger", 1) < 50
           && me->can_improve_skill("whip")
           && me->can_improve_skill("finger"))
	{
                write(HIC "���ڽ�ˮ�����жԱ޷���ָ����Щ��ᡣ\n" NOR);
                me->improve_skill("whip",(query("int", me)/6));
                me->improve_skill("finger",(query("int", me)/6));
        }
        return 1;
}
