// zhu.c ����

inherit NPC;
#include <ansi.h>

string ask_buy();
int ask_degree();
void create()
{
        set_name("������", ({ "lao xiansheng", "lao", "xiansheng"}));
        set("long",
"��λ���������й�״Ԫ��������٣��������ϻ��ϼ������������꣬��
����ʹ���ĵµ��������룬�����Ϊ����ǽ��Ρ�\n");
        set("gender", "����");
        set("age", 65);
        set("no_get", 1);
        set_skill("literate", 300);

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage", 10);

        set("combat_exp", 4000);
        set("shen_type", 1);
        setup();
}

int recognize_apprentice(object ob)
{
        if( !query_temp("mark/��", ob) )
                return 0;
        addn_temp("mark/��", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        object me = this_player();
        if( !query_temp("mark/��", who) )
                set_temp("mark/��", 0, who);
        if( query("money_id", ob) && ob->value() >= 1000 )
        {
                message_vision("������ͬ��ָ��$NһЩ����д�ֵ����⡣\n", who);
                addn_temp("mark/��", ob->value()/50, who);
                if( me->query_skill("literate", 1) > 21)
                {
tell_object(me,"����������һ�����Ļ�֪ʶ��Ҳ�����Լ����������ˡ�\n");
                        return 1;
                }
                return 1;
        }
}
