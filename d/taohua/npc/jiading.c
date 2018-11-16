//Cracked by Kafei
//ָ��yapu_npc�ļҶ�
//maco

inherit NPC;
#include <ansi.h>
string ask_yapu();

void create()
{
        set_name("�Ҷ�", ({ "jia ding", "ding" }));
        set("long", "һ����ʮ��ͷ��С���ӣ�����ʵ��˫Ŀ�����ƺ��������깦��\n");
        set("gender", "����");
        set("age", 25);

        set_skill("unarmed", 30);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set_skill("stick", 30);
        set_skill("staff", 30);
        set_skill("sword", 30);
        set_skill("blade", 30);
        set("combat_exp", 10000);
        set("shen_type", 1);
        set("inquiry", ([
                "����" : (:ask_yapu:),
                "yapu" : (:ask_yapu:),
        ]));
        create_family("�һ���", 4, "�Ҷ�");
        delete("title");
        setup();
}

int start_check(object me)
{
                call_out("leave", 1200, me);
                call_out("check", 1, me);
}

void init()
{
        ::init();

        add_action("do_recognize", "ren");
        add_action("do_recognize", "recognize");
        add_action("do_bring", "bring");
        add_action("do_bring", "dai");
        add_action("do_order", "order");

}
void leave(object me)
{
        string killer=query_temp("my_killer", me);
        object jiading = this_object();

        if (query("recognized") && objectp(present(me, environment(jiading)))) {
        command("addoil"+query("job_master", jiading));
        call_out("leave", 60, me);
        }

        else if(objectp(present(me, environment(jiading)))){
        message_vision(CYN"$N˵��������û�׽������"+query("find_yapu_real")+"װ�ɵ�"+query("find_yapu")+"���ҿ������Ǵ��������ˣ������Ȼع���ׯ�ɡ�\n"NOR,jiading);
        command("sigh");
        message_vision("$N�첽�뿪�ˡ�\n"NOR,jiading);
        destruct(jiading);
        }

        else {
        message_vision("$N�첽�뿪�ˡ�\n"NOR,jiading);
        destruct(jiading);
        }

        return;
}

void check(object me)
{
        string killer=query_temp("my_killer", me);
        object jiading = this_object();

        if( !query("find_yapu", me) )
        {
        command("bye"+query("id", me));
        message_vision("$N�첽�뿪�ˡ�\n"NOR,jiading);
        destruct(jiading);
        }

        else if(me->is_ghost() )
        {
        command("ah");
        command("cry corpse");
        command("grpfight"+query_temp("my_killer", me));
        command("kill"+query_temp("my_killer", me));
        }
        else call_out("check", 1, me);
}

