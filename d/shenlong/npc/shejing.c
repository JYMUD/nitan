#include <ansi.h>

#define MEMBER_D "/adm/daemons/memberd"
#define MAX_POINT 200

inherit NPC;

string slong();

void check_weapon();
void check_environment();
void die_gift();
void check_time();
void random_move();

void create()
{
        set_name(HIR "��ͷ�߾�" NOR, ({ "jiutou shejing", "jiutou", "shejing" }) );
        set("title", HIY "ǧ��" NOR);
        set("gender", "Ů��");
        set("age", 999);

        set("str", 60);
        set("int", 80);
        set("con", 60);
        set("dex", 70);

        set_temp("apply/attack", 5000);
        set_temp("apply/unarmed_damage", 5000);
        set_temp("apply/damage", 5000);
        set_temp("apply/armor", 5000);

        set("max_qi", 9000000000);
        set("eff_qi", 9000000000);
        set("qi", 9000000000);

        set("max_jing", 9000000000);
        set("jing", 9000000000);
        set("eff_jing", 9000000000);
        set("max_jingli", 9000000000);
        set("jingli", 9000000000);

        set("neili", 2000000000);
        set("max_neili", 20000000);
        set("jiali", 4000);
        set("combat_exp", 2100000000);

        set_skill("unarmed", 1500);
        set_skill("finger", 1500);
        set_skill("claw", 1500);
        set_skill("strike", 1500);
        set_skill("hand", 1500);
        set_skill("cuff", 1500);
        set_skill("parry", 1500);
        set_skill("dodge", 1500);
        set_skill("force", 1500);
        set_skill("sword", 1500);
        set_skill("pixie-jian",1500);
        set_skill("blade", 1500);
        set_skill("zuoyou-hubo", 1500);

        set_skill("badao", 1500);
        set_skill("jiuyin-shengong", 1500);
        set_skill("martial-cognize", 1600);
        set_skill("literate", 1500);

        set("no_nuoyi", 1); // ����Ų��Ӱ��

        map_skill("parry", "jiuyin-shengong");
        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("finger", "jiuyin-shengong");
        map_skill("strike", "jiuyin-shengong");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");
        map_skill("sword", "pixie-jian");
        map_skill("blade", "badao");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");

        // ����
        set("life", 9);

        // yun perform
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                // �Ե�
                (: command("perform blade.san and blade.juan") :),
                (: command("perform blade.gui and blade.xiong") :),
                (: command("perform blade.gui twice") :),
                (: command("perform blade.xiong twice") :),
                (: command("perform blade.xiong and balde.juan") :),
                (: command("perform blade.gui and blade.juan") :),
                (: command("perform blade.dasha and blade.san") :),
                (: command("perform blade.san twice") :),
                (: command("perform blade.san twice") :),
                (: command("perform blade.san twice") :),
                (: command("perform blade.san twice") :),
                // ������
                (: command("perform claw.zhua twice") :),
                (: command("perform claw.xin twice") :),
                (: command("perform shou twice") :),
                (: command("perform quan twice") :),

                (: exert_function, "roar" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "roar" :),
                (: exert_function, "recover" :),
                (: check_weapon :),
                (: check_environment :),
                (: check_time :),
        }));

        set("long", HIR "����һ�����ǧ����߾�������ǧ����������ѻ�Ϊ���Σ��볣�����졣\n"
                    HIM "���������ɣ��������ף����˶��ˣ��������˼��κ��������ݡ�\n"
                    HIM "����ɫ�԰ף�û��һ˿Ѫɫ���ƺ�������У��Ӳ����ݡ�\n" NOR + slong());

        setup();

        // �·���Ҫ���ģ������·���
        //carry_object("/clone/cloth/cloth")->wear();

        // ����
        carry_object("/clone/weapon/haoyue-wandao")->wield();

        // ���õص�
        set("startroom", "/d/shenlong/shejingdong");

}

void heart_beat()
{
        keep_heart_beat();

        if( !environment(this_object()) )
        {
                set_heart_beat(0);
                return;
        }

        check_time();
        check_environment();

        if( !objectp(this_object()) ) return;
        if( !environment(this_object()) )
                return;
        return ::heart_beat();
}

