// This program is a part of NT MudLIB

#include <ansi.h>
#include "taohua.h"
#include "game.h"

inherit NPC;
inherit F_NOCLONE;

string ask_chicken();
int ask_jiuyin();
int ask_game();

void create()
{
        set_name("����", ({"huang rong", "huang", "rong"}));
        set("title", "�����һ�����֮Ů");
        set("nickname", HIY "ؤ��ǰ�ΰ���" NOR);
        set("gender", "Ů��");
        set("age", 28);
        set("long", "������һ��������Ķ���Ů�������ڵ�������\n"
                    "���������������Ů�������۰�������������\n"
                    "���ϲ���Ĵ����ܡ�\n");
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 28);
        set("int", 40);
        set("con", 30);
        set("dex", 30);
        set("qi", 4800);
        set("max_qi", 4800);
        set("jing", 3500);
        set("max_jing", 3500);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 200);
        set("level", 20);
        set("combat_exp", 3000000);

        set_skill("force", 240);
        set_skill("bibo-shengong", 240);
        set_skill("hand", 240);
        set_skill("strike", 240);
        set_skill("luoying-shenzhang", 240);
        set_skill("dodge", 240);
        set_skill("luoying-shenfa", 240);
        set_skill("parry", 220);
        set_skill("sword", 220);
        set_skill("luoying-shenjian", 220);
        set_skill("yuxiao-jianfa", 220);
        set_skill("lanhua-shou", 240);
        set_skill("staff", 240);
        set_skill("dagou-bang", 240);
        set_skill("unarmed", 200);
        set_skill("xiaoyaoyou", 200);
        set_skill("throwing", 200);
        set_skill("mantianhuayu", 200);
        set_skill("qimen-wuxing", 280);
        set_skill("count", 280);
        set_skill("literate", 280);
        set_skill("mathematics", 280);
        set_skill("cooking", 280);
        set_skill("martial-cognize", 220);

        map_skill("force", "bibo-shengong");
        map_skill("hand", "lanhua-shou");
        map_skill("dodge", "luoying-shenfa");
        map_skill("parry", "lanhua-shou");
        map_skill("staff", "dagou-bang");
        map_skill("sword", "yuxiao-jian");
        map_skill("strike", "xiaoyaoyou");
        map_skill("throwing", "mantianhuayu");

        prepare_skill("hand", "lanhua-shou");
        prepare_skill("strike", "xiaoyaoyou");

        create_family("�һ���", 2, "��Ů");

        set("inquiry", ([
                "�����澭����" : (: ask_jiuyin :),
                "��Ϸ"   : (: ask_game :),
                "�л���" : (: ask_chicken :),

        ]) );

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.fu" :),
                (: perform_action, "hand.fei" :),
                (: perform_action, "strike.zhuan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 4);
        setup();
        carry_object("/clone/unique/ruanwei-jia")->wear();
        carry_object("/d/taohua/obj/shudai")->wear();
        set("startroom", "/d/wuguan/guofu_huayuan");
        check_clone();
}

void attempt_apprentice(object ob)
{
        command("say ���ڹ��ѵ�ͷ����������ʱ����ͽ����");
        return;
}

string ask_chicken()
{
        if( query_temp("marks/��", this_player()) )
                return "���������ô��ô������˵����ꤻ���\n";
        else
        {
                say("�ض�������˵���л������Ǻ��������ز����ҵ�������˺ô�ľ��Ÿ㵽������\n"
                    "�����ط�������������ʲô��\n");

                set_temp("marks/��", 1, this_player());

                return "����Գ�ȥ�ˡ�\n";
        }
}
int ask_jiuyin()
{
        object me = this_player();

        if( query("family/family_name", me) == "����ɽ��" && !query("reserve", me )
                 && query("family/master_id", me) == "ouyang feng" )
        {
                if( query("combat_exp", me)>500000 && present("mask_jiuyin",me) )
                {
                        destruct( present("mask_jiuyin", me) );
                        message_vision(HIY "������������һ˿�������ɫ��������֪���澭�Ľ���ô���ðɣ���˵���������ǡ���\n", me);
                        message_vision("˵�գ��ӹ�$N���еľ��飬��������������\n", me);
                        message_vision("���������������Ƕ�ã�˹�����������ǡ����ù��࣬����ʮ����Ϣ������˼��\n", me);
                        message_vision("�������Ļ�˼����������....����������������������ͨ����...��\n", me);
                        message_vision(HIG "$N��Ϊ�˷ܣ�æ������������Ϣ���ڲ�֪�����а��ջ�������֮���Ĵ�����......\n", me);
                        message_vision("$N�����ǽ����Ժ�����������ץ��������������ͷ��˼�����ֹ�״�����˲��⡣\n", me);
                        message_vision("ͻȻ�䣬$N����žžž�����Լ��������⣬˫�ֳŵأ�������������ȫ�������������� \n"NOR, me);
                        if (random(5) == 3)
                        {
                                tell_object(me,"���˰��Σ���ֻ����ȫ�������з�ʽ��Ϊ�쳣����һ������������ά����ά����ὣ� \n");
                                tell_object(me,"���������������֮�ƣ����ɵ��־���ϲ��\n");
                                set("reserve", 1, me);
                                addn("eff_jing", -100, me);
                                addn("max_neili", -2, me);
                        } else {
                                tell_object(me,"���˰��Σ�������һ�����飬��������ͷʹ���ѡ�һ��˻�����˹�ȥ...\n");
                                addn("eff_jing", -100, me);
                                addn("max_neili", -2, me);
                                me->unconcious();
                        }
                        return 1;
                } else  return notify_fail("���ذ�����һ�ۣ����������΢ĩ���У���ѧ�����澭��Ҳ���±���Ц������ô����\n");
        } else return 0;
}

int ask_game()
{
        object me = this_player();
        object ob = this_object();

        if( query_temp("match_game/playing", me)){
                write("���Ѿ�������Ϸ�ˡ�\n");
                return 1;
        }
/*if( query_temp("match_game/lost", me)){
                message_vision( "$n����ͷ��м�Ķ�$N˵������̫���ˣ��ҲŲ��������ء�\n", me, ob );
                return 1;
        }*/
        if( query_temp("match_game/win", me)){
                message_vision( "$n���˵�ͷ�����ðɣ��ϴν�������Ӯ�ˣ�������û��ô�������ˡ�\n", me, ob );
                delete_temp("match_game/win", me);
        }
        else
                message_vision( "$nüͷһ���$N˵�����ð��������㵽���ж������\n", me, ob );
        return play_game(me,ob);
}