int do_recognize(string arg)
{
        object me, ob, jiading, where, weapon, huwei;
        mapping skill_status;
        string *sname;
        int i ,num, level = 0, s_level, j, gain, exp, ob_exp, rate;

        me = this_player();
        exp=query("combat_exp", me);

        jiading = this_object();
        if( query("job_master") != query("id", me) )
                return 0;
        if( query("recognized"))
                return notify_fail("�Ҷ��Ѿ�ָ�ϳ����Է��ˣ�\n");
        if( !living(jiading) )
                return notify_fail("��....����ȰѼҶ�Ū����˵��\n");
        if( !arg )
                return notify_fail("��Ҫ�Ҷ�ָ��˭��\n");
        if(!objectp(ob = present(arg, environment(this_player()))))
                return notify_fail("����û������ˡ�\n");
        if( query("th_victim", ob) )
                return notify_fail(ob->name()+"�Ѿ���ָ�ϳ����ˣ�\n");
        if(ob == me)
                return notify_fail("ָ�����Լ�����������\n");
        if(ob == jiading)
                return notify_fail("Ҫ�Ҷ�ָ�ϼҶ���\n");
        if( query("family/family_name", ob) == "�һ���" )
                return notify_fail("�����һ���������Ҳ�ϲ�������\n");
        if( me->is_busy() || me->is_fighting() )
                return notify_fail("����æ���ء�\n");
        if( jiading->is_busy() || jiading->is_fighting() )
                return notify_fail( "�Ҷ���æ���ء�\n");
        if( query("no_fight", environment(me)) )
                return notify_fail("���ﲻ��ս�����ϳ���Ҳû�á�\n");


        me->start_busy(1);

        message_vision("$N�����ڼҶ�����˵�����ǲ������"+ob->name()+"��\n",me,ob);
        where = environment(ob);

        if( query("yapu_target", ob) == query("id", me )
         && query("name", ob) == query("find_yapu") )
        {
        if( !living(ob) )
        ob->revive();
        command("ah");
        command("points"+query("id", ob));
        ob->interrupt_me();
        set("real_face", 1, ob);
        set("recognized",1);

        //yapu_npc����ָĻ�
        {
        set("long",query("real_long",  ob), ob);
        if( query("real_title", ob) )
        set("title",query("real_title",  ob), ob);
        ob->clear_condition();
        set("shen_type", -1, ob);
        
        if ( mapp(skill_status = me->query_skills()) ) {
                skill_status = me->query_skills();
                sname = keys(skill_status);

                for(i=0; i<sizeof(skill_status); i++) {
                        if ( skill_status[sname[i]] > level ) level = skill_status[sname[i]];
                }
                
                level = (int)level*4/5 + 1;
                s_level = (int)level*21/20;

                rate = random(3)+9;

                set("combat_exp", exp*rate/10+random(exp/100), ob);
                ob_exp=query("combat_exp", ob);

                set("th_victim",query("id",  me), ob);
                //��npc��reward
                
                set("gain", 50+level, ob);
                gain=query("gain", ob);
                if(gain>300) gain=300;

                if(exp <  100000) //100k
                        gain = gain + random(level/2);
                else if(exp <  500000) //500k
                        gain = gain + random(level/3);
                else if(exp < 1000000) //1m
                        gain = gain + random(level/4);
                else if(exp < 3000000) //3m
                        gain = gain + random(level/5);
                else gain = gain + random(level/8);

                set("gain_exp", gain, ob);
                set("gain_pot", gain/4+random(gain/10), ob);
                set("shen", -ob_exp/10, ob);
                
                if(ob_exp < 1000000) {
                addn("gain_exp", random(5)+10, ob);
                addn("gain_pot", random(5)+1, ob);
                }
                else if(ob_exp < 2000000) {
                addn("gain_exp", random(5)+15, ob);
                addn("gain_pot", random(5)+5, ob);
                }
                else if(ob_exp < 3000000) {
                addn("gain_exp", random(5)+20, ob);
                addn("gain_pot", random(5)+10, ob);
                }
                else {
                addn("gain_exp", random(5)+25, ob);
                addn("gain_pot", random(5)+15, ob);
                }


                set("max_qi",query("max_qi",  me)*9/10, ob);
                set("eff_qi",query("max_qi",  me)*9/10, ob);
                set("max_jing",query("max_jing",  me)*9/10, ob);
                set("eff_jing",query("max_jing",  me)*9/10, ob);
                set("qi",query("max_qi",  ob), ob);
                set("jing",query("max_jing",  ob)*9/10, ob);
                set("jiali",query("jiali",  me)/2, ob);
                if( query("max_neili", me)>0){
                        set("max_neili", level*30, ob);
                        if( query("max_neili", ob)>query("max_neili", me) )
                                set("max_neili",query("max_neili",  me)+level, ob);
                }
                else set("max_neili", 500, ob);
                
                if( query("max_jingli", me)>0){
                        set("max_jingli",query("max_jingli",  me)*9/10, ob);
                }
                else set("max_jingli", 500, ob);
                set("neili",query("max_neili",  ob), ob);
                set("jingli",query("max_jingli",  ob), ob);
                set("no_sing", 1, ob);
                ob->set_skill("dodge", level);
                ob->set_skill("parry", level );
                ob->set_skill("force", level);
                
        switch(query("real_menpai", ob)){
        case "huashan" :
        ob->set_name("���", ({"da dao", "dao" ,"robber"}) );
        ob->set_skill("blade", s_level);
        ob->set_skill("sword", s_level);
        ob->set_skill("cuff", s_level);
        ob->set_skill("strike", s_level);
        ob->set_skill("huashan-jianfa", level);
        ob->set_skill("liangyi-dao", level);
        ob->set_skill("ding-dodge", s_level);
        ob->set_skill("zixia-gong", level);
        ob->set_skill("pishi-poyu", level);
        ob->set_skill("hunyuan-zhang", level);
        ob->set_skill("ziyin-yin", level);
        ob->set_skill("zhengqi-jue", level);

        ob->map_skill("force", "zixia-gong");
        ob->map_skill("dodge", "ding-dodge");
        ob->map_skill("parry", "huashan-jianfa");
        ob->map_skill("strike", "hunyuan-zhang");
        ob->map_skill("cuff", "pishi-poyu");
        ob->map_skill("sword", "huashan-jianfa");
        ob->map_skill("blade", "liangyi-dao");
        ob->prepare_skill("cuff", "pishi-poyu");
        ob->prepare_skill("strike", "hunyuan-zhang");
        set("real_message", HIR"С����ɫһ�䣬�ȵ���"+RANK_D->query_rude(me)+"ԭ���ǻ���а���£���׽"+RANK_D->query_self_rude(ob)+"����û�������ף�\n"NOR, ob);
        addn("gain_exp", random(10)+30, ob);
        addn("gain_pot", random(5)+20, ob);
        ob->add_money("silver", 20+random(31));
        if(random(3) == 1)  weapon=new("/clone/weapon/gangdao");
        else if(random(3) == 1) weapon=new("/clone/weapon/changjian");
        
                break;
                
        case "dajin" :
        ob->set_name("ɱ��", ({"shashou", "shou", "killer"}) );
        ob->set_skill("sword", s_level);
        ob->set_skill("cuff", s_level);
        ob->set_skill("taiji-shengong", s_level);
        ob->set_skill("taiji-jian", s_level);
        ob->set_skill("tiyunzong", level);
        ob->set_skill("taiji-quan", s_level);
        ob->set_skill("taoism", level);
        ob->set_skill("literate", level);
        ob->map_skill("force", "taiji-shengong");
        ob->map_skill("parry", "taiji-jian");
        ob->map_skill("cuff", "taiji-quan");
        ob->map_skill("dodge", "tiyunzong");
        ob->map_skill("sword", "taiji-jian");
        ob->prepare_skill("cuff", "taiji-quan");
        set("real_message", HIR"������Цһ��������"+RANK_D->query_rude(me)+"���ص�ǰ��������\n"NOR, ob);
        set("jiali", 0, ob);
        set("str", 27+random(4), ob);
        ob->carry_object("/clone/anqi/feibiao")->set_amount(2+random(3));
        if(random(3) != 0) weapon=new("/clone/weapon/changjian");
                break;
                
        case "tiezhang" :
        ob->set_name("���", ({"e ba", "ba"}) );
        ob->set_skill("strike", s_level+20);
        ob->set_skill("blade", s_level);
        ob->set_skill("taixuan-gong", level);
        ob->set_skill("tie-zhang", s_level+20);
        ob->set_skill("ding-dodge", s_level);
        ob->set_skill("wuhu-duanmen", s_level);
        ob->map_skill("blade","wuhu-duanmen");
        ob->map_skill("dodge","ding-dodge");
        ob->map_skill("strike","tie-zhang");
        ob->map_skill("force", "taixuan-gong");
        ob->map_skill("parry", "tie-zhang");
        ob->prepare_skill("strike", "tie-zhang");
        addn("gain_exp", -20, ob);
        addn("gain_pot", -20, ob);
        set("real_message", HIR"�����ֳ���һ�������϶���ɱ������$N���˹�����\n"NOR, ob);
                break;
                
        case "shaolin" :
        ob->set_name("�ƽ�ɮ", ({"pojie seng", "seng"}) );
        ob->set_skill("blade", s_level);
        ob->set_skill("sword", s_level);
        ob->set_skill("club", s_level);

        ob->set_skill("buddhism", level);
        ob->set_skill("damo-jian", s_level);
        ob->set_skill("xiuluo-dao", s_level);
        ob->set_skill("zui-gun", s_level);
        ob->set_skill("jingang-quan", s_level);
        ob->set_skill("shaolin-shenfa", level);
        ob->set_skill("hunyuan-yiqi", level);
        ob->set_skill("yizhi-chan", level);
        ob->set_skill("banruo-zhang", level);
        ob->map_skill("force", "hunyuan-yiqi");
        ob->map_skill("dodge", "shaolin-shenfa");
        ob->map_skill("parry", "damo-jian");
        ob->map_skill("cuff","jingang-quan");
        ob->map_skill("sword", "damo-jian");
        ob->map_skill("blade", "xiuluo-dao");
        ob->map_skill("club", "zui-gun");
        set("real_message", HIR"ɮ����ɫһ�䣬��Ц�������ۣ����Ȼ�ϳ���"+RANK_D->query_self_rude(ob)+"���������㲻�ã�\n"NOR, ob);
                switch (random(3)) {
                case 0 :
                        ob->set_skill("finger", s_level);
                        ob->set_skill("yizhi-chan", s_level);
                        ob->set_skill("strike", s_level);
                        ob->set_skill("banruo-zhang", s_level);
                        ob->map_skill("finger","yizhi-chan");
                        ob->map_skill("strike","banruo-zhang");
                        ob->prepare_skill("finger","yizhi-chan");
                        ob->prepare_skill("strike","banruo-zhang");
                        if(random(3) == 0) weapon=new("/d/shaolin/npc/obj/jiedao");
                        break;
                case 1 :
                        ob->set_skill("cuff", s_level);
                        ob->set_skill("jingang-quan", s_level);
                        ob->map_skill("cuff","jingang-quan");
                        ob->prepare_skill("cuff","jingang-quan");
                        if(random(3) == 0) {
                        ob->apply_condition("drunk",query("con", ob)+query("max_neili", ob)/100+3);
                        weapon=new("/d/shaolin/npc/obj/qimeigun");
                                }
                        break;
                case 2 :
                        ob->set_skill("claw", s_level);
                        ob->set_skill("longzhua-gong", s_level);
                        ob->map_skill("claw","longzhua-gong");
                        ob->prepare_skill("claw","longzhua-gong");
                        break;
                }
                break;
                
        case "xiyu" :
        ob->set_name("�ɹ��佫", ({"menggu wujiang", "wujiang", "jiang"}) );
        set("class", "officer", ob);
        set("dali/rank", 3, ob);
        set("rank_info/rude", "������", ob);
        ob->set_skill("hamagong", s_level+10);
        ob->set_skill("lingshe-zhang", s_level);
        ob->set_skill("wuxingbu", s_level);
        ob->set_skill("luan-blade", s_level);
        ob->set_skill("blade", s_level);
        ob->set_skill("strike", s_level);
        ob->set_skill("parry", s_level);
        ob->set_skill("shentuo-zhang", s_level);
        ob->set_skill("lingshe-quan", s_level);

        ob->map_skill("force", "hamagong");
        ob->map_skill("blade", "luan-blade");
        ob->map_skill("dodge", "wuxingbu");
        ob->map_skill("parry", "luan-blade");
        
        set("real_message", "", ob);
        message_vision(HIR"����˫��һ�⣬��Ц������ƾ����"+RANK_D->query_rude(me)+"��Ҳ���"+RANK_D->query_self_rude(ob)+"���ԣ�\n"NOR, me, ob);

        {
        num = 1+random(3);
        message_vision(HIR"�����������֣�����ͻȻԾ��"+chinese_number(num)+"�����׻�����"+chinese_number(num+1)+"����$N���Ұ�����\n"NOR, me, ob);
                    for (i=0; i<num; i++) {
                huwei = new("/d/taohua/npc/mg_huwei");
                set("combat_exp", exp/2+random(exp/1000), huwei);
                set("rank_info/rude", "������", huwei);
                set("max_qi",query("max_qi",  ob)/2, huwei);
                set("eff_qi",query("max_qi",  ob)/2, huwei);
                set("max_jing",query("max_jing",  ob)/2, huwei);
                set("eff_jing",query("max_jing",  ob)/2, huwei);
                set("qi",query("max_qi",  huwei), huwei);
                set("jing",query("max_jing",  huwei), huwei);
                set("jiali",query("jiali",  ob)/2, huwei);
                set("max_neili",query("max_neili",  ob)/2, huwei);
                set("max_jingli",query("max_jingli",  ob)/2, huwei);
                set("neili",query("max_neili",  huwei), huwei);
                set("jingli",query("max_jingli",  huwei), huwei);

                huwei->set_skill("ding-force", level*3/4);
                huwei->set_skill("san-sword", level*3/4);
                huwei->set_skill("ding-dodge", level*3/4);
                huwei->set_skill("luan-blade", level*3/4);
                huwei->set_skill("wrestling", level*3/4);
                huwei->set_skill("hand", level*3/4);
                huwei->set_skill("force", level*3/4);
                huwei->set_skill("parry", level*3/4);
                huwei->set_skill("dodge", level*3/4);
                huwei->set_skill("sword", level*3/4);

                huwei->map_skill("force", "ding-force");
                huwei->map_skill("sword", "san-sword");
                huwei->map_skill("dodge", "ding-dodge");
                huwei->map_skill("parry", "san-sword");
                huwei->map_skill("hand", "wrestling");
                huwei->prepare_skill("hand", "wrestling");

                huwei->move(environment(me));
                
                huwei->kill_ob(me);
                huwei->start_check(ob);
                huwei->set_leader(ob);
                me->fight_ob(huwei);
                addn("gain_exp", random(10)+20, ob);
                addn("gain_pot", random(5)+5, ob);
                }
        }
        ob->add_money("silver", 20+random(31));
        if( query_temp("armor/cloth", ob) )
        destruct(query_temp("armor/cloth", ob));
        ob->carry_object("/clone/armor/tiejia")->wear();
        if(random(3) == 0) weapon=new("/clone/weapon/gangdao");
        if( random(query("combat_exp", me))>2000000){
        ob->map_skill("strike", "hamagong");
        ob->prepare_skill("strike", "hamagong");
        addn("gain_exp", random(10)+40, ob);
        addn("gain_pot", random(5)+10, ob);
        }
        else {
        ob->map_skill("cuff","lingshe-quan");
        ob->map_skill("strike","shentuo-zhang");
        ob->prepare_skill("cuff","lingshe-quan");
        ob->prepare_skill("strike","shentuo-zhang");
        }

                break;
                
        case "mizong" :
        ob->set_name("��������", ({"hufa lama", "hufa", "lama"}) );
        set("class", "lama", ob);
        ob->set_skill("longxiang-banruo", level);
        ob->set_skill("shenkongxing", level);
        ob->set_skill("huoyan-dao", s_level);
        ob->set_skill("yujiamu-quan", level);
        ob->set_skill("dashou-yin", s_level);
        ob->set_skill("lamaism", level);
        ob->set_skill("xue-dao", s_level);
        ob->set_skill("mingwang-jian", s_level);
        ob->set_skill("jingang-chu", level);
        ob->set_skill("staff", level);
        ob->set_skill("sword", s_level);
        ob->set_skill("blade", s_level);
        ob->set_skill("cuff", s_level);
        ob->set_skill("hand", s_level);
        ob->set_skill("strike", s_level);
        ob->map_skill("force", "longxiang-banruo");
        ob->map_skill("dodge", "shenkongxing");
        ob->map_skill("parry", "xue-dao");
        ob->map_skill("blade", "xue-dao");
        ob->map_skill("sword", "mingwang-jian");
        ob->map_skill("staff", "jingang-chu");
        set("real_message", HIR"���$NĿ�����������Ϻ�Ȼ��������ɲ����е���"+RANK_D->query_rude(me)+"���һ������ģ�\n"NOR, ob);
        
        if( query_temp("armor/cloth", ob) )
        destruct(query_temp("armor/cloth", ob));
        
        ob->carry_object("/d/qilian/obj/lamajiasha")->wear();
        if(random(6) == 0) weapon=new("/clone/weapon/changjian");
        else if(random(5) == 1)        weapon=new("/d/xueshan/obj/miandao");
        else if(random(4) == 2) weapon=new("/d/xueshan/obj/fachu");

        if( random(query("combat_exp", me))>2000000){
        ob->map_skill("strike", "huoyan-dao");
        ob->prepare_skill("strike", "huoyan-dao");
        addn("gain_exp", random(20)+50, ob);
        addn("gain_pot", random(10)+20, ob);
        }
        else {
        ob->map_skill("hand", "dashou-yin");
        ob->map_skill("cuff", "yujiamu-quan");
        ob->prepare_skill("hand", "dashou-yin");
        ob->prepare_skill("cuff", "yujiamu-quan");
        }
                break;
        case "miaojiang" :
        ob->set_name("�置��Ů", ({"miaojiang wunu", "wunu", "nu"}) );
        ob->set_skill("claw", s_level);
        ob->set_skill("strike", s_level);
        ob->set_skill("huagong-dafa", level);
        ob->set_skill("zhaixinggong", level);
        ob->set_skill("chousui-zhang", s_level);
        ob->set_skill("sanyin-zhua", s_level);
        ob->set_skill("feixing-shu", s_level);
        ob->set_skill("poison", level);
        ob->set_skill("dodge", s_level);

        ob->map_skill("force", "huagong-dafa");
        ob->map_skill("strike", "chousui-zhang");
        ob->map_skill("claw", "sanyin-zhua");
        ob->map_skill("dodge", "zhaixinggong");
        ob->map_skill("parry", "sanyin-zhua");
        ob->prepare_skill("strike", "chousui-zhang");
        ob->prepare_skill("claw", "sanyin-zhua");

        set("real_message", "", ob);
        message_vision(HIR"Ů������һת��΢Ц������λ"+RANK_D->query_respect(me)+"����ò���Ҫ׽�Ұɣ��ǡ����ҿ�Ҫ�������ӡ�\n"NOR, me);
        
        ob->carry_object("/clone/drug/xxqingxin-san");
        ob->carry_object("/d/xingxiu/obj/lianxin");
        ob->carry_object("/d/xingxiu/obj/blzhen")->set_amount(1+random(3));

        if( query_temp("armor/cloth", ob) )
        destruct(query_temp("armor/cloth", ob));
        ob->carry_object("/d/city/obj/jin_ao")->wear();
        //has poison,add reward
        addn("gain_exp", random(10)+30, ob);
        addn("gain_pot", random(5)+10, ob);

        if( random(query("combat_exp", me))>2000000 && ob->query_skill("strike")>250 && query("neili", ob)>1000 && random(2) == 1){
        message_vision("$N����ѷŵ��ڱߣ�����һ����ֻ��һ�󼫼⼫ϸ��������ԶԶ���˳�ȥ��\n", ob);
        message_vision(HIR"�����������������ͻȻ�ɳ���ӡӡ��һ����ǣ����Ƕ���Ϩ���漴���������һ���죬�����գ�������������Ż������䡣\n"NOR, me);
        new("/d/xingxiu/obj/flute_fire")->move(environment(me));
        addn("gain_exp", random(20)+50, ob);
        addn("gain_pot", random(10)+30, ob);
        }

                break;

        }
                if(weapon != 0) {
                weapon->move(ob);
                weapon->wield();
                }
                //�趨���
                message_vision(""+query("real_message", ob)+"",me,ob);
                ob->kill_ob(me);
                me->fight_ob(ob);

        }

        }
        //�Ļ����
        }
        else if( query("name", ob) == query("find_yapu") )
        {
        command("shake");
        command("say ����࣬�������ǡ�");
        }

        else if( query("race", ob) != "����" )
        {
        command("consider");
        command("say ������"+query("find_yapu_real")+"�����ˣ����޲��磬�ô�Ҳ���Ǹ����ġ�����");
        }

        else if( query("gender", ob) == "Ů��" && query("per", ob) >= 30 && query("age", ob)<30 )
        {
        message_vision("�Ҷ������ؿ���$n����\n",me,ob);
        command("shake");
        command("say ��λ"+ RANK_D->query_respect(me) +"����һ��������������Ǹ�"+query("find_yapu_real")+"��");
        }
        else if( query("gender", ob) == "����" && query("per", ob) >= 30 )
        {
        command("shake");
        command("say ��λ"+ RANK_D->query_respect(me) +"�Ǳ����ã�������"+query("find_yapu_real")+"���Ա��⣿");
        }
        else
        {
        command("shake");
        command("say ���ǲ��ǡ�");
        }
        return 1;

}