// ���ʱ�� 6 Сʱ����ʧ
// δս��״̬����ʧ
void check_time()
{
        int t;
        object env;

        // ͬʱ��������
        set("neili", 20000000);

        t = time() - query("life_time");

        if (t > 60 && ! is_fighting())
        {
                env = environment(this_object());
                env->move_all_player_out(1);
                destruct(this_object());
                return;
        }

        if (t > 2 * 3600)
        {
                message_vision(BLINK + HIG "\n�˴ζԿ��߾��Ѿ�����2Сʱ����սʧ�ܣ�\n" NOR, this_object());
                env = environment(this_object());
                env->move_all_player_out(1);
                destruct(this_object());
                return;
        }

        return;
}

// ���ص�
void check_environment()
{        /*
        if (! environment(this_object()))return;

        if (base_name(environment(this_object())) != query("startroom"))
        {
                command("say �ף�����ô��������������ף��������ף���ʦ�������");
                destruct(this_object());
        }
*/

}

// �������
void check_weapon()
{
        object me, ob;

        me = this_object();

        if( !query_temp("weapon", me) )
        {
                ob = new("/clone/weapon/haoyue-wandao");
                ob->move(me);
                "/cmds/std/wield"->main(me, "haoyue wandao");
        }

        // ͬʱ��������
        set("neili", 20000000);

        if (random(10) == 1)
        {
                //log_file("shejing", "�ɹ�ɾ��BUSY��NO_PERFORM��״̬���ݡ���\n");
                delete_temp("no_perform", me);
                delete_temp("no_exert", me);
                me->interrupt_me(me);

                addn_temp("apply/damage", 50000, me);
                command("perform blade.san twice");
                addn_temp("apply/damage", -50000, me);

                if (random(2))
                {
                        delete_temp("eff/jiuyin-shengong/xin", me);
                }
        }

        if (me->is_busy()) me->interrupt_busy(this_object(),1000);

        // ��С���ʻָ���Ѫ
        if (random(20) == 1)
        {
                //log_file("shejing", "�ɹ��ָ���Ѫ��\n");
                if( query("eff_qi", me)<query("max_qi", me)/3)addn("eff_qi",query("max_qi",  me)/5, me);
                if( query("qi", me)<query("max_qi", me)/3)addn("qi",query("max_qi",  me)/5, me);
        }

        return;
}

// ��������
string slong()
{
        string msg;

        msg = HIG "ֻ���߾������ " + chinese_number(query("life")) + " ��ͷ��\n" NOR;

        return msg;
}

void init()
{
        object me;

        me = this_player();

        if (! wizardp(me))
                this_object()->kill_ob(me);
}

