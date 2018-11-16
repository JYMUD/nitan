// Written by Lonely@chinamud.cn

#include <ansi.h>
inherit NPC;

int ask_blue();
int ask_pink();
int ask_gold();
int ask_green();
int ask_steady();
int do_combine(object me, object ob);
int do_finish(object me, object ob);
mapping upgrade_material = ([
        "blue" : ([ "/clone/item/bcrystal" : 3, ]),
        "pink" : ([ "/clone/item/pcrystal" : 1,
                    "/d/item/obj/xuantie"  : 3, ]),
        "gold" : ([ "/clone/item/ycrystal" : 2, ]),
        "green" : ([ "/clone/item/gcrystal" : 1,
                     "/d/item/obj/xuantie" : 5, ]),
        "steady" : ([ "/clone/item/bcrystal" : 1,
                      "/d/item/obj/xuantie" : 4,
                      "/clone/item/mcrystal" : 1, ]),
        //"increase":
]);

void create()
{
        set_name("ŷұ��", ({ "ouye zi", "zi" }) );
        set("nickname", RED "���Ľ���" NOR );
        set("gender", "����" );
        set("age", 60);
        set("long",
                "��ͷ�ϰ���ͷ�����Ƴ���Ʈ����ǰ����Ŀ���ݵ������й⣬\n"
                "��Ŀ��������˸˸���ž��������ݵĽ��⣬�����ƺ�����Χ\n"
                "��һ�ɽ���֮�С�\n");
        set("str", 25);
        set("dex", 20);
        set("con", 17);
        set("int", 30);
        set("shen_type", 0);
        set("max_neli",5000);
        set("jiali",50);
        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("jiuyin-baiguzhao",200);
        set_skill("force",150);
        set_skill("sword",150);
        set_skill("bibo-shengong",100);
        set_skill("luoying-shenjian",100);
        set_skill("parry",90);
        set_skill("anying-fuxiang",100);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage",50);
        create_family("������", 1, "����");
        set("combat_exp", 250000);

        map_skill("force","bibo-shengong");
        map_skill("parry","luoying-shenjian");
        map_skill("sword","luoying-shenjian");
        map_skill("unarmed","jiuyin-baiguzhao");
        map_skill("dodge","anying-fuxiang");

        set("attitude", "peaceful");

        set("inquiry", ([
                "����" : "���Ѿ��ܾúܾ�û�������ˣ��㻹�����ұ��˰ɡ�\n",
                "��װ" : (: ask_blue() :),
                "��װ" : (: ask_pink() :),
                "��װ" : (: ask_gold() :),
                "��װ" : (: ask_green() :),
                "ǿ��" : (: ask_steady() :),
        ]) );
        setup();
        set("chat_chance", 3);
        set("chat_msg", ({
                "ŷұ�Ӹ������裺��������⣬�����͡����������⣬��Ӣ�ۣ�\n",
                "ŷұ�ӵ�ͷ�������ƺ���˼��ʲô��\n"
                "ŷұ��̾��һ�����������Ӣ�ۣ���Ӣ�ۡ�����������\n"
        }) );
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        add_action("do_show", "show");
}

int ask_blue()
{
        object me = this_player();
        object ob = this_object();

        message_vision(CYN "$N��$n" CYN "˵��������Ҫ�ϳ���ɫװ�������ȸ�����һ�����ƽ�Ȼ������²���׼���ø��ҡ�\n"
                "       1����Ҫ�ϳɵİ�ɫװ�� 1 ��\n"
                "       2����ͬ�ȼ��Ѿ���ȡ���Եĺ�ˮ���򳬼���ˮ�� 3 ��\n" NOR, ob, me);
        set_temp("upgrade/money", 100000000, me);
        set_temp("upgrade/do", "blue", me);
        return 1;
}

int ask_pink()
{
        object me = this_player();
        object ob = this_object();

        message_vision(CYN "$N��$n" CYN "˵��������Ҫ�ϳɷ�ɫװ�������ȸ�����һ�����ƽ�Ȼ������²���׼���ø��ҡ�\n"
                "       1����Ҫ�ϳɵ���ɫװ�� 1 ��\n"
                "       2����ˮ���򳬼���ˮ�� 1 ��\n"
                "       3������ʯ 3 ��\n" NOR, ob, me);
        set_temp("upgrade/money", 100000000, me);
        set_temp("upgrade/do", "pink", me);
        return 1;
}

