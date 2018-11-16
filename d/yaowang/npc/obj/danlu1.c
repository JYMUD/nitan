#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(CYN"����¯"NOR, ({ "liandan lu", "liandan", "lu" }) );
        set_weight(300000);
        set_max_encumbrance(500000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ����ͭ���ɵ�����¯��\n");
                set("value", 1000);
                set("no_get",1);
                set("amount",10);
                set("container",1);
        }
        setup();
}
int is_container() { return 1; }
void init()
{
//      add_action("do_fang", "fang");
        add_action("do_lian", "liandan");
        add_action("do_ran", "ran");
}
/*
int do_fang(string arg)
{
        object me, ob;
        me = this_player();

        if( query("family/family_name", me) != "ҩ����" || me->query_skill("medical",1)<80){
                return notify_fail("�㻹����������������\n");
        }

        if( query("shen", me)<0){
                return notify_fail("��Ӧ�������������ȥ������\n");
        }

        if(!arg || !ob=present(arg, me))
                return notify_fail("��Ҫ��ʲô�Ž�����¯��\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("����æ���أ�\n");

        message_vision(YEL"\n$N��һ"+query("unit", ob)+query("name", ob )
                +"�Ž�����¯��\n\n"NOR, me);

        destruct(ob);
        ob->move(this_object());
        return 1;
}
*/
int do_lian(string arg)
{
        object ob1, ob2, ob3, ob4, ob5;
        object me, ob, obj;
        me=this_player();
        ob=this_object();

        if( query("family/family_name", me) != "ҩ����" || me->query_skill("medical",1)<80){
                return notify_fail("�㻹����������������\n");
        }

        if( query("shen", me)<0){
                return notify_fail("��Ӧ�������������ȥ������\n");
        }

        if( !arg && ((arg!="bigu wan")) )
                return notify_fail("ָ���ʽ��liandan <��ҩID> \n"
                "        �������ĵ�ҩ�У� �ٹ���(bigu wan)\n"
                "                         ******(********)\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("����æ���أ�\n");

        if( !query_temp("liandan", me) )
                return notify_fail("��¯��û�е�ȼ����ô������\n");

        if( objectp(ob1=present("lu xue",ob))
                && objectp(ob2=present("lu rong",ob))
                && objectp(ob3=present("xiong dan",ob))
                && objectp(ob4=present("xiong zhang",ob))
                && objectp(ob5=present("she dan",ob)) ) {
                        destruct(ob1);
                        destruct(ob2);
                        destruct(ob3);
                        destruct(ob4);
                        destruct(ob5);
                if(arg=="bigu wan") { obj=new(__DIR__"biguwan"); }
        message_vision(HIR"$N���ϵ�¯��¯�ţ��߶�������ʼ������\n\n"NOR, me);
        call_out("lian_over", 5, me);   
                return 1;
                }
        else
        return notify_fail("����ҩ�Ļ�û׼����ѽ��\n");
}
int lian_over(object me)
{
        int lvl;
        object obj;
        lvl = me->query_skill("medical",1);
        if (random(lvl) > 80)
        {
        message_vision(HIR"һ���¯���ڵĻ��潥��Ϩ��\n\n"NOR, me);
        message_vision(HIR"$N�ĵ�ҩ�����ˡ�\n"NOR, me);
        message_vision(HIR"¯�𽥽�Ϩ���ˣ�\n"NOR, me);
        message_vision(HIR"$N���¯���ó�һ�űٹ���\n"NOR, me);
        me->improve_skill("medical", ((int)me->query_skill("medical",1)/10));
        obj=new(__DIR__"biguwan");
        obj->move(me);
        delete_temp("liandan", me);
        return 1;
        }
        else
        {
                message_vision(HIR"$N�ĵ�ҩ��ʧ���ˡ�\n"NOR, me);
                return 1;
                
        }

}
int do_ran(string arg)
{
        object me;
        me=this_player();

        if( query("family/family_name", me) != "ҩ����" || me->query_skill("medical",1)<80
                 || query("shen", me)<0){
                return notify_fail("������������Ķ�����\n");
        }

        if( query_temp("liandan", me) )
                return notify_fail("��¯�Ļ��Ѿ������ˣ��쿪ʼ�����ɣ�\n");

        set_temp("liandan", 1, me);
        message_vision(HIR"$N�����������¯�ţ��ѵ�¯��ȼ��\n"NOR, this_player());
        return 1;
}
