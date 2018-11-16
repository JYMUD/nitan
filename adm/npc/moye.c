// moye.c  Īа
// Written by Doing Lu  1998/11/2

inherit NPC;
inherit F_NOCLONE;

#include <ansi.h>

int     ask_me();
int     no_money();

#define ITEM_TYPE       0
#define ITEM_STYPE      1
#define ITEM_UNIT       2
#define ITEM_WEIGHT     3
#define ITEM_POINT      4
#define ITEM_PROP       5

string ask_jinlan();
nosave mapping item_type = ([
//      ����        �������  �̳��ļ�    ��λ  ���� ���� �������
        "��"   : ({ "weapon", "blade",    "��", 150, 100, 0, }),
        "��"   : ({ "weapon", "sword",    "��", 150, 100, 0, }),
        "��"   : ({ "weapon", "club",     "��", 150, 100, 0, }),
        "��"   : ({ "weapon", "staff",    "��", 150, 100, 0, }),
        "��"   : ({ "weapon", "hammer",   "��", 350, 100, 0, }),
        "��"   : ({ "weapon", "axe",      "��", 220, 100, 0, }),
        "��"   : ({ "weapon", "whip",     "��", 150, 100, 0, }),
        "�̱�" : ({ "weapon", "dagger",   "֧", 30,  100, 0, }),
        "����" : ({ "weapon", "throwing", "��", 30,  100, 0, }),
        "����" : ({ "armor",  "armor",    "��", 150, 80,
                     ([ "armor_prop" : ([ "parry"   : "apply_armor() / 15 + 1",
                                          "armor"   : "apply_armor()",
                                       ]),
                      ]) }),
        "ս��" : ({ "armor",  "cloth",    "��", 200, 100, 0, }),
        "ѥ��" : ({ "armor",   "boots",   "˫", 60,  40,
                     ([ "armor_prop" : ([ "dodge"   : "apply_armor() / 10 + 1",
                                          "armor"   : "apply_armor()",
                                       ]),
                      ]) }),
        "ͷ��" : ({ "armor",  "head",     "��", 75,  50,  0, }),
        "����" : ({ "armor",  "waist",    "��", 80,  40,  0, }),
        "����" : ({ "armor",  "wrists",   "��", 50,  25,
                     ([ "armor_prop" : ([ "sword"   : "apply_armor() / 6 + 1",
                                          "staff"   : "apply_armor() / 6 + 1",
                                          "blade"   : "apply_armor() / 6 + 1",
                                          "club"    : "apply_armor() / 6 + 1",
                                          "hammer"  : "apply_armor() / 6 + 1",
                                          "whip"    : "apply_armor() / 6 + 1",
                                          "dagger"  : "apply_armor() / 6 + 1",
                                          "stick"   : "apply_armor() / 6 + 1",
                                          "unarmed" : "apply_armor() / 6 + 1",
                                          "claw"    : "apply_armor() / 6 + 1",
                                          "cuff"    : "apply_armor() / 6 + 1",
                                          "hand"    : "apply_armor() / 6 + 1",
                                          "strike"  : "apply_armor() / 6 + 1",
                                          "finger"  : "apply_armor() / 6 + 1",
                                          "parry"   : "apply_armor() / 6 + 1",
                                          "whip"    : "apply_armor() / 6 + 1",
                                          "armor"   : "apply_armor()",
                                       ]),
                      ]) }),
        "��"   : ({ "weapon", "xsword",   "֧", 30,  100, 0, }),
        "����" : ({ "armor",  "hands",    "˫", 45,  100,
                    ([ "armor_prop" : ([  "hand"   : "10",
                                          "strike" : "10",
                                          "unarmed_damage" : "apply_damage()",
                                          "armor"  : "10",
                                       ]),
                     ]) }),
        "����" : ({ "armor",  "hands",    "˫", 40,  100,
                    ([ "armor_prop" : ([  "unarmed": "10",
                                          "cuff"   : "10",
                                          "unarmed_damage" : "apply_damage()",
                                          "armor"  : "10",
                                       ]),
                     ]) }),
        "ָ��" : ({ "armor",  "finger",   "��", 35,  100,
                    ([ "armor_prop" : ([  "claw"   : "10",
                                          "finger" : "10",
                                          "unarmed_damage" : "apply_damage()",
                                          "armor"  : "10",
                                       ]),
                     ]) }),
]);

