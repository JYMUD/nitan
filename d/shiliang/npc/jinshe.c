// This program is a part of NT MudLIB
// jinshe.c �����ɾ�

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

#define QUESTDIR "skybook_quest/���߽���/"

void dest(object ob);
int ask_fuchou();
int ask_jinshe();
string ask_skill1(object me,string arg);
string ask_skill2(object me,string arg);
string ask_skill3(object me,string arg);
void create()
{
        set_name("��ѩ��", ({"xia xueyi", "xia", "xueyi"}));
        set("nickname", HIY"�����ɾ�"NOR);
        set("gender", "����");
        set("age", 25);
        set("long", 
                "�������˳ơ������ɾ�����һ���ֽܡ�����ѩ�ˡ�\n"
                "������ȫƾ�ö�ʱ��ʱа���˵��Ƕ����������ò�������\n"
                "��˵���������ܲң���Ҳ���ƫ��������\n"
                "���������������˵��ˣ���ɫ���ѿ���\n");
         set("attitude", "peaceful");
        
        set("str", 100);
        set("int", 20);
        set("con", 30);
        set("dex", 25);
        set("chat_chance", 15);
        set("chat_msg", ({
                "��ѩ��ͻȻ��ݺݵ�˵�����Ƕ����㵽��ΪʲôҪ���ң���\n",
                "��ѩ�����з·�Ҫ���������\n",
                "ͻȻ����ѩ�ˡ��ۡ���һ�����³�һ��ڴ��ڵ�Ѫ��\n",
        }));
        set("inquiry", ([
                "����": "��....��..... \n",
                "����" : (: ask_fuchou :),
                "������"  :        (: ask_skill1 :),
                "���ǲ���":        (: ask_skill2 :),
                "��������":        (: ask_skill3 :),
                "�ĵ�"    : (: ask_jinshe :),
                "���߽���": (: ask_jinshe :),
                "�ؾ�"    : (: ask_jinshe :),
        ]));
        set("qi", 10000);
        set("max_qi", 10000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 9000);
        set("max_neili", 9000);
        set("jiali", 100);
        set("no_get",1);
        set(QUESTDIR+"pass", 1);
        
        set("combat_exp", 10000000);
         
        set_skill("force", 200);                // �����ڹ�
        set_skill("huntian-qigong", 200);       // ��������
        set_skill("unarmed", 220);              // ����ȭ��
        set_skill("dodge", 200);                // ��������
        set_skill("parry", 200);                // �����м�
        set_skill("sword", 200);                // ��������
        set_skill("jinshe-jian",200);           // ���߽���
        set_skill("strike", 200);
        set_skill("jinshe-zhang", 200);
        set_skill("throwing", 200);
        set_skill("jinshe-zhui", 200);
        set_skill("martial-cognize", 200);
        
        map_skill("force", "huntian-qigong");
        map_skill("sword", "jinshe-jian");
        map_skill("parry", "jinshe-jian");
        map_skill("strike", "jinshe-zhang");
        
        setup();
        
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

int accept_object(object who, object ob)
{
        object obn;
        if( !who || environment(who) != environment() ) return 0;
        if( !objectp(ob) ) return 0;
        if( !present(ob, who) ) return notify_fail("��û�����������\n");
        if( query("id", ob) != "wen shoupa" )
                return notify_fail("��ѩ�˲���Ҫ���������\n");
        write(HIY "��ѩ�˽ӹ������������س���ͻȻ����Ȼ���¡� \n" NOR);
        write(HIR "��ѩ���૵����Ƕ�������֪��������⣬��ʵ��������ģ���Ҳ���ں��ġ�\n" NOR);         
        write(HIY "��ѩ��ת��ͷ������˵���Ҹ�������л���أ�\n" NOR);
        write(HIY "����ת��ȥ����Ĭ���������˼����ʲô��\n" NOR);
        write(HIY "��ѩ��ͻȻ�����˺ܴ�����Ƶض���˵���ҿ�\n" NOR);
        write(HIY "��Ҳ���������ˣ������������ұ�����Ѫ�ġ�������ܸ����\n" NOR);
        write(HIY "������������˵�Ѿ�û��ʲô���ˣ������ȥ�ɡ�\n" NOR);
        write(HIY "��ѩ��̾�˿����������ǳ�������Ҳ�ã���������Ҳ�ã�������ΪҲ�ã�ͨͨ�����޹ء�\n" NOR);
        write(HIY "��ѩ�˻��˻��֣����ˣ���������ˡ�\n" NOR);
        /*
        obn = new("/clone/book/jinshe2");
        obn->move(who);
        */
        obn = new("/clone/book/jinshe2");
        obn->move(who);
        obn = new("/clone/book/jinshe3");
        obn->move(who);
        write(HIR "��ѩ�˻��װ���ǽ�ϵ�һ�����أ�ֻ����¡¡�������죬ʯ��֮��¶��һ���ķ��Ķ�������\n"NOR);
        set("exits/east","/d/shiliang/jinshedong1", get_object("/d/shiliang/jinshedong"));
        destruct(ob);
        return 1;
}
void dest(object ob)
{
        destruct(ob);
}
string ask_skill1(object me,string arg)
{
        return teach_perform(this_player(),this_object(),([
                "perform"        : "suo",        //pfm�Ĵ���
                "name"                : "������",        //pfm������
                "sk1"                : "jinshe-jian",//��Ҫ���书��id
                "lv1"                : 100,                //��Ҫ���书�ĵȼ�
                "sk2"                : "sword",        //��Ҫ�书sk2��id
                "lv2"                : 100,                //��Ҫ�书sk2 �ĵȼ�
                "neili"                : 300,                //��Ҫ�����ڹ��ȼ�
                "free"                : 1,                 //free=1����Ҫͬһ����
                "msg1"                : "$N����һЦ��Ҫѧ��ʵ���в����ѣ������˶��Գ�����С�\n"+
                                "���ҽ��߽�����������У�����Ҫּ�����⾳��������ʽ��\n"+
                                "$n����$N��ָ������Ȼ����",
                "msg2"                : "���ˣ����Լ�������ϰ�ɡ�",
                ]));
}
string ask_skill2(object me,string arg)
{
        return teach_perform(this_player(),this_object(),([
                "perform"        : "fugu",        //pfm�Ĵ���
                "name"                : "���ǲ���",        //pfm������
                "sk1"                : "jinshe-zhang",//��Ҫ���书��id
                "lv1"                : 100,                //��Ҫ���书�ĵȼ�
                "sk2"                : "strike",        //��Ҫ�书sk2��id
                "lv2"                : 100,                //��Ҫ�书sk2 �ĵȼ�
                "neili"                : 300,                //��Ҫ�����ڹ��ȼ�
                "free"                : 1,                 //free=1����Ҫͬһ����
                ]));
}
string ask_skill3(object me,string arg)
{
        return teach_perform(this_player(),this_object(),([
                "perform"         : "tuwu",        //pfm�Ĵ���
                "name"                : "��������",        //pfm������
                "sk1"                : "jinshe-zhui",//��Ҫ���书��id
                "lv1"                : 100,                //��Ҫ���书�ĵȼ�
                "sk2"                : "throwing",        //��Ҫ�书sk2��id
                "lv2"                : 100,                //��Ҫ�书sk2 �ĵȼ�
                "force"                : 100,                //��Ҫ�����ڹ��ȼ�
                "neili"                : 300,                //��Ҫ�����������
                "free"                : 1,                 //free=1����Ҫͬһ����
                ]));
}

int ask_fuchou() 
{
        object me = this_player();

        if( me->query_skill("jinshe-jian",1) <200 )
                   return 1;

        if( me->query_condition("killer") )
        {
                command("fear "+query("id", me));
                command("say С�Ĺٸ�ͨ����");
                return 1;
        }

        if( query_temp(QUESTDIR+"start", me) )
        {
                command("shake "+query("id", me));
                command("say �㲻��˵Ҫ���Ҹ��������ô�������");
                return 1;
        } 
        
        if( query(QUESTDIR+"over", me) )
        {
                command("thank "+query("id", me));
                command("say ���Ѿ�ɱ���¼����ϰ��Ҹ����ˣ�����̫��л�ˣ�");
                return 1;
        } 
        //��vip��ң�ֻ��ʧ������
        if( query(QUESTDIR+"fail", me) >= 3 && query("registered", me)<3 )
        {
                command("shake "+query("id", me));
                command("say ����ʱ��������⸴������黹���Ժ���˵�ɡ�");
                return 1;
        }
        //��Ҫ���һ�죬������Ҫ���500k

        if( query(QUESTDIR+"start/time", me) && time()-query(QUESTDIR+"start/time", me)<86400 )
        {
                command("shake "+query("id", me));
                command("say ����������ɣ���ʲô����������˵�ɡ�");
                return 1;
        }
        if( query(QUESTDIR+"combat_exp", me) && query("combat_exp", me)-query(QUESTDIR+"combat_exp", me)<500000 )
        {
                command("look "+query("id", me));
                command("say ���㵱ǰ�ľ�����»������԰��Ҹ��𣬻���ץ��ȥ����ȥ�ɡ�");
                return 1;
        }
        
        command("look "+query("id", me));
        command("say �ðɣ���ȥ����ɱ���¼����ϣ��Ҷ�����л��");
        command("say ��ֻҪ���¼����ϵ��ϴ����𡰽����ɾ������ɡ�");

        set_temp(QUESTDIR+"start", 1, me);//��ʼ��־
         //��ǿ�ʼʱ��;���
        set(QUESTDIR+"time", time(), me);
        set(QUESTDIR+"combat_exp",query("combat_exp", me), me);
        return 1;
}

int ask_jinshe() 
{
        object me = this_player();      
        int exp, neili;
     
       //����书�ȼ�������250����
        if( me->query_skill("jinshe-zhui",1) <250 )
                   return 1;
                   
        if( me->query_skill("jinshe-zhang",1) <250 )
                   return 1;
                   
          //����ɱ�����¼�����
        if( !query(QUESTDIR+"over", me) )
                   return 1;

        if( me->query_condition("killer"))
        {
                command("fear "+query("id", me));
                command("say С�Ĺٸ�ͨ����");
                return 1;
        }

        //��vip��ң�ֻ��ʧ������
        if( query(QUESTDIR+"fail", me) >= 3 && query("registered", me)<3 )
        {
                command("shake "+query("id", me));
                command("say �Ҳ��Ƕ����������������˿������Լ��������ˡ�");
                return 1;
        }
        //�书ѧϰ֮����Ҫ���һ�죬������Ҫ���500k

        if( query(QUESTDIR+"time", me) && time()-query(QUESTDIR+"time", me)<86400 )
        {
                command("shake "+query("id", me));
                command("say ����������ɣ���ʲô����������˵�ɡ�");
                return 1;
        }
        if( query(QUESTDIR+"combat_exp", me) && query("combat_exp", me)-query(QUESTDIR+"combat_exp", me)<500000 )
        {
                command("look "+query("id", me));
                command("say ���㵱ǰ�ľ�����»�����������Ҫ��������ץ��ȥ����ȥ�ɡ�");
                return 1;
        }
        exp=7000+random(3000);
        neili=200+random(300);
        command("look "+query("id", me));
        command("say ��Ȼ����ұ��˴���Ҿͽ��ҶԽ����ؼ����о��ĵø�����ɡ�");
        //����书��ʱ��ͱ�־
        set(QUESTDIR+"time", time(), me);
        set(QUESTDIR+"combat_exp",query("combat_exp",  me), me);
        if( random(query("kar", me)) > 22 )
        {
                set(QUESTDIR+"pass", 1, me);
                tell_object(me,HIG"\n��������ѩ�˵�ָ�㣬������������в���֮��һ�Ӳ��գ���ʱ��Ȼ��ͨ����Ȼ�������\n\n"NOR);
                tell_object(me,HIC"\n���Ŀڤ˼�����������š��������书�ذ£�����һ���γ���СϪ������������������\n"NOR);
                tell_object(me,HIC"��ɼ��ף����Ȱ�����ң�ֱ����ò��Ѿ�������һ���˼������ͨ���˽����ɾ���\n"NOR);
                tell_object(me,HIC"\n��ѧ�ؾ�����ʦ����������ϳ��书��Ҳ�и���һ����ᡣ\n"NOR);
                command("wa "+query("id", me));
                tell_object(me,HBYEL"\n����"+NATURE_D->game_time()+"�õ���ѩ�˵�ָ�㣬��ѧ��Ϊ���������"+exp+"�㾭�齱����"+neili+"�����������\n"NOR);
                addn("combat_exp", exp, me);
                addn("max_neili", neili, me);
                me->improve_skill("jinshe-jian", 2000000);
                log_file("quest/jinshequest",sprintf("%s(%s)ʧ��%d�κ�õ���ѩ�˵�ָ�㣬��ѧ��Ϊ������������%d�㾭�飬%d�����������\n",me->name(1),query("id", me),query("quest/���߽���/fail", me),exp,neili));

                return 1;
        }
        tell_object(me,HIR"\n��˼ڤ�룬�����Լ���Ȼ�޷������ѩ�������ؾ���\n\n"NOR);
        command("sigh "+query("id", me));
        addn(QUESTDIR+"fail", 1, me);
        log_file("quest/jinshequest",sprintf("%s(%s)��%d������ѩ����̣�������Ȼ�޷�������о��ϡ�\n",me->name(1),query("id", me),query("quest/���߽���/fail", me)));

        return 1;
}
