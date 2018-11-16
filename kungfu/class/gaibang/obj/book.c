// dgb_book.c

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;

int do_start(object me);


void create()
{
        set_name("�򹷰���", ({ "dgb book", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
        set("long", "�򹷰��Ŀھ��������ǿڴ���������Ӽ����Ŵ򹷰������һ�������޹�����⡣\n");
                set("material", "paper");
                                set("no_drop","�������������뿪�㡣\n");
                                set("no_get",1);
                                set("no_steal",1);
                set("value", 300000);

        }
}
void init()
{
  add_action("do_lingwu","lingwu");
  
}
int do_lingwu(string arg)
{
        object me;
        int cost;
        object *ob;
        object weapon;
        int i;
        me=this_player();
         if (me->is_busy())
            return notify_fail("����æ����!\n");

        
        if( arg != query("id", this_object()))return notify_fail("��Ҫ����ʲô?\n");
        if(me->query_skill("dagou-bang", 1) <250)
        return notify_fail("�����򹷰������������ʽ��δ����أ�\n");
        if( query("wugou", me)>500 )
        {
            set("can_perform/dagou-bang/tian", 1, me);
        return notify_fail("���Ѿ���ȫ�����˴򹷰��ľ��С�\n");
        }
        if( query("no_fight", environment(me)))return notify_fail("����������ã��޷�ר������\n");
        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
            if( query("race", ob[i]) == "����" && ob[i] != me )
            return notify_fail("�򹷰��ľ��пɲ����������˿���Ŷ��\n");
        }
        if( !objectp(weapon=query_temp("weapon", me)) )
        return notify_fail("�������޴򹷰�����������!\n");
        
        if( query("skill_type", weapon) != "staff" )
        return notify_fail("�����������Ȳ�������򹷰����ľ���!\n");
        if( query("qi", me)<query("max_qi", me) || query("jing", me)<query("max_jing", me) )
        return notify_fail("�������״�����ѣ�\n");
        if( query("neili", me)<query("max_neili", me) || query("jingli", me)<query("max_jingli", me) )
        return notify_fail("��ľ�����������δ��ӯ���޷�����\n");
        if( query("max_neili", me)<1000 )
                return notify_fail("���������������޷�����򹷰�����\n");
        if( query("master", this_object()) != query("id", me) )
        {
        if( query("max_neili", me)<20 )
                return notify_fail("����û����������ƺ�һ���ڹ��Ѿ�����ɢȥ��\n");
        addn("max_neili", -20, me);
        return notify_fail(HIR"�㲻֪�ھ���ǿ��������ʽ��ͻȻ�Ŀ���˵���������ܡ�\n"NOR);

        }
if (wizardp(me)) printf("int = %d\n",me->query_int());
        message_vision(HIY"$NĬ��ھ������ô򹷰����������е����ƱȻ���......\n"NOR,me);
        if (random(me->query_int())>35 || random(10)==3)
        {
                 addn("wugou", 1, me);
                if( query("wugou", me)<60 )
                 tell_object  (me,HIR"���ƺ��Դ򹷰����һ����һ˿����\n"NOR);
                 else if( query("wugou", me) == 60 )
                 tell_object  (me,HIR"���������ʽ�����޹��е���ʽ��Ҳ��������������ˡ�\n"NOR);
                 else if( query("wugou", me)>500 )
                 {
                         set("can_perform/dagou-bang/tian", 1, me);
             if (me->can_improve_skill("staff")) 
                     me->improve_skill("staff", 1500000); 
             if (me->can_improve_skill("staff")) 
                     me->improve_skill("staff", 1500000); 
             if (me->can_improve_skill("staff")) 
                     me->improve_skill("staff", 1500000); 
             if (me->can_improve_skill("dagou-bang")) 
                     me->improve_skill("dagou-bang", 1500000); 
             if (me->can_improve_skill("dagou-bang")) 
                     me->improve_skill("dagou-bang", 1500000); 
             if (me->can_improve_skill("dagou-bang")) 
                     me->improve_skill("dagou-bang", 1500000); 
             me->improve_skill("martial-cognize", 1500000); 
                 tell_object  (me,HIR"����������������޹������еľ��С�\n"NOR);
             }
                 else
                 tell_object  (me,HIR"��������޹��������˸�����˽⡣\n"NOR);
        }
        else
        {
                tell_object(me,HIR"���ķ����ң��Ѿ�����Ҳ��������\n"NOR);
        }
        addn("qi", -100, me);
        addn("jing", -100, me);
        addn("neili", -100, me);
        addn("jingli", -100, me);
        if (!wizardp(me)) me->start_busy(2+random(5));
        return 1;

}
