#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;

string ask_me();
mixed ask_skill1();
mixed ask_skill2();
string ask_recover();
int do_answer(string arg);

void create()
{
            set_name("һ�ƴ�ʦ", ({ "yideng dashi", "yideng", "dashi" }));
            set("long", @LONG
һ�ƴ�ʦ�˽������˳ơ���а�������ϵ۱�ؤ����
���ϵ۶λ�ү������ƾ�Ŷ��ϡ�һ��ָ����������
�֣�������֡���ȴ������ʱ��һ�α��������Ϊ
ɮ��֮��󳹴��򣬳�Ϊһλ�õ���ɮ��
LONG );
            set("title", "�������λ�ʵ�");
            set("nickname", HIY "�ϵ�" NOR);
            set("gender", "����");
            set("age", 71);
            set("shen_type", 1);
            set("attitude", "friendly");

            set("str", 33);
            set("int", 35);
            set("con", 38);
            set("dex", 33);

            set("qi", 6500);
            set("max_qi", 6500);
            set("jing", 5000);
            set("max_jing", 5000);
            set("neili", 8000);
            set("max_neili", 8000);
            set("jiali", 200);
            set("combat_exp", 4000000);
            set("score", 500000);

        set_skill("force", 640);
        set_skill("xiantian-gong", 600);
        set_skill("duanshi-xinfa", 640);
        set_skill("kurong-changong", 640);
        set_skill("dodge", 640);
        set_skill("tiannan-bu", 640);
        set_skill("cuff", 600);
        set_skill("jinyu-quan", 600);
        set_skill("strike", 600);
        set_skill("wuluo-zhang", 600);
        set_skill("sword", 600);
        set_skill("staff", 600);
        set_skill("duanjia-jian", 600);
        set_skill("finger", 640);
        set_skill("qiantian-zhi", 640);
        set_skill("sun-finger", 640);
        set_skill("parry", 600);
        set_skill("jingluo-xue", 600);
        set_skill("buddhism", 640);
        set_skill("literate", 600);
        set_skill("sanscrit", 600);
        set_skill("qimai-liuzhuan", 700);
        set_skill("martial-cognize", 640);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "sun-finger");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "sun-finger");
        map_skill("sword", "duanjia-jian");
        map_skill("staff", "sun-finger");

        prepare_skill("finger", "sun-finger");

        create_family("���ϻ���", 11, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.jian" :),
                (: perform_action, "finger.qian" :),
                (: perform_action, "finger.dian" :),
                (: perform_action, "finger.die" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

            set("inquiry",([
                  "������"   : "����ͨ�������������������ĺ��������",
                  "����"     : "�������ĳ���ǰ��һ����Ե������Ҳ�ա�",
                  "����ͯ"   : "�Ǻǣ������书��ǿ�������Ļ�ȴ����ͯһ�㡣",
                  "�ܲ�ͨ"   : "�Ǻǣ������书��ǿ�������Ļ�ȴ����ͯһ�㡣",
                  "����"     : "Ŷ���Ǹ���С���ĵ��������Һ���ʵ��û����һ��Ҫ�Կ���",
                 "����"     : "�ǹ����Ǻ�С�ӵİ��°ɣ��˵����ǻ��顣",
                  "֪ʶ"     : "�ҿ��Դ����������ķ������ģ������������ʦ��ѧϰ�ɡ�",
                  "����"     : "�ҿ��Դ����������ķ������ģ������������ʦ��ѧϰ�ɡ�",
                  "��������" : (: ask_skill1 :),
                "һ��ָ"   : (: ask_me :),
                "Ǭ������" : (: ask_skill2 :),
                "����"     : (: ask_recover :),
                "����"     : (: ask_recover :),
            ]));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

            set("master_ob", 5);
        setup();
            carry_object("/clone/cloth/seng-cloth")->wear();
}

void init()
{
        object ob;
        ::init();
        add_action("do_answer","answer");

                 if (interactive(ob = this_player()) && ! is_fighting())
                 {
                   remove_call_out("greeting");
                   call_out("greeting", 1, ob);
                   }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) return;

        if( query("shen", ob)<-50000 )
                command("say ��λʩ�������������أ�Ȱʩ������Ϊ֪��");

        else
        if( query("shen", ob)<-5000 )
                command("say ��λʩ�����м�ħ������������");

        else
        if( query("shen", ob)<0 )
                command("say ��λʩ�������н��������е����������߽�аħ�����");

        else
        if( query("shen", ob)>50000 )
                command("say ʩ�����¹������䣬�պ��Ϊ�����̳���");

        else
                command("say ��λʩ�����������������ߣ���ʩ����ӱ��ء�");

        return;
}

