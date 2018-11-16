
#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob, stone;
        string type;
        int p, mp;

        if( !str )
                return notify_fail("��Ҫ����ʲô��Ʒ��\n");

        if( me->is_busy() )
                return notify_fail("��æ����������������������ɡ�\n");

        if( me->is_fighting() )
                return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

        if( !objectp(ob = present(str, me)) )
                return notify_fail("������û�������Ʒ��\n");

        if( me->query_skill("force") < 300 )
                return notify_fail("����ڹ���Ϊ����������������Ʒ��\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("���������Ϊ����������������Ʒ��\n");

        if( query("neili", me)<3000 )
                return notify_fail("�����ڵ��������㣬����������Ʒ��\n");

        if( !query("can_sign", ob) || !(p=query("quality_level", ob)) )
                return notify_fail("�ⶫ���ƺ���������ʲô��\n");

        if( !query("require/level", ob) || query("require/level", ob) < 20 )
                return notify_fail("������20�����ϵ�װ������������\n");

        message_vision(HIM "$N" HIM "��" + ob->name() +
                       HIM "�������У�ĬĬ��ת��������ʼ������\n" NOR, me);

        if (random(100)<50 )
        {
                message_vision(HIR "ͻȻȴ��" + ob->name() +
                               HIR "�͵Ļ���һ�����̣�ʲô��"
                               "û�����¡�\n" NOR, me);
                destruct(ob);
                return 1;
        }

        if( query("skill_type", ob) )
                stone = new("/clone/enchase/weapon_soul"+p);
        else 
        {
                type = query("armor_type", ob);
                stone = new("/clone/enchase/"+type+"_soul"+p);
        }

        message_vision(HIM "��ʱֻ��$N" HIM "���İ������ڣ��ƺ���"
                       "����ʲô��ͬѰ�������顣\n" NOR, me);

        if( query("value", stone) )
        {
                mp=query("value", stone)/300;
                mp = 5 + random(mp);
                if (mp < 5) mp = 5;
                if (mp > 100) mp = 100;

                addn("magic_points", mp, me);
                tell_object(me, HIC "��ͨ������"+ stone->name() +
                                HIC "�Ĺ��̣��Ӷ������" +
                                chinese_number(mp) + "����ۡ�\n" NOR);
        }
        addn("max_neili", -1, me);
        addn("neili", -3000, me);
        me->start_busy(5);

        stone->move(me, 1);
        destruct(ob);
        return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ��concise <��ƷID>

��ָ������㽫ĳЩ��Ʒ������һ����˵���й�������װ��������
������������������Ʒ��Ҫ�Ƚϸߵ��ڹ��ȼ���������Ϊ��ÿ�γɹ�
��������������һ����������ۣ����ǻ�����һ�����������
HELP);
        return 1;
}