void create()
{
        set_name("Īа", ({ "mo ye", "moye", "mo" }));
        set("long", "����������������һ����ʳ�˼��̻��ģ����������������ʦ�ɽ������ӡ�\n" );

        set("nickname", HIY "����" NOR);
        set("gender", "Ů��");
        set("attitude", "friendly");

        set("age", 1525);
        set("shen_type", 0);

        set("str", 1000);                       // ��֤������Ϊ���ɹ�������ܲ��˶���

        set("inquiry", ([
/*
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "װ��" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "װ��" : (: ask_me :),

                "ûǮ" : (: no_money :),
                "Ǯ����":(: no_money :),
                "�Ȼ�" : (: no_money :),
*/
                "��������" : (: ask_jinlan :),

/*
                "����" : "����ͰѶ������ɽ�������������",
                "�˻�" : "����ͰѶ������ɽ�������������",
                "ԭ��" : "���Ƶ��߿ɲ���û��ԭ�ϰ���Ҫ�����ƺ������͵���"
                         "���׽�ĸһ��Ķ�����\n          Ҫ�����ƺ÷��߾�"
                         "���к�˿������Щ��������Щԭ�Ϻ����ң����������󰡣�\n",
                "�۸�" : "���ԭ�ϸ��ҿ���(show)���Ҿ��ܹ�����һ����Ǯ��",
*/
        ]));

        setup();

        set("startroom", "/d/item/xiaowu");
        check_clone();
        if (! this_object()) return;

        carry_object("/clone/misc/cloth")->wear();
}
// ������������
string ask_jinlan()
{
        object me = this_player();
        object ob_jinzhipg, ob_yinzhipg, ob_liangzhipg, ob_xiangbianpg, ob_hongzhipg;
        object ob_lanzhipg, ob_foguangbz, ob_shenzhizs, ob_shenzhifc, ob_shenzhisj, ob_shenzhimn;
        object ob;
        
        int i;
        
        if ( query("reborn/times", me) < 3 )
                return "�����û���ֻ�ת���ɣ�������������Ĳ����ʺ��㡣\n";

        // ���Ƿ��п�ȡ�������ı�־������ʱ�䳬����24Сʱ
        if (query("badao_quest/qu_jiasha", me))
        {
                // ����ȡ������
                if (time() - query("badao_quest/qu_jiasha", me) > 0)
                {
                        ob = new("/clone/armor/jinlan-jiasha");
                        
                        // ������ڵ�������10�����������˲��ܼ�                 
                        set("who_get", ([
                                "id"     : query("id", me),
                                "time"   : 600,
                        ]), ob);
                        ob->move(me, 1);
                        command("smile " + query("id", me));
                        command("say �����������ã���Ҫ�Ķ������Ѿ������ˣ������°ɣ�");
                        message_vision(HIC "$N" HIC "�ó�" + ob->name() + HIC "��$n" HIC "��\n", 
                                       this_object(), me); 
                        delete("badao_quest/qu_jiasha", me);
                        me->save();
                        
                        return "���ˣ����ҴӴ�������Ƿ�����أ�\n";
                }
                else
                        return "��Ľ������Ļ�û����������أ��� " + HIY + 
                               chinese_number((query("badao_quest/qu_jiasha", me) - time()) / 3600) + 
                               NOR + CYN " ��Сʱ�������ɡ�\n";
                
        }

        // ��Ҫ����
          /*
           *����Ƥ�� 10 ��
           *����Ƥ�� 10 ��
           *����Ƥ�� 10 ��
           *���Ƥ�� 10 ��
           *����Ƥ�� 10 ��
           *����Ƥ�� 10 ��
           *��ⱦ�� 10 ��
           *��֮��ʯ 1  ��
           *��֮��� 1  ��
           *��֮ˮ�� 1  ��
           *��֮��� 1  ��
           */
       
        command("nod");
        command("say ���¼䣬ֻ�������������������ģ�������ҪһЩ�ر�Ĳ��ϣ�");
        message_vision(HIM  + "\n"
                "*����Ƥ�� 10 ��\n"
                "*����Ƥ�� 10 ��\n"
                "*����Ƥ�� 10 ��\n"
                "*���Ƥ�� 10 ��\n"
                "*����Ƥ�� 10 ��\n"
                "*����Ƥ�� 10 ��\n"
                "*��ⱦ�� 10 ��\n"
                "*��֮��ʯ 5  ��\n"
                "*��֮��� 5  ��\n"
                "*��֮ˮ�� 5  ��\n"
                "*��֮��� 5  ��\n"
                "�����ֹ����� �ƽ� 10 ������YSG��\n" NOR, this_object());
        command("say �������Щ���϶������˵Ļ��������Ұɣ�");
        
        if (! query_temp("want_make_jinlanjiasha", me))
        {
                set_temp("want_make_jinlanjiasha", 1, me);
                return "��ô��������㿼�Ǻ��ˣ��������ң�\n";          
        }

        // ��Ҫ����Ƥ�� 10 
        if (! objectp(ob_jinzhipg = present("jinzhi pige", me)))
                return "�����û�������Ƥ��ɣ�\n";                  
        if (base_name(ob_jinzhipg) != "/clone/quarry/item/combine/jinzhi-pige")
                return "�����û�������Ƥ��ɣ�\n";

        if (ob_jinzhipg->query_amount() >= 10)
        {
                //ob_jinzhipg->add_amount(-10);
                //if (ob_jinzhipg->query_amount() < 1)destruct(ob_jinzhipg);
        }
        else
        {
                return "��ô����10�Ž���Ƥ�ﱸ������\n";
        }


        // ��Ҫ����Ƥ�� 10 
        if (! objectp(ob_yinzhipg = present("yinzhi pige", me)))
                return "�����û��������Ƥ��ɣ�\n";                  
        if (base_name(ob_yinzhipg) != "/clone/quarry/item/combine/yinzhi-pige")
                return "�����û��������Ƥ��ɣ�\n";

        if (ob_yinzhipg->query_amount() >= 10)
        {
                //ob_yinzhipg->add_amount(-10);
                //if (ob_yinzhipg->query_amount() < 1)destruct(ob_yinzhipg);
        }
        else
        {
                return "��ô����10������Ƥ�ﱸ������\n";
        }

        // ��Ҫ����Ƥ�� 10 
        if (! objectp(ob_liangzhipg = present("liangzhi pige", me)))
                return "�����û��������Ƥ��ɣ�\n";                  
        if (base_name(ob_liangzhipg) != "/clone/quarry/item/combine/liangzhi-pige")
                return "�����û��������Ƥ��ɣ�\n";

        if (ob_liangzhipg->query_amount() >= 10)
        {
                //ob_liangzhipg->add_amount(-10);
                //if (ob_liangzhipg->query_amount() < 1)destruct(ob_liangzhipg);
        }
        else
        {
                return "��ô����10������Ƥ�ﱸ������\n";
        }

        // ��Ҫ����Ƥ�� 10 
        if (! objectp(ob_lanzhipg = present("lanzhi pige", me)))
                return "�����û��������Ƥ��ɣ�\n";                  
        if (base_name(ob_lanzhipg) != "/clone/quarry/item/combine/lanzhi-pige")
                return "�����û��������Ƥ��ɣ�\n";
                
        if (ob_lanzhipg->query_amount() >= 10)
        {
                //ob_lanzhipg->add_amount(-10);
                //if (ob_lanzhipg->query_amount() < 1)destruct(ob_lanzhipg);
        }
        else
        {
                return "��ô����10������Ƥ�ﱸ������\n";
        }

        // ��Ҫ����Ƥ�� 10 
        if (! objectp(ob_hongzhipg = present("hongzhi pige", me)))
                return "�����û�������Ƥ��ɣ�\n";                  
        if (base_name(ob_hongzhipg) != "/clone/quarry/item/combine/hongzhi-pige")
                return "�����û�������Ƥ��ɣ�\n";

        if (ob_hongzhipg->query_amount() >= 10)
        {
                //ob_hongzhipg->add_amount(-10);
                //if (ob_hongzhipg->query_amount() < 1)destruct(ob_hongzhipg);
        }
        else
        {
                return "��ô����10�ź���Ƥ�ﱸ������\n";
        }               

        // ��Ҫ���Ƥ�� 10 
        if (! objectp(ob_xiangbianpg = present("xiangbian pige", me)))
                return "�����û�������Ƥ��ɣ�\n";                  
        if (base_name(ob_xiangbianpg) != "/clone/quarry/item/combine/xiangbian-pige")
                return "�����û�������Ƥ��ɣ�\n";

        if (ob_xiangbianpg->query_amount() >= 10)
        {
                //ob_xiangbianpg->add_amount(-10);
                //if (ob_xiangbianpg->query_amount() < 1)destruct(ob_xiangbianpg);
        }
        else
        {
                return "��ô����10�����Ƥ�ﱸ������\n";
        }
        
        // ��Ҫ��ⱦ�� 10 
        if (! objectp(ob_foguangbz = present("foguang baozhu", me)))
                return "�����û�����ⱦ��ɣ�\n";                  
        if (base_name(ob_foguangbz) != "/clone/quarry/item/combine/foguang-baozhu")
                return "�����û�����ⱦ��ɣ�\n";

        if (ob_foguangbz->query_amount() >= 10)
        {
                //ob_foguangbz->add_amount(-10);
                //if (ob_foguangbz->query_amount() < 1)destruct(ob_foguangbz);
        }
        else
        {
                return "��ô����10����ⱦ�鱸������\n";
        }

        // ��Ҫ��֮ˮ�� 1 
        if (! objectp(ob_shenzhisj = present("magic crystal", me)))
                return "�����û������֮ˮ���ɣ�\n";                  
        if (base_name(ob_shenzhisj) != "/clone/gift/mcrystal")
                return "�����û������֮ˮ���ɣ�\n";                   
                        
        // ��Ҫ��֮��� 1
        if (! objectp(ob_shenzhifc = present("magic jade", me)))
                return "�����û������֮���ɣ�\n";                  
        if (base_name(ob_shenzhifc) != "/clone/gift/mjade")
                return "�����û������֮���ɣ�\n";
        
        // ��Ҫ��֮��ʯ 1 
        if (! objectp(ob_shenzhizs = present("magic diamond", me)))
                return "�����û������֮��ʯ�ɣ�\n";                  
        if (base_name(ob_shenzhizs) != "/clone/gift/mdiamond")
                return "�����û������֮��ʯ�ɣ�\n";
        
        // ��Ҫ��֮��� 1 
        if (! objectp(ob_shenzhimn = present("magic agate", me)))
                return "�����û������֮��觰ɣ�\n";                  
        if (base_name(ob_shenzhimn) != "/clone/gift/magate")
                return "�����û������֮��觰ɣ�\n";   
        
        // ��Ҫ�ƽ�10����
        if (query("balance", me) < 100000)
                return "�����û�б���10�����ƽ�ɡ�\n";       
 
        // ���Ĳ���
        ob_jinzhipg = present("jinzhi pige", me);
        ob_yinzhipg = present("yinzhi pige", me);
        ob_lanzhipg = present("lanzhi pige", me);
        ob_hongzhipg = present("hongzhi pige", me);
        ob_liangzhipg = present("liangzhi pige", me);
        ob_xiangbianpg = present("xiangbian pige", me);
        ob_foguangbz = present("foguang baozhu", me);
                
        ob_jinzhipg->add_amount(-10);
        if (ob_jinzhipg->query_amount() < 1)destruct(ob_jinzhipg);
        ob_yinzhipg->add_amount(-10);
        if (ob_yinzhipg->query_amount() < 1)destruct(ob_yinzhipg);
        ob_lanzhipg->add_amount(-10);
        if (ob_lanzhipg->query_amount() < 1)destruct(ob_lanzhipg);
        ob_hongzhipg->add_amount(-10);
        if (ob_hongzhipg->query_amount() < 1)destruct(ob_hongzhipg);
        ob_liangzhipg->add_amount(-10);
        if (ob_liangzhipg->query_amount() < 1)destruct(ob_liangzhipg);
        ob_xiangbianpg->add_amount(-10);
        if (ob_xiangbianpg->query_amount() < 1)destruct(ob_xiangbianpg);
        ob_foguangbz->add_amount(-10);
        if (ob_foguangbz->query_amount() < 1)destruct(ob_foguangbz);  

        ob_shenzhifc = present("magic jade", me);
        ob_shenzhizs = present("magic diamond", me);
        ob_shenzhimn = present("magic agate", me);
        ob_shenzhisj = present("magic crystal", me);
                
        destruct(ob_shenzhifc);
        destruct(ob_shenzhizs);
        destruct(ob_shenzhimn);
        destruct(ob_shenzhisj);
        
        addn("balance", -100000, me);                
        
        //log_file("badao_quest_jiasha", query("id". me) + " �����������ĳɹ���\n");
        
        command("say ����������Щ���Ͼ�Ȼ�㶼�����ˣ����Ҿ��������ˡ�");
        command("say ��Ȼ����Ϻ͹�Ǯ�Ҷ����ˣ���������ľ�����Īа���Ͱɡ�");
        command("say �����������������ĺ�ʱ�ܳ�����������24Сʱ������ȡ�ɡ�");
        
        // ����24Сʱ���ȡ��������
        set("badao_quest/qu_jiasha", time() + 24 * 3600, me);
                
        tell_object(me, HIG "��ϲ�㣬Īа�Ѿ���Ӧ���������������ģ�����24Сʱ����ȡ(ask mo about ��������)��\n" NOR);        
        
        delete_temp("want_make_jinlanjiasha", me);
        
        me->save();
        
        return "��ס���ɱ����ˡ�\n";    
}


