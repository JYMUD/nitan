// This program is a part of NT MudLIB

#include <ansi.h>

inherit NPC;

string *quest_msg = ({
        HIW "���󳤳��ĳ���һ������Ȼ���ͳ�һ��Ӣ�������ݵ�����ǰ����\n" NOR,
        HIW "����˵��������ׯ������֣���Ӧ�ò���İ���ɡ�\n" NOR,
        HIW "ǰЩʱ�������ֵܺ�Ѧ��ҽ�ڽ����Ϲ㷢Ӣ�������ټ�����Ӣ�ۺ��ܹ�������ׯ���μ����ִ�ᡣ\n" NOR,
        HIW "���������Ǹ���ģ������������ĺ�Ϊ�ң����޶���������ׯ�������ӵ����˾Ͱ����Ӣ�����͵����������ˣ�ϣ���ҿ����ҵ��㡣\n" NOR,
        HIW "����������ִ�᾿����Ϊ���£�������Ҳ���Ǻ������ֻ��˵��ؤ����Ī��Ĺ�ϵ�������ϵķ��Զ��������ȥ�ģ��������ŵ��Ѿ������ˡ�\n" NOR,
        HIW "������ȥ������ؤ����쳤�ϣ�����������������ġ�\n" NOR,
});

int ask_juxianzhuang();

void create()
{
        set_name("����", ({ "bei chou", "bei", "chou", "xizi" }));
        set("long", @LONG
����һ������Ϸ�Ӵ�����С��ͷ�����ü���
����������һ�����ࡣ˭����֪����ǵ�����
���кųơ����ͱ���Ϸ�ӱ�������������
����֮�£���ȴҲ��������ƽ��η��֮�ˡ�
LONG);
        set("nickname", HIW "��Ϸ��" NOR);
        set("title", HIC "����̩��" NOR);
        set("gender", "����" );
        set("age", 68);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);
        set("level", 100);

        set_skill("dodge", 500);
        set_skill("unarmed", 500);
        set_skill("force", 500);
        set_skill("parry", 500);
        set_skill("sword", 500);
        set_skill("poison", 500);
        set_skill("medical", 500);
        set_skill("hand", 500);
        set_skill("strike", 500);
        set_skill("staff", 500);
        set_skill("finger", 500);
        set_skill("claw", 500);
        set_skill("blade", 500);
        set_skill("pixie-jian", 500);
        set_skill("literate", 500);
        set_skill("taoism", 500);
        set_skill("buddhism", 500);
        set_skill("jiuyang-shengong", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("xuanming-zhang", 500);
        set_skill("jiuyin-baiguzhao", 500);
        set_skill("dugu-jiujian", 500);
        set_skill("qianzhu-wandushou", 500);
        set_skill("ranmu-daofa", 500);
        set_skill("dagou-bang", 500);
        set_skill("shaolin-yishu", 500);
        set_skill("wudu-qishu", 500);
        set_skill("throwing", 500);
        set_skill("mantian-xing", 500);
        set_skill("idle-force", 500);
        set_skill("sad-strike", 500);

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

        set("inquiry", ([
                "����"  :"Ҫ��������������ӣ������������������Ȼ�� team bunch <������> �Ϳ����ˡ�\n",
                "Ӣ����": (: ask_juxianzhuang :),
                "��սBOSS" : "����սBOSS������ ask bei chou about <BOSS����> ���ɽ�����ս�ռ�", 
        ]) );

        set("chat_chance", 1);
        set("chat_msg",({
                CYN "���������е�˵��������㲻�����㣬��������ô��Ϸ���Ҷ�֪����\n" NOR,
        }));

        setup();
        carry_object("/clone/cloth/cloth")->wear();

/*
        if (! clonep(this_object()))
        {
                move("/d/xiakedao/haibin");
                message_vision(CYN "\n$N" CYN "Ц���������������ˣ�Ϸ�������ˡ�\n"
                               NOR, this_object());
                set("startroom", "/d/xiakedao/haibin");
        }
*/
}

void init()
{
        ::init();
        add_action("do_join", "join");
}

int ask_juxianzhuang()
{
        object me = this_player();
        call_out("quest_stage", 0, me, 0);
        return 1;
}

void quest_stage(object ob, int stage)
{

        if (! ob || ! present(ob)) return;

        tell_object(ob, quest_msg[stage]);
        if (++stage < sizeof(quest_msg))
        {
                call_out( "quest_stage", 1, ob, stage );
                return;
        }
        set_temp("juxianzhuang_step", 1, ob);
}

mixed accept_ask(object me, string arg)
{
        int valid;
           
        if( !arg || arg == "" || arg == "all" )
                return 0;
        
        if( arg == "��սBOSS" || arg == "��սboss" || arg == "BOSS" || arg == "boss" )
        {
                write(HIW"��Ҫ��սBOSS������ ask shizhe about <BOSS����> ���ɽ�����ս�ռ䡣\n"NOR);
                return 1;
        }
        
        valid = FUBEN_D->valid_enter(me, arg); 
        if( valid >=1 )
                FUBEN_D->enter_fuben(me, arg);
        else {
                if( valid == 0 )
                        write("��ʵս���鲻�㣬����սBOSS���в��⣬����������һ�������ɡ�\n");
                else if( valid == -1 )
                        write("������̫���ˣ��Ͳ�Ҫ��ȥ�۸���Щ������С�����˰ɡ�\n");
                else if( valid == -2 )
                        write("��Ϸ��Ŀǰ��û�п��Ÿ�BOSS�������˶Ժ����ԡ�\n");
                else if( valid == -3 )
                        write("��սBOSS����IP���ؽ��룬���Ѿ�����������ޡ�\n");
                else if( valid == -4 )
                        write("��BOSS����ʦ�رգ�����ʱ�޷����롣\n");
                else if( valid == -5 )
                        write("�����ϴ���ս��BOSS��ʱ��̫�̣�����Ϣ��������\n");
                else if( valid == -6 )
                        write("��BOSS������Ӳ��ܽ��롣\n");
                else if( valid == -7 )
                        write("��Ķ�������������BOSS�涨�����ޡ�\n");
                else if( valid == -8 )
                        write("��BOSSҪ������ս���������ɢ���鷽�ɽ��롣\n");
        }        
        return 1;
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        command("say �ߣ���֪���");
        command("exert powerup");
        command("exert sword");
        ::fight_ob(ob);
}

int accept_fight(object who)
{
        command("say û��Ȥ��");
        return 0;
}

int accept_ansuan(object who)
{
        return notify_fail("����밵�㣬������ǰһ��������̫�����\n");
}

varargs void die(object killer)
{
        full_self();
        return;
}

void unconcious()
{
        die();
}