int recognize_apprentice(object me, string skill)
{
        if( query("shen", me)<0 )
        {
                command("say ʩ�������������أ���������֮�������Իᴫ�ڸ��㡣");
                return -1;
        }

        if (skill != "sanscrit" && skill != "buddhism" && skill != "jingluo-xue")
        {
                command("say ��Щ���������ʦ��ѧ�ɣ�����ֻ�ܴ���Щ֪ʶ���㡣");
                return -1;
        }

        if (skill == "buddhism" && me->query_skill("buddhism", 1) > 5000)
        {
                command("haha");
                command("say ��ķ������Ѿ���ͬ�����ˣ�ʣ�µ��Լ�ȥ�о��ɡ�");
                return -1;
        }

        if( !query_temp("can_learn/yideng", me) )
        {
                command("say ���ް���٢��");
                command("say ��Ȼʩ��������������Ե��������ڡ�");
                set_temp("can_learn/yideng", 1, me);
        }

        return 1;
}
string ask_me()
{
        object me;

        me = this_player();

        if( query("shen", me)<0 )
                return "ʩ�������������أ�������֮�������Իᴫ�ڸ��㡣";

        if (me->query_skill("sun-finger", 1) > 600)
               return "���һ��ָ���������־��磬������ûʲô�ɽ̵��ˡ�";

        if( query("family/family_name", me) != query("family/family_name") )
               return "�����������ģ��㲻���Ҷμ�֮�ˣ���������֮�ֽ����ѧ�������������²��ס�";

        if( query("combat_exp", me)<500000 )
               return "�书��ע�ظ�������Ḭ̄ͼ�ݾ�����ѻ��������ú������Իᴫ�ڸ��㡣";

        addn_temp("can_learn/yideng/sun-finger", 1, me);
               return "�ðɣ����ľʹ���һ��ָ�������㣬���м����н��������е�������Ҫ�߽�аħ�����";
}
mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/sun-finger/die", me) )
                return "��һ��ָ�������־��磬������ûʲô�ɽ̵��ˡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "ʩ���������ز���ʶ����֪ʩ���˻��Ӻ�˵��";

        if (me->query_skill("sun-finger", 1) < 1)
                return "����һ��ָ����ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<2500 )
                return "��Ϊ�����������Ĺ��׻�����������������ʱ�����ܴ��㡣";

        if( query("shen", me)<50000 )
                return "����������»����ò���������������ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 300)
                return "���ڹ�����Ϊ�������������������ɡ�";

        if( query("max_neili", me)<5000 )
                return "���������Ϊ�����������ߵ������ɡ�";

        if (me->query_skill("jingluo-xue", 1) < 200)
                return "��Ծ���ѧ���˽⻹��͸�����о�͸���������Ұɡ�";

        if (me->query_skill("sun-finger", 1) < 200)
                return "���һ��ָ����������������������˵�ɡ�";

        message_sort(HIY "\n$n" HIY "������$N" HIY "��һ������漴���˵�"
                     "ͷ����$N" HIY "������ߣ��ڶ��Ե���ϸ˵���ã�$N" HIY
                     "������ĵ�һЦ��������$n" HIY "�Ľ̵���������\n\n"
                     NOR, me, this_object());

        command("buddhi");
        command("say �����ѽ��˾������ڸ��㣬�м�Ī�߽�аħ�����");
        tell_object(me, HIC "��ѧ���ˡ�������������\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("jingluo-xue"))
                me->improve_skill("jingluo-xue", 1500000);
        if (me->can_improve_skill("jingluo-xue"))
                me->improve_skill("jingluo-xue", 1500000);
        if (me->can_improve_skill("jingluo-xue"))
                me->improve_skill("jingluo-xue", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/sun-finger/die", 1, me);
        addn("family/gongji", -2500, me);

        return 1;
}
mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/xiantian-gong/jian", me) )
                return "�����칦��Ǭ�������������־��磬������ûʲô�ɽ̵��ˡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "ʩ���������ز���ʶ����֪ʩ���˻��Ӻ�˵��";

        if (me->query_skill("sun-finger", 1) < 1)
                return "����һ��ָ����ûѧ����̸ʲô���п��ԣ�";

        if (me->query_skill("xiantian-gong", 1) < 1)
                return "������ʱ���ܴ������㣬����ѧ�����칦�������Ұɡ�";

        if( query("family/gongji", me)<2500 )
                return "��Ϊ�����������Ĺ��׻�����������������ʱ�����ܴ��㡣";

        if( query("shen", me)<50000 )
                return "����������»����ò���������������ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 600)
                return "���ڹ�����Ϊ�������������������ɡ�";

        if( query("max_neili", me)<5000 )
                return "���������Ϊ�����������ߵ������ɡ�";

        if (me->query_skill("xiantian-gong", 1) < 600)
                return "������칦��������������������˵�ɡ�";

        message_sort(HIY "\n$n" HIY "������$N" HIY "��һ������漴���˵�"
                     "ͷ����$N" HIY "������ߣ��ڶ��Ե���ϸ˵���ã�$N" HIY
                     "������ĵ�һЦ��������$n" HIY "�Ľ̵���������\n\n"
                     NOR, me, this_object());

        command("buddhi");
        command("say �Ȿ������ͨ�ľ������������ѽ��˾������ڸ��㣬�м�Ī�߽�аħ�����");
        tell_object(me, HIC "��ѧ���ˡ�Ǭ����������\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1500000);
        if (me->can_improve_skill("xiantian-gong"))
                me->improve_skill("xiantian-gong", 1500000);
        if (me->can_improve_skill("sun-finger"))
                me->improve_skill("sun-finger", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xiantian-gong/jian", 1, me);
        addn("family/gongji", -2500, me);

        return 1;
}

string ask_recover()
{
        object me;
        me = this_player();

        if (environment(me)!=find_object("/d/heizhao/houyuan"))
                return "ʩ���ʵ���ʲô��ƶɮ��֪������\n";
        if( query_temp("yideng_asked", me) )
                return "����Ҫ������\n";
        else {
                if( query("family/family_name", me) == "���ϻ���" )
                {
                        set_temp("yideng_asked", 1, me);
                        return "��������������Ȼ������Ϊ�����ƣ�����֪���Ƿ���Ҫ��\n";
                }
                else {
                        set_temp("yideng_asked", 1, me);
                        return "ʩ����Ȼ��Ե�������£�ƶɮ�������񾡵���֮��Ϊ�������ƣ���֪�����Ƿ���Ҫ��\n";
                }
        }
}

int do_answer(string arg)
{
        object me;
        me=this_player();

        if( arg == "��Ҫ����" && query_temp("yideng_asked", me) )
        {
                tell_object(me, "������һ�ƴ�ʦΪ���˹����ơ�\n");
                delete_temp("yideng_asked", me);
                if( query("dali/yideng_rewarded", me) )
                {
                        // command("look "+getuid(me));
                        command("say ����������һ�Σ����Ѿ��þ���Ե�ˣ���������");
                        command("say Ϊ�����̰�����ᣬ���������뿪����ɡ�");
                        message_vision("$N�����ѵ�����ɫͨ�죬��������뿪�ˡ�\n", me);
                        me->move("/d/heizhao/maze1");
                        return 1;
                }
                if( query("family/family_name", me) == "���ϻ���" )
                {
                        command("pat "+getuid(me));
                        command("smile");
                        command("say �õģ�������͸������ơ������ҵ���������");
                        set_temp("yideng_waitreward", 1, me);
                        delete_temp("yideng_asked", me);
                        this_object()->move("/d/heizhao/chanfang");
                        me->move("/d/heizhao/chanfang");
                        command("say ��׼�����˾͸����ҡ�");
                        return 1;
                }
                if( query("kar", me)>random(30) )
                {
                        // command("look "+getuid(me));
                        command("smile");
                        command("say �õģ�������͸������ơ������ҵ���������");
                        set_temp("yideng_waitreward", 1, me);
                        delete_temp("yideng_asked", me);
                        this_object()->move("/d/heizhao/chanfang");
                        me->move("/d/heizhao/chanfang");
                        command("say ��׼�����˾͸����ҡ�");
                        return 1;
                }
                else {
                        // command("look "+getuid(me));
                        command("sigh");
                        command("say ʵ�ڱ�Ǹ��ʩ����Ե�ֲ��������Ĳ���Ϊ�����ơ�");
                        command(":(");
                        delete_temp("yideng_asked", me);
                        set("dali/yideng_rewarded", 1, me);
                        return 1;
                }
        }
        if (arg == "��׼������"
                 && query_temp("yideng_waitreward", me )
                && environment(me)==find_object("/d/heizhao/chanfang"))
        {
                command("nod");
                command("say ������������Ϳ�ʼΪ�������ˡ�");
                write("һ�Ƶ�����Ŀ��ü���붨�˹�������Ծ���������أ�������� \n");
                write("ʳָ������������ͷ���ٻ�Ѩ��ȥ�������ɼ���΢΢һ����\n");
                write("ֻ����һ�������Ӷ���ֱ͸������\n");
                write("һ��һָ������������أ��ڶ�ָ���������İٻ�Ѩ��һ����\n");
                write("�ִ��ĺ�Ѩ������ǿ�䣬�Ի����縮����׶���յ���������\n");
                write("�������̨һ·�㽫������һ֧��ȼ��һ�룬�ѽ��㶽������ʮ \n");
                write("��Ѩ˳�ε㵽��\n");
                message_vision(HIR "$NͻȻ����һ��ů���Զ����룬��ǰһ�ھ�ʲôҲ�������ˣ�\n" NOR, me );
                me->unconcious();

                // if (me->query("family/family_name") == "���ϻ���")
                {
                        addn("con", 2, me);
                        addn("dex", 1, me);
                        addn("str", 1, me);
                }
                addn("max_neili", 150, me);
                addn("combat_exp", 15000, me);
                set("dali/yideng_rewarded", 1, me);
                delete_temp("yideng_waitreward", me);
                this_object()->move("/d/heizhao/houyuan");
                me->move("/d/heizhao/houyuan");
                return 1;
        }
        write("����ش�ʲô(��Ļش���񲻶�)\n");
        return 1;
}