/*
void init()
{
        object me;

        // ���ѯ�ʱ�־
        if (! objectp(me = this_player()) || ! interactive(me))
                return;

        add_action("do_show", "show");
        add_action("do_answer", "answer");
        if( query_temp("item/status", me) == "item_gived" )
        {
                remove_call_out("greeting2");
                call_out("greeting2", 1, me);
        } else
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
}
*/

void greeting(object me)
{
        if (objectp(me) && environment(me) == environment())
        {
                message_vision("$NЦ�Ŷ�$n˵����ã�������������"
                               "��\n", this_object(), me);
        }
}

void greeting2(object me)
{
        if (objectp(me) && environment(me) == environment())
        {
                message_vision("$N��$n˵����Ǯ�Ϳ��Դ�����Ŷ��\n",
                               this_object(), me);
        }
}

int do_show(string arg)
{
        object  me;
        object  ob;
        string  msg;
        string  mat;
        int     power_point;
        int     value;
        int     n;

        me = this_player();
        if (! arg)
                return notify_fail("�����ʲô����Ҫ������ô��\n");

        mat = arg;
        power_point = 0;

        if (! objectp(ob = present(mat, me)))
                return notify_fail("���˰ɣ�������û�� " + mat + " ���ֶ�����\n");

        if( !query("material_attrib", ob) )
        {
                message_vision("$Nһ㶣���$n˵�������ֶ���Ҳ��������"
                               "�ƣ���û��˵����\n", this_object(), me);
        }

        power_point=query("power_point", ob);
        if (! power_point)
        {
                message_vision("$N��ϸ�Ŀ��˿�$n�ó���ԭ�ϣ�̾����"
                               "����ԭ�Ͽ����Ѿ��Ƕ��첻���ˡ�\n",
                               this_object(), me);
                return 1;
        }
        value = power_point * 2 + 10;
        msg = sprintf("$N��ϸ���˿�$n�ó���ԭ�ϣ�˵��������ԭ�ϴ�����ߣ�\n" +
                      "ֻ��Ҫ%s���ƽ���ô�������Ǽ۸�ܺ���ɡ�Ҫ��û����"
                      "�������ԭ�ϲ���Ǯ��\n", chinese_number(value));
        message_vision(msg, this_object(), me);

        return 1;
}

