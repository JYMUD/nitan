// Code of ShenZhou
// guiyuan.c ��Ԫ��
// Ryu
// Modified by xQin to forbid the abuse of gyd

inherit PILL;
#include <ansi.h>
void setup()
{}
void init();
void wear(int);

int worn;

int cure_ob(string);
void create()
{
        set_name("��Ԫ��", ({"guiyuan dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ��Ө����Բ�Ĺ�Ԫ����\n");
                set("value", 5000);
                set("no_sell", 1);
                set("medicine", 1);
        }
        setup();
}

int cure_ob(object me)
{
        addn("neili", -200, this_player());
        message_vision(HIR "$N����һ�ù�Ԫ����ֻ����ͷ�ؽ��ᣬ�������ڣ�ԭ����ʳ���ͣ�ҩЧ�ʵ��䷴��\n" NOR, this_player());
        this_player()->apply_condition("bonze_drug",
                this_player()->query_condition("bonze_drug")+10);
        destruct(this_object());
        return 1;
}

void init()
{
        worn = 0;
        call_out("wear", 1200, 1);

        add_action("do_pour", "drop");
}



void wear(int phase)
{
        worn = phase;
        switch(phase) {
        case 1:
                set("long", "����һ�����˺ܳ�ʱ��Ĺ�Ԫ����\n");
                call_out("wear", 300, phase+1);
                break;
        case 2:
                set("long", "����һ���Ѿ���̫���εĹ�Ԫ�����챻�绯�ˡ�\n");
                call_out("wear", 100, phase+1);
                break;
        case 3:
                destruct(this_object());
                break;
        }
}
int effect_in_liquid(object ob)
{
        object me = this_player();
        if (this_player()->query_condition("bonze_drug" ) > 0 )
        {        
        addn("neili", -50, me);
        message_vision(HIR "$N����һ��ҩ�ƣ�����ԭ������ҩ�Թ��ͣ��ʵ��䷴��\n" NOR, this_player());
        this_player()->apply_condition("bonze_drug",
        this_player()->query_condition("bonze_drug")+10);
        return 1;
        }
        
        if( query("neili", this_player())>query("max_neili", this_player())*2 )
        set("neili",query("max_neili",  this_player())*2-1, this_player());
        if( query("liquid/type", ob) == "alcohol" && !query("zuixian", ob)){
        tell_object(this_player(), HIG"��ֻ������������ԴԴ�������������ơ�\n"NOR);
        addn("neili", random(10)+10*query("liquid/drunk_apply", ob), this_player());
        me->apply_condition("bonze_drug", 30);
        return 1;
        }
}