// /d/xiakedao/shishi24.c ���͵� ʯ��24

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
������谵��ֻ������������ľ������ϥ���ڽ���֮�ϣ����
ʯ��(wall)�������˼����ʯ������ɽ�������ȴ�����ߴ����
���½����ˡ����л�������������Ķ�����֮�ࡣ
LONG );
        set("exits", ([
                "east" : __DIR__"shihole6",
        ]));
        set("item_desc", ([
                "wall" : @WALL
ǽ�����Ϸ����š�����̫�������������֡��ֵ��·��̵�����������
������ģ���ǧ�������������������룬����������ֱ��б����
�µĴ�Ƭ�������һ���ѷִ���ίʵ���Ա��ϡ�
WALL
        ]));
        set("objects", ([
                CLASS_D("xiakedao") + "/long" : 1,
                CLASS_D("xiakedao") + "/mu"   : 1,
        ]));
        set("no_fight", 1);
        set("coor/x", -3100);
        set("coor/y", -25600);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_study", "think");
        add_action("do_study", "study");
        add_action("do_canwu", "canwu");
}

int do_canwu(string msg)
{
        object me = this_player();
        string where, witch;

        if (! msg) return notify_fail("ʲô��\n");

        if (sscanf(msg, "%s from %s", witch, where) != 2)
                return notify_fail("��ʲô��\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if (me->is_fighting())
                return notify_fail("����ս��Ŷ����С�ģ����ˣ�����\n");

        if (witch != "����̫����")
                return notify_fail("�������ʲô��\n");

        if (where != "wall")
                return notify_fail("����ûʲô�������İ���\n");

        if (me->query_skill("literate", 1)
         || query("learned_literate", me) )
                return notify_fail("�����ʯ�����˰���Ҳû����ʲô��\n");

        if ((int)me->query_skill("force", 1) < 340)
                return notify_fail("����ڹ���Ϊ�������޷���ͨʯ���ϵľ�ѧ��\n");

        if( query("max_neili", me)<10000 )
                return notify_fail("���������Ϊ���㣬�޷���ͨʯ���ϵľ�ѧ��\n");

        if( query("jing", me)<100 )
                return notify_fail("��ľ����޷����У��޷�����ʯ���ϵľ�ѧ��\n");

        if (me->query_skill("taixuan-gong", 1) < 340)
                return notify_fail("���̫������֪ʵ�����ޣ��޷�����ʯ���ϵľ�ѧ��\n");

        if( query("can_perform/taixuan-gong/jing", me) )
                return notify_fail("�����ѧ�㲻���Ѿ�������\n");

        me->receive_damage("jing", 95);

        me->start_busy(2 + random(4));

        if (random(50) == 1 || wizardp(me))
        {
                addn("taixuan_perform/jing/count", 1, me);

                if( query("taixuan_perform/jing/count", me) >= 300 )
                {
                        write(HIM "��Ȼ�䣬��һ����Х�����л�Ȼ��ͨ���������ǡ�\n" NOR);
                        write(HIC "������ͨ���˾�ѧ������̫��������\n" NOR);

                        set("can_perform/taixuan-gong/jing", 1, me);
                        delete("taixuan_perform/jing/count", me);

                        if (me->can_improve_skill("force"))
                                me->improve_skill("force", 1500000);
                        if (me->can_improve_skill("taixuan-gong"))
                                me->improve_skill("taixuan-gong", 1500000);
                        if (me->can_improve_skill("martial-cognize"))
                                me->improve_skill("martial-cognize", 1500000);

                        return 1;
                }

                write(HIC "��ԡ�����̫���������������µ���ʶ������������಻��֮����\n" NOR);
                me->start_busy(2 + random(6));
                return 1;
        }

        else return notify_fail("����ͼ��ʯ�����о��йء�" + witch + "�������ݣ���ȴûʲôЧ����\n");

}

int do_study(string arg)
{
        object me;
        int lvl;

        if (arg != "wall")
                return notify_fail("�����о�ʲô��\n");

        me = this_player();
        if( query("combat_exp", me)<500000 )
        {
                write("�㿴�˰��죬ֻ���Լ�ʵս����̫ǳ�����޷���������ĸ���֪ʶ��\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("��������æ��û���о������ʫ�䡣\n");
                return 1;
        }

        me->receive_damage("jing", 15);
        me->start_busy(1);

        lvl = me->query_skill("literate", 1);
        if (lvl >= 200)
                write("�㿴�˰��죬��������ʫд�ĺܺã������ƺ�ûʲô�ر�֮����\n");
        else
        if (lvl >= 100)
                write("������������ʫ����Ԣ�⣬���ɵľ��Ŀ�˼��\n");
        else
        if (lvl >= 1)
                write("�����а��룺�ⶨ��ǰ���������µ��ؼ�����Щ�ʾ��Ҫ�ú÷�����\n");
        else
        if (random(2))
        {
                write("����������ıʻ�����������ϰ���书������������������ᡣ\n");
                if( query("experience", me)<me->query_experience_limit() )
                        addn("experience", 1, me);
        } else
                write("��Ǳ����ĥ����ıʻ���ȫȻû��������ʲô���塣\n");

        return 1;
}