// ������ʾ��Ϣ
int ask_me()
{
        message_vision("$N��$n˵����"
                "����Ҫ�����Լ��ĵ�����\n"
                "�����������Ϊ�������������������������ޡ��Ⱥͻ��ף����ǵ�һ���ġ�\n"
                "���Ȱ�ԭ�ϸ��ҿ���(show)�����ȹ���һ�¼�Ǯ�����������"
                "���Ǿ�һ�ֽ�Ǯ��һ�ֽ�����\n", this_object(), this_player());
        return 1;
}

int no_money()
{
        object me;
        object ob;

        me = this_player();
        if( query_temp("item/status", me) == "item_gived" )
        {
                message_vision("$N������һ��$n����ûǮ�Ǿ��´ΰɣ�\n",
                               this_object(), me);
                if (objectp(ob = query_temp("item/accept")))
                {
                        message_vision("$N��" + ob->name() +
                                       "������$n��\n", this_object(), me);
                        if (! ob->move(me))
                                ob->move(environment());
                }
                delete_temp("item");
                delete_temp("item", me);
                return 1;
        }

        message_vision("$N�۾�һ�ɣ���$n˵����ûǮ����ûǮ����ɶ�£�"
                       "���ֲ��ǲ���ү��\n", this_object(), me);
        return 1;
}

