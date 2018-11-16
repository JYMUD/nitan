// npc: /d/npc/m_weapon/npc/tianjianshi.c
// Last Modified by winder on Feb. 28 2001
// Modified by sir 4/13/2001

#include <ansi.h>
inherit NPC;

int do_weapon();
int do_give_weapon(object me);
object creat_weapon();

void create()
{
        set_name("ŷұ��", ({ "ouye zi", "zi" }) );
        set("nickname", RED "���Ľ���" NOR );
        set("gender", "����" );
        set("age", 60);
        set("no_get", 1);
        set("long", "��ͷ�ϰ���ͷ�����Ƴ���Ʈ����ǰ����Ŀ���ݵ������й⣬\n"
                "��Ŀ��������˸˸���ž��������ݵĽ��⣬�����ƺ�����Χ\n"
                "��һ�ɽ���֮�С�\n");
        set("str", 25);
        set("dex", 20);
        set("con", 17);
        set("int", 30);
        set("shen_type", 0);
        set("max_neli",5000);
        set("jiali",50);

        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("claw",200);
        set_skill("jiuyin-baiguzhao",200);
        set_skill("force",150);
        set_skill("sword",150);
        set_skill("bibo-shengong",100);
        set_skill("luoying-shenjian",100);
        set_skill("parry",90);
        set_skill("anying-fuxiang",100);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage",50);

        set("combat_exp", 250000);
        set("score",0);
        
        map_skill("force","bibo-shengong");
        map_skill("parry","luoying-shenjian");
        map_skill("sword","luoying-shenjian");
        map_skill("claw","jiuyin-baiguzhao");
        map_skill("dodge","anying-fuxiang");
        
        set("attitude", "peaceful");
        
        set("inquiry", ([
                "����" : "�������Ǽ�ʮ�ּ����£�Ҫ�����˵ľ��������������о��ĺ�������\n",
                "ԭ��" : "��������ǧ���������������ҵ����Ҳ��ܰ���������\n",
                "����" : (: do_weapon() :),
        ]) );

        setup();
        set("chat_chance", 3);
        set("chat_msg", ({
                "ŷұ�Ӹ������裺��������⣬�����͡����������⣬��Ӣ�ۣ�\n",
                "ŷұ�ӵ�ͷ�������ƺ���˼��ʲô��\n"
                "ŷұ��̾��һ�����������Ӣ�ۣ���Ӣ�ۡ�����������\n"
        }) );
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        ::init();
        add_action("do_answer","answer");
}

int accept_object(object who, object ob)
{        
        switch(query("name", ob) )
        {
                case "����" :
                case "�л���" :
                case "��Ƥ��":
                case "��":
                case "��а����":
                        if( (query_temp("condition", who)) != query("name", ob) )
                        {
                                message_vision(HIC "ŷұ��һ㶣��Ҷ���˵����Ҫ��������ô��\n" NOR, who);
                                return 0;
                        }
                        else
                        {
                                delete_temp("condition", who);
                                message_vision(HIG "ŷұ��΢Ц�ţ��ܺúܺã����ҾͰ�����һ�ΰɣ�\n" NOR, who);
                                set_temp("condition_ok", 1, who);
                                destruct(ob);
                                do_give_weapon(who);
                                return 1;
                        }
        }
        if( (query("weapon/make", who)) )
        {
                say("ŷұ��һ��ãȻ�����Ѿ���һ������������ˣ�������ʲô���ѵ�������ô��\n");
                return 0;
        }
        switch(query("id", ob) )
        {
                case "shen mu": 
                        set_temp("or", 1, who);
                        set_temp("get_orc", 1, who);
                        break;
                case "jin mu":
                        set_temp("or", 2, who);
                        set_temp("get_orc", 1, who);
                        break;
                case "han zhu": 
                        set_temp("or", 3, who);
                        set_temp("get_orc", 1, who);
                        break;
                case "iron stone": 
                        set_temp("or", 4, who);
                        set_temp("get_orc", 1, who);
                        break;
                default :
                        message("vision","����ʲô���ⲻ���������������",who);
                        return 0;
        }
        message("vision","ŷұ�ӵ�ͷ������һ�����е�"+query("name", ob)+"���˵�ͷ˵��\n",who);
        write("��������Դ������±�����\n"+
                "     ��(sword)\n"+
                "     ��(blade)\n"+
                "     ǹ(spear)\n"+
                "     ��(club)\n"+
                "     ��(stick)\n"+
                "     ��(staff)\n"+
                "     ��(hammer)\n"+
                "     ��(hook)\n"+
                "     ��(axe)\n"+
                "     ��(whip)\n");                  
        say("��λ"+RANK_D->query_respect(who)+"Ҫ��ʲô�����������˸�����(answer)��\n");
        return 2;

}

