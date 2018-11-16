// zhang.c ����ʦ

#include <ansi.h>

inherit KNOWER;

#define ZHOUTIAN_D      "/adm/daemons/zhoutiand"

int ask_me();
string ask_fu();
int life_warcraft();
string ask_tianjidao();

void create()
{
        set_name("����ʦ", ({ "zhang tianshi", "zhang" }));
        set("age", 57);
        set("gender", "����");
        set("long", "����һλ�ɷ���ǣ���ò��Ȼ�ķ�ʦ��\n");
        set("attitude", "peaceful");

        set("str", 28);
        set("int", 35);
        set("con", 38);
        set("dex", 31);

        set("max_qi", 8000);
        set("max_jing", 8000);
        set("max_neili", 8000);

        set_skill("magic", 200);
        set_skill("taoism", 350);

        set("chat_chance_combat", 3);
        set("chat_msg_combat", ({
                "����ʦҡҡ���������������飬�����㣬̫���Ͼ��������飿\n",
                "����ʦ�����Ĵ��˼�������\n",
        }));

        set("inquiry", ([
                "����" : (: ask_me :),
                "ħ�޸���": (: life_warcraft :),
                "ûǮ" : "ûǮ��ȥ׬������˵ʲô��",
                "��"   : "����Ҳ��һ��������",
                "ħ��" : "ħ����ʲô���գ�",
                "����" : "�������ֺܶ����أ�������������������һ���㡣",
                "����" : "����������Ǳ�Դ���ڣ�",
                "����" : "�������������³ˣ�����Ϊ�ᡣ",
                "����" : "����ֻ�������гˣ����ǲ��ܺ͵�����ȡ�",
                "����" : "��Ҫ�ǲ����ҿ��԰��㿴��(show)������Ҫ��ʲô��Ʒ��",
                "����" : "�ҿ��԰��㿴��(show)��ı�ʯ���̺���Щ���ԡ�",
                "������" : "�Ǻǣ�����ƶ����һλ���ѣ�����Ҳ��֪����������ˡ�",
                "�����" : "�������¼����ϳ˵����ϣ�������ѡ�����ñ�Ѫʯ+������+Ǭ��ʥˮ�ϳɡ�",     
                "ͯ��ͯŮ��" : (: ask_fu :),
                "�켫��" : (: ask_tianjidao :),
        ]));

        setup();
        carry_object("/clone/cloth/dao-cloth")->wear();
}

string ask_fu()
{
        object me;
        object ob_wnh,ob_zz;
        object ob_fu;
        
        me = this_player();

        command("say ͯ��ͯŮ����ƶ��Ϊ���չ������죬���������Ҫ�Ļ�ƶ�����ǿ���Ч�͡�");
        command("say ����������Ҫ����һЩ���ϣ�����������죬���˹�͢��Ʒ�����¼����ϳ˵����ϡ�");
        command("say ��Σ���Ȼ���飬����Ȼ�����ĩ���������ͣ���ʹ�����ķ�Ч����ѡ�");
        command("say ��󣬵�Ȼ��ƶ��Ҳ��Ҫ��ȡһЩ�����ѣ��ܹ���Ҫ10�����ƽ�");
        command("ke");
        command("say ��ô����������ϲ��϶������˿��������ң��һ�������ͯ��ͯŮ�����㣬�˷����߲���ʧ��");
        
        // ��Ҫ�����
        if (! objectp(ob_wnh = present("wannian hong", me)))
                return "�����û������������ϰɣ�\n";        
                                
        if (base_name(ob_wnh) != "/clone/fam/item/wannian-hong")
                return "�����û������������ϰɣ�\n";
                
        // ��Ҫ��Ȼ���� 
        if (! objectp(ob_zz = present("tianran zhenzhu", me)))
                return "�����û������Ȼ����ɣ�\n";          
                        
        if (base_name(ob_zz) != "/clone/quarry/item/zhenzhu")
                return "�����û������Ȼ����ɣ�\n";          
        
        // ��Ҫ�ƽ�һ����
        if (query("balance", me) < 1000000000)
                return "�����û�б���10�����ƽ�ɡ�\n";
                
        // ��Ʒ�Ѿ�����
        destruct(ob_wnh);
        destruct(ob_zz);
        addn("balance", -1000000000, me);
        
        ob_fu = new("/clone/fam/item/tntn_fu");
        
        command("say ������Ȼ��Ҫ�Ķ����㶼�����ˣ�����ͽ�ͯ��ͯŮ�����㡣");
        
        message_sort("\n" HIC "$N" HIC "����������Ȼ�����ĩ�����һ���ó�һ�Ż�ɫ�ĵ�����Ȼ�����"
                     "Ĭ����䣬һ�����ʱ�䣬һ��ͯ��ͯŮ���Ѿ����á�\n" NOR, this_object());

        ob_fu->move(me, 1);
        
        message_vision("$N" NOR "�ó�" + ob_fu->name() + NOR "��$n" NOR "��\n" NOR, this_object(), me);

        return "�����Ҳ�����ˣ�ǮҲ���ˣ��Ӵ�����������Ƿ��\n";                
}

