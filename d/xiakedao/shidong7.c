// Room: /xiakedao/shidong7.c

inherit ROOM;

#include <ansi.h>

string look_bi();

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
����һ��ʯ�������ܵ��Ű�յ�͵ƣ�ʹ����������ǳ���
����ɽ������ʯ��(bi)�����ǿ̻���ʲô�����������ס�뿴
����
LONG );
        set("exits", ([
                "west" : __DIR__"shidong8",
                "north" : __DIR__"shidong6",
        ]));
        set("no_clean_up", 0);
        set("item_desc",([
                "bi"  : (: look_bi :),
                "weapon": "ͼ�������ֳֵ���������ӿ�����\n",
        ]));
        set("coor/x", -3100);
        set("coor/y", -22100);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_think", "think");
        add_action("do_canwu", "canwu");
}

string look_bi()
{
        object me = this_player();
        string msg;

        if( me->query_skill("literate", 1)
         || query("learned_literate", me)){
                msg = HIC "\n���ߵ�ʯ��ǰ����ϸ�ۿ�ʯ���ϵ����ݣ�����ʯ�ڲ���\n"
                        "�����״�����֡�����ϸ������Щ����ȴһ������\n" NOR;
        } else {
                msg = HIC "\n���ߵ�ʯ��ǰ����ϸ�ۿ�ʯ���ϵ����ݣ�����ʯ�ڲ���\n"
                        "�����״�����֣��������δ�����飬�����㲢û����\n"
                        "����Щ���֡�����Ȼ�������������кܶ�ͼ����������\n"
                        "�����̡����滭�Ÿ�ʽ����������е��ֳֳ�������\n"
                        "�����ոֵ���������ͼ���������б���(weapon)������\n"
                        "ͬ��ÿ��������书��ʽҲ��ͬ��������������ȴ�Ծ�\n"
                        "��¶ȫ�������������������ޱȣ�����Ÿ�����ʽ��\n"
                        "���ƺ�������������������̫������������У��ƺ���\n"
                        "���������������й�ϵ�� ����һʱȴҲ����(canwu)��\n"
                        "͸��������ˣ���ȴ�̲�ס�����ѧ(think)������\n" NOR;
        }

        return msg;
}

int do_think(string arg)
{
        object here, me = this_player();
        int add;

        if (! here = find_object(__DIR__"furong1"))
                here = load_object(__DIR__"furong1");

        if( query("special_skill/clever", me) )
                add = me->query_int() / 4;
        else
                add = me->query_int() / 10;

        if (! living(me) || arg != "bi")
                return notify_fail("��Ҫ����ʲô��\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("��������æ���ء�\n");

        if( me->query_skill("literate",1) || query("learned_literate", me) )
                return notify_fail("�㷢��ʯ���ϵ��书���֮����һʱ������ᣡ\n");

        if( query("int", me)<27 )
                return notify_fail("����������Ȼ�������е㲻���ס�\n");

        if( query("dex", me)<27 )
                return notify_fail("���о��˰��죬ֻ����ʽʼ���޷�����ʩչ��\n");

        if ((int)me->query_skill("force", 1) < 220)
                return notify_fail("��Ļ����ڹ���򲻹����޷�����ʯ��"
                                   "�ϵ��书��\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("���������Ϊ���㣬�޷�ѧϰʯ���ϵ��书��\n");

        if( query("jing", me)<85 )
                return notify_fail("�����ھ��񲻼ã�����ƣ�룬������Ϣ"
                                   "һ��ɡ�\n");

        if ((int)me->query_skill("taixuan-gong", 1) < 120)
                return notify_fail("�����ʯ���ϼ��ص��书������˵���ڸ��ӣ�һ"
                                   "ʱ��������\n");

        if ((int)me->query_skill("taixuan-gong", 1) >= 180)
                return notify_fail("�����ʯ���ϼ��ص��书������˵̫ǳ�ˣ������"
                                   "ʲôҲûѧ����\n");

        me->receive_damage("jing", 75);

        if (me->can_improve_skill("taixuan-gong"))
                me->improve_skill("taixuan-gong", add);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "�۾�����Ĳ���ǽ�������ص��񹦣�"
                       "��������\n" NOR, me);
        write(HIC "��ԡ�̫�����������µ�����\n" NOR);
        return 1;
}

int do_canwu(string msg)
{
    object me = this_player();

    string where, witch;

    if (! msg)return notify_fail("ʲô��\n");

    if (sscanf(msg, "%s from %s", witch, where) != 2)
          return notify_fail("��ʲô��\n");

    if (me->is_busy())
          return notify_fail("��������æ���ء�\n");

    if (me->is_fighting())
          return notify_fail("����ս��Ŷ����С�ģ����ˣ�����\n");

    if (witch != "weapon")
          return notify_fail("�������ʲô��\n");

    if (where != "bi")
          return notify_fail("����ûʲô�������İ���\n");

    if (me->query_skill("literate", 1)
         || query("learned_literate", me) )
          return notify_fail("�����ʯ�����˰���Ҳû����ʲô��\n");

    if ((int)me->query_skill("force", 1) < 240)
          return notify_fail("����ڹ���Ϊ�������޷������������"
                             "̫����������������\n");

    if( query("max_neili", me)<6000 )
          return notify_fail("���������Ϊ���㣬�޷������������"
                             "̫����������������\n");

    if( query("jing", me)<100 )
          return notify_fail("��ľ����޷����У��޷������������"
                             "̫����������������\n");

    if (me->query_skill("taixuan-gong", 1) < 200)
          return notify_fail("���̫������֪ʵ�����ޣ��޷������������"
                             "̫����������������\n");

    if( query("can_learned/taixuan-gong/enable_weapon", me) )
          return notify_fail("ʯ���ϵľ����������ڻ��ͨ�������ٲ����ˡ�\n");

    me->receive_damage("jing", 95);

    me->start_busy(3 + random(5));

    if (random(6) == 1)
    {
        addn("canwu_taixuan/count", 1, me);

        if( query("canwu_taixuan/count", me) >= 50 )
        {
            write(HIM "��Ȼ�䣬��һ����Х�����л�Ȼ��ͨ���������ǡ�\n" NOR);
            write(HIC "������ͨ�����������̫����������������\n" NOR);

            set("can_learned/taixuan-gong/enable_weapon", 1, me);
            delete("canwu_taixuan/count", me);

            if (me->can_improve_skill("force"))
                    me->improve_skill("force", 1500000);
            if (me->can_improve_skill("taixuan-gong"))
                    me->improve_skill("taixuan-gong", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);

            return 1;
        }

        write(HIC "����������̫�����������������˸��µ���ʶ����������Ȼ����"
                  "�಻��֮����\n" NOR);
        return 1;
    }
    else return notify_fail("����ϸ�о�ʯ�������̻������ݣ���ȴûʲôЧ����\n");

}