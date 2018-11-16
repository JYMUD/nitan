// punish the berays user
#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_DBASE;

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "ִ������");
        CHANNEL_D->do_channel( this_object(), "sys", "ִ�������Ѿ�������");
        remove_call_out("monitor");
        call_out("monitor", 1);
}

int clean_up() { return 1; }

void family_punish();

string *punishers = ({
        CLASS_D("xiakedao") + "/zhangsan",
        CLASS_D("xiakedao") + "/lisi",
});

string *catchers = ({
        CLASS_D("misc") + "/zhang",
});

mapping family_punishers = ([
        "�䵱��"   : ({ CLASS_D("misc") + "/chongxu" }),
        "������"   : ({ CLASS_D("misc") + "/fangsheng" }),
        "��ɽ��"   : ({ CLASS_D("misc") + "/murenqing" }),
        "��ɽ����" : ({ CLASS_D("misc") + "/murenqing" }),
        "������"   : ({ CLASS_D("misc") + "/guoxiang" }),
        "�һ���"   : ({ CLASS_D("misc") + "/taogu" }),
        "������"   : ({ CLASS_D("misc") + "/zhong" }),
        "ؤ��"     : ({ CLASS_D("misc") + "/wangjiantong" }),
        "��Ĺ��"   : ({ CLASS_D("misc") + "/popo" }),
        "ȫ���"   : ({ CLASS_D("misc") + "/laodao" }),
        "������"   : ({ CLASS_D("misc") + "/xiaoxian" }),
        "��ң��"   : ({ CLASS_D("misc") + "/liqiushui" }),
        "ѩɽ��"   : ({ CLASS_D("misc") + "/laoseng" }),
        "Ѫ����"   : ({ CLASS_D("misc") + "/hongri" }),
        "���չ�"   : ({ CLASS_D("misc") + "/tonglao" }),
        "Ľ������" : ({ CLASS_D("misc") + "/furen" }),
        "ŷ������" : ({ CLASS_D("misc") + "/laonu" }),
        "�������" : ({ CLASS_D("misc") + "/huyidao" }),
        "���ϻ���" : ({ CLASS_D("misc") + "/duansh" }),
        "��ɽ"     : ({ CLASS_D("misc") + "/songshan" }),
        "��ɽ"     : ({ CLASS_D("misc") + "/hengshan" }),
        "����"     : ({ CLASS_D("misc") + "/bosi" }),
        "ħ��"     : ({ CLASS_D("misc") + "/chiyou" }),
        "�컨��"   : ({ CLASS_D("misc") + "/yuwanting" }),
        "�������" : ({ CLASS_D("misc") + "/zhanglao" }),
// add by wuji
              "�嶾��"   : ({ CLASS_D("misc") + "/wudu" }), 
              "��������"   : ({ CLASS_D("misc") + "/tangmen" }),
              "������"   : ({ CLASS_D("misc") + "/lingxiao" }), 
              "���ư�"   : ({ CLASS_D("misc") + "/tiezhang" }), 
              "�����"   : ({ CLASS_D("misc") + "/jueqing" }), 
              "������"   : ({ CLASS_D("misc") + "/kunlun" }),
]);

void monitor()
{
        int i;
        object *obs;
        string *aviable;
        string punisher;
        string catcher;
        string msg;

        remove_call_out("monitor");
        call_out("monitor", 180 + random(60));

        /*
        if (VERSION_D->is_boot_synchronizing())
                // ����������ͬ���汾����ô�������ͷ�ϵͳ
                return;
        */

        // when the pking was going, I won't let the punisher out,
        // because the competitor may in PKD.
        if (PK_D->is_pking())
                return;

        CHANNEL_D->do_channel(this_object(), "sys",
                              "��������ɨ������������ҡ�");

        // search all the player for punishing
        obs = filter_array(users(),
                           (: query("combat_exp", $1) >= 100000 &&
                              query("pk_score", $1) >= 8 &&
                              ! $1->is_in_prison() &&
                              ! $1->is_ghost() &&
                              ! wizardp($1) &&
                              environment($1) :));

        if (sizeof(obs))
        {
                obs = sort_array(obs, (: query("combat_exp", $2) -
                                         query("combat_exp", $1):));
                aviable = filter_array(catchers, (: ! find_object($1) :));
                i = 0;
                while (sizeof(aviable) && i < sizeof(obs))
                {
                        punisher = aviable[random(sizeof(aviable))];
                        punisher->catch_ob(obs[i]);
                        aviable -= ({ punisher });
                        i++;
                }
        }

        // search all the player for killing
        obs = filter_array(users(),
                           (: query("combat_exp", $1) >= 100000 &&
                              query("combat/need_punish", $1) &&
                              ! $1->is_in_prison() &&
                              ! $1->is_ghost() &&
                              ! wizardp($1) &&
                              environment($1) :));

        if (sizeof(obs))
        {
                obs = sort_array(obs, (: query("combat_exp", $2) -
                                         query("combat_exp", $1):));
                aviable = filter_array(punishers, (: ! find_object($1) :));
                i = 0;
                while (sizeof(aviable) && i < sizeof(obs))
                {
                        msg=query("combat/need_punish", obs[i]);
                        punisher = aviable[random(sizeof(aviable))];
                        punisher->start_punish(obs[i], msg);
                        aviable -= ({ punisher });
                        i++;
                }
        }

        // search all the player for catching
        obs = filter_array(users(),
                           (: query("combat_exp", $1)<300000 &&
                              $1->query_condition("killer") &&
                              ! $1->is_ghost() &&
                              ! $1->is_in_prison() &&
                              ! wizardp($1) &&
                              environment($1) :));

        if (sizeof(obs))
        {
                obs = sort_array(obs, (: query("combat_exp", $2) -
                                         query("combat_exp", $1):));
                aviable = filter_array(catchers, (: ! find_object($1) :));
                i = 0;
                while (sizeof(aviable) && i < sizeof(obs))
                {
                        punisher = aviable[random(sizeof(aviable))];
                        punisher->start_catch(obs[i]);
                        aviable -= ({ punisher });
                        i++;
                }
        }

        // Normal I won't check the player
        if (random(10) == 0 || 1)
                family_punish();
}

void family_punish()
{
        object ob;
        object *obs;
        mapping betrayer;
        string *punishers;
        string punisher;
        string key;

        obs = filter_array(users(), (: query("combat_exp", $1) >= 100000 &&
                                       environment($1) &&
                                       !query("no_fight", environment($1)) &&
                                       mapp(query("betrayer", $1)):));

        if (! sizeof(obs))
                return;

        foreach (ob in obs)
        {
                betrayer=query("betrayer", ob);
                foreach (key in keys(betrayer))
                {
                        if (key == "times") continue;
                        if (! arrayp(punishers = family_punishers[key]))
                        {
                                addn("detach/"+key, 1, ob);
                                addn("detach/times", 1, ob);
                                betrayer["times"] -= betrayer[key];
                                map_delete(betrayer, key);
                                if (betrayer["times"] < 1)
                                        delete("betrayer", ob);
                                continue;
                        }

                        punishers = filter_array(punishers, (: ! find_object($1) :));
                        if (! sizeof(punishers))
                                // No punishers aviable now
                                continue;

                        punisher = punishers[random(sizeof(punishers))];
                        if (file_size(punisher + ".c") < 0)
                        {
                                log_file("static/log", "can not find punisher: "
                                         + punisher + "\n");
                                break;
                        }
                        punisher->start_punish(ob, key);
                        break;
                }
        }
}
