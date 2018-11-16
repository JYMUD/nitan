#include <ansi.h>
inherit ITEM;
//inherit F_CLEAN_UP;
void kf_same(object who,object me);

void setup()
{}

void init()
{
        add_action("do_watch","guancha");
        add_action("do_watch","watch");
        add_action("do_catch","daibu");
        add_action("do_catch","catch");
}
int is_container() { return 1; }


void create()
{
        set_name("����", ({"ling pai","ling" }));
       set_max_encumbrance(10);
       set("unit", "��");
       set("long", "����һ����������,���ִ��죬����֤���ٸ���ʿ����ݡ�\n�����������Ȩ��Ѱ�ﷸ(guancha)���������ɷ�(daibu)��\n");
       set("value", 0);
       set("no_drop", "�������������뿪�㡣\n");
       set("no_burn",1);
       set("no_get", "���ǳ�͢�Ķ�����ƽ�������˻����鷳�ġ�\n");
       set_weight(200);
       set("place","on");

       setup();
}
int do_watch(string arg)
{
        object obj,new_obj;
        object me = this_player();
        object ob = this_object();
        string targ;
        if( !query("kaifengfu", me) )
                return notify_fail("�㲢�ǳ�͢��Ա���αز�������ģ�\n");
        if (!ob=present("ling pai",me))
                return notify_fail("ʲô��\n");
        if( query_temp("kf_finish", me) )
                return notify_fail("��ҩ�����Żػ��ģ��㻹��ĥ��ʲô��\n");
        if (!arg||!obj=present(arg,environment(me)))
                return notify_fail("��Ҫ�۲�˭��\n");
        if( !obj->is_character() || obj->is_corpse() )
        return notify_fail("��ֻ�ܹ۲�һ��������塣\n");
        if( me->is_busy() )
                return notify_fail("����æ�š�\n");
        targ=query("name", obj);
        tell_object(me,"����������������"+targ+"��\n\n");

        if( query_temp("kf_tufei", obj) == query_temp("kf_npc", me )
         && random(query("kar", me))>15){
                switch(random(5)) {
                case 0:
                        tell_object(me,WHT"�㷢��"+targ+"��Ȼ��ͷһ�ͣ��ƺ���ܿ����Ŀ�⡣\n\n"NOR);
                     break;
                case 1:
                        tell_object(me,WHT"�㷢��"+targ+"��Ȼ���˸����£�������ɫ��\n\n"NOR);
                        break;
                case 2:
                        tell_object(me,WHT"�㷢��"+targ+"̫��Ѩ�߸߷����ƺ��Ǹ�������ˡ�\n\n"NOR);
                        break;
                case 3:
                        tell_object(me,WHT"�㷢��"+targ+"����Ĺ����ҵģ���������һ�����С�\n\n"NOR);
                        break;
                case 4:
                        tell_object(me,WHT"�㷢��"+targ+"�����о���һ���������ֱ��һ��ãȻ��\n\n"NOR);
                        break;
                }
                set_temp("kf_faxian", 1, me);
                set_temp("kf_faxianed",query("id",  me), obj);

                }  
        else{
                switch(random(11)) {
                        case 0:
                        tell_object(me,"ֻ��"+targ+"����üŪ�ۣ�ɫ���ԵĶ���������\n\n");
                        break;
                        
                        case 1:
                        tell_object(me,"ֻ��"+targ+"������Ƽ��ݣ��������\n\n");
                        break;
                        
                        case 2:
                        tell_object(me,"ֻ��"+targ+"���΢�죬һ�����ߵ�ģ����\n\n");
                     break;
                
                        case 3:
                        tell_object(me,"ֻ��"+targ+"�������⣬�������硣\n\n");
                        break;
                        
                        case 4:
                        tell_object(me,"ֻ��"+targ+"��ʹ�������޵���������Ƶġ�\n\n");
                        break;

                        case 5:
                        tell_object(me,"ֻ��"+targ+"���㽩Ӳ������ɢ���Ž�������\n\n");
                        break;

                        case 6:
                        tell_object(me,"ֻ��"+targ+"���ޱ��飬����ľ����\n\n");
                        break;
                        
                        case 7:
                        tell_object(me,"ֻ��"+targ+"���ü��������Ŀ���թ��\n\n");
                        break;
         
                        case 8:
                        tell_object(me,"ֻ��"+targ+"��Ц���������ϼ���һ˿��Ц��\n\n");
                        break;
                
                        case 9:
         
                        tell_object(me,"ֻ��"+targ+"ͦ�ص��ǣ�һ����������ɫ��\n\n");
                     break;
                
                        case 10:
                        tell_object(me,"ֻ��"+targ+"���������ݣ�һ���������ɫ��\n\n");
                        break;
                }
        }
        return 1;
}

