// huoji. ������
#include <ansi.h>
#include <dbase.h>

inherit BUNCHER; 
int ask_me();
int ask_send();
int do_send(string arg);
string makeup_space(string s);
mixed ask_back();
void create()
{
       set_name("����", ({ "zi yin", "zi", "yin" }));
        set("shen_type", 1);
        set("gender", "Ů��");
        set("age", 15);
        set("long","�������������Ů��ֻ���京Ц�紺�ң��񴽺��㣬����ϸ������ȶ��ˣ���ֲ����£������������㣬ʵ���˼��ɫ��\n");
        set("attitude", "friendly");
        set("inquiry", ([
                "�ͻ�" : (: ask_send :),
                "song" : (: ask_send :),
                "send" : (: ask_send :),
                "�һ�ʢ��" : (: ask_back :),
        ]));
        set("vendor_goods", ([
                "/clone/flower/red_rose":99,
                "/clone/flower/white_rose":99,
                "/clone/flower/qingren_cao":99,
                "/clone/flower/ding_xiang":99,
                "/clone/flower/mu_dan":99,
                "/clone/flower/yu_jinxiang":99,
                "/clone/flower/bai_he":99,
                "/clone/flower/kang_naixin":99,
                "/clone/flower/ma_tilian":99,
                "/clone/flower/jin_yucao":99,
                "/clone/flower/huo_he":99,
                "/clone/flower/hu_dielan":99,
                "/clone/flower/qiu_haitang":99,
                "/clone/flower/shi_hulan":99,
                __DIR__"obj/zhongzhi": 20,
        ]));
        setup();
        carry_object(CLOTH_DIR"pink_cloth")->wear();
        carry_object(CLOTH_DIR"boot/flower_shoe")->wear();
        //remove_call_out("do_check_flower");
        //call_out("do_check_flower", 10+random(10) );
        remove_call_out("do_full_flower");
        call_out("do_full_flower", 1800 );
}
int do_full_flower()
{
        tell_room(environment(), "\n�����������˽�����\n");
        tell_room(environment(), "���ˣ��������������ʻ����ˡ�����ͷ���Ǹ�������������к���\n");
        tell_room(environment(), "����ϲ��������лл�������壬���ں���Ļ�����ɡ���\n");
        tell_room(environment(), "�������߹�ȥ�������úá�\n");
        tell_room(environment(), "���������˳���������˵���������ź��ˣ������´���������\n");
        tell_room(environment(), "���������˳�ȥ��\n");
        set("vendor_goods", ([
                "/clone/flower/red_rose":99,
                "/clone/flower/white_rose":99,
                "/clone/flower/qingren_cao":99,
                "/clone/flower/ding_xiang":99,
                "/clone/flower/mu_dan":99,
                "/clone/flower/yu_jinxiang":99,
                "/clone/flower/bai_he":99,
                "/clone/flower/kang_naixin":99,
                "/clone/flower/ma_tilian":99,
                "/clone/flower/jin_yucao":99,
                "/clone/flower/huo_he":99,
                "/clone/flower/hu_dielan":99,
                "/clone/flower/qiu_haitang":99,
                "/clone/flower/shi_hulan":99,
        ]));
        remove_call_out("do_full_flower");
        call_out("do_full_flower",1800);
        return 1;
}
private void go_home()
{
        if( !living(this_object()) ) return;
        message_vision("$N��ɫ���ŵ��뿪�ˡ�\n", this_object());
        this_object()->move("/d/city/huadian");
        message_vision("$N�첽���˹�����\n", this_object());
}
void init()
{
        if( environment() != load_object("/d/city/huadian") )
        {
                remove_call_out("go_home");
                call_out("go_home", 1);
        }
        add_action("do_check", "list");
        add_action("do_buy", "buy");
        //add_action("do_send", "send");
        //add_action("do_check_flower", "check_test");

}
string inventory_desc(object ob)
{
        return sprintf("%s%s",
                query("equipped", ob)?HIC"��"NOR:"",
                ob->short()
        );
}
string price_string(int v)
{
        if( v%10000 == 0 )
                return chinese_number(v/10000) + "���ƽ�";
        if( v%100 == 0 )
                return chinese_number(v/100) + "������";
        return chinese_number(v) + "��ͭ��";
}
int do_buy(string what)
{
        int i, amount, value, val_factor;
        string ob_file;
        object ob, me = this_player();
        mapping goods;
        string *name, last = "";
        amount=1;
        val_factor=10;
        if( !what ) return notify_fail("����˵��������ʲô��\n");
        if( sscanf(what, "%d %s", amount, what)!=2 )
        {
                amount = 1;
        }
        if( amount < 1 ) return notify_fail("����˵����������٣�\n");
        if( amount > 10 ) return notify_fail("����˵������һ�������ʮ�䡣\n");
        if( !mapp(goods = query("vendor_goods")) )
                return notify_fail("����˵������Ķ���ȫ�����ˡ�\n");
        if(this_player()->is_busy())
                return notify_fail("��������æ���ء�\n");
        name = keys(goods);
        for(i=0; i<sizeof(name); i++)
        {
                if(what == name[i]->name() || name[i]->id(what))
                {
                        if( stringp(ob_file = name[i]) )
                        {
                                if(goods[name[i]]<amount)
                                        return notify_fail("����˵��������û����ô����Ҫ������ֻ��ˡ�\n");
                                ob = new(ob_file);
                                if(goods[name[i]]<10)
                                {
                                        val_factor=30;
                                        tell_object(this_player(), "����˵��������"+query("name",ob)+"ֻʣ�º����ˣ��۸�������������"+MONEY_D->price_str(query("value",ob)*val_factor/10)+"һ"+query("unit",get_object(name[i]))+"��\n");
                                }
                                else if(goods[name[i]]<20)
                                {
                                        val_factor=20;
                                       tell_object(this_player(), "����˵��������"+query("name",ob)+"̫�����ˣ��۸�����һ������"+MONEY_D->price_str(query("value",ob)*val_factor/10)+"һ"+query("unit",get_object(name[i]))+"��\n");
                                }
                                else if(goods[name[i]]<50)
                                {
                                        val_factor=15;
                                       tell_object(this_player(), "����˵��������"+query("name",ob)+"ϲ�����˺ܶ࣬�۸�����һ�룬��"+MONEY_D->price_str(query("value",ob)*val_factor/10)+"һ"+query("unit", get_object(name[i]))+"��\n"); 
                                }
                                switch(MONEY_D->player_pay(me,query("value", ob)*amount*val_factor/10) )
                                {
                                        case 0: destruct(ob);
                                                return notify_fail("����˵����⵰��һ�ߴ���ȥ��\n");
                                        case 2: destruct(ob);
                                                return notify_fail("����˵��������Ǯ�����ˣ���Ʊ��û���ҵÿ���\n");
                                }
                                ob->set_amount(amount);
                                if (ob->move(me))
                                {
                                        goods[name[i]]=goods[name[i]]-amount;
                                        if(goods[name[i]] <= 0)
                                        {
                                                map_delete(goods,name[i]);
                                                last = "���";
                                        }
                                        message_vision(sprintf("$N��$n����%s"+chinese_number(amount)+"%s%s��\n",last,query("unit", ob),ob->name()),me,this_object());
                                } else destruct(ob);
                                this_player()->start_busy(1);
                                return 1;
                        }
                }
        }
        return notify_fail("������ʲô��\n");
}
int do_check(string arg)
{
        mapping goods;
        string list, *name;

        int i;
        if( arg && !this_object()->id(arg) ) return 0;
        if( !mapp(goods = query("vendor_goods")) ) return 0;
        name = keys(goods);
        if(!sizeof(name)) return 0;
        list = "����Թ���������Щ������\n";
        for(i=0; i<sizeof(name); i++)
                list += sprintf("%-30s��\t%s\t��ʣ%s%s\n",
                        makeup_space(query("name",get_object(name[i]))+"("+ 
                        query("id", get_object(name[i]))+")"),
                        MONEY_D->price_str(query("value", get_object(name[i]))),
                        CHINESE_D->chinese_number(goods[name[i]]),
                        query("unit", get_object(name[i])));
        write(list);
        return 1;
}
string query_flower_file( string arg)
{
        return sprintf( DATA_DIR "flower/%c/%s", arg[0], arg );
}
int do_check_flower()
{
        object *ob,ob_letter;
        string file ;
        int i;
        ob = users();
        i = sizeof(ob);
        while (i--)
        {
                if (userp(ob[i]))
                {
                        file=query_flower_file(query("id", ob[i])+".o");
                        assure_file( file );
                        if(file_size(file)!=-1)
                        {
                                if( (interactive(ob[i])) && (living(ob[i])) &&
                                        (!ob[i]->is_busy()) &&
                                        (!ob[i]->is_fighting()) )
                                {
                                        ob_letter=new("/clone/misc/flower");
                                        ob_letter->set_owner(query("id", ob[i]));
                                        ob_letter->check(ob[i],this_object());
                                        destruct(ob_letter);
                                }
                        }
                }
        }
        remove_call_out("do_check_flower");
        call_out("do_check_flower", 10+random(10) );
        return 1;
}
int ask_send()
{
        write( "����Ƿ��˵��������л�͹ٹ���С�꣬���������ｫ����ã�\nȻ�����СŮҪ�͸�˭��СŮһ��Ϊ���͵���\n(send flower_name to playername)��\n���ǻ����շѹ����ǣ��ͻ��������ʮ��������\nÿһ�仨��ȡһ���������ͻ��ѡ�\n");
        return 1;
}
int do_send(string arg)
{
        object tar, ob_flower, send_flower, me=this_player();
        int i, k, money_amount;
        mapping flower, *flowers;
        string flower_name, who;

        if( !arg || sscanf(arg, "%s to %s", flower_name, who)!=2 )
                return notify_fail("����˵������Ҫ��ʲô����˭��\n");
        if(!FINGER_D->acquire_login_ob(who))
                return notify_fail("����˵�����������������\n");
        ob_flower=present(flower_name,me);
        if(!ob_flower) return notify_fail("������������Ϻ���û�����ֻ���\n");
        if( !query("flower", ob_flower) )
                return notify_fail("��������Բ����������ﲻ�����������\n");
        if(me->is_busy())
                return notify_fail("��������æ���ء�\n");
        if(!send_flower=new("/clone/misc/flower"))
                return notify_fail("/clone/misc/flower��ʼ������\n");
        send_flower->set_owner(who);
        if( query("flowername", send_flower) == flower_name )
        {
                command("hmm ");
                return notify_fail("��������Բ����һ�û�����ϴεĻ��͵��أ������Ժ������ɡ�\n");
        }
        if( query("from", send_flower) == (me->name(1)+"("+query("id", me)+")") )
        {
                command("hmm ");
                return notify_fail("��������Բ����һ�û�����ϴεĻ��͵��أ������Ժ������ɡ�\n");
        }
        //******************************�շ�*******************************************//
        if(ob_flower->query_amount()<10) money_amount=10;
        else money_amount=ob_flower->query_amount();
        if(ob_flower->query_amount()>1000) money_amount=1000;
        else money_amount=ob_flower->query_amount();
        switch (MONEY_D->player_pay(me, money_amount*100) )
        {
                case 0: destruct(send_flower);
                        return notify_fail("�������������û���㹻��������֧���ͻ����á�\n");
                case 2: destruct(send_flower);
                        return notify_fail("�������������Ǯ�����ˣ���Ʊ��û���ҵÿ���\n");
        }
        message_vision("$N��$n˵�������ͻ�������"+price_string(money_amount*100)+"����\n",this_object(), me);

        set("flowername",query("name",  ob_flower), send_flower);
        set("flower_id",query("id",  ob_flower), send_flower);
        set("to", who, send_flower);
        set("from", me->name(1)+"("+query("id", me)+")", send_flower);
        set("amount", ob_flower->query_amount(), send_flower);

        flower = ([
                "flowername":query("name", ob_flower),
                "flower_id":query("id", ob_flower),
                "to": who,
                "from":me->name(1)+"("+query("id", me)+")",
                "amount": ob_flower->query_amount(),
        ]);
        send_flower->send_flower(flower);
        send_flower->save();
        destruct(send_flower);
        destruct(ob_flower);
        me->start_busy(1);

        message_vision("$n�����ϵ�"+flower["flowername"]+"�ó�����$N��\n",this_object(), me);
        message_vision("$N��$n˵�������ðɣ�СŮ�Ӷ��Ὣ���͵�����\n",this_object(), me);

        remove_call_out("do_check_flower");
        call_out("do_check_flower", 10+random(10) );
        return 1;
}
string makeup_space(string s)
{
        string *ansi_char = ({
                BLK,   RED,   GRN,   YEL,   BLU,   MAG,   CYN,   WHT,
                BBLK,  BRED,  BGRN,  BYEL,  BBLU,  BMAG,  BCYN,
                       HIR,   HIG,   HIY,   HIB,   HIM,   HIC,   HIW,
                       HBRED, HBGRN, HBYEL, HBBLU, HBMAG, HBCYN, HBWHT,
                NOR
        });

        string space = s;
        int i, space_count;

        for (i = 0; i < sizeof(ansi_char); i ++)
                space = replace_string(space, ansi_char[i], "", 0);

        space_count = sizeof(s) - sizeof(space);
        if (sizeof(s) >= 15)
                space_count = 15 - sizeof(space);

        space = s;

        for (i = 0; i < space_count; i ++) space += " ";
        return space;
}

