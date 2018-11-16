// /d/xueshan/npc/fsgelun.c
// Summer 9/26/1996.
// Rama modified for hx

inherit NPC;

#define BUSY_TIME 240
int do_fashi();
void create()
{
        set_name("��������", ({ "jisi lama", "jisi", "lama" }));
        set_weight(3000000);
        set("long", 
"�������ڵĽ���ɮ�����ð�������������ŷ��������Ż��ۣ�ͷ����ñ��\n"
"������ɱ֮����\n");
        set("gender", "����");
        set("age", 20);
        set("attitude", "heroism");
        set("class","bonze");
        set("shen_type", -1);
        set("str", 50);
        
        set("max_qi", 500);
        set("max_jing", 450);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 40);
        set("combat_exp", 50000);
        set("score", 5000);

        set_skill("force", 50);
        set_skill("dodge", 55);
        set_skill("parry", 60);
        set_skill("staff", 60);
        set_skill("cuff", 60);
        set_skill("hammer", 60);

        
        set("inquiry", ([
                "׼������" : (: do_fashi :),
                "preparation" : (: do_fashi :),
        ]) );

        setup();
        switch( random(3) )
        {
                case 0:
                         carry_object("/clone/weapon/falun")->wield();
                         break;
                case 1:
                         carry_object("/d/xueshan/obj/fachu")->wield();
                         break;
                case 2:
                         carry_object("/d/xueshan/obj/faling")->wield();
        }
        carry_object("/d/xueshan/obj/lamajiasha")->wear();
}


