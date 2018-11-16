// Room: /d/gumu/obj/bishou.cذ��
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
inherit ITEM;
void create()
{
        set_name( "ذ��" , ({ "bi shou", "blade", "bishou" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�ѱ�Ե������ذ�ף��������ն(zhan)������\n");
                set("value", 0);
                set("material", "iron");
        }
        setup();
}

void init()
{
        add_action("mark_success", ({"zhan", "ն"}));
}

int mark_success(string arg)
{
        object target, ob,name1, me = this_player();

        name1=query("id", me);
        if(!arg) return notify_fail("��Ҫնʲô��\n");  
        target = present(arg, environment(me));  
        if(!target)
                return notify_fail("�Ҳ������������\n");
        if(!target->is_corpse())
                return notify_fail("������㣬�ǲ���ʬ�塣\n");
        if( query("no_head", target) )
                return notify_fail("�Ǿ�ʬ���Ѿ�û���׼��ˡ�\n");
        if(!target->is_character())
                return notify_fail("�Ǿ�ʬ���Ѿ������ˡ�\n");
        message_vision(HIR"$N����ذ�� ����׼$n�Ĳ��Ӵ��͵�ն����ȥ��\n"NOR, me, target);
        ob=new("/d/gumu/obj/head");
        ob->set_name(query("victim_name", target)+"���׼�",({"head"}));
        set("long", "����һ��"+query("victim_name", target)+"���׼���\n", ob);
        if( query("victim_user", target) )
        set("victim_user", 1, ob);
        if( query("kill_by", target) )
        set("kill_by",query("kill_by",  target), ob);
        delete("kill_by", target);
        message_vision(HIR"$N��$nն���������������С�\n"NOR, me, ob);
        ob->move(me);
        set("name", "��ͷʬ��", target);
        set("no_head", 1, target);
        set("long", "һ����ͷʬ�壬�������磬��״�ɲ���\n", target);
        return 1;
}