int accept_hit(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_kill(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int receive_damage(string type, int damage, object who)
{
        object ob;

        if (! objectp(who))
                return ::receive_damage(type, damage, who);

        if( random(10000) == 1 && time()-query_temp("last_get_shejing_linpian", who)>1800 )
        {
                ob = new("/d/shenlong/npc/obj/linpian");
                ob->move(who, 1);
                set("last_get_shejing_linpian", time(), ob);
                tell_object(who, HIG "\n���" + name() + HIG "���ϻ����" + ob->name() + HIG "��\n" NOR);
        }

        if (random(100000) == 1)
        {
                check_weapon();
        }

        return ::receive_damage(type, damage, who);
}

void unconcious()
{
        object ob;

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
                return;
        }

        die(query_last_damage_from());
}

// �������
void check_life()
{
        object env;

        // ���life<=1������
        if (query("life") <= 1)
        {
                message_vision(HIR "\n$N" HIR "��Хһ���������������͸������ʧ�ˣ�\n" NOR, this_object());

                message_vision(BLINK + HIY "\n�˴ζԿ��߾��Ѿ�������2���Ӻ��峡����ץ��ʱ�䡣\n\n" NOR, this_object());

                env = environment(this_object());
                env->move_all_player_out(120);
                set("doing", 1, env);
                destruct(this_object());
        }
        else
        {
                // ��������

                message_vision(HIR "\n����~һ����һ��ͷ­��$N" HIR "����ϵ�������������һ̲Ѫ�� ���� һ�ɴ̱ǵ�Ѫ��ζ"
                             "�˱Ƕ�����\n" NOR, this_object());

                set("str", 60);
                set("int", 80);
                set("con", 60);
                set("dex", 60);

                set("max_qi", 90000000);
                set("eff_qi", 90000000);
                set("qi", 90000000);

                set("max_jing", 90000000);
                set("jing", 90000000);
                set("eff_jing", 90000000);
                set("max_jingli", 90000000);
                set("jingli", 90000000);

                set("neili", 20000000);
                set("max_neili", 150000);
                set("jiali", 400);
                set("combat_exp", 2100000000);
                revive();

                addn("life", -1);

                // ���һ��ͷ��ǿ����
                if (query("life") == 1)
                {
                        set_skill("unarmed", 2000);
                        set_skill("finger", 2000);
                        set_skill("claw", 2000);
                        set_skill("strike", 2000);
                        set_skill("hand", 2000);
                        set_skill("cuff", 2000);
                        set_skill("parry", 2000);
                        set_skill("dodge", 2000);
                        set_skill("force", 2000);
                        set_skill("sword", 2000);
                        set_skill("pixie-jian",2000);
                        set_skill("blade", 2000);
                        set_skill("zuoyou-hubo", 2000);

                        set_skill("badao", 2000);
                        set_skill("jiuyin-shengong", 2000);
                        set_skill("martial-cognize", 2000);
                }

                set("long", HIR "����һ�����ǧ����߾�������ǧ����������ѻ�Ϊ���Σ��볣�����졣\n"
                               HIM "���������ɣ��������ף����˶��ˣ��������˼��κ��������ݡ�\n"
                            HIM "����ɫ�԰ף�û��һ˿Ѫɫ���ƺ�������У��Ӳ����ݡ�\n" NOR + slong());

                set("neili", 2000000);
                return;
        }
}

void die(object killer)
{
        object dob;             // �������NPC����
        int n;                  // ���Խ������˵���Ŀ
        int exp;                // ��Ҫ�Ϸֵľ���
        int pot;                // ��Ҫ�Ϸֵ�Ǳ��
        int weiwang;            // ��Ҫ�Ϸֵ�����
        int score;              // ��Ҫ�Ϸֵ�����
        object *t;              // ɱ���ҵ��˵Ķ����б�
        object tob;
        int mar;                //  ��Ҫ�Ϸֵ����
        int i;
        object ob_yuanbao;      // ��Ԫ��
        string prop, name;
        mapping data;
        object ob, where;
        string *apply = ({ "reduce_busy", "avoid_busy", "def_damage", "avoid_weak",
                "add_forget", "reduce_damage", "add_busy", "add_weak", "avoid_forget",
                "add_damage", "add_skill" });


        // ���影����Ʒ�б�
        // ����  X / �ٷ�֮
        mixed oblist = ([
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/zhanhun-xue3"              :                15,
                "/clone/armor/fenghuang-chai3"           :                10,
                "/clone/armor/feima-xue3"                :              20,
                "/clone/armor/shengling-yaodai3"         :              30,
                "/clone/armor/shangu-zhixing3"           :              20,
                "/clone/book/xuedao-book1"               :              35,
                "/clone/book/xuanxudao-book"             :              35,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/zhanhun-xue3"              :                15,
                "/clone/armor/fenghuang-chai3"           :                10,
                "/clone/armor/feima-xue3"                :              20,
                "/clone/armor/shengling-yaodai3"         :              30,
                "/clone/armor/shangu-zhixing3"           :              20,
                "/clone/book/xuedao-book1"               :              35,
                "/clone/book/xuanxudao-book"             :              35,

                "/clone/armor/shuijing-guan"             :              5,
                "/clone/armor/shuijing-guan2"            :              3,
                "/clone/armor/shuijing-guan3"            :              1,
                "/clone/horse/chaoying"                  :              2,
                "/clone/tuteng/diwang-suipian43"         :              5,
                "/clone/tuteng/diwang-suipian44"         :              5,
                "/clone/tuteng/diwang-suipian45"         :              5,
                "/clone/tuteng/diwang-suipian46"         :              5,
                "/clone/tuteng/diwang-suipian11"         :              5,
                "/clone/tuteng/diwang-suipian12"         :              5,
                "/clone/tuteng/diwang-suipian13"         :              5,
                "/clone/tuteng/diwang-suipian14"         :              5,
                "/clone/armor/sheyao-ring"               :              15,
                "/clone/armor/sheyao-ring2"              :              10,
                "/clone/armor/sheyao-ring3"              :              5,

                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
        ]);

        object gift_ob;
        string s_gift, *key_s_gift;
        int gift_point;

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
                return;
        }

        // �ҵ�ɱ����(NPC)���Ǵ����ҵ���
        if (! objectp(dob = killer))
                dob = query_last_damage_from();

        if (! dob)
        {
                // ����������麯��
                check_life();
                return;
        }

        t = dob->query_team();

              // ������ͼ
        // ���43-46, 11-14
        if( MEMBER_D->is_valid_member(dob) && query("quest_tuteng/start", dob) )
        {
                int n_tt;
                object ob_tt;

                if (random(1000) == 1)
                {
                        n_tt = 43 + random(4);
                        if (random(3) == 1)n_tt = 11 + random(4);
                        ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                        if (ob_tt)
                        {
                                write(HIG "������һ�ŵ�����ͼ��Ƭ��\n" NOR);
                                ob_tt->move(dob, 1);
                        }
                }
        }

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = 60000 + random(80000);
                pot = 80000 + random(80000);
                weiwang = 30000 + random(50000);
                score = 40000 + random(40000);
                mar = 10000 + random(30000);
                n = 0;

                n = sizeof(t);
                if (! n || n < 3)
                {
                       exp /= 5;
                       pot /= 5;
                       weiwang /= 3;
                       score /= 3;
                       mar /= 5;
                }

                if (n >= 3)
                {
                        exp /= n;
                        pot /= n;
                        weiwang /= n;
                        score /= n;
                        mar /= n;
                }

                // ���������30%����
                exp = exp + exp * 3 / 10;
                pot = pot + pot * 3 / 10;
                weiwang = weiwang + weiwang * 3 / 10;
                score = score + score * 3 / 10;
                mar = mar + mar * 3 / 10;

                if (n)
                {
                        foreach(tob in t)
                        {
                                if (objectp(tob) && living(tob))
                                {
                                        // ��Ա���������30%
                                        /*
                                        if( MEMBER_D->is_valid_member(query("id", tob)) )
                                        {
                                                if (environment(tob) == environment(dob))
                                                        GIFT_D->delay_boss_bonus(tob,
                                                                     ([ "exp"      : exp + exp * 3 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "pot"      : pot + pot * 3 / 10 / 10 + ((tob == dob) ? 50000 : 0),
                                                                     "weiwang"  : weiwang + weiwang * 3 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "score"    : score + score * 3 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "mar"      : mar + mar * 3 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "prompt"   : "��Ķ���ɱ��" + name() + HIG "֮��"]), 999);
                                        }
                                        else */
                                        {
                                                if (environment(tob) == environment(dob))
                                                        GIFT_D->delay_boss_bonus(tob,
                                                                ([ "exp"      : exp + ((tob == dob) ? 50000 : 0),
                                                                   "pot"      : pot + ((tob == dob) ? 50000 : 0),
                                                                   "weiwang"  : weiwang + ((tob == dob) ? 50000 : 0),
                                                                   "score"    : score + ((tob == dob) ? 50000 : 0),
                                                                   "mar"      : mar + ((tob == dob) ? 50000 : 0),
                                                                   "prompt"   : "��Ķ���ɱ��" + name() + HIG "֮��"]), 100);
                                        }

                                }
                        }
                }
                else
                {
                        /*
                        if( MEMBER_D->is_valid_member(query("id", dob)) )
                        {
                                GIFT_D->delay_boss_bonus(dob,
                                        ([ "exp"      : exp + exp * 3 / 10,
                                           "pot"      : pot + pot * 3 / 10,
                                           "weiwang"  : weiwang + weiwang * 3 / 10,
                                           "score"    : score + score * 3 / 10,
                                           "mar"      : mar + mar * 3 / 10,
                                           "prompt"   : "����ɱ��" + name() + HIG "֮��"]), 999);
                        }

                        else */
                        {
                                GIFT_D->delay_boss_bonus(dob,
                                        ([ "exp"      : exp,
                                           "pot"      : pot,
                                           "weiwang"  : weiwang,
                                           "score"    : score,
                                           "mar"      : mar,
                                           "prompt"   : "����ɱ��" + name() + HIG "֮��"]), 100);
                       }
                }
        }

        // һ�����ʵ���Ʒ��ɱ�ҵ�������dob
        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                key_s_gift = keys(oblist);
                s_gift = key_s_gift[random(sizeof(key_s_gift))];
                gift_point = oblist[s_gift];

                // �жϼ���
                if( MEMBER_D->is_valid_member(query("id", dob) )
                    && random(MAX_POINT / ITEM_D->gift_point()) < gift_point)
                {
                        // �����Ʒ--������Ʒֱ�ӷ���dob����
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIW "��~~һ������$N" HIW "���ϵ���" + gift_ob->name() + HIW "��$n" HIR
                                                   "�Ͻ�����������\n" NOR, this_object(), dob);
                                tell_object(dob, BLINK + HIG "\n��õ���" + BLINK + gift_ob->name() + BLINK + HIG "��\n" NOR);
                                gift_ob->move(dob, 1);
                        }
                        else // ��¼֮
                        {
                                log_file("shejing-gift-none", s_gift + "\n");
                        }
                }
        }

        // һ�����ʵ���Ʒ�ڵ���
        if (1)
        {
                key_s_gift = keys(oblist);
                s_gift = key_s_gift[random(sizeof(key_s_gift))];
                gift_point = oblist[s_gift];

                // �жϼ���
                if (random(MAX_POINT / ITEM_D->gift_point()) < gift_point)
                {
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + gift_ob->name() + HIC "�����ڵ��ϡ�\n" NOR, this_object());

                                gift_ob->move(environment(this_object()));
                        }
                        else // ��¼֮
                        {
                                log_file("shejing-gift-none", s_gift + "\n");
                        }
                }
        }

        // ÿɱ��һ��ͷ����50��100����Ԫ��
        ob_yuanbao = new("/clone/money/yuanbao");
        ob_yuanbao->set_amount(50 + random(101));
        ob_yuanbao->move(environment(this_object()));
        set("who_get/id", "NONE", ob_yuanbao);
        set("who_get/time", time()+5, ob_yuanbao);//5�����ڶ����ܼ�ȡ

        // ����������������������Ʒ�ڵ���
        if( query("life", this_object()) == 1 )
        {
                die_gift();
        }

        where = environment();

        prop = apply[random(sizeof(apply))];
        name = EQUIPMENT_D->chinese(prop)+"Ԫ��";

        data = ([]);
        data["element"] = prop;
        data["name"] = name;
        ob = TEMPLATE_D->create_object("/inherit/template/element/element", prop, data);
        ob->set_name(name, ({prop, "element"}));
        ob->move(where);
        message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + ob->name() + NOR + HIC "�����ڵ��ϡ�\n" NOR, this_object());

        // �������
        check_life();

        return ;
}
// ����������������������Ʒ�ڵ���
void die_gift()
{
        object gift_ob;
        string s_gift, *key_s_gift;
        int gift_point;
        object ob_xz;
        int i;

        // ���影����Ʒ�б�
        // ����  X / �ٷ�֮
        mapping oblist = ([
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/zhanhun-xue3"              :                15,
                "/clone/armor/fenghuang-chai3"           :                10,
                "/clone/armor/feima-xue3"                :              20,
                "/clone/armor/shengling-yaodai3"         :              30,
                "/clone/armor/shangu-zhixing3"           :              20,
                "/clone/horse/chaoying"                  :              2,
                "/clone/book/xuedao-book1"               :              35,
                "/clone/book/xuanxudao-book"             :              35,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/zhanhun-xue3"              :                15,
                "/clone/armor/fenghuang-chai3"           :                10,
                "/clone/armor/feima-xue3"                :              20,
                "/clone/armor/shengling-yaodai3"         :              30,
                "/clone/armor/shangu-zhixing3"           :              20,
                "/clone/book/xuedao-book1"               :              35,
                "/clone/book/xuanxudao-book"             :              35,

                "/clone/fam/max/naobaijin"               :                5,
                "/clone/armor/shuijing-guan"             :              5,
                "/clone/armor/shuijing-guan2"            :              3,
                "/clone/armor/shuijing-guan3"            :              1,
                "/clone/horse/chaoying"                  :              2,
                "/clone/tuteng/diwang-suipian43"         :              5,
                "/clone/tuteng/diwang-suipian44"         :              5,
                "/clone/tuteng/diwang-suipian45"         :              5,
                "/clone/tuteng/diwang-suipian46"         :              5,
                "/clone/tuteng/diwang-suipian11"         :              5,
                "/clone/tuteng/diwang-suipian12"         :              5,
                "/clone/tuteng/diwang-suipian13"         :              5,
                "/clone/tuteng/diwang-suipian14"         :              5,
                "/clone/armor/sheyao-ring"               :              15,
                "/clone/armor/sheyao-ring2"              :              10,
                "/clone/armor/sheyao-ring3"              :              5,

                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
                "/clone/armor/tiankong-zhiyi3"           :                10,
                "/clone/armor/piaoxue3"                  :                10,
                "/clone/armor/suomai3"                   :                15,
                "/clone/armor/tianming3"                 :                15,
                "/clone/armor/wuwei3"                    :                15,
                "/clone/armor/fenghuang-chai3"           :                20,
                "/clone/armor/haizhi-xin3"               :                20,
                "/clone/armor/hong-feihun3"              :                15,
                "/clone/armor/lan-feihun3"               :                10,
                "/clone/armor/zi-feihun3"                :                10,
                "/clone/armor/moling-zhiyi3"             :                15,
        ]);

        for (i = 0; i < 3; i ++)
        {
                key_s_gift = keys(oblist);
                s_gift = key_s_gift[random(sizeof(key_s_gift))];
                gift_point = oblist[s_gift];
                // �жϼ���
                if (random(MAX_POINT / ITEM_D->gift_point()) < gift_point || 1)
                {
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIC "��~~һ������$N" HIC "���ϵ���" + gift_ob->name() + HIC "�����ڵ��ϡ�\n" NOR, this_object());
                                gift_ob->move(environment(this_object()));
                        }
                        else // ��¼֮
                        {
                                log_file("shejing-gift-none", s_gift + "\n");
                        }
                }
        }

        // 50%���ʱ���ն��ѫ��
        if (random(2) == 1)
        {
                ob_xz = new("/clone/armor/zhanyao-xunzhang");
                ob_xz->move(environment(this_object()));
                message_vision(HIR "�ѵ�~~һ������$N" HIR "���ϵ���һö" + ob_xz->name() + HIR "�����ڵ��ϡ�\n" NOR, this_object());
                set("who_get/id", "NONE", ob_xz);
                set("who_get/time", time()+5, ob_xz);//5���ڶ����ܼ�ȡ
        }

        // 5/100���ʵ�������ͭ��
        if (random(100) < 5)
        {
                object ob_tongren;
                if( random(2) )
                        ob_tongren = new("/clone/tongren/tongren1");
                else
                        ob_tongren = new("/clone/tongren/tongren2");
                message_vision(HIR "��~~һ������$N" HIR "���ϵ���" + ob_tongren->name() + HIR "�����ڵ��ϡ�\n" NOR, this_object());
                set("who_get/id", "NONE", ob_tongren);
                set("who_get/time", time()+30, ob_tongren);//30���ڶ����ܼ�ȡ
                ob_tongren->move(environment(this_object()));
        }
}