int do_bring(string arg)
{
        object me, ob, jiading, where, weapon;
        int yapu_exp, yapu_pot;
        string lu;
        me = this_player();
        jiading = this_object();

        if( query("job_master") != query("id", me) )
                return 0;
        if( !living(jiading) )
                return notify_fail("��....����ȰѼҶ�Ū����˵��\n");
        if( !arg )
                return notify_fail("��Ҫ�Ҷ�����˭��\n");
        if(!objectp(ob = present(arg, environment(this_player()))))
                return notify_fail("����û������ˡ�\n");
        if(ob == me)
                return notify_fail("�����Լ����㵽������ʲ�᣿\n");
        if(ob == jiading)
                return notify_fail("Ҫ�Ҷ����߼Ҷ���\n");
        if( query("th_victim", ob) != query("id", me) )
                return notify_fail("���޷�ȷ��"+ob->name()+"�ǲ�����Ҫ׽�Ķ���\n");
        if( me->is_busy() || me->is_fighting() )
                return notify_fail("����æ���ء�\n");
        if( jiading->is_busy() || jiading->is_fighting() )
                return notify_fail( "�Ҷ���æ���ء�\n");

        switch(query("family/master_name", me)){
        case "��ҩʦ" :
        lu = "��½ʦ��";
        break;
        default:
        lu = "½ׯ��";
        }

        yapu_exp=query("gain_exp", ob);
        yapu_pot=query("gain_pot", ob);

        if(yapu_exp > 500) yapu_exp = 500+random(40);
        if(yapu_pot > 250) yapu_exp = 240+random(30);

        if (arg == "corpse" && (ob = present(arg, environment(me))) 
         && query("yapu_fail", ob) == query("id", me) )
        {
        command("shrug");
        command("say ������˴����ˣ��������ˣ������Ȱ�������ȥ����ɡ�");
        message_vision("�Ҷ���"+ob->name()+"�����������ڱ��ϣ��ߵ��ˡ�\n",me,ob);
        delete("find_yapu", me);
        me->apply_condition("th_yapu_fail", 5);
        destruct(ob);
        destruct(jiading);
        }
        else if( query("th_victim", ob) == query("id", me) && !living(ob)){
                message_vision(CYN"$N˵��������"+ob->name()+"�����ˣ�\n"NOR,me,ob);
                command("nod "+getuid(me));
                
                if( query_temp("last_damage_from", ob) == me && query("age", ob)<20 && query("shen", me)>1000){
                message_vision(HIR"�Ҷ��ͳ�һ��ϸ��������С�����⿪$n����ͣ���Ҫնȥ$n����ͷ����\n"NOR,me,ob);
                message_vision(CYN"$N��Ȼ˵������������"+ob->name()+"������ᣬ��Ȼ������;������δʼ���ܸĹ���\n"NOR,me,ob);
                message_vision(CYN"$N˵�������ȱ��֣�ֱ�Ӱ�$p���ع���ׯ������"+lu+"������������ǡ�\n"NOR,me,ob);
                command("ok");
                addn("th_exp", yapu_exp, me);
                addn("th_pot", yapu_pot, me);
                set("th_help_yapu", 1, me);
                }
                else if( query_temp("last_damage_from", ob) == me){
                message_vision(HIR"�Ҷ��ͳ�һ��ϸ��������С�����⿪$n����ͣ��ɿ��նȥ��$n����ͷ������ת�����棬��$p˫������һ������ʱ��ѪȪӿ��\n"NOR,me,ob);
                message_vision(HIR"�Ҷ�����С����ȡ��һ����ƿ��������ҩ����$p�����˫���˴�����Ѫ���������ǴӴ�Ҳ�ѳ�����֮�ˡ�\n"NOR,me,ob);
                addn("th_exp", yapu_exp, me);
                addn("th_pot", yapu_pot, me);
                }
                else {
                command("say ��Ȼ����"+ RANK_D->query_respect(me) +"���ְ�ƽ�ģ����������Ǵ�����"+RANK_D->query_rude(ob)+"�ˣ�");
                set_temp("not_me", 1, me);
                //��ɹ�������ûreward��
                }
        command("say �����ھͰ���"+RANK_D->query_rude(ob)+"���ع���ׯ�ϡ�");
        message_vision("�Ҷ���"+ob->name()+"�����������ڱ��ϣ��ߵ��ˡ�\n",me,ob);
        set("th_yapu_ok", 1, me);

                if( query_temp("not_me", me)){
                tell_object(me,"�˴ι��������ɻ��"+yapu_exp+"���һ�exp��"+yapu_pot+"���һ�pot��������Ϊ�������Լ���ɵģ����Բ��㡣\n");
                log_file("test/yapu_job",
                sprintf("%s(%s) failed to get %d th_exp and %d th_pot from %s on %s\n", 
                me->name(),query("id", me),yapu_exp,yapu_pot,ob->name(),ctime(time())));
                delete_temp("not_me", me);
                }
                else {
                tell_object(me,"�˴ι������"+yapu_exp+"���һ�exp��"+yapu_pot+"���һ�pot��\n");
                log_file("test/yapu_job",
                sprintf("%s(%s) got %d th_exp and %d th_pot from %s on %s\n", 
                me->name(),query("id", me),yapu_exp,yapu_pot,ob->name(),ctime(time())));

                }
                if( query("th_exp", me)>10000){
                set("th_exp", 10000, me);
                tell_object(me,"����һ������Ѿ��ﵽ10000������㣬�������ۻ��ˡ�\n");
                }

                if( query("th_pot", me)>query("max_potential", me)*10){
                set("th_pot",query("max_potential",  me)*10, me);
                tell_object(me,"����һ�Ǳ���Ѿ��ﵽ"+(query("max_potential", me)*10)+"������㣬�������ۻ��ˡ�\n");
                }
                
        destruct(ob);
        destruct(jiading);
        }
        else tell_object(me,"����ȴ��"+ob->name()+"���У�\n");

        return 1;
}

