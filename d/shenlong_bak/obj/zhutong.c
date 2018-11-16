// Rama@hx

#include <ansi.h>
inherit ITEM;
inherit F_SSERVER;
void setup()
{}
void init()
{
        add_action("do_entice","entice");
        add_action("do_throw","fang");
        add_action("do_put", "put");
}

void create()
{
        set_name("��Ͳ", ({"zhu tong" ,"zt"}));
        set_max_encumbrance(10000);
        set("unit", "��");
        set("long", "����һ�������Ƴɵ���Ͳ���������������ն�������������׽����(entice)��\n");
        set("value", 100);
//      set("no_drop", "�������������뿪�㡣\n");
        set_weight(105);
        set("no_sell",1);
        setup();
}
int is_container() { return 1; }

int do_entice(string arg)
{
    object me,ob1,ob;
    string who,what;
    me = this_player();
    if( !arg
        ||      sscanf(arg, "%s in %s", who, what)!=2)
         return notify_fail("�����ʽ: entice <����> in <��Ʒ>��\n");
    ob1= present(what,me);
    ob = present(who,environment(me));
    if (!ob )
         return notify_fail("��Ҫ����ʲô��\n");
    if( !ob1 || query("id", ob1) != "zhutong" )
         return notify_fail("��Ҫ�ѳ����������\n");
    if(!present("long xianxiang",ob1))
         return notify_fail("��Ͳ�ƺ���"+query("name", ob)+"��û����������\n");
    if( query("race", ob) != "����" && query("race", ob) != "����" && query("name", ob) == HIW"����"NOR )
         return notify_fail("��Ͳ̫С���ƺ��Ų���"+query("name", ob)+"��\n");
    if( ((int)ob1->query_max_encumbrance()-(int)ob1->query_encumbrance())< ob->query_weight()  )
        return notify_fail("��Ͳ̫С���ƺ��Ų���"+query("name", ob)+"��\n");
    if (sizeof(all_inventory(ob1)) >= 2) 
        return notify_fail("��Ͳ�����Ѿ��ж����ˡ�\n");              
    message_vision("$N����Ͳ�����Ӱε�������"+query("name", ob)+"����Ĵ��ſ��ڡ�\n",me);
    if(me->query_skill("poison",1) < 80)
    {
        message_vision("����"+query("name", ob)+"��Ϊ������������ʼ��$N������������\n",me);
        ob->kill_ob(me);
        return 1;
    }
    else {      
        message_vision("ֻ��"+query("name", ob)+"����Ͳ��̽ͷ̽�Ե������ţ���Ȼһ���������$N����Ͳ�\n",me);
        message_vision("$N��æ����Ͳ��ס��Ĩ��Ĩ��ͷ���亹�����롰���հ�������\n",me);
        ob->move(ob1);
        return 1;
        }
     return 1;
}
int do_throw(string arg)
{
    object me,ob1,ob,target;
    string who,what;
    me = this_player();
//  ob1= this_object();
    if( !arg
        ||      sscanf(arg, "%s from %s", who, what)!=2)
         return notify_fail("�����ʽ: fang <����> from <��Ʒ>��\n");
    ob1 = present(what,me);
    if (!ob1)
         return notify_fail("��Ҫ������Ŷ��棿\n");
    ob = present(who,ob1);
    if (!ob )
         return notify_fail("��Ҫ��ʲô��\n");
    if( !target ) target = offensive_target(me);
    if( !target
        ||      !me->is_fighting(target) )
                return notify_fail(query("name", ob)+"ֻ������ս���а�����֡�\n");
    if( query("family/family_name", me) != "������"
         ||me->query_skill("poison",1) < 50)
    {
         tell_object(ob, HIG "��Ӳ����Ŵӻ����ͳ���Ͳ������ôҲû�е���������\n" NOR );
         message_vision(HIG"ֻ��$N�ӻ����ͳ�һ����Ͳ����ɫ���ף��ֽŲ�����֪��Ҫ��ʲô��\n",me);
    }
    tell_object(me,  "�����Ĵӻ����ͳ�һ����Ͳ���������ӡ�\n" );
    message_vision("ֻ��$N���һ�а���һ�һ����������"+query("name", target)+"���ʺ�\n",me);
    ob->move(environment(me));
    set("combat_exp",query("combat_exp",  ob)*2+query("combat_exp", target), ob);
    ob->kill_ob(target);
    target->start_busy(1);
        COMBAT_D->do_attack(ob,target,query_temp("weapon", ob),0);
    message_vision("ֻ��"+query("name", ob)+"�����ڿ���һ�ۣ�ҧ��"+query("name", target)+"��ͷ����\n",me);
        COMBAT_D->do_attack(ob,target,query_temp("weapon", ob),0);
    message_vision("ֻ��"+query("name", ob)+"β��һ�����ڿ���һ����ת���Ƶ���"+query("name", target)+"�ı���\n",me);
        COMBAT_D->do_attack(ob,target,query_temp("weapon", ob),0);
    message_vision(query("name", target)+"ֻ����ǰһ����"+query("name", ob)+"��ҧ��"+query("name", target)+"�ļ�ͷ��\n",target);
        COMBAT_D->do_attack(ob,target,query_temp("weapon", ob),0);
    message_vision(query("name", ob)+"�����þ�������棬˳��ҧ��"+query("name", target)+"�Ľű���\n",me);
        COMBAT_D->do_attack(ob,target,query_temp("weapon", ob),0);
    message_vision(query("name", ob)+"�䵽���棬���ѵ������ˡ�\n",me);
    destruct(ob);
    return 1;
}
int do_put(string arg)
{
    object me=this_player();
    object ob,item;
    if(!arg) return notify_fail("��Ҫ��ʲô�����Ž����\n");

    if( sscanf(arg,"%s in %s",ob,item)!=2 || !objectp(ob = present(ob, me)) || !objectp(item = present(item, me)))
    {
        write("��Ҫ��ʲô������\n");
        return 1;
    }
    else if( query("id", item) != "zhutong" )
        return 0;
        else if( query("id", ob) != "longxianxiang" )
    {
        write("�㲻�ܰ���������ŵ���Ͳ���档\n");
        return 1;
    }
    else if( present("long xianxiang", item) )
    {
        write("��Ͳ�����Ѿ���һ���������ˡ�\n");
        return 1;
    }
    else return 0;
}
