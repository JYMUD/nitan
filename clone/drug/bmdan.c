// Code of ShenZhou
// /d/shenlong/obj/bmdan.c ����������
// by Aln  1/98

#include <ansi.h>

inherit ITEM;
void create()
{
        set_name("����������", ({"baoming dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 4000);
                set("long", 
"������������������������ɽ�˲Ρ����ܵ���ѩ���������ɵ��鵤\n");
                set("medicine", 1);
                set("no_sell", 1);
                set("only_do_effect", 1);  
                set("no_drop", "�������������Ʋ��ף��������ӣ�\n");
        }

        setup();
}

int do_effect(object me)
{
        if( query("eff_qi", me)*10>query("max_qi", me)*3
         && query("eff_jing", me)*10>query("max_jing", me)*3){
                write("�������ò��ŷ�������������\n");
                return 1;
        }

        if( !me->is_fighting() ) {
                write("�����ֲ���Σ����ͷ�����˷��ˣ�\n");
                return 1;
        }

        message_vision("$N����һ��" + name() + "��\n", me);

        set("eff_qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);

        message_vision(YEL "$Nֻ������ȫ���ˡ�\n\n" NOR, me);
        destruct(this_object());
        return 1;
}