void init()
{
        add_action("do_show", "show");
        add_action("do_summon", "summon");
}

int life_warcraft()
{
        object me, ob;
        
        me = this_player();
        
        if( !query("warcraft/file", me) ) 
        {
                command("say ��Ŀǰû��ħ�ޣ��뵽�����ҿ�繺������� help warcraft��");
                return 1;
        }

        if( query("warcraft/status", me) != "died" )
        {
                command("shake");
                command("say ���ħ��Ŀǰ��û����������");
                return 1;
        }
        if( !query_temp("want_life_warcraft", me) )
        {
                command("hehe");
                command("say ��Ȼ��ˣ�����ͽ���ǧ���ƽ�ɣ�ƶ���������һ�η���");
                command("say �����ȷ�����������㹻�ƽ���ô��������һ�θ�ָ�");
                
                set_temp("want_life_warcraft", 1, me);
                
                return 1;
        }
        
        if( query("balance", me) < 50000000)
        {
                command("heng");
                command("say ˵����ǧ���ƽ��ѵ�����Ϸˣƶ��������");
                return 1;
        }
        
        addn("balance", -50000000, me);
        
        message_vision(HIM "$N" HIM "�ó�һ�ŷ�����ȼ��������У�Ȼ�����ţ�#��%��������������#��...\n" NOR, this_object());
        
        set("warcraft/status", "living", me);

        command("say ���ˣ����ħ�޸����ˣ�ʹ�� whistle <id> �Ϳ����ٻ������ˡ�");
        
        delete_temp("want_life_warcraft", me);
        me->save();

        return 1;
        
}
int ask_me()
{
        command("heihei");
        command("say ��ֻ������������⣬Ѱ������Ī�ᣡҪ"
                "�㱾�˵ģ��ҿɲ��ܰ��������£�");
        tell_object(this_player(), GRN "����ʦ�����������˵��"
                    "���Ҫ������ó������ҿ���(show)��\n" NOR);
        return 1;
}

int do_summon(string arg)
{
        if (! wizardp(this_player()))
        {
                command("say ��������ǰϹץ��ʲô���������ȥ��");
                return 1;
        }

        return 0;
}