/*
// ���ܶ���
int accept_object(object me, object ob)
{
        string status;
        int    val;

        if( query("level", me)<10 )
        {
                message_vision("$N�ź��Ķ�$n˵���������������������ȼ��ﵽ10�����ɡ�\n",
                               this_object(), me);
                return 0;
        }

        status = query_temp("item/status");
        if (status == "look_working")
        {
                message_vision("$N���ŵĶ�$n˵���𳳣��ɽ����ڸɻ��ء�\n",
                               this_object(), me);
                return 0;
        }

        if (status == "waiting")
        {
                if( query_temp("item/player_id") == query("id", me) )
                {
                        command("say ��úú͸ɽ�̸���ٴ��");
                        return 0;
                }

                message_vision("$N��$n˵���𳳣��ɽ����ں͹˿�̸���ء�\n",
                               this_object(), me);
                return 0;
        }

        if (status == "accept")
        {
                if( query_temp("item/player_id") != query("id", me) )
                {
                        command("say �����ںͱ�Ŀ��������أ����ȱ����ң�");
                        return 0;
                }

                if( !query("money_id", ob) )
                {
                        command("say �㻹�ǿ�㽻Ǯ�ɣ�Ҫ��ûǮ����˵��");
                        return 0;
                }
        }

        if( query("material_attrib", ob) && 
            query("power_point", ob) )
        {
                // �����ֵ
                val=query("power_point", ob)*2+10;
                message_vision("$N��$n˵�����ܺã������ԭ�ϴ��������Ҫ" +
                               chinese_number(val) + "���ƽ𣬽�Ǯ�ɡ�\n",
                               this_object(), me);
                val *= 10000;
                if (wizardp(me))
                {
                        message_vision("$N��ϸ���˿�$n��Ц��˵����ԭ"
                                       "������ʦ����ô����������ˡ�\n",
                                       this_object(), me);
                        val = 1;
                }
                set("item/value", val, ob);
                set_temp("item/status", "item_gived", me);
                set_temp("item/value", val, me);
                set_temp("item/status", "accept");
                set_temp("item/player_id",query("id", me));
                set_temp("item/accept", ob);

                // �����һ��ʱ��û�н�������ߴ���
                remove_call_out("time_out");
                call_out("time_out", 30, me, ob);
                return 1;
        }

        if( query("money_id", ob) )
        {
                object origin;
                mixed p;
                string *types;

                if( query_temp("item/status", me) == "answer_type" )
                {
                        message_vision("$Nҡҡͷ����$n˵����˵��Ҫ��ʲô������\n",
                                       this_object(), me);
                        return 0;
                }

                if( query_temp("item/status", me) != "item_gived" )
                {
                        message_vision("$N��$n�ݹ�ȥ��" + ob->name() +
                                       "���˻����������޹�����»��\n",
                                       this_object(), me);
                        return 0;
                }

                if( ob->value()<query_temp("item/value", me) )
                {
                        message_vision("$N��$n˵���Բ��𣬱��꿪��һ"
                                       "ǧ����������û�д���ۿۡ�\n",
                                       this_object(), me);
                        return 0;
                }

                origin = query_temp("item/accept");
                if( (p=query("can_make", origin)) == "all" )
                {
                        types = keys(item_type);
                } else
                if (arrayp(p))
                        types = p;
                else
                if (stringp(p))
                        types = ({ p });

                p=query("not_make", origin);
                if (arrayp(p))
                        types -= p;
                else
                if (stringp(p))
                        types -= ({ p });

                set_temp("item/types", types);
                set_temp("item/money", ob);
                ob->move(this_object());

                message_vision("$N��$n˵�����ã���͸�������������"
                               "��ʲô�������������(answer ����)��\n"
                               "��" + implode(types, "��") + "��\n",
                               this_object(), me);

                set_temp("item/status", "answer_type", me);
                return -1;
        }

        message_vision("Īа�۾�һ�ɣ���$N˵�����������Щ������ʲô���Ҳ�Ҫ��\n", me);
        return 0;
}
*/