int do_answer(string arg)
{
        object me,w_or;
        me = this_player();
        if( !(query_temp("get_orc", me)) )
        {
//                write("���ҵ�ԭ������\n");
                return 0;
        }
        
        if(!arg)
        {
                write("��Ҫ��ʲô������\n");
                return 0;
        }

        message("vision",me->name()+"��ŷұ������˵�˼��䡣\n",environment(me), ({me}) );
        switch (arg)
        {
                case "sword" :
                        addn_temp("sword", 1, me);
                        write("����ԭ��ȥ���̽��ɣ�\n");
                        message("vision","ȥ�ɣ�"+me->name()+"��\n",me);
                        break;
                case "blade" :
                        addn_temp("blade", 1, me);
                        write("����ԭ��ȥ���̵��ɣ�\n");
                        message("vision","ȥ�ɣ�"+me->name()+"��\n",me);
                        break;
                case "spear" :
                        addn_temp("spear", 1, me);
                        write("����ԭ��ȥ����ǹ�ɣ�\n");
                        message("vision","ȥ�ɣ�"+me->name()+"��\n",me);
                        break;
                case "club" :
                        addn_temp("club", 1, me);
                        write("����ԭ��ȥ���̹��ɣ�\n");
                        message("vision","ȥ�ɣ�"+me->name()+"��\n",me);
                        break;
                case "stick" :
                        addn_temp("stick", 1, me);
                        write("����ԭ��ȥ���̰��ɣ�\n");
                        message("vision","ȥ�ɣ�"+me->name()+"��\n",me);
                        break;
                case "staff" :
                        addn_temp("staff", 1, me);
                        write("����ԭ��ȥ�����Ȱɣ�\n");
                        message("vision","ȥ�ɣ�"+me->name()+"��\n",me);
                        break;
                case "axe" :
                        addn_temp("axe", 1, me);
                        write("����ԭ��ȥ���̸��ɣ�\n");
                        message("vision","ȥ�ɣ�"+me->name()+"��\n",me);
                        break;
                case "hammer" :
                        addn_temp("hammer", 1, me);
                        write("����ԭ��ȥ���̴��ɣ�\n");
                        message("vision","ȥ�ɣ�"+me->name()+"��\n",me);
                        break;
                case "hook" :
                        addn_temp("hook", 1, me);
                        write("����ԭ��ȥ���̹��ɣ�\n");
                        message("vision","ȥ�ɣ�"+me->name()+"��\n",me);
                        break;
                case "whip" :
                        addn_temp("whip", 1, me);
                        write("����ԭ��ȥ���̱ްɣ�\n");
                        message("vision","ȥ�ɣ�"+me->name()+"��\n",me);
                        break;
                default :
                        message_vision(HIC"ŷұ��һ�����ɣ�ʲô������\n"NOR,me);
                        return notify_fail("ŷұ����ϸ��˵�����²��ɶ�Ϸ�������أ���\n");
        }
        switch(query_temp("or", me) )
        {
                case 1:
//                        w_or = new("/d/npc/m_weapon/tan/item/shenmu",1);
//                        w_or->move(me);                        
//                        message_vision(HIC"ŷұ�Ӹ���$Nһ��ǧ����ľ��\n"NOR,me);
                command("giveshenmuto"+query("id", me));
                        break;
                case 2:
//                        w_or = new("/d/npc/m_weapon/tan/item/jinmu",1);
//                        w_or->move(me);
//                        message_vision(HIC"ŷұ�Ӹ���$Nһ�麣�׽�ĸ��\n"NOR,me);
                command("givejinmuto"+query("id", me));
                        break;
                case 3:
//                        w_or = new("/d/npc/m_weapon/tan/item/hanzhu",1);
//                        w_or->move(me);
//                        message_vision(HIC"ŷұ�Ӹ���$Nһ�麮˿����\n"NOR,me);
                command("givehanzhuto"+query("id", me));
                        break;
                case 4:
//                        w_or = new("/d/qilian/obj/ironstone",1);
//                        w_or->move(me);
//                        message_vision(HIC"ŷұ�Ӹ���$Nһ��������ʯ��\n"NOR,me);
                command("giveironstoneto"+query("id", me));
                        break;
        }

        delete_temp("get_orc", me);
        return 1;
}

