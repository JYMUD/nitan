// ���ǰ�����Ը��츳������

#include <ansi.h>

inherit NPC;

mixed ask_chucun();       //�������

void create()
{
        set_name(HIC "����" NOR, ({ "hua bo", "hua", "bo" }));
        set("long", @LONG
����һ�����ɵ����ߣ��������а�ʮ���꣬�����ϴ峤��ͽ�ܣ�
�����Ҫ���壬����������ask hua about ���壩��
LONG);        
        set("gender", "����" );
        set("title", HIR "�Ŵ�����" NOR); 
        set("age", 88);
        set("attitude", "friendly");
        set("max_jing", 5000000);
        set("max_qi", 5000000);
        set("max_jingli", 5000000);
        set("jingli", 5000000);
        set("max_neili", 5000000);
        set("neili", 5000000);
        set("jiali", 600);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);
        set("combat_exp", 100000000);

        set("inquiry", ([
                "����" : (: ask_chucun :),
        ]));

        set_skill("dodge", 800);
        set_skill("unarmed", 800);
        set_skill("force", 800);
        set_skill("parry", 800);
        set_skill("sword", 800);
        set_skill("poison", 800);
        set_skill("medical", 800);
        set_skill("hand", 800);
        set_skill("strike", 800);
        set_skill("staff", 800);
        set_skill("finger", 800);
        set_skill("claw", 800);
        set_skill("blade", 800);
        set_skill("pixie-jian", 800);
        set_skill("literate", 800);
        set_skill("taoism", 800);
        set_skill("buddhism", 800);
        set_skill("jiuyang-shengong", 800);
        set_skill("lingbo-weibu", 800);
        set_skill("qiankun-danuoyi", 800);
        set_skill("xuanming-zhang", 800);
        set_skill("jiuyin-baiguzhao", 800);
        set_skill("dugu-jiujian", 800);
        set_skill("qianzhu-wandushou", 800);
        set_skill("ranmu-daofa", 800);
        set_skill("dagou-bang", 800);
        set_skill("shaolin-yishu", 800);
        set_skill("wudu-qishu", 800);
        set_skill("throwing", 800);
        set_skill("mantian-xing", 800);
        set_skill("idle-force", 800);
        set_skill("sad-strike", 800);

        map_skill("unarmed", "sad-strike");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("strike", "xuanming-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("sword", "dugu-jiujian");
        map_skill("blade", "ranmu-daofa");
        map_skill("staff", "dagou-bang");
        map_skill("throwing", "mantian-xing");
        map_skill("poison", "wudu-qishu");
        map_skill("medical", "shaolin-yishu");

        prepare_skill("unarmed", "sad-strike");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.po" :),
                (: perform_action, "blade.zhenyan" :),
                (: perform_action, "blade.huo" :),
                (: perform_action, "staff.wugou" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.ban" :),
                (: perform_action, "unarmed.xiao" :),
                (: perform_action, "parry.nuoyi" :),
                (: perform_action, "dodge.lingbo" :),
                (: perform_action, "throwing.shan" :),
                (: perform_action, "hand.zhugu" :),
                (: perform_action, "strike.wuji" :),
                (: perform_action, "finger.six" :),
                (: perform_action, "finger.zhongheng" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));

        setup();
        carry_object("d/city/obj/cloth")->wear();
}

int accept_fight(object me)
{
          tell_object(me, HIG "��λ" + RANK_D->query_respect(me) +
                "���㻹�ǵ����䳡���˱��԰ɣ�\n" NOR);
          return 0;
}