/*
inherit NPC;
inherit F_DEALER;
#include <ansi.h>;
int do_send(string arg);
void create()
{
        set_name("������", ({ "huadian huoji", "huoji" }));
        set("str", 20);
        set("gender", "����");
        set("age", 18);
        set("long", "��ʮ��ǿ׳������ȥ�Ἰ���书���Ի�������Ҳ���Ǿ�ͨ��\n");
        set("combat_exp", 2500);
        set("attitude", "friendly");

        set("vendor_goods", ({
                __DIR__"obj/red_rose",
                __DIR__"obj/yellow_rose",
                __DIR__"obj/yujinxiang",
                __DIR__"obj/kangnaixin",
                __DIR__"obj/dog_grass",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_send", "send");
}
int do_send(string arg)
{
        object obj, flower, me = this_player();
        string target, item;

        if(!arg) return notify_fail("������˵����Ҫ��˭ʲô������\n");
        if( me->is_busy() )
                return notify_fail("����һ��������û����ɣ�\n");
        if( sscanf(arg, "%s to %s", item, target) !=2)
                return notify_fail("������˵����Ҫ��˭ʲô������\n");
        obj = find_player(target);
                if(!obj || !me->visible(obj))
                        return notify_fail("������˵���������ڲ��ڡ�û�������ͻ���\n");

        if( !living(obj))
                return notify_fail("������˵����Ǹ������û�������ͻ���\n");
        if( !objectp(flower = present(item, me)) )
                return notify_fail("������˵��������û�����ֻ���\n");
        if( !query("flower", flower) )
                return notify_fail("������˵����ֻ�����Ұ����ͻ���\n");
        if( query("no_drop", flower) )
                return notify_fail("�����������������ˡ�\n");

        flower->move(obj);
        me->save();
        obj->save();
        tell_object(me,HIC"������Ц��Ц��������λ"+RANK_D->query_respect(me)+"�Ժ���͸����͵�"+query("name", obj)+"���ϡ���ת�����ȥ�ˡ�\n"NOR);
        tell_object(obj,HIC"�������߹����ݸ���һ"+query("unit", flower)+query("name", flower)+HIC"������˵����������"+query("name", me)+"�͸���ġ���ת��Ц��Ц�����ˡ�\n"NOR);
        tell_object(me, HIC"������Ƭ�̺����Ц���������İɣ��͵��ˡ���\n" NOR );
        return 1;
}
*/


mixed ask_back()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "�һ���" )
        {
                message_vision("$N�Թ��Եĸɻ����û������$n��˵ʲô��\n",
                               this_object(), me);
                return -1;
        }

        message_sort("$N��Ȼ̧��ͷ�����������´�����һ��"
                     "��$n���۽�΢΢һ�������̷������е�"
                     "��ƣ����������һֻ�׵�˵������"
                     "������ֻ�׵���һ����ɡ�\n", 
                     this_object(), me);

        tell_object(me, HIW "�����ϰ׵���˺ܾã�Խ���󺣣���Ȼ��ǰһ����"
                    "���Ѿ��������һ�����\n" NOR);
        me->move("/d/taohua/jingshe");
        return -1;
}

