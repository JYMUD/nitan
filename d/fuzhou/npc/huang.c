// huang.c

#include <ansi.h>

inherit NPC;

int ask_diubiao();

void create()
{
        set_name("������", ({ "huang xiansheng", "huang" }));
        set("title", HIR"��"HIC"��"YEL"�ھ�"HIY"�˷�"NOR);
        set("gender", "����");
        set("age", 36);

        set("inquiry", ([
                "����" : (: ask_diubiao :),
                "ʧ��" : (: ask_diubiao :),
                "ʧ��" : (: ask_diubiao :),
        ]) );

        set("combat_exp", 10000);
        set("shen_type", 1);

        set("eff_qi",800);
        set("qi",800);
        set("max_neili", 100);
        set("neili", 100);
        set("jiali", 10);


        setup();
        carry_object("/clone/misc/cloth")->wear();
}

int accept_object(object who, object ob)
{
        object myenv ;
        if( query_temp("fuwei_diubiao_ask", who) && (query("money_id", ob) && ob->value() >= 100000) )
    {
                message_vision(HIY"����������$N˵���ðɣ����ٸ���һ�λ����ˣ�\n"NOR , who);
            delete_temp("fuwei_destm", who);
            delete_temp("fuwei_dest", who);
            delete_temp("fuwei_diubiao_ask", who);
            delete_temp("fuwei_ready", who);
            delete_temp("fuwei_prepare", who);
            return 1;
         }
        if( query_temp("fuwei_ready", who) )
        {
                message_vision(HIY"����������$N˵���ָ���Ǯ���ã��ã������Һ��Ͼƣ�\n"NOR , who);
                return 1;
        }
        if( !query_temp("fuwei_prepare", who) )
        {
                message_vision(HIY"����������$N˵��ҪѺ�ڣ�����ȥ������ͷ��\n"NOR, who);
                return 1;
        }
        if( wizardp(who) || (query("money_id", ob) && ob->value() >= 200000) )
        {
                message_vision(HIY "����������$N˵���ڳ�׼�����ˣ���Ժ�����ء��Ͽ����(jiebiao)�ɣ�\n������Ѻ����⳥��������\n"NOR , who);
                set_temp("fuwei_ready", 1, who);
                delete_temp("fuwei_prepare", who);
                return 1;
        }
        else
        {
                message_vision(HIR"������������ü��$N˵������㣿�㻹��ʲô�ڣ���ȥ��ȥ��\n"NOR, who);
                return 0;
        }
}

int ask_diubiao()
{
        object me = this_player();
        if( query_temp("fuwei_dest", me) )
        {
message_vision(HIR"������������ü��$N˵������������кü�������������Ҫ����������ھ��Ƚ�ʮ���ƽ����ɣ�\n"NOR, me);
        set_temp("fuwei_diubiao_ask", 1, me);
        return 1;
        }
        else
        {
          message_vision(HIR"��������ü��:�����û�ӹ��ڰɣ�\n",me);
          return 1;
        }

}