int do_fashi()
{
        int i;
        object ob, me, mengzhu, room, *obj, room1, gang;
        ob=(present("fa tan", (environment(this_object()))));
        me=this_player();
        
        
        if (! present("fa tan", (environment(this_object())))){
        command("say ����æ���أ���ȥ��ֵ�յĸ��ײ��ɡ�");
        return 1;
        }

        if( query("class", me) != "bonze"){
        command("say �����������Ǵ�������㳬���ˣ��ǰɣ�");
        return 1;
        }

        if( query("family/family_name", me) != "ѩɽ��"
         && query("family/family_name", me) != "Ѫ����"){
        command("say �����������Ǵ�������㳬���ˣ��ǰɣ�");
        return 1;
        }

        if (me->query_skill("lamaism", 1) < 60){
        command("say �ܺã���ȥŪЩ�������õ��������ɡ�");
        return 1;
        }

    // add to involve the butter stuff
        if(!( room1 = find_object("/d/xueshan/dumudian")) )
                room1 = load_object("/d/xueshan/dumudian");
        if ( !objectp(gang = present("tong gang", room1)) ) {
        command("say �������õ����Ͳ����ˣ����˸Ͽ�ȥ��һ�°ɣ�");
                return 1;
        }

        if (gang->query_current_liquid() < 40) {
            command("say �������õ����Ͳ������ˣ�������ŪЩ�������ɡ�");
                return 1;
        }
        
        if( time()<query("burn/jobtime", me)+BUSY_TIME )
        {       command("say �����������һ���ܺķѾ�Ԫ�Ļ���˻�����ȥЪϢһ�°ɡ�");
                return 1;
        }
             // add by Yujie
        
        if( query("burning", ob)){
        obj = all_inventory(environment());
        for(i=0; i<sizeof(obj); i++){
        if( query("name", obj[i]) == query("pending", ob) )
        {
        command("say"+query("pending", ob)+"�������������£���λ"
        + RANK_D->query_respect(me) + "��һ���Ժ�\n");
        return 1;
        }
        }
        command("say"+query("pending", ob)+"���˷�������һ���᲻֪������ȥ�ˣ��治�󻰣�"
        +query("name", me)+"������"+query("pending", ob)+"���˰����µķ�������ɡ�\n");
        set("pending",query("name",  me), ob);
        return 1;
        }
/*
        if( query("name", me) == query("last_burner", ob)){
        command("say  ���˲��Ǹ����귨�����㻹����Ъһ����ɡ�");
        return 1;
        } 
*/
        if( query("pending", ob)){
        command("say"+query("pending", ob)+"���˸����귨�£���̳��δϨ�����ҵ���������"
         + RANK_D->query_respect(me) + "���������°ɡ�\n");
        return 1;
        }
        
        else{
        command("say"+query("name", me)+RANK_D->query_respect(me)+
        "��Ҫ����λʩ��������ѽ��\n");
        set_temp("marks/��", 1, me);
        return 1;
        }
}
int accept_object(object me, object ob)
{
        if (ob->is_character() || userp(ob))
                return 0;

        if( query("beheaded", ob)){
        command("say ����û��ͷ��");
        return 0;
        }

        if( query("id", ob) == "corpse" && present("fatan",(environment(this_object())) )
         && query_temp("marks/��", me) == 1){
        write("�������Ｑ��ææ�Ը���������̳����񣬵����͡�\n");
        delete_temp("marks/��", me);
        if( query("combat_exp", ob)>query("combat_exp", me )
         && query("my_killer", ob) == query("id", me)){
        set_temp("award_pending",query("combat_exp",  ob), me);
        set_temp("award_pot",query("combat_exp",  ob), me);
        if( query("was_userp", ob) )
        set_temp("award_doubling", 1, me);
        }
        if( query("combat_exp", ob)>1000000
         && query("my_killer", ob) == query("id", me)){
        set_temp("award_pot",query("combat_exp",  ob), me);
        }
        remove_call_out("preparing");
        call_out("preparing",5, me);
        return 1;
        }

        if (ob->name()=="���͹�"
         && query("class", me) == "bonze"){
        if (me->query_skill("lamaism", 1) < 30){
        set("lama_butter",query("mud_age",  me), me);
        command ("bow");
        command ("say ��������ʩ����");
//        remove_call_out("destroy_it");
        call_out("destroy_it", 1, ob);
        return 1;
        }
        if (me->query_skill("lamaism", 1) >= 30
        && me->query_skill("lamaism", 1) < 60){
        set("lama_butter",query("mud_age",  me)+7600, me);
        command ("bow");
        command ("say ��������ʩ����");
        remove_call_out("destroy_it");
        call_out("destroy_it", 1, ob);
        return 1;
        }
   }
//      else if (ob->name()!="����" && ob->query("id") != "corpse") {
        else {
        write("���ײ�����¶���Ի�ı��顣\n");
        command ("shake");
//      remove_call_out("destroy_it");  // if player #10 give him some stuff,
                                        // 1 got dest but others 9 still on him   
        call_out("destroy_it", 1, ob);
        return 1;
        }
        return 1;
}       
void destroy_it (object ob)
{
        destruct(ob);
        return;

}
void preparing(object me)
{
        object ob, obj, room, tonggang, guan;
        ob=(present("fa tan", (environment(this_object()))));
        if (! objectp(ob)) 
        {
                write("׼��δ�ɹ�������������\n");
                return;
        }
        obj=(present("corpse", this_object()));
        if (! objectp(obj)) 
        {
                write("��֣���ôʬ�岻���ˣ�\n");
                return;
        }
        set("pending",query("name",  me), ob);
        set("burn/jobtime", time(), me);
        set("in_use", 1, ob);

        say("�������ｫ"+query("name", obj)+"������"+query("name", ob)+"�\n");
        write("��һ�����һ��׼��ͣ����\n");
        command("say"+query("name", me)+"������Ϊ���鳬�Ȱɣ�\n");
/*
        command("chat"+query("title", me)+query("name", me)+
                "���ˣ��ڽ���" + NATURE_D->game_time() + "����" 
                +query("victim_name", obj)+"��\n");

*/
        destroy_it(obj);
        ob->set_weight(ob->query_weight()*10);
        return;
}
