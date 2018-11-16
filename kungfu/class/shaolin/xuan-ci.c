// This program is a part of NT MudLIB
// xuan-ci.c ���ȴ�ʦ

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#define        IS_XUAN_CI        1

#include "xuan.h"

mixed ask_wldh();
void create()
{
        set_name("���ȴ�ʦ", ({
                "xuanci dashi",
                "xuanci",
                "dashi",
        }));
        set("long",
                "����һλ�����ü����ɮ����һϮ��˿������ġ�\n"
                "������������ͣ���ȴ�����⣬Ŀ�̴�Ц���Ե��������㡣\n"
        );

        set("nickname", "�����·���");
        set("gender", "����");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 70);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 2800);
        set("max_jing", 1400);
        set("neili", 3800);
        set("max_neili", 3800);
        set("jiali", 50);
        set("level", 20);
        set("combat_exp", 1450000);
        set("score", 500000);

        set_skill("force", 170);
        set_skill("hunyuan-yiqi", 170);
        set_skill("dodge", 160);
        set_skill("shaolin-shenfa", 160);
        set_skill("finger", 170);
        set_skill("strike", 170);
        set_skill("hand", 160);
        set_skill("claw", 160);
        set_skill("parry", 160);
        set_skill("nianhua-zhi", 170);
        set_skill("sanhua-zhang", 170);
        set_skill("fengyun-shou", 160);
        set_skill("longzhua-gong", 160);
        set_skill("buddhism", 160);
        set_skill("literate", 160);
        set_skill("medical", 180);
        set_skill("shaolin-yishu", 180);
        set_skill("martial-cognize", 120);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");
        map_skill("hand", "fengyun-shou");
        map_skill("claw", "longzhua-gong");
        map_skill("parry", "nianhua-zhi");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        create_family("������", 36, "����");

        set("master_ob",4);
        setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() &&
            query_temp("juxianzhuang_step", ob) == 4){
                set("inquiry/���ִ��", (: ask_wldh :));
                set("inquiry/����ׯ", (: ask_wldh :));
        }
}

mixed ask_wldh()
{
        object me = this_player();

        if( (int)query_temp("in_speech")
         || query_temp("juxianzhuang_step", me) != 4 )
                return notify_fail("���ȴ�ʦ���Ի�Ŀ��˿��㡣����\n");

        set_temp("in_speech", 1);
        remove_call_out("say_msg");
        call_out("say_msg", 1, me, 1);
        return CYN"�����ӷ�ʩ���������ֵ�Ŀ�������Ѿ��µ��ˡ���ϧ�������ں쳾�⣬���ʺ쳾���ˣ������ӷ𡭡�" NOR;
}