int do_weapon()
{
        object me,obj;
//object weapon;        
        string w_id;
        me = this_player();
        w_id=query("weapon/id", me);
        if( !(query("weapon/make", me)) )
                return notify_fail("�����������\n");

        if( objectp(obj = present(w_id, me)) )
        {
                say("ŷұ����ɫһ���������������������ֱ�ô��������ʲô��\n");
                return 1;
        }
        if( query_temp("condition", me) )
        {
                say("ŷұ����ɫһ������������ȥ��"+(query_temp("condition", me))+
"��ô����û�õ��������\n");
                return 1;
        }

        if( !(query_temp("condition_ok", me)) )
        {
                message_vision(HIY"��λ"+RANK_D->query_respect(me)+"��Ҫ���µõ��������ⲻ�ѡ�����......\n" NOR, me);
                message_vision(HIY"ŷұ�ӳ�����һ��˵������ҵ���Ҫ�Ķ�����\n" NOR, me);
                switch( random(5) )
                {
                        case 0:
                                message_vision("�õ������������ɣ�\n",me);
                                set_temp("condition", "����", me);
                                break;
                        case 1:
                                message_vision("���ҽл������ҾͰ��㣡��\n",me);
                                set_temp("condition", "�л���", me);
                                break;
                        case 2:
                                message_vision("��..�������Ƥ�������ɣ�\n",me);
                                set_temp("condition", "��Ƥ��", me);
                                break;
                        case 3:
                                message_vision("..���뿴������\n",me);
                                set_temp("condition", "��", me);
                                break;
                        case 4:
                                message_vision("������������ҵ���а���׵Ļ�......\n",me);
                                set_temp("condition", "��а����", me);
                                break;
                }
        }
        return 1;
}
int do_give_weapon(object me)
{
                object weapon;
                object *obs;
                int i;
                object env;
                string env_name;
    string area;
    

                
                delete_temp("condition_ok", me);
                obs = children("/d/npc/m_weapon/weapon/m_weapon");
                for (i=0;i<sizeof(obs);i++)
                {
                        if( query("owner", obs[i]) == query("id", me) )
                        {
                                if (!environment(obs[i])) continue;
                                env = environment(obs[i]);
        sscanf(base_name(env),"/%*s/%s/%*s",area);
        area=to_chinese(area);
                                if (env->is_character())
                                  env_name=query("name", env)+"����";
                                else
                                  env_name=query("short", env);
                          if (!userp(env))
                            env_name = area +"��" + env_name;
                          message_vision("$N˵�������"+query("name", obs[i])+
                          "��"+ env_name+"����ȥ�Ұɡ�\n",this_object());
                          return 1;
                        }
                }
                
                weapon = creat_weapon();
                weapon->move(me);
                return 1;
}

object creat_weapon()
{
        object me,weapon;
        string mask;        //the verible that record the type of weapon
        me = this_player();
        mask=query("weapon/type", me);
        weapon = new("/d/npc/m_weapon/weapon/m_weapon",1);
        return weapon;
/*
        switch(mask)
        {
                case "��":
                        weapon = new("/d/npc/m_weapon/weapon/m_sword",1);
                        return weapon;
                case "��":
                        weapon = new("/d/npc/m_weapon/weapon/m_blade",1);
                        return weapon;
                case "ǹ":
                        weapon = new("/d/npc/m_weapon/weapon/m_spear",1);
                        return weapon;
                case "��":
                        weapon = new("/d/npc/m_weapon/weapon/m_club",1);
                        return weapon;
                case "��":
                        weapon = new("/d/npc/m_weapon/weapon/m_stick",1);
                        return weapon;
                case "��":
                        weapon = new("/d/npc/m_weapon/weapon/m_staff",1);
                        return weapon;
                case "��":
                        weapon = new("/d/npc/m_weapon/weapon/m_hammer",1);
                        return weapon;
                case "��":
                        weapon = new("/d/npc/m_weapon/weapon/m_hook",1);
                        return weapon;
                case "��":
                        weapon = new("/d/npc/m_weapon/weapon/m_whip",1);
                        return weapon;
                case "��":
                        weapon = new("/d/npc/m_weapon/weapon/m_axe",1);
                        return weapon;
        }
*/
}