mixed ask_chucun()
{
        object me;
        string msg;

        me = this_player();

        if( !query("newbie_quest_completed/can_out", me) )
                return "û����ʦ�������ҿɲ���������壡\n";

        if( query("combat_exp", me)>200000 )
        {
                return "�Բ����㾭��̫���ˣ�������Ҳ�ﲻ�����ˣ����鲻�ܳ���20�򣩣�\n";
        }

        msg = HIG "�ðɣ���ѡ����Ҫȥ�ĵط��ɣ�\n" NOR;
        msg+= HIW "--------------------------------------------\n" NOR;
        msg+= HIC "1. ֱ�ӳ��壨����������\n" NOR;
        msg+= HIC "2. �����������������������⣩\n" NOR;
        msg+= HIC "3. ��ʦ������������ʦ������\n" NOR;
        msg+= HIC "4. �һ������ڹŴ��Ĵ����ɡ�\n" NOR;
        msg+= HIW "--------------------------------------------\n" NOR;
        msg+= HIR "������1��4��š�\n\n" NOR;

        tell_object(me, msg);

        input_to("get_select", me);
        
        return 1;
}

void get_select(string arg, object me)
{
        string msg;

        if (! arg || arg == "4")return;

        if (arg != "1" && arg != "2" && arg != "3")
        {
                tell_object(me, HIG "������ 1��4 �е����֣�\n");
                input_to("get_select", me);
                return;
        }

        
        if (arg == "1")
        {
                me->move("/d/city/wumiao");
                set("startroom", "/d/city/wumiao", me);

                // �������5����10��Ǳ��
                addn("combat_exp", 50000, me);
                addn("potential", 100000, me);
                tell_object(HIG "���ֽ�������ɹ����Ŵ壬���5�����10��Ǳ�ܵĽ�����\n" NOR);
                        
                // ȡ����ʦ��־
                delete("family", me);
                delete("title", me);
                set("title", "��ͨ����", me);

                // ��������
                set("mud_age", 0, me);
                me->save();
                return;
        }
        if (arg == "2")
        {
                me->move("/d/wuguan/guofu_gate");
                tell_object(me, BLINK + HIR "\n����ָ�� join ���� ���������\n" NOR);
                set("startroom", "/d/wuguan/guofu_gate", me);

                // �������5����10��Ǳ��
                addn("combat_exp", 50000, me);
                addn("potential", 100000, me);
                tell_object(HIG "���ֽ�������ɹ����Ŵ壬���5�����10��Ǳ�ܵĽ�����\n" NOR);
                                
                // ȡ����ʦ��־
                delete("family", me);
                delete("title", me);
                set("title", "��ͨ����", me);
                // ��������
                set("mud_age", 0, me);
                me->save();
                return;
        }
        if (arg == "3")
        {
                msg = HIC "��ѡ����Ҫȥ�����ɣ��ҽ����㵽���ɰ�ʦ������\n" NOR;
                msg+= HIW "------------------------------------------\n" NOR;
                msg+= HIY "f1.  ��ɽ��            f15. Ѫ����\n"
                          "f2.  ��ɽ��            f16. ������\n"
                          "f3.  ��ɽ��            f17. ؤ  ��\n"
                          "f4.  ������            f18. ���ư�\n"
                          "f5.  �䵱��            f19. �컨��\n"
                          "f6.  ������            f20. �嶾��\n"
                          "f7.  ��ң��            f21. ��  ��\n"
                          "f8.  ���չ�            f22. ��ڤ��\n"
                          "f9.  ������            f23. ÷  ׯ\n" 
                          "f10. ��Ĺ��            f24. ѩɽ��\n"
                          "f11. ȫ����            f25. ��Զ�ھ�\n"
                          "f12. ������            f26. �����\n"
                          "f13. �һ���            f27. �������\n"
                          "f14. ҩ����\n\n"
                          "s1.  ŷ������          s2.  ��ԭ���\n"
                          "s3.  Ľ������          s4.  ���Ե��̼ұ�\n"
                          "s5.  �������          s6.  �������\n\n" NOR;
               msg+= HIW "--------------------------------------\n" NOR;
               msg+= HIR "������f1��f15��s1��s6��š�\n\n" NOR;

               tell_object(me, msg);
               input_to("get_sel_fam", me);

               return;                
        }
        return;                
        
}

