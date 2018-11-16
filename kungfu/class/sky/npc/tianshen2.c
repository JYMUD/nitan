// ͨ������ �ƹ�ת��
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

#define MEMBER_D   "/adm/daemons/memberd"

mixed start_thborn();

void create()
{
        set_name(HIY "�׻�����" NOR, ({ "yanhuang tianshen", "yanhuang", "tianshen" }));
        set("long", HIY "    �׻������������ݣ��ڴ˹�������ʱ�ˣ����ƺ�����������ϣ����\n"
                        "��������һ�����ӣ���\n" NOR);

        set("gender", "����");
        set("age", 9999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 90000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("unarmed", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "����"   :   (: start_thborn :),
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object(__DIR__"obj/xianpao")->wear();
        carry_object(__DIR__"obj/tianlai-zhiyuan")->hand();
}

mixed start_thborn()
{
        object me = this_player();
        
        mapping job_special;
        string *key_job_special;
        int i, job_add, sk_12t_add, sk_bd_add, sk_lhj_add, total_lhd;
        mapping skills_status;
        string *myskills;
        
        string user, login;
        
        if (me->query("thborn/ok"))
        {
                if (! me->query("thborn/repeat")) // ��repeat��־���ٴ�2ת
                        return "�㲻���Ѿ���ת�����𣬿���뿪�ɣ���Ҫ����ҵ����ˣ�\n";
        }

        // �жϸ��أ�����30%����ת
        if ((int)me->query_encumbrance() * 100 / (int)me->query_max_encumbrance() > 30)
                return "Ϊ������Ʒ���ݰ�ȫ�����ز��ܳ���30%��������һ�±��������ɣ�\n";

        // �����Ѿ�������ϣ�ְҵ����Ѿ�ѡ�񼴿�2ת
        if (me->query("check_yhjob"))
        {
                if (! me->query("yhjob/job"))
                        return "��ѡ��ְҵ��ָ�yhjob <ְҵ>�����������Ұɣ�\n";

                if (! me->query("thborn/ok")) // ������2ת������ʾ������special
                {
                        CHANNEL_D->do_channel(this_object(), "rumor", HIY + me->name() + "(" + me->query("id") + ")" HIY "��������"
                                                                      "֮����������ʶ������˵ڶ���ת����\n" NOR);
                        tell_object(me, HIC "\n��ϲ���ת�ɹ������������⼼�ܡ�������ԡ���\n" NOR);
                        me->set("special_skill/riyue", 1);
                }
                
                me->set("thborn/ok", 1);
                
                command("say ������ڣ�ף����ˣ�");
                me->move("/d/city/wumiao");
                me->delete("thborn/repeat"); // ɾ����������2ת��־
                me->set("thborn/times", time()); // ��¼2תʱ��
                
               // ʮ�����ڼ䣬ת���ɹ�������⽱��
               me->add("combat_exp", 10000000);
               me->add("potential", 10000000);
               me->add("experience", 2000000);
               me->set_skill("force", 300);
               tell_object(me, HIG "��ϲ���׻Ʒ���ʮ���ڼ䣬�ڶ���ת���ɹ���������1000�����Ǳ�ܣ�200����ѧ��\n"
                               "����300�������ڹ�������\n" NOR);
                       
                me->save();
                return 1;
        }
        else
        {
                // ��������
                user =  me->query("id");
                user = "/data/user/" + user[0..0] + "/" + user + ".o";
                login = "/data/login/" + user[0..0] + "/" + user + ".o";
                "/adm/daemons/scbornd"->beifen_thborn(me, user, login);
        }

        // �������һ���10������
        if (! me->query("thborn/ok") && me->query("scborn/ok") && 
            me->query_skill("zuoyou-hubo", 1) >= 385 && ! me->query("buchang-hubo"))
        {
                log_file("buchang-hubo", me->query("id") + " " + ctime(time()) + " ���10��INT������\n");
                me->add("int", 10);
                me->set("buchang-hubo", 1);
                me->add("int", 10);
                tell_object(me, HIM "\n���ѭ��������ƽ�⣺������ʮ���������ԵĲ�����\n");
                me->save();
        }
        
        if (! me->query("thborn/ok")) // �ٴ�2ת�������ֻص�
        {
                // ���LHDʹ�üӳɣ���ָ�������ԣ���Ϊ���ܺ�SPECIALJOB���ܶ�ҪDELETE
                // 1������12T���ѵ�LHD
                if (me->query_skill("yinyang-shiertian", 1))
                {
                        sk_12t_add += 5;
                        if (me->query("yinyang-shiertian/yinyang"))
                                sk_12t_add += 2;
                        if (me->query("yinyang-shiertian/qiankun"))
                                sk_12t_add += 3;
                        if (me->query("yinyang-shiertian/shier"))
                                sk_12t_add += 4;
                }
                // 2������Ե����ѵ�LHD
                if (me->query_skill("badao", 1))
                {
                        sk_bd_add += 7;
                        if (me->query("can_perform/badao/san"))
                                sk_bd_add += 8;
                }
                // 3�������ֻؽ����ѵ�LHD
                if (me->query_skill("lunhui-sword", 1))
                {
                        sk_lhj_add += 6;
                        if (me->query("can_perform/lunhui-sword/zhen"))
                                sk_lhj_add += 6;
                }
                // 4�����ǿ��ְҵspecial��LHD
                job_special = me->query("lhpoint/special");
                job_add = 0;
                if (sizeof(job_special))
                {
                        key_job_special = keys(job_special);
                        for (i = 0; i < sizeof(key_job_special); i ++)
                        {
                                job_add = job_add + job_special[key_job_special[i]];
                        }        
                }
        
                total_lhd = sk_12t_add + sk_bd_add + sk_lhj_add + job_add;
                
                // �����ֻص�
                if (total_lhd >= 18)
                {
                        total_lhd = 18;
                        log_file("thborn_lhd", me->query("id") + " " + ctime(time()) + " " + sk_12t_add + " " + sk_bd_add + " " + sk_lhj_add + " " + job_add + " \n");
                        //return "�ֻص����ݳ�������ϵ��Ϸ����Ա��\n";        
                }        
                
                // ����ֻص�ʹ�ü�¼
                me->delete("lhpoint/special");        
                        
                if (total_lhd + me->query("scborn/cur_lunhui_point") >= 18)
                        me->set("scborn/cur_lunhui_point", 18);
                else
                        me->add("scborn/cur_lunhui_point", total_lhd);
                        
                tell_object(me, HIY "\n���ܹ����" + chinese_number(total_lhd) + "���ֻص㷵����\n" NOR);
                
                // �ֻص���������Ϊ18��2ת��Ͳ����ٻ��
                me->set("scborn/total_lunhui_point", 18);
        }
        else// ����2ת�ĵ�������ְҵ���ܵ��ֻص�
        {
                // 4�����ǿ��ְҵspecial��LHD
                job_special = me->query("lhpoint/special");
                job_add = 0;
                if (sizeof(job_special))
                {
                        key_job_special = keys(job_special);
                        for (i = 0; i < sizeof(key_job_special); i ++)
                        {
                                job_add = job_add + job_special[key_job_special[i]];
                        }        
                }
        
                total_lhd = job_add;

                // �����ֻص�
                if (total_lhd >= 18)
                {
                        total_lhd = 18;
                        log_file("thborn_lhd", me->query("id") + " " + ctime(time()) + " " + sk_12t_add + " " + sk_bd_add + " " + sk_lhj_add + " " + job_add + " \n");
                        //return "�ֻص����ݳ�������ϵ��Ϸ����Ա��\n";        
                }

                // ����ֻص�ʹ�ü�¼
                me->delete("lhpoint/special");

                if (total_lhd + me->query("scborn/cur_lunhui_point") >= 18)
                        me->set("scborn/cur_lunhui_point", 18);
                else
                        me->add("scborn/cur_lunhui_point", total_lhd);

                tell_object(me, HIY "\n���ܹ����" + chinese_number(total_lhd) + "���ֻص㷵����\n" NOR);

                // �ֻص���������Ϊ18��2ת��Ͳ����ٻ��
                me->set("scborn/total_lunhui_point", 18);                
        }
        
        // ����������
        skills_status = me->query_skills();
        if (sizeof(skills_status))
        {
                myskills = keys(skills_status);
                for (i = 0; i < sizeof(myskills); i ++)
                {
                        // �����2��ת������������
                        if (me->query("thborn/ok") && myskills[i] == "martial-cognize")
                                continue;
                                
                        me->delete_skill(myskills[i]);
                }
        }
        // �������
        me->delete("can_perform");
        me->delete("yinyang-shiertian");
        me->delte("can_learn");
        
        // ɾ���Դ��书
        me->delete("pmskills");
        
        //���ѧϰ��¼
        me->delete("marks");
        
        // ���tuoli2��¼
        me->delete("thborn/tuoli");
        
        // lhj ��¼ 
        me->delete("lunhui-sword_quest");
        
        // �����ʦ�������¼
        me->delete("detach");
        me->delete("betrayer");
        
        // ������飬Ǳ�ܣ���
        me->set("combat_exp", 0);
        me->set("learned_points", 0);
        me->set("potential", 0);
        me->set("gongxian", 0);
        me->set("weiwang", 0);
        me->set("score", 0);
        me->set("shen", 0);
        me->set("max_neili", 0);
        me->set("neili", 0);
        me->set("experience", 0);  
        me->set("learned_experience", 0);
        me->set("max_jing", 100);     
        me->set("eff_jing", 100); 
        me->set("jing", 100); 
        me->set("max_qi", 100);      
        me->set("eff_qi", 100);  
        me->set("qi", 100);      
        me->set("max_jingli", 0);
        me->set("jingli", 0);
        me->delete("combat");
        me->set("shaqi", 0);
        me->set("age", 5);
        me->set("mud_age", 0);
        me->set("jiali", 0);
        me->delete("family");
        
        if (me->query("gender") == "����")
                me->set("gender", "����");
        

        // ���ְҵ��SPECIAL
        if (me->query("yhjob/job") == "����")
        {
                me->delete("special_skill/haoran");
                me->delete("special_skill/xiagu");
                me->delete("special_skill/shewo");
        }
        else if (me->query("yhjob/job") == "ħʦ")
        {
                me->delete("special_skill/moxin");
                me->delete("special_skill/youran");
                me->delete("special_skill/haoling");
        }
        else // ��ʿ
        {
                me->delete("special_skill/haina");
                me->delete("special_skill/xianyun");
                me->delete("special_skill/tianxia");
        }        
        me->delete("yhjob");
        
        // ɾ����������
        me->delete("can_learn/dugu-jiujian/nothing");
        
        // ��ʾ����ѡ��ְҵ
        tell_object(me, HIG "\n�������������ϣ�������ѡ��ְҵ��ָ�yhjob <ְҵ>������������Ի���\n" NOR); 
        me->set("check_yhjob", 1);
        me->delete("chose_yhjob");
        
        me->delete("class");
        me->delete("can_learn");
        
        me->save();

        return 1;
}

void init()
{
        add_action("do_yhjob", "yhjob");
        command("hand tianlai zhiyuan");
}

// ѡ��ְҵ
int do_yhjob(string arg)
{
        object me;
        string msg;

        me = this_player();

        if (me->query("chose_yhjob"))
        {
                return notify_fail("���Ѿ�ѡ���ְҵ�ˣ�����������ѡ��\n");
        }
        
        if (! me->query("check_yhjob"))
                return notify_fail("����������Ի�������������ݣ���ɺ����ѡ��ְҵ��\n");
        
        if (me->query("thborn/ok") && ! me->query("thborn/ok"))
                return notify_fail("���Ѿ���ת���ˣ�����Ҫ��ѡ��ְҵ��\n");
                
            // ����
        if (! arg)
        {
                // ְҵ����
                msg  = HIR "\n��Ŀǰ����ѡ������ְҵ��Ϊ��ת�����ְҵ��\n" NOR;
                msg += HIC "���ͣ�������˾�����ְҵ��ӵ�������๥���ؼ���\n" NOR;
                msg += HIM "ħʦ: ������η���ְҵ��ӵ��а���๥���ؼ���\n" NOR;
                msg += HIG "��ʿ: ���������������������⣬ӵ�ж��ָ������ؼ���\n" NOR;
                msg += HIY "����ְҵ������μ�ת��ְҵ�����ļ� help scborn_yhjob\n" NOR;
                msg += HIY "������ָ��" HIR " yhjob ְҵ " HIY "��ѡ����ת�����ְҵ��ѡ��ǰ�������Ķ�ת��ְҵ�����ļ���\n\n" NOR;

                write(msg);
                return 1;        
        }

        if (arg != "����" && arg != "ħʦ" && arg != "��ʿ")
                return notify_fail("��ѡ����ȷ��ְҵ�����͡�ħʦ����ʿ��\n");
        
        if (sizeof(me->query("yhjob/job")))
                return notify_fail("�Բ��������ڻ���������ѡ��ְҵ��\n");

        write(HIG "��ѡ���� " + arg + " ��ְҵ��\n");
        me->set("chose_yhjob", 1);
        me->set("yhjob/job" , arg);
        
        // ��������ؼ�
        // ����ְҵ����
        if (arg == "����")
        {
                me->set("special_skill/haoran",1);
                me->set("special_skill/xiagu",1);
                me->set("special_skill/shewo",1);
        }
        else if (arg == "ħʦ")
        {
                me->set("special_skill/moxin",1);
                me->set("special_skill/youran",1);
                me->set("special_skill/haoling",1);
        }
        else // ��ʿ
        {
                me->set("special_skill/haina",1);
                me->set("special_skill/xianyun",1);
                me->set("special_skill/tianxia",1);
        }
        
        me->save();

        return 1;
}

void unconcious()
{
        die();
}