int ask_gold()
{
        object me = this_player();
        object ob = this_object();

        message_vision(CYN "$N��$n" CYN "˵��������Ҫ�ϳɽ�ɫװ�������ȸ�����һ�����ƽ�Ȼ������²���׼���ø��ҡ�\n"
                "       1����Ҫ�ϳɵķ�ɫװ�� 1 ��\n"
                "       2����ˮ���򳬼���ˮ�� 2 ��\n" NOR, ob, me);
        set_temp("upgrade/money", 100000000, me);
        set_temp("upgrade/do", "gold", me);
        return 1;
}

int ask_green()
{
        object me = this_player();
        object ob = this_object();

        message_vision(CYN "$N��$n" CYN "˵�����ϳ���װ(��װ)����ĵ�������
       1��1������ȼ�Ϊ30 �����ϣ�����30�����Ľ�װ��
       2��1����ˮ��
       3��5 ���ɫ���ֵ��������ϣ�����ʯ)
�����׼�����˵��ߣ��Ƚ�����1�����ƽ�\n" NOR, ob, me);
        set_temp("upgrade/money", 100000000, me);
        set_temp("upgrade/do", "green", me);
        return 1;
}

int ask_steady()
{
        object me = this_player();
        object ob = this_object();

        message_vision(CYN "$N��$n" CYN "˵����ǿ������ĵ�������
       1��1������ȼ�Ϊ30 �����ϣ�����30��������װ������װ������װ������װ����
       2��1��ʥˮ��
       3��1����ȡ�˸������Եĺ�ˮ����������ˮ����
       4��4 ���ɫ���ֵ��������ϣ�����ʯ)
�����׼�����˵��ߣ��Ƚ�����1�����ƽ�\n" NOR, ob, me);
        set_temp("upgrade/money", 100000000, me);
        set_temp("upgrade/do", "steady", me);
        return 1;
}

int check_legal_name(string name, int max_len)
{
        int i;

        i = strlen(name);
        if ((strlen(name) < 2) || (strlen(name) > max_len ))
        {
                write(sprintf("�Բ��������ֱ����� 1 �� %d �������֡�\n",
                      max_len / 2));
                return 0;
        }

        if (max_len < 9 && ! is_chinese(name))
        {
                write("�Բ��������á����ġ�Ϊ��װȡ���֡�\n");
                return 0;
        }
        return 1;
}


void get_modname(string arg, object me, object ob)
{
        string arg_old;

        if( arg == "q" || arg == "Q" ) {
                write("��ȡ�����̻�װ������װ��ȡ�ء�\n");
                ob->move(me, 1);
                return;
        }
        arg_old = arg;
        arg = trans_color(arg, 3);
        arg = filter_color(arg, 1);

        if (! check_legal_name(arg, 8))
        {
                write("�������̻�װ�������׺����(��Ҫ����4���֣��ɼ���ɫ)��\n");
                input_to( (: get_modname :), me, ob);
                return;
        }

        arg = arg_old;
        arg = trans_color(arg, 3);
        arg = HIG "��" NOR+arg+NOR+HIG "��" NOR;
        set_temp("upgrade/modname", arg, me);

        do_combine(me, ob);
        return;
}

