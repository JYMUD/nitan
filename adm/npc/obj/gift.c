// This program is a part of NT MudLIB

#include <ansi.h>
#define GIFT_NAME "�츳���乤��"
inherit ITEM;

int do_fen(string arg);

void create()
{
        set_name(HIR + GIFT_NAME + NOR, ({"gift allocate"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", @LONG
���԰�mygift��õ������츳�֣�fen��������Ҫ������������
��ʽΪ fen ���� 1 ���ָ�ʽ��
LONG );
                set("value", 0);
                /*
                set("no_give", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_put", 1);
                set("no_sell", 1);
                set("no_drop", 1);
                */
        }
        setup();
}

void init()
{
        object me = this_player();

        if (me == environment())
        {
                add_action("do_fen", "fen");
        }
}

int do_fen(string arg)
{
        string htsx;
        int jnd;

        object me = this_player();

        if (! arg || sscanf(arg, "%s %d", htsx, jnd) != 2)
                return notify_fail("ָ���ʽ��fen <��������> <����>\n");

        if( query("tianfu", me)<1 )
                return notify_fail("��Ŀǰû��ʣ���κε������츳�������������䣡\n");

        if (htsx != "����" && htsx != "����" && htsx != "����" && htsx != "��"
                && htsx != "str" && htsx != "int" && htsx != "con" && htsx != "dex")
                return notify_fail("��ֻ���Խ������츳�������䵽���������ԡ����Ǻ����������츳�����ϣ�\n");

        if (jnd < 1) return notify_fail("�����츳�����ķ���ÿ������Ҫ���ǣ��㡣\n");

        if( jnd>query("tianfu", me) )
                return notify_fail("��û����ô��������츳������\n");

        switch (htsx)
        {
        case "����":
        case "str":
                addn("str", jnd, me);
                tell_object(me, HIY "ڤڤ�У����ƺ��о���һ����â����������ڣ�\n" NOR);
                tell_object(me, HIG "��ġ�" + HIR + "��������" + NOR + HIG "�������� " + HIR + chinese_number(jnd) + NOR + HIG + " �㣡\n" NOR);
                break;
        case "����":
        case "int":
                addn("int", jnd, me);
                tell_object(me, HIY "ڤڤ�У����ƺ��о���һ����â����������ڣ�\n" NOR);
                tell_object(me, HIG "��ġ�" + HIR + "��������" + NOR + HIG "�������� " + HIR + chinese_number(jnd) + NOR + HIG + " �㣡\n" NOR);
                break;
        case "����":
        case "con":
                addn("con", jnd, me);
                tell_object(me, HIY "ڤڤ�У����ƺ��о���һ����â����������ڣ�\n" NOR);
                tell_object(me, HIG "��ġ�" + HIR + "�������" + NOR + HIG "�������� " + HIR + chinese_number(jnd) + NOR + HIG + " �㣡\n" NOR);
                break;
        case "��":
        case "dex":
                addn("dex", jnd, me);
                tell_object(me, HIY "ڤڤ�У����ƺ��о���һ����â����������ڣ�\n" NOR);
                tell_object(me, HIG "��ġ�" + HIR + "������" + NOR + HIG "�������� " + HIR + chinese_number(jnd) + NOR + HIG + " �㣡\n" NOR);
                break;
        default:
                return notify_fail("ָ���ʽ��fen <��������> <����>\n");
                break;
        }
        addn("tianfu", -jnd, me);

        if( query("tianfu", me)<1 )
        {
                delete("tianfu", me);
                destruct(this_object());
        }

        if( query("tianfu", me)>0 )
                tell_object(me,HIG"��Ŀǰ����"+chinese_number(query("tianfu", me))+"�������츳û�з��䣡\n\n"NOR);
        return 1;
}

void owner_is_killed() { destruct(this_object()); }