int do_show(string arg)
{
        object money;
        object ob;
        mixed  obj;
        object me;
        string fn, filename;
        int    n, d;

        if (! arg)
                return notify_fail("��Ҫ����ʲô������\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("������û�����ֶ�����\n");

        if( query("equipped", ob) )
                return notify_fail("���Ƚ��" + ob->name() + "��װ����˵��\n");

        message_vision("$n�ó�һ"+query("unit", ob)+ob->name()+
                       "��$N˵�������а���...��\n",
                       this_object(), me);

        if( query("money_id", ob) )
        {
                command("say ������Ǯ��ʲô�����׸�����Ǿ͸��Һ��ˡ�");
                return 1;
        }

        if( !wizardp(me) && !query_temp("zhangpaid/����ʦ", me) )
        {
                command("heihei");
                command("say ��...��ôҲ���е���˼��˼�ɣ���"
                        "˵ʮ���ƽ���ô������Ȼ��Щ��Ҳ�����ԡ�");
                return 1;
        }

        if( ob->query_tongren() && query("no_identify", ob) )
        {
                if (! objectp(obj = ZHOUTIAN_D->identify_tongren(me, ob)))
                {
                        command("say �����Ʒ��������δ����������ʦ������ɡ�");
                        return 1;
                }
                obj->move(me, 1);
                command("say ���ˣ���ĳ�Ѩͭ���Ҹ��������ˣ���ȥ�ɡ�");
                delete_temp("zhangpaid/����ʦ", me);
                return 1;
        }

        if( ob->is_tessera() && query("no_identify", ob) )
        {
                if (! objectp(obj = IDENTIFY_D->identify_ob(me, ob)))
                {
                        command("say �����Ʒ��������δ����������ʦ������ɡ�");
                        return 1;
                }
                message("vision", sort_string(HIM + name() + "�ӿڴ�������һ�Ż�ɫ"
                                "�ķ�ֽ������������ľ�������Ƿ�ֽ��ȼ�ˣ�����" +
                                ob->name() + HIM "�ϣ�Ȼ����������дʣ���̫���Ͼ�"
                                "�������ɴ����˵��һ�����н����ȵ�����������\n" NOR, 64),
                                environment());
                tell_object(me, HIC "�����" + ob->name() + HIC"�����˲��������ı仯��\n" NOR);

                destruct(ob);
                obj->move(me, 1);
                delete("no_identify", obj);
                command("say ���ˣ���ı����Ҹ��������ˣ���ȥ�ɡ�");
                delete_temp("zhangpaid/����ʦ", me);
                return 1;
        }

        if( stringp(query("magic/imbue_ob", ob)) )
        {
                command("say ��...�ҿ�����Ӧ����" +
                        query("magic/imbue_ob", ob)->name()+
                        CYN "���������ܽ�һ����������Ǳ����" NOR);
                delete_temp("zhangpaid/����ʦ", me);
                return 1;
        }

        if( mapp(query("magic/imbue_ok", ob)) )
        {
                command("say Ŷ���ҿ��������Ѿ�����Ҫ�ڽ����ˣ�"
                        "Ҫ����Ǳ�����ñ�ķ����ˡ�\n");
                return 1;
        }

        if (! ob->is_item_make())
        {
                command("heng");
                command("say ��...��...�ҿ��������˰ɣ�");
                return 1;
        }

        if( ob->item_owner() != query("id", me) )
        {
                command("kick"+query("id", me));
                command("say ����Ϊ��ɽ�˵����������µİ��������������ģ�");
                return 1;
        }

        if( query("can_summon/"+query("id", ob), me) )
        {
                if (ob->weapon_level() > 1)
                {
                        command("poor"+query("id", me));
                        command("say �����ڻ����������ʱ��..."
                                "��Ҫ��ʥ�������а���");
                } else
                {
                        command("kok"+query("id", me));
                        command("say ������Ѿ���Ե�ˣ���˵���"
                                "������ô��ô�");
                }
                return 1;
        }

        message("vision", sort_string(HIM + name() + "�ӿڴ�������һ�Ż�ɫ"
                                "�ķ�ֽ������������ľ����"
                                "���Ƿ�ֽ��ȼ�ˣ�ɨ��" + ob->name() + HIM "��Ȼ"
                                "������ľ�����ˣ������㵸�����������дʣ�"
                                "��̫���Ͼ��������ɴ����˵��һ�����н���"
                                "�ȵ�����������\n" NOR, 64), environment());
        message_vision("��⻮��һ���⻪��$N���˷�����Ҳ��֪��������ô���¡�\n",
                       me);
        command("say ���ˣ����ˣ���������ˡ�");
        delete_temp("zhangpaid/����ʦ", me);
        set("can_summon/"+query("id", ob), base_name(ob), me);
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/kaiguang");
        log_file("static/item", sprintf("%s %s sancitfy %s(%s)\n",
                        log_time(), log_id(me),
                        filter_color(ob->name(1)),query("id", ob)));
        return 1;
}

int accept_object(object who, object ob)
{
        if( !query("money_id", ob) )
        {
                command("say �������ҿ�ûɶ��Ȥ��");
                return 0;
        }

        if (ob->value() < 50000)
        {
                command("say ���Ǹ���������ô�����Ҿ������ˣ�");
                return 1;
        }

        if (ob->value() < 100000)
        {
                command("say ��������Ҳ���е����⣬�Ҿ����㿪һ�ι�ɣ�");
                set_temp("zhangpaid/����ʦ", 1, who);
                destruct(ob);
                return 1;
        }

        command("say ��...��...��ô�չ˱��ۣ����ܰ����ʲô��");
        set_temp("zhangpaid/����ʦ", 1, who);
        destruct(ob);
        return 1;
}

void fight_ob(object ob)
{
        ::fight_ob(ob);
        message_vision("$N��Цһ��������������ͷ��ʲô�˶��С���˵������һָ$n��\n",
                       this_object(), ob);
        ob->unconcious();
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

void receive_damage(string type, int n)
{
        return;
}

void receive_wound(string type, int n)
{
        return;
}

string ask_tianjidao()
{
        object *obs;
        object ob;
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "����������Ի������������켫�����ҿ��㻹���Ȼ�ȥ�ɡ�\n";


        if( query("reborn/times", me)<3 )
                return "�߿����߿���û������æ��\n";
        
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                return "�����书�Ѿ��������£��α����̰��?\n";

        if (me->query_skill("lunhui-sword",1))
                return "�ߣ��������ӣ���Ȼ���̰�ģ�\n";
                                        
        // �Ѿ��������
        if( query("lunhui-sword_quest/tianjidao/finish", me) )
                return "�Ǻǣ��������ϴ���Щ���˿�����Ϸ�ȼü֮������\n";

        // ��������
        if( !query("lunhui-sword_quest/tianjidao/give_quest", me) )
        {
                command("shake");
                command("say ����ǰ���Ϸ򽫽�����һ����ϱ��׸�Ū���ˣ���֪����Ǻã�");
                command("say ������Ѽ���30�����˿���Ϸ����а취��������һ��");
                command("��������");
                command("tan");
                command("say �����˿���Ƿ��ֻ����ɽ������������У�����������Ǵ�����ˣ�");
                command("look"+query("id", me));
                command("say ����������Ѽ���30�����˿���Ϸ��Ϸ����ﵹ����һЩ�������书���Դ��ڸ��㡣");
                tell_object(me, this_object()->name() + HIG "��������Ѽ�30�����˿���Ͽ�ȥ�ɣ�\n" NOR);
                set("lunhui-sword_quest/tianjidao/give_quest", 1, me);
                me->save();
                return "��ô�������ǿ��ǣ�";
        }
        
        // �������
        
        if (! objectp(ob_hlp = present("tiancan si", me)))
                return "��ô����30�����˿�Ѽ�������\n";
                
        if (base_name(ob_hlp) != "/clone/quarry/item/cansi2")
                return "��ô����30�����˿�Ѽ�������\n";
                
        obs = all_inventory(me);
        obs = filter_array(obs, (: base_name($1) == "/clone/quarry/item/cansi2" :));
        if( sizeof(obs) < 30 )
                return "��ô����30�����˿�Ѽ�������\n";
                
        for (i = 0; i < 30; i++)
        {
                ob = obs[i];
                obs[i] = 0;
                destruct(ob);
        }
        
        command("hehe");
        command("nod");
        command("say ��Ȼ����������æ���ã��Ϸ�Ҳ����ŵ�ԣ����㡸�켫��������");
        
        message_sort(HIC "\n$N" HIC "����ǰȥ����$n" HIC "��������˵�˼��䣬Ȼ�����ó�һ���飬ָָ��㣬"
                     "$n" HIC "��ס�ص�ͷ������üͷ������������ͷ��˼ ����\n���ã�$n" HIC "��Цһ�����ƺ�"
                     "�Ըղŵ�������������\n", this_object(), me);
                        
        tell_object(me, HIG "��ϲ�������ˡ��켫����������Ŀǰ�ȼ�Ϊ10����\n");
        me->set_skill("tianji-dao", 10);
        set("lunhui-sword_quest/tianjidao/finish", 1, me);
        
        return "��л�ˣ�";
        
                
}