int accept_object(object me, object ob)
{
        string *obj, str;
        mapping nds, data;
        int i;

        if( query_temp("upgrade/making") ) {
                message_vision("$N��$n˵����������æ���أ����Ե�һ�ᣡ\n",
                               this_object(), me);
                return 0;
        }

        if( query("money_id", ob)){
                if( !query_temp("upgrade/money", me)){
                        message_vision("$N��$n�ݹ�ȥ��" + ob->name() +
                                       "���˻����������޹�����»��\n",
                                       this_object(), me);
                        return 0;
                }

                if( ob->value()<query_temp("upgrade/money", me)){
                        message_vision("$N��$n˵���Բ����Ϸ���һ"
                                       "ǧ����������û�д���ۿۡ�\n",
                                       this_object(), me);
                        return 0;
                }
                if( query_temp("upgrade/do", me) == "steady" )
                        message_vision("$N��$n˵�����ã�����Ͱ����Ҫǿ����װ�����ҿ���(show)�ȡ�\n",
                                this_object(), me);
                else
                        message_vision("$N��$n˵�����ã�����Ͱ����Ҫ�ϳɵ�װ�����ҿ���(show)�ȡ�\n",
                                this_object(), me);

                set_temp("paid/ŷұ��", 1, me);
                destruct(ob);
                return -1;
        }

        if( !mapp(nds=query_temp("upgrade/needs", me)) && !query_temp("upgrade/prepare", me)){
                message_vision("$N��$n˵������������ʲô����\n",
                               this_object(), me);
                return 0;
        }

        if( query("material_file", ob) && base_name(ob) == query_temp("upgrade/file", me)){
                if( query_temp("upgrade/prepare", me)){
                        if( query_temp("upgrade/do", me) == "green"){
                                write("�������̻�װ�������׺����(��Ҫ����4���֣��ɼ���ɫ)��\n");
                                input_to( (: get_modname :), me, ob);
                        }
                        else
                                do_combine(me, ob);
                        return 1;
                } else {
                        message_vision("$N��$n˵������������ʲô����\n",
                                              this_object(), me);
                        return 0;
                }
        }

        if( !mapp(nds) ) return 0;

        obj = keys(nds);
        for( i = 0; i < sizeof(obj); i++ ) {
                if( ob->query_name() == obj[i]->query_name() ) {
                        if( ob->query_name() == "��ˮ" ) {
                                if( query_temp("upgrade/level", me) && 
                                    query("enchase/level", ob) != query_temp("upgrade/level", me)){
                                        message_vision("$N��$n˵��" + ob->name() + "�ĵȼ���Ҫ�󲻷���\n",
                                                this_object(), me);
                                        return 0;
                                }
                                if( query_temp("upgrade/type", me) && 
                                    query("enchase/type", ob) != query_temp("upgrade/type", me)){
                                        message_vision("$N��$n˵��" + ob->name() + "�����ͺ�Ҫ�󲻷���\n",
                                                this_object(), me);
                                        return 0;
                                }
                                str=keys(query("enchase/apply_prop", ob))[0];
                                if( query_temp("upgrade/do", me) == "steady"){
                                        if( !query_temp("upgrade/steady_prop/"+str, me)){
                                                message_vision("$N��$n˵��" + ob->name() + "����ȡ�����Ժ�����ǿ����װ��ԭʼ���Բ�һ�£���������ǿ����\n",
                                                        this_object(), me);
                                                return 0;
                                        }
                                        set_temp("upgrade/apply_prop/"+str,query("enchase/apply_prop/"+str,  ob), me);
                                } else {
                                        if( query_temp("upgrade/apply_prop/"+str, me)){
                                                message_vision("$N��$n˵��" + ob->name() + "����ȡ�����Բ����ظ������ϳɣ�\n",
                                                        this_object(), me);
                                                return 0;
                                        }
                                        set_temp("upgrade/apply_prop/"+str,query("enchase/apply_prop/"+str,  ob), me);
                                }
                        }
                        nds[obj[i]] = nds[obj[i]] - 1;
                        if( nds[obj[i]] < 1 ) {
                                map_delete(nds, obj[i]);
                        }
                        destruct(ob);
                        set_temp("upgrade/needs", nds, me);

                        if( !mapp(nds=query_temp("upgrade/needs", me)) || sizeof(keys(nds))<1){
                                set_temp("upgrade/prepare", 1, me);
                                delete_temp("upgrade/needs", me);
                                tell_object(me, HIR "\n�ϳ�װ������Ʒ���ˣ����ڰ����Ҫ�ϳɵ�װ�����Ұɣ�\n" NOR);
                                return -1;
                        }

                        tell_object(me, HIR "\n������������û���ˣ���\n" NOR);
                        return -1;
                } else {
                        message_vision("$N��$n˵������������ʲô������Ҫ���ҵĲ��ϲ��������\n",
                                   this_object(), me);
                        return 0;
                }
        }
}