int do_answer(string arg)
{
        object money;
        object ob;
        object me;
        object ganjiang;

        me = this_player();
        if( query_temp("item/status", me) != "answer_type" )
                return 0;

        if (! arg)
                return notify_fail("��Ҫ�ش�ʲô��\n");

        message_vision("$n��$N�����ʹ���" + arg + "�ɣ�\n",
                       this_object(), me);

        if (member_array(arg, query_temp("item/types")) == -1 ||
            undefinedp(item_type[arg]))
        {
                message_vision("$N�����һ�´��˸����磬һ���޹��Ŀ���$n��\n",
                               this_object(), me);
                return 1;
        }

        // ����ɽ�����
        if (! objectp(ganjiang = present("gan jiang")))
        {
                message_vision("$N���˿����ܣ�����һ����˵�����ɽ���"
                               "�������ڣ�û�취����...����������ɡ�\n",
                               this_object());
                if (ob = query_temp("item/accept"))
                {
                        message_vision("$N��" + ob->name() + "������$n��\n",
                                       this_object(), me);
                        if (! ob->move(me))
                                ob->move(environment());
                }
                delete_temp("item");
                delete_temp("item", me);
                return 0;
        }

        if (objectp(money = query_temp("item/money")))
                destruct(money);
        delete_temp("item/money");
        set_temp("item/status", "look_working");
        set_temp("item/status", "waiting", me);
        ob = query_temp("item/accept");
        set("item/ctype", arg, ob);
        set("item/type", item_type[arg][ITEM_TYPE], ob);
        set("item/stype", item_type[arg][ITEM_STYPE], ob);
        set("item/unit", item_type[arg][ITEM_UNIT], ob);
        set("item/point",query("power_point",  ob)*item_type[arg][ITEM_POINT]/100, ob);
        set("item/power",query("power_special",  ob), ob);
        set("item/owner", me, ob);
        set("item/owner_id",query("id",  me), ob);
        set("item/owner_name", me->name(1), ob);
        set("item/wscale", item_type[arg][ITEM_WEIGHT], ob);
        set("item/prop", item_type[arg][ITEM_PROP], ob);
        message_vision("$N��" + ob->name() + "������$n��\n",
                       this_object(), ganjiang);
        if (! ob->move(ganjiang))
                error("Can move the object to ganjiang.");
        remove_call_out("time_out");
        ganjiang->accept_object(this_object(), ob);
        return 1;
}

void time_out(object me, object ob)
{
        object money;
        int at_present;

        money = query_temp("item/money");

        if (! objectp(me))
                me = find_player(query_temp("item/player_id"));

        if (! objectp(me) || environment(me) != environment())
        {
                command("say ��֣��ղ���λ�����أ���ô������ˣ�\n");
                at_present = 0;
        } else
        {
                command("say ��������ԥ�ɣ��ҿɲ��ܸ�����ţ���������ɣ�");
                at_present = 1;
        }

        delete_temp("item");
        if (objectp(me))
                delete_temp("item", me);

        if (money)
        {
                if (at_present)
                          command("give "+query("id", money)+
                                  " to "+query("id", me));

                if (environment(money) == this_object())
                        command("drop"+query("id", money));
        }

        if (ob)
        {
                if (at_present)
                          command("give "+query("id", ob)+
                                  " to "+query("id", me));

                if (environment(ob) == this_object())
                        command("drop"+query("id", ob));
        }
}