int say_msg(object me, int index)
{
        object ob;

        if( environment() != environment(me) )
                return 0;

        switch( index ) {
        case(1):
                message_vision(CYN"$N˵���������ӷ����ĵ��그�������������մ�һ��������Ҳ���Բ��������ﻹ����ȥ���ʺ쳾�е��ȷ�Ѫ�갡��\n"NOR, this_object(), me);
                break;
        case(2):
                message_vision(WHT"<$Nһ������ǧ���ģ��������$n��ʼ�����������������ű���˫�ı��졣>\n"NOR, this_object(), me);
                break;
        case(3):
                message_vision(CYN"$N˵����������Ȼ�쳤�Ϻ�ʩ�������������Ǻðɣ������ִ�������һ������ѡ�������λʦ��ǰȥ����ׯ�����������ɲμӴ�ᡣ\n"NOR, this_object(), me);
                break;
        case(4):
                message_vision(CYN"$N˵������Ե��������ϲ�����������з��������գ�ʩ�������������飬���Ի��������ҵ���˼ת��(report)���쳤���ˡ�\n"NOR, this_object(), me);
                break;
        case(5):
                message_vision(WHT"<$N˵�����Ŀ�붨����������𾭡�>\n"NOR, this_object(), me);
                break;
        case(6):
                message_vision(CYN"$N������Ҷ�����ʱ�������ڴ��ڣ�������ʮ������������������Ωʧ��������Ϊ����ڿ��\n"NOR, this_object(), me);
                break;
        case(7):
                message_vision(CYN"$N������ҳ�����ҹ��ÿ˼Ω���£�����������ΪʧΪ��ʧ���ҳ������𣬳�������������������ҹ�����������¡�����\n"NOR, this_object(), me);
                break;
        default:
                set_temp("juxianzhuang_step", 5, me);
                delete("inquiry/���ִ��");
                delete("inquiry/����ׯ");
                delete_temp("in_speech");
                return 1;
        }
        remove_call_out("say_msg");
        call_out("say_msg", 0, me,++index);
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

        case "һέ�ɽ�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shaolin-shenfa/du",
                           "name"    : "һέ�ɽ�",
                           "sk1"     : "shaolin-shenfa",
                           "lv1"     : 100,
                           "sk2"     : "dodge",
                           "lv2"     : 100,
                           "gongxian": 1000, ]));
                break;

        case "�޺���ħ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/luohan-quan/xiangmo",
                           "name"    : "�޺���ħ",
                           "sk1"     : "luohan-quan",
                           "lv1"     : 100,
                           "sk2"     : "buddhism",
                           "lv2"     : 100,
                           "gongxian": 200, ]));
                break;

        case "������ͨ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jingang-quan/jingang",
                           "name"    : "������ͨ",
                           "sk1"     : "jingang-quan",
                           "lv1"     : 100,
                           "sk2"     : "buddhism",
                           "lv2"     : 100,
                           "gongxian": 600, ]));
                break;

        case "�黨��Ѩ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/nianhua-zhi/fuxue",
                           "name"    : "�黨��Ѩ",
                           "sk1"     : "nianhua-zhi",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 600, ]));
                break;

        case "��ħһָ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yizhi-chan/jingmo",
                           "name"    : "��ħһָ",
                           "sk1"     : "yizhi-chan",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 600, ]));
                break;

        case "ָ�㽭ɽ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yizhi-chan/dian",
                           "name"    : "ָ�㽭ɽ",
                           "sk1"     : "yizhi-chan",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 600, ]));
                break;

        case "��ɫ����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/wuxiang-zhi/wuse",
                           "name"    : "��ɫ����",
                           "sk1"     : "wuxiang-zhi",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 400, ]));
                break;

        case "��������ָ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xiuluo-zhi/jueming",
                           "name"    : "��������ָ",
                           "sk1"     : "xiuluo-zhi",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 800, ]));
                break;

        case "��շ�ħ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jingang-zhi/fumo",
                           "name"    : "��շ�ħ��",
                           "sk1"     : "jingang-zhi",
                           "lv1"     : 150,
                           "sk2"     : "buddhism",
                           "lv2"     : 200,
                           "gongxian": 600, ]));
                break;

        case "һָ������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jingang-zhi/san",
                           "name"    : "һָ������",
                           "sk1"     : "jingang-zhi",
                           "lv1"     : 200,
                           "sk2"     : "jingluo-xue",
                           "lv2"     : 200,
                           "gongxian": 1000, ]));
                break;

        case "�������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/duoluoye-zhi/jimie",
                           "name"    : "�������",
                           "sk1"     : "duoluoye-zhi",
                           "lv1"     : 150,
                           "sk2"     : "buddhism",
                           "lv2"     : 200,
                           "gongxian": 1000, ]));
                break;

        case "��ħ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/banruo-zhang/feng",
                           "name"    : "��ħ",
                           "sk1"     : "banruo-zhang",
                           "lv1"     : 100,
                           "sk2"     : "buddhism",
                           "lv2"     : 100,
                           "gongxian": 300, ]));
                break;

        case "��Ůɢ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/sanhua-zhang/san",
                           "name"    : "��Ůɢ��",
                           "sk1"     : "sanhua-zhang",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 500, ]));
                break;

        case "Ⱥɽ��Ӱ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xumishan-zhang/ying",
                           "name"    : "Ⱥɽ��Ӱ",
                           "sk1"     : "xumishan-zhang",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 500, ]));
                break;

        case "����˷�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenzhang-bada/bafang",
                           "name"    : "����˷�",
                           "sk1"     : "shenzhang-bada",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 500, ]));
                break;

        case "����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/fengyun-shou/qinna",
                           "name"    : "����",
                           "sk1"     : "fengyun-shou",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 400, ]));
                break;

        case "ǧҶ����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qianye-shou/qianye",
                           "name"    : "ǧҶ����",
                           "sk1"     : "qianye-shou",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 400, ]));
                break;

        case "����ץ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/longzhua-gong/zhua",
                           "name"    : "����ץ",
                           "sk1"     : "longzhua-gong",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 1000, ]));
                break;

        case "������ħ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yingzhua-gong/chumo",
                           "name"    : "������ħ",
                           "sk1"     : "yingzhua-gong",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 600, ]));
                break;

        case "���Ľ�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/fumo-jian/foxin",
                           "name"    : "���Ľ�",
                           "sk1"     : "fumo-jian",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 700, ]));
                break;

        case "��������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xiuluo-dao/suoming",
                           "name"    : "��������",
                           "sk1"     : "xiuluo-dao",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 500, ]));
                break;

        case "����ιӥ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/cibei-dao/sheshen",
                           "name"    : "����ιӥ",
                           "sk1"     : "cibei-dao",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 400, ]));
                break;

        case "�޳��廯" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/wuchang-zhang/wuchang",
                           "name"    : "�޳��廯",
                           "sk1"     : "wuchang-zhang",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 400, ]));
                break;

        case "�������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/pudu-zhang/zhao",
                           "name"    : "�������",
                           "sk1"     : "pudu-zhang",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "sk3"     : "buddhism",
                           "lv3"     : 200,
                           "gongxian": 400, ]));
                break;

        case "�������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zui-gun/zuida",
                           "name"    : "�������",
                           "sk1"     : "zui-gun",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 400, ]));
                break;

        case "Τ�ӷ�ħ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/weituo-gun/fumo",
                           "name"    : "Τ�ӷ�ħ",
                           "sk1"     : "weituo-gun",
                           "lv1"     : 150,
                           "sk2"     : "buddhism",
                           "lv2"     : 150,
                           "gongxian": 400, ]));
                break;

        default:
                return 0;
        }
}
