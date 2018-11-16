// This program is a part of NT MudLIB
// enchant
// Written by Lonely@nitan.org

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }
int main(object me, string arg)
{
        string what, tessera;
        object item, obj;
        object scroll;
        int flag = 0;

        if( !arg || sscanf(arg,"%s from %s", tessera, what) != 2 )
                return notify_fail("ָ���ʽ��enchant <��Ʒ> from <װ��>\n");

        if( me->is_busy() )
                return notify_fail("��æ����������������������ɣ�\n");

        if( me->is_fighting() )
                return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

        if( !objectp(obj = present(tessera, me)) )
                return notify_fail("������û�� " + tessera + " ������Ʒ����\n");

        if( !objectp(item = present(what, me)) )
                return notify_fail("������û��" + what + "����װ������\n");

        if( me->query_skill("enchanting", 1) < 200 )
                return notify_fail("�������ĸ�ħ���ջ�������죬����óȻ���֡�\n");

        if( query("max_jingli", me)<300 )
                return notify_fail("�����ڵľ�����Ϊ���ޣ��޷���ħ��Ʒ��\n");

        if( query("jingli", me)<300 )
                return notify_fail("�����ھ������ã��޷���ħ��Ʒ��\n");

        if( query("equipped", item) )
                return notify_fail("����ж�����ȡ�\n");

        if( query("no_identify", item) )
                return notify_fail("����Ʒ��û��ǩ����\n");

        if( !query("enchase", item) || !query("enchase/apply_prop", item) )
                return notify_fail("�����Ʒ����û�п�������ħ�����ԡ�\n");

        if( item->is_item_make() || !query("insert", item) )
                return notify_fail("�����Ʒ�޷�������ħ�����ԡ�\n");

        if( query("maze_item", item) )
                return notify_fail("�����Ʒ����������������������ħ���ԡ�\n");

        if( query("enchase/increase", item) )
                return notify_fail("�������װ��������������ħ���ԡ�\n");

        if( !query("can_enchant", obj) )
                return notify_fail("ֻ���ջ�����ǲſ���������ħװ�����ԡ�\n");

        if( query("enchase", obj) )
                return notify_fail(obj->name()+"���Ѿ���ħ�������ˡ�\n");

        if( query("skill_type", item )
         || (query("armor_type", item) == "hands"
         || query("armor_type", item) == "finger") )
        {
                if( query("can_enchant", obj) != "weapon" )
                        return notify_fail("ֻ���ջ�ſ���������ħ��װ�����ԡ�\n");
        }
        else
        {
                if( query("can_enchant", obj) != "armor" )
                        return notify_fail("ֻ�����ǲſ���������ħ��װ�����ԡ�\n");
        }

        scroll = present("enchant scroll", me);

        if( objectp(scroll) )
                tell_object(me, HIW "\n��˫Ŀ΢�գ���"+item->name()+HIW"��"+obj->name()+HIW"���ڸ�ħ������������ǰ����ת�ھ���"
                        "ʹ���ǿ�����ת���ڡ�\n" NOR);
        else
                tell_object(me, HIW "\n��˫Ŀ΢�գ���"+item->name()+HIW"��"+obj->name()+HIW"������ǰ����ת�ھ���"
                        "ʹ���ǿ�����ת���ڡ�\n" NOR);

        me->start_busy(1);
        addn("jingli", -200, me);

        flag = obj->do_extract(item);

        if( flag ) {
                message("vision", HIW "\n��ʱ��ֻ��" + me->name() + HIW "��ǰһ��"
                        "�⻪��������ת˲���ţ��ƺ�������ʲô��ͬѰ����"
                        "���顣\n\n" NOR, environment(me), ({me}));

                tell_object(me, HIW "��ʱ��ֻ������⻪�����������㼱æ���˫�ֽ�"+obj->name()+HIW"��ס��"
                        "��������"+obj->name()+HIW"��������ɫϼ�⡣\n\n" NOR);

                if( objectp(scroll) )
                {
                        tell_object(me, HIW"ֻ��"+scroll->name()+HIW"������ע�����ѻ�Ϊ�ҽ���\n"NOR);
                        destruct(scroll);
                }
                
                addn("max_jingli", -1, me);

                return 1;
        }
        if( objectp(scroll) )
        {
                tell_object(me, HIW"����"+scroll->name()+HIW"������ע�����ѻ�Ϊ�ҽ���\n"NOR);
                destruct(scroll);
        }
        else
        {
                tell_object(me, HIW"����"+item->name()+HIW"˲�����ѣ����ƬƬ��Ƭ����һ�ء�\n");
                destruct(item);
        }

        tell_object(me, HIR "�㲻��һ����̾��\n" NOR);

        return 1;
}