int do_catch(string arg)
{
        object obj,new_obj;
        object me = this_player();
        object ob = this_object();                        //100
        if (!ob=present("ling pai",me))
                return notify_fail("ʲô��\n");
        if( !query("kaifengfu", me) )
                return notify_fail("�㲢�ǳ�͢��Ա���αز�������ģ�\n");
        if( query_temp("kf_finish", me) )
                return notify_fail("�ִ��˵��Żػ��ģ��㻹��ĥ��ʲô��\n");
        if (!arg||!obj=present(arg,environment(me)))
                return notify_fail("��Ҫ����˭��\n");
        if( !obj->is_character() || obj->is_corpse() )
                return notify_fail("��ֻ�ܴ���һ�����ˡ�\n");
        if( !query_temp("kf_faxian", me )
         || query_temp("kf_faxianed", obj) != query("id", me) )
                return notify_fail("��͢����������û��֤���������ˣ�\n");
        message_vision ("$N����$n��Цһ���������µİ��ӷ��ˣ�����ʵʵ��������һ�ˡ�\n\n",me,obj);
        if( query_temp("kf_whatnpc", me) == 1)new_obj=new("/d/kaifeng/npc/tufei1.c");
    if( query_temp("kf_whatnpc", me) == 2)new_obj=new("/d/kaifeng/npc/tufei2.c");
    if( query_temp("kf_whatnpc", me) == 3)new_obj=new("/d/kaifeng/npc/tufei3.c");
    if( query_temp("kf_whatnpc", me) == 4)new_obj=new("/d/kaifeng/npc/tufei4.c");
    if( query_temp("kf_whatnpc", me) == 5)new_obj=new("/d/kaifeng/npc/tufei5.c");
    if( query_temp("kf_whatnpc", me) == 6)new_obj=new("/d/kaifeng/npc/tufei6.c");
    if( query_temp("kf_whatnpc", me) == 7)new_obj=new("/d/kaifeng/npc/tufei7.c");
    if( query_temp("kf_whatnpc", me) == 8)new_obj=new("/d/kaifeng/npc/tufei8.c");
        message_vision (RED"$n���һ���ҿ�αװ��¶��������Ŀ��\n"NOR,me,obj);
//      destruct(obj);
        delete_temp("kf_faxianed", obj);
//       new_obj = present("picture",ob);
        kf_same(new_obj,me);    
       new_obj->move(environment(me));    
        message_vision (RED"$n��ȵ������Ӻ���ƴ�ˣ�\n"NOR,me,new_obj);
       new_obj->kill_ob(me);
       me->kill_ob(new_obj);
       new_obj->set_leader(me);
       set_temp("kf_npc",query_temp("kf_npc",  me), new_obj);
       set_temp("kf_ownname",query("id",  me), new_obj);
       delete("no_see", new_obj);
       new_obj->start_busy(1);
       delete_temp("kf_faxian", me);
//      me->set_temp("kf_finish");
       return 1;
}

void kf_same(object who,object me)
{
        mapping myscore;
        int maxskill;
        myscore = me->query_entire_dbase();
        set("combat_exp",query("combat_exp",  me)*10/7, who);

        set("max_qi", myscore["max_qi"], who);
        set("eff_qi", myscore["eff_qi"], who);
        set("qi", myscore["max_qi"], who);

        set("max_jing", myscore["max_jing"], who);
        set("eff_jing", myscore["eff_jing"], who);
        set("jing", myscore["max_jing"], who);

          set("max_neili", myscore["max_neili"], who);
        set("neili", myscore["max_neili"], who);
        set("jiali", 0, who);
        maxskill = me->query_skill("force",1);
        if(maxskill < me->query_skill("parry",1)) maxskill=me->query_skill("parry",1); 
        if(maxskill < me->query_skill("dodge",1)) maxskill=me->query_skill("dodge",1); 
        if(maxskill < me->query_skill("sword",1)) maxskill=me->query_skill("sword",1); 
        if(maxskill < me->query_skill("blade",1)) maxskill=me->query_skill("blade",1); 
        if(maxskill < me->query_skill("unarmed",1)) maxskill=me->query_skill("unarmed",1); 
        set("maxskill", maxskill, who);

}