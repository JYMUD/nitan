// This program is a part of NT MudLIB
// da-mo.c

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "shaolin.h"

mixed ask_qingxin();
mixed ask_luan();
mixed ask_shang();
mixed ask_zhe();

void create()
{
        set_name("��Ħ����", ({
                "da mo",
                "da",
                "mo",
        }));
        set("long",
                "����һλ���������������ɮ����һϮ���ݽ�˿������ġ�\n"
                "��ȴ�����⣬Ŀ�̴�Ц���������飬һ�ɵõ���ɮ���ơ�\n"
                "�����������ɿ�ɽ���桢�������ֵ�������ɮ��Ħ��ʦ��\n"
        );

        set("title", HIR"���ֿ�ɽ��ʦ"NOR);
        set("gender", "����");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 300);
        set("shen_type", 1);

        set("str", 40);
        set("int", 50);
        set("con", 45);
        set("dex", 40);

        set("max_qi", 8000);
        set("max_jing", 4000);
        set("neili", 9000);
        set("max_neili", 9000);
        set("jiali", 50);
        set("level", 60);
        set("combat_exp", 10000000);

        set_skill("buddhism", 600);
        set_skill("literate", 600);
        set_skill("sanscrit", 600);
        set_skill("martial-cognize", 500);

        set_skill("blade", 600);
        set_skill("claw", 600);
        set_skill("club", 600);
        set_skill("cuff", 600);
        set_skill("dodge", 600);
        set_skill("finger", 600);
        set_skill("force", 600);
        set_skill("hand", 600);
        set_skill("parry", 600);
        set_skill("staff", 600);
        set_skill("strike", 600);
        set_skill("sword", 600);
        set_skill("whip", 600);
        set_skill("unarmed", 600);
        set_skill("medical", 600);
        set_skill("shaolin-yishu", 600);

        set_skill("banruo-zhang", 600);
        set_skill("shenzhang-bada", 600);
        set_skill("xumishan-zhang", 600);
        set_skill("cibei-dao", 600);
        set_skill("damo-jian", 600);
        set_skill("lunhui-jian", 600);
        set_skill("fengyun-shou", 600);
        set_skill("fumo-jian", 600);
        set_skill("hunyuan-yiqi", 600);
        set_skill("shaolin-xinfa", 600);
        set_skill("jingang-quan", 600);
        set_skill("longzhua-gong", 600);
        set_skill("luohan-quan", 600);
        set_skill("nianhua-zhi", 600);
        set_skill("xiuluo-zhi", 600);
        set_skill("yipai-liangsan", 600);
        set_skill("duoluoye-zhi", 600);
        set_skill("jingang-zhi", 600);
        set_skill("wuxiang-zhi", 600);
        set_skill("pudu-zhang", 600);
        set_skill("qianye-shou", 600);
        set_skill("sanhua-zhang", 600);
        set_skill("riyue-bian", 600);
        set_skill("shaolin-shenfa", 600);
        set_skill("weituo-gun", 600);
        set_skill("wuchang-zhang", 600);
        set_skill("xiuluo-dao", 600);
        set_skill("ranmu-daofa", 600);
        set_skill("yingzhua-gong", 600);
        set_skill("yijinjing", 600);
        set_skill("yizhi-chan", 600);
        set_skill("zui-gun", 600);
        set_skill("zui-quan", 600);
        set_skill("lunhui", 600);

        map_skill("blade", "cibei-dao");
        map_skill("claw", "longzhua-gong");
        map_skill("club", "wuchang-zhang");
        map_skill("cuff", "luohan-quan");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "nianhua-zhi");
        map_skill("force", "yijinjing");
        map_skill("hand", "fengyun-shou");
        map_skill("parry", "nianhua-zhi");
        map_skill("staff", "weituo-gun");
        map_skill("strike", "sanhua-zhang");
        map_skill("sword", "fumo-jian");
        map_skill("whip", "riyue-bian");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        set("inquiry", ([
                "����"   : "����ѧʲô���У�",
                "����"   : "����ѧʲô������",
                "��Ħ���Ľ�": (: ask_qingxin :),
                "���Ľ�"    : (: ask_qingxin :),
                "��Ħ������": (: ask_luan :),
                "������"    : (: ask_luan :),
                "��Ħ����": (: ask_shang :),
                "����"    : (: ask_shang :),
                "��Ħ��Ԫ��": (: ask_zhe :),
                "��Ԫ��"    : (: ask_zhe :),
        ]));

        create_family("������", 1, "��ɽ��ʦ");

        set_temp("apply/attack", 300);
        set_temp("apply/defense", 300);
        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);

        set("master_ob",5);
        setup();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void attempt_apprentice(object ob)
{
        object me;
        mapping ob_fam, my_fam;
        string name, new_name;

        if (! permit_recruit(ob))
                return;

        me = this_object();
        my_fam=query("family", me);

        name=query("name", ob);

        if( !(ob_fam=query("family", ob)) || 
            ob_fam["family_name"] != "������")
        {
                command("say " + RANK_D->query_respect(ob) +
                        "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }

        if( query("class", ob) != "bonze" )
        {
                command("say " + RANK_D->query_respect(ob) +
                        "���׼ҵ��ӣ�����������ѧ�ա�");
                return;
        }

        if ((int)ob_fam["generation"] != 36)
        {
                command("say " + RANK_D->query_respect(ob) +
                        "��ƶɮ����ҵ� !");
                return;
        }

        if ((int)ob->query_int() < 35)
        {
                command("say " + RANK_D->query_respect(ob) + "�������в��㣬"
                        "��Ҫ��һ�������������������ķ𷨡�");
        }

        if( query("WPK", ob)>3 )
        {
                command("sigh");
                command("say " + RANK_D->query_respect(ob) + "ɱ¾��̫�أ�"
                        "���ʺϼ���ѧϰ�书��");
                return;
        }

        if ((int)ob->query_skill("buddhism", 1) < 180)
        {
                command("say " + RANK_D->query_respect(ob) + "�����ķ�"
                        "����ò����������ȶ�����С�");
                return;
        }

        if ((int)ob->query_skill("dodge", 1) < 180)
        {
                command("say " + RANK_D->query_respect(ob) + "�����Ṧ"
                        "�������Ƿȱ�������ȿ���������");
                return;
        }

        if ((int)ob->query_skill("force", 1) < 180)
        {
                command("say " + RANK_D->query_respect(ob) + "�����ڹ�"
                        "�������Ƿȱ�������ȿ���������");
                return;
        }

        if ((int)ob->query_skill("parry", 1) < 180)
        {
                command("say " + RANK_D->query_respect(ob) + "�����м�"
                        "�������Ƿȱ�������ȿ���������");
                return;
        }

        if( query("combat_exp", ob)<1000000 )
        {
                command("say " + RANK_D->query_respect(ob) + "ʵս����"
                        "������Ƿȱ�������ȿ���������");
                return;
        }

        command("char �����ֵ�һ����֮�ţ����Ǵ��ϻ� !");
        name=query("name", ob);
        new_name = "��" + name[2..3];
        NAME_D->remove_name(query("name", ob),query("id", ob));
        set("name", new_name, ob);
        NAME_D->map_name(query("name", ob),query("id", ob));

        command("say �ӽ��Ժ���ķ�������" + new_name + "��");
        command("recruit "+query("id", ob));
        return;
}

mixed ask_luan()
{
        object me;

        me = this_player();
        if( query("can_perform/damo-jian/luan", me) )
                return "�Լ��úö���ϰ�ɣ��μǴȱ�Ϊ����������ã�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) +
                       "�����������ֵ��ӣ��γ����ԣ�";

        if (! me->is_apprentice_of(this_object()))
                return "���з��ҵ��Ӳ��ܴ���������λ" +
                       RANK_D->query_respect(me) + "���¡�";

        if( query("shen", me)<120000 )
                return "�������ڽ�����ħ�����Ȼ�����ڴ˵����ֺα�ѧ����";

        if (me->query_skill("damo-jian", 1) < 200)
                return "��Ĵ�ħ�����������ң��޷�������а��";

        if( query("family/gongji", me)<600 )
                return "��Ϊ��������Ч�����������������Ȳ�æ���㡣";

        message_vision(HIY "$n" HIY "����$N" HIY
                       "���������ðɣ���������ϸ�ˣ���˵����$N"
                       HIY "��������˵��Щʲô��\n" NOR,
                       me, this_object());
        command("say ��ס�����ǽ�����ħ�򲻵��ѣ���Ҫ����ʹ�á�");
        tell_object(me, HIG "��ѧ���˴�ħ��������\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 160000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1600000);
        if (me->can_improve_skill("damo-jian"))
                me->improve_skill("damo-jian", 1600000);
        me->improve_skill("martial-cognize", 1600000);
        set("can_perform/damo-jian/luan", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_qingxin()
{
        object me;

        me = this_player();
        if( query("can_perform/damo-jian/qingxin", me) )
                return "�Լ��úö���ϰ�ɣ��μǴȱ�Ϊ����������ã�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�����������ֵ��ӣ��γ����ԣ�";

        if (! me->is_apprentice_of(this_object()))
                return "���з��ҵ��Ӳ��ܴ���������λ" +
                       RANK_D->query_respect(me) + "���¡�";

        if( query("shen", me)<120000 )
                return "�������ڽ�����ħ�����Ȼ�����ڴ˵����ֺα�ѧ����";

        if (me->query_skill("damo-jian", 1) < 200)
                return "��Ĵ�ħ�����������ң��޷�������а��";

        if( query("family/gongji", me)<600 )
                return "��Ϊ��������Ч�����������������Ȳ�æ���㡣";

        message_vision(HIY "$n" HIY "����$N" HIY
                       "���������ðɣ���������ϸ�ˣ���˵����$N"
                       HIY "��������˵��Щʲô��\n" NOR,
                       me, this_object());
        command("say ��ס�����ǽ�����ħ�򲻵��ѣ���Ҫ����ʹ�á�");
        tell_object(me, HIG "��ѧ���˴�ħ���Ľ���\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 160000);
        if (me->can_improve_skill("damo-jian"))
                me->improve_skill("damo-jian", 1600000);
        me->improve_skill("martial-cognize", 1600000);
        set("can_perform/damo-jian/qingxin", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_shang()
{
        object me;

        me = this_player();
        if( query("can_perform/damo-jian/shang", me) )
                return "�Լ��úö���ϰ�ɣ��μǴȱ�Ϊ����������ã�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) +
                       "�����������ֵ��ӣ��γ����ԣ�";

        if (! me->is_apprentice_of(this_object()))
                return "���з��ҵ��Ӳ��ܴ���������λ" +
                       RANK_D->query_respect(me) + "���¡�";

        if( query("shen", me)<120000 )
                return "�������ڽ�����ħ�����Ȼ�����ڴ˵����ֺα�ѧ����";

        if (me->query_skill("damo-jian", 1) < 200)
                return "��Ĵ�ħ�����������ң��޷�������а��";

        if( query("family/gongji", me)<600 )
                return "��Ϊ��������Ч�����������������Ȳ�æ���㡣";

        message_vision(HIY "$n" HIY "����$N" HIY
                       "���������ðɣ���������ϸ�ˣ���˵����$N"
                       HIY "��������˵��Щʲô��\n" NOR,
                       me, this_object());
        command("say ��ס�����ǽ�����ħ�򲻵��ѣ���Ҫ����ʹ�á�");
        tell_object(me, HIG "��ѧ���˴�ħ���񽣡�\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 160000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 160000);
        if (me->can_improve_skill("damo-jian"))
                me->improve_skill("damo-jian", 1600000);
        me->improve_skill("martial-cognize", 1600000);
        set("can_perform/damo-jian/shang", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

mixed ask_zhe()
{
        object me;

        me = this_player();
        if( query("can_perform/damo-jian/zhe", me) )
                return "�Լ��úö���ϰ�ɣ��μǴȱ�Ϊ����������ã�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) +
                       "�����������ֵ��ӣ��γ����ԣ�";

        if (! me->is_apprentice_of(this_object()))
                return "���з��ҵ��Ӳ��ܴ���������λ" +
                       RANK_D->query_respect(me) + "���¡�";

        if( query("shen", me)<120000 )
                return "�������ڽ�����ħ�����Ȼ�����ڴ˵����ֺα�ѧ����";

        if (me->query_skill("damo-jian", 1) < 200)
                return "��Ĵ�ħ�����������ң��޷�������а��";

        if( query("family/gongji", me)<600 )
                return "��Ϊ��������Ч�����������������Ȳ�æ���㡣";

        message_vision(HIY "$n" HIY "����$N" HIY
                       "���������ðɣ���������ϸ�ˣ���˵����$N"
                       HIY "��������˵��Щʲô��\n" NOR,
                       me, this_object());
        command("say ��ס�����ǽ�����ħ�򲻵��ѣ���Ҫ����ʹ�á�");
        tell_object(me, HIG "��ѧ���˴�ħ��Ԫ����\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 160000);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 160000);
        if (me->can_improve_skill("damo-jian"))
                me->improve_skill("damo-jian", 1600000);
        me->improve_skill("martial-cognize", 1600000);
        set("can_perform/damo-jian/zhe", 1, me);
        addn("family/gongji", -600, me);
        return 1;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "��Ħ������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/damo-jian/sanjue",
                           "name"    : "��Ħ������",
                           "sk1"     : "damo-jian",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "sk3"     : "buddhism",
                           "lv3"     : 200,
                           "gongxian": 600, ]));
                break;

        case "ȼľ����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/ranmu-daofa/zhenyan",
                           "name"    : "ȼľ����",
                           "sk1"     : "ranmu-daofa",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "sk3"     : "buddhism",
                           "lv3"     : 200,
                           "gongxian": 600, ]));
                break;

        case "����ʴ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/ranmu-daofa/huo",
                           "name"    : "����ʴ��",
                           "sk1"     : "ranmu-daofa",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "sk3"     : "buddhism",
                           "lv3"     : 200,
                           "gongxian": 600, ]));
                break;
        case "��շ�ħ��" :
               return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/jingang-zhi/fumo",
                             "name"    : "��շ�ħ��",
                             "sk1"     : "jingang-zhi",
                             "lv1"     : 120,
                             "sk2"     : "force",
                             "lv2"     : 120,
                             "sk3"     : "buddhism",
                             "lv3"     : 200,
                             "gongxian": 600, ]));
                  break;
        case "һָ������" :
               return MASTER_D->teach_pfm(me, this_object(),
                            ([ "perform" : "can_perform/jingang-zhi/san",
                               "name"    : "һָ������",
                               "sk1"     : "jingang-zhi",
                               "lv1"     : 120,
                               "sk2"     : "force",
                               "lv2"     : 120,
                               "sk3"     : "buddhism",
                               "lv3"     : 200,
                               "gongxian": 600, ]));
                    break;
        case "��������" :
                             return MASTER_D->teach_pfm(me, this_object(),
                              ([ "perform" : "can_exert/yijinjing/jiuyang",
                                 "name"    : "��������",
                                 "sk1"     : "yijinjing",
                                 "lv1"     : 120,
                                 "sk2"     : "force",
                                 "lv2"     : 120,
                                 "sk3"     : "buddhism",
                                 "lv3"     : 200,
                                 "gongxian": 600, ]));
                      break;
        case "�������" :
                             return MASTER_D->teach_pfm(me, this_object(),
                              ([ "perform" : "can_exert/yijinjing/buddha",
                                 "name"    : "�������",
                                 "sk1"     : "yijinjing",
                                 "lv1"     : 1000,
                                 "sk2"     : "force",
                                 "lv2"     : 1000,
                                 "sk3"     : "buddhism",
                                 "lv3"     : 1000,
                                 "reborn"  : 1,
                                 "gongxian": 3000, ]));
                      break;
        case "��ָѨ" : 
                return MASTER_D->teach_pfm(me, this_object(), 
                        ([ "perform" : "can_perform/lunhui-jian/zhi", 
                           "name"    : "��ָѨ", 
                           "sk1"     : "lunhui-jian", 
                           "lv1"     : 160, 
                           "force"   : 300, 
                           "gongxian": 550, 
                           "neili": 2000, 
                           "shen"    : 30000, ])); 
                break; 
        case "�������" : 
                return MASTER_D->teach_pfm(me, this_object(), 
                        ([ "perform" : "can_perform/lunhui-jian/ru", 
                           "name"    : "�������", 
                           "sk1"     : "lunhui-jian", 
                           "lv1"     : 200, 
                           "neili"   : 4000, 
                           "force"   : 300, 
                           "gongxian": 1000, 
                           "shen"    : 100000, ])); 
                break; 
        case "�����ֻ�" : 
                return MASTER_D->teach_pfm(me, this_object(), 
                        ([ "perform" : "can_perform/lunhui-jian/lun", 
                           "name"    : "�����ֻ�", 
                           "sk1"     : "lunhui-jian", 
                           "lv1"     : 240, 
                           "neili"   : 5000, 
                           "force"   : 350, 
                           "gongxian": 1500, 
                           "shen"    : 100000, ])); 
                break; 
         

        default:
                return 0;
        }
}
