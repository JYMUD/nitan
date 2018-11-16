// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// resolve

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }
int main(object me, string arg)
{
        object item, ob;
        object scroll;
        mapping ins;
        int    i, j;
        string *ks, *ap;
        string my_id, my_name;
        mapping apply;
        mapping data;

        if( !arg )
                return notify_fail("ָ���ʽ��resolve <��̬װ��>\n");

        if( me->is_busy() )
                return notify_fail("��æ����������������������ɣ�\n");

        if( me->is_fighting() )
                return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

        if( !objectp(item = present(arg, me)) )
                return notify_fail("������û��" + arg + "����װ������\n");

        if( !objectp(scroll = present("resolve scroll", me)) )
                return notify_fail("������û�зֽ���ᡣ\n");

        if( query("max_neili", me)<300 )
                return notify_fail("�����ڵ�������Ϊ���ޣ��޷��ֽ���Ʒ��\n");

        if( query("max_jingli", me)<300 )
                return notify_fail("�����ڵľ�����Ϊ���ޣ��޷��ֽ���Ʒ��\n");

        if( query("jingli", me)<300 )
                return notify_fail("�����ھ������ã��޷��ֽ���Ʒ��\n");

        if( query("equipped", item) )
                return notify_fail("����ж�����ȡ�\n");

        if( query("no_identify", item) )
                return notify_fail("����Ʒ��û��ǩ����\n");

        if( !query("enchase", item) || !query("enchase/apply_prop", item) )
                return notify_fail("�����Ʒ����û�п������ֽ������Ԫ�ء�\n");

        if( item->is_item_make() || !sizeof(ins=query("insert", item)) )
                return notify_fail("�����Ʒ�޷������ֽ�����Ԫ�ء�\n");

        if( query("maze_item", item) )
                return notify_fail("�����Ʒ���������������������ֽ⡣\n");

        if( query("enchase/increase", item) )
                return notify_fail("�������װ�������������ֽ�����Ԫ�ء�\n");

        tell_object(me, HIM "\n��˫Ŀ΢�գ����ֽ������"+item->name()+HIM"������ǰ����ת�ھ���"
                        "ʹ���ǿ�����ת���ڡ�\n" NOR);

        me->start_busy(1);
        addn("jingli", -200, me);
        
        ap = keys(ins);
        for( i=0; i<sizeof(ap); i++ ) {
                apply = copy(ins[ap[i]]["apply_prop"]);
                ks = keys(apply);
                for( j=0; j<sizeof(ks); j++ ) {
                        my_id = ks[j];
                        my_name = EQUIPMENT_D->chinese(my_id)+"Ԫ��";
                        data = ([]);
                        data["element"] = my_id;
                        data["name"] = my_name;
                        ob = TEMPLATE_D->create_object("/inherit/template/element/element", my_id, data);
                        ob->set_name(my_name, ({my_id, "element"}));
                        ob->move(me, 1);
                }
        }

        message("vision", HIW "\n��ʱ��ֻ��" + me->name() + HIW "��ǰһ����"
                "�⻪��������ת˲���ţ��ƺ�������ʲô��ͬѰ����"
                "���顣\n\n" NOR, environment(me), ({me}));

        tell_object(me, HIW "��ʱ��ֻ������⻪�����������㼱æ���˫�֣�����������������ɫϼ�⡣\n\n" NOR);

        addn("max_jingli", -1, me);
        destruct(scroll);
        destruct(item);

        return 1;
}