int do_combine(object me, object ob)
{
        mapping data, temp, prop, prop2;
        int rate, level, value;
        string combine_to, type, str;

        set_temp("upgrade/making", ob);
        set_temp("upgrade/player_id",query("id", me));

        message_vision(HIM "$N�ó����Ƶ�ħ������" + ob->name() + HIM "�ͺϳɲ��Ϸ��˽�ȥ��\n"
                       "����$N���������˳��ħ����ת����ʱ��ֻ��ħ������һ������Ĺ�â��\n"
                       "һ"+query("unit", ob)+"ո�µ�"+ob->name()+HIM"�����������ǰ��\n\n"NOR,
                       this_object(), me);

        temp = ([]);
        level=query("require/level", ob);
        temp["level"] = level;
        rate = random(100);
        if( rate < 40 ) temp["str"] = level + random(level);
        else if( rate < 60 ) temp["con"] = level + random(level);
        else if( rate < 80 ) temp["dex"] = level + random(level);
        else temp["int"] = level + random(level);

        if( ob->is_weapon() || ob->is_unarmed_weapon() ) type = "weapon";
        else type=query("armor_type", ob);
        prop = EQUIPMENT_D->apply_props(type, level, 2);
        prop2 = EQUIPMENT_D->apply_props("ultimate", level, 1);
        if( type == "weapon" ) {
                map_delete(prop, "damage");
        } else {
                map_delete(prop, "armor");
        }

        combine_to=query("combine_to", ob);
        if( query_temp("upgrade/do", me) == "steady"){
                str=keys(query_temp("upgrade/apply_prop", me))[0];
                value = random(EQUIPMENT_D->query_prop_value(str, level))+1;
                set("enchase/apply_prop/"+str, value, ob);
                addn("enchase/steady", 1, ob);
        }
        else if( combine_to == "blue" ) {
                data=copy(query_temp("upgrade/apply_prop", me));
                set("enchase/apply_prop", data, ob);
                set("enchase/flute", 3, ob);
                set("enchase/used", 3, ob);
                ob->set_color("$HIB$");
                set("combine_to", "pink", ob);
                set("require", temp, ob);
                set("makeinfo", HIR"\n"+me->query_idname()+HIR"��Ʒ\n"NOR, ob);
        }
        else if( combine_to == "pink" ) {
                set("enchase/pink_prop", prop, ob);
                addn("enchase/flute", 1, ob);
                addn("enchase/used", 1, ob);
                ob->set_color("$HIM$");
                set("combine_to", "gold", ob);
                set("require", temp, ob);
                set("makeinfo", HIR"\n"+me->query_idname()+HIR"��Ʒ\n"NOR, ob);
        }
        else if( combine_to == "gold" ) {
                ob->set_color("$HIY$");
                set("combine_to", "green", ob);
                set("makeinfo", HIR"\n"+me->query_idname()+HIR"��Ʒ\n"NOR, ob);
        }
        else if( combine_to == "green" ) {
                set("enchase/green_prop", prop, ob);
                set("enchase/mod_prop", prop2, ob);
                set("modname",query_temp("upgrade/modname",  me), ob);
                set("mod", "itemmake", ob);
                ob->set_color("$HIG$");
                set("combine_to", "ultimate", ob);
                set("makeinfo", HIR"\n"+me->query_idname()+HIR"��Ʒ\n"NOR, ob);
        }

        ob->save();

        remove_call_out("do_finish");
        call_out("do_finish", 1, me, ob);
        return 1;
}

int do_finish(object me, object ob)
{
        if( !objectp(me) )
                me = find_player(query_temp("upgrade/player_id"));

        if( !objectp(me) || environment(me) != environment() ) {
                message_vision(HIW "$N̾�˿�����˵��������Ϊ�����ȥ"
                               "�ˣ������˰��ˣ������ˣ�ȥ�ɣ�\n"
                               "$N��"+ob->name()+"�׽���¯���ʹ˲�����\n\n" NOR,
                               this_object());
                if( objectp(me) )
                        delete_temp("upgrade", me);

                if( objectp(ob) && present(ob, this_object()) )
                        destruct(ob);

                delete_temp("upgrade");
                return 1;
        }
        ob->move(me, 1);
        message_vision("$N��"+query("name", ob)+"��������$n��\n",
                       this_object(), me);
        delete_temp("upgrade", me);
        delete_temp("upgrade");
        return 1;
}