void get_sel_fam(string arg, object me)
{
        
        mapping path;
        string where;

        path = ([
            "f1"    :  "/d/huashan/laojun",
            "f2"    :  "/d/songshan/dadian",
            "f3"    :  "/d/henshan/zhurongdian",
            "f4"    :  "/d/shaolin/guangchang1",
            "f5"    :  "/d/wudang/sanqingdian",
            "f6"    :  "/d/emei/huayanding",
            "f7"    :  "/d/xiaoyao/xiaodao4",
            "f8"    :  "/d/lingjiu/damen",
            "f9"    :  "/d/xingxiu/xxh1",
            "f10"   :  "/d/gumu/mumen", 
            "f11"   :  "/d/quanzhen/jiaobei",
            "f12"   :  "/d/kunlun/guangchang",
            "f13"   :  "/d/taohua/jingshe",
            "f14"   :  "???",
            "f15"   :  "/d/xuedao/shandong2",
            "f16"   :  "/d/xueshan/shanmen",
            "f17"   :  "/d/gaibang/inhole",
            "f18"   :  "/d/tiezhang/guangchang",
            "f19"   :  "/d/huijiang/damen",
            "f20"   :  "/d/wudu/neijin",
            "f21"   :  "/d/mingjiao/shanmen",
            "f22"   :  "/d/xuanminggu/zulin2",
            "f23"   :  "/d/meizhuang/keting",
            "f24"   :  "/d/lingxiao/gate",
            "f25"   :  "/d/beijing/gate",
            "f26"   :  "/d/jueqing/shanzhuang",
            "f27"   :  "0",
            "s1"    :  "/d/city/beidajie1",
            "s2"    :  "/d/zhongzhou/miaojia_houting",
            "s3"    :  "/d/yanziwu/shuiyun",
            "s4"    :  "/d/shaolin/guangchang1",
            "s5"    :  "/d/guanwai/xiaowu",
            "s6"    :  "/d/dali/neitang",

        ]);

        
        if (! arg)return;

        if (arg == "f14")
        {
                tell_object(me, HIG "ҩ������ʱ��û���ţ�\n" NOR);
                get_select("3", me);
                return;
        }
        if (arg == "f25")
        {
                tell_object(me, HIG "��Զ�ھ���ʱ��û���ţ�\n" NOR);
                get_select("3", me);
                return;
        }
        // ������̷���Ů
        if (arg == "f27")
        {
                if( query("gender", me) == "����" )
                {
                        where = "/d/heimuya/pingdingzhou";
                }
                else
                        where = "/d/heimuya/shenggu";

        }

        if (! stringp(where))where = path[arg];

        if (! stringp(where))
        {
                tell_object(me, HIR "�����Ŵ���\n" NOR);
                get_select("3", me);
                return;
        }


        // �������5����10��Ǳ��
        addn("combat_exp", 50000, me);
        addn("potential", 100000, me);
        tell_object(HIG "���ֽ�������ɹ����Ŵ壬���5�����10��Ǳ�ܵĽ�����\n"
                        "����������(����)������ָ�� ask nanxian ���ָ��� ������ȡ���ָ���!\n" NOR);
                
        // ȡ����ʦ��־
        delete("family", me);
        delete("title", me);
                set("title", "��ͨ����", me);
        // ��������
        set("mud_age", 0, me);
        // ȡ����½�ص�
        set("startroom", where, me);

        //write("where = " + where +"\n");
        // �ƶ���ȥ
        me->move(where);
        me->save();

        return;
}

void init()
{
        object me;

        me = this_player();

        tell_object(me, HIG "\n��������˵������λ" + RANK_D->query_respect(me) +
                "�����Ҫ�������� " HIR "ask hua about ���� \n\n" NOR);

        return;

}
