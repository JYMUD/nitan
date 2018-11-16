// mishi2.c ����
// Java Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����ǹ�Ĺ�е����ң������ܲ�͸�磬��ֻ�ܽ���ǽ�ϻ谵�ĵƹ�
����ǿ�ֱ淽��ǽ�����������ʯ���������ģ��Ӻϵ�������������
���Դ����ҳ�һ˿��϶��ǽ��(wall)�������һЩ���֡�
LONG        );
        set("exits", ([
                "east"  : __DIR__"mishi3",
                "west"  : __FILE__,
                "north" : __FILE__,
                "south" : __DIR__"mishi1",
                "up" : __DIR__"houting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3200);
        set("coor/y", 30);
        set("coor/z", 100);
        setup();
}


void init()
{
        add_action("do_think", "think");
}

int do_think(string arg)
{
        object here, me = this_player();
        int add;

        if (! here = find_object(__DIR__"mishi2"))
                here = load_object(__DIR__"mishi2");

        if( query("special_skill/clever", me) )
                add = me->query_int() * 4;
        else
                add = me->query_int() * 3;

        if (! living(me) || arg != "wall")
                return notify_fail("��Ҫ����ʲô��\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("��������æ���ء�\n");

        if ((int)me->query_skill("sword", 1) < 30)
                return notify_fail("����ڹ���Ϊ�������޷�����ǽ"
                                   "�ϵ��ķ���\n");

        if( !query("can_learn/yunv-xinfa/wall", me) )
                return notify_fail("���о��˰��죬ȴ����ǽ���ϵ��ķ�"
                                   "��������\n");

        if ((int)me->query_skill("yunv-xinfa", 1) < 180)
                return notify_fail("�㷢��ǽ�������ص��ķ�������£���"
                                   "��һʱ��������\n");

        if ((int)me->query_skill("yunv-xinfa", 1) > 240)
                return notify_fail("�㷢��ǽ�������ص��ķ����ڷ�ǳ����"
                                   "���޷���ᵽ�κζ�����\n");

        if( query("jing", me)<35 )
                return notify_fail("�����ھ��񲻼ã�����ƣ�룬������Ϣ"
                                   "һ��ɡ�\n");

        me->receive_damage("jing", 30);

        if (me->can_improve_skill("yunv-xinfa"))
                me->improve_skill("yunv-xinfa", add);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "�۾�����Ĳ���ǽ�������ص��ķ���"
                       "��������\n" NOR, me);
        write(HIC "��ԡ���Ů�ķ��������µ�����\n" NOR);
        return 1;
}