int do_show(string arg)
{
        object money;
        object ob, item;
        object me;
        string *obs;
        string str, type;
        mapping data;
        int level, i;

        if( query_temp("upgrade/making") )
                return notify_fail("������æ���أ����Ե�һ�ᣡ\n");

        if( !arg )
                return notify_fail("��Ҫ����ʲô������\n");

        me = this_player();
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("������û�����ֶ�����\n");

        if( query("equipped", ob) )
                return notify_fail("���Ƚ��" + ob->name() + "��װ����˵��\n");

        if( query_temp("upgrade/file", me) )
                return notify_fail("���Ȱ������ڽ��еĺϳ�/ǿ��/�����깤����˵��\n");

        message_vision("$n�ó�һ"+query("unit", ob)+ob->name()+
                       "��$N˵�������а���...��\n",
                       this_object(), me);

        if( !wizardp(me) && !query_temp("paid/ŷұ��",1, me)){
                command("say �����������Ұ����ʲô�أ�");
                /*command("heihei");
                set_temp("upgrade/money", 100000000, me);
                command("say ��...��ôҲ���е���˼��˼�ɣ���"
                        "˵һ�����ƽ���ô������Ȼ��Щ��Ҳ�����ԡ�");*/
                return 1;
        }

        if( !query("material_file", ob)){
                command("heng");
                command("say ��...��...�ҿ��������˰ɣ�");
                return 1;
        }

        /*if( ob->item_owner() != query("id", me)){
                command("kick"+query("id", me));
                command("say ����Ϊ�ҵ����������µİ��������������ģ�");
                return 1;
        }*/
        if( query_temp("upgrade/do", me) == "steady"){
                data = copy(upgrade_material["steady"]);
                level=query("require/level", ob);

                if( query("skill_type", ob) )
                        type=query("skill_type", ob);
                else
                        type=query("armor_type", ob);

                set_temp("upgrade/type", type, me);
                set_temp("upgrade/level", level, me);
                set_temp("upgrade/steady_prop", copy(query("enchase/apply_prop", ob)), me);
        } else {
                data=copy(query("combine_to", upgrade_material[ob)]);
                if( !mapp(data) ) return notify_fail("���װ���Ѿ�����Ҫ�ٺϳ��ˡ�\n");

                if( query("combine_to", ob) == "blue"){
                        level=query("require/level", ob);

                        if( query("skill_type", ob) )
                                type=query("skill_type", ob);
                        else
                                type=query("armor_type", ob);

                        set_temp("upgrade/type", type, me);
                        set_temp("upgrade/level", level, me);
                }
        }
        set_temp("upgrade/file", base_name(ob), me);
        set_temp("upgrade/needs", data, me);
        obs = keys(data);

        if( query_temp("upgrade/do", me) == "steady" )
                str = "\n���" + ob->short() + HIG + "�˴�ǿ����Ҫ����Ʒ���£�\n\n";
        else
                str = "\n���" + ob->short() + HIG + "�˴κϳ���Ҫ����Ʒ���£�\n\n";
        for( i=0; i<sizeof(obs); i++ ) {
                item = new(obs[i]);
                str += sprintf("%-40s ��\t%d %s\n",
                               item->short(),
                               data[obs[i]],
                               query("unit", item));
                destruct(item);
        }
        str += "\n";
        tell_object(me, HIG + str + NOR);
        tell_object(me, "��ǧ��Ҫ�Ǻ��ҽ����ҵĵ���Ʒ������.....\n");
        tell_object(me, "���" + ob->short() + "�������Ʒ���룬�������Ұɣ�\n");
        delete_temp("paid/ŷұ��", me);
        return 1;
}

void kill_ob(object ob)
{
        ::kill_ob(ob);
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