string ask_yapu()
{
        object me;
        me = this_player();

        if( query("job_master") == query("id", me)){
        return "����"+query("yapu_region")+""+query("yapu_room")+CYN"������"+query("find_yapu_real")+"ʱ�������Ǹ�Ѱ��"+query("find_yapu")+"ģ����";        
        }
        else return 0;
}

int do_order(string arg)
{
        object me, jiading;
        me = this_player();
        jiading = this_object();

        if( query("job_master") != query("id", me) )
                return 0;
        if( !living(jiading) )
                return notify_fail("��....����ȰѼҶ�Ū����˵��\n");
        if( me->is_busy() )
                return notify_fail("����æ���ء�\n");
        if( jiading->is_busy() || jiading->is_fighting() )
                return notify_fail( "�Ҷ���æ���ء�\n");

        if( arg == "follow" ) {
        message_vision("$N��Ҷ��������֣�Ҫ����������\n",me);
        command("follow"+query("id", me));
        }
        if( arg == "stay" ) {
        message_vision("$N����Ҷ�����ԭ�ء�\n",me);
        command("nod"+query("id", me));
        command("follow none");
        }
        if( arg == "leave" ) {
        message_vision("$N��Ҷ�һ���֣�˵���������뿪�����\n",me);
        command("nod");
        jiading->random_move();
        }

        return 1;
}
