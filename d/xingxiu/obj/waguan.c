// This program is a part of NT MudLIB
//10/8/00
//Last Update by Scatter

inherit ITEM;
#include <ansi.h>

void setup() {}


void create()
{
        set_name("�߹�", ({"wa guan", "wa", "guan"}));
        set_weight(15000);
        set_max_encumbrance(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ֻ");
                set("long", "һֻ�ʵؾ�ϸ���߹ޣ���֪����ʲô��;��\n");
                set("no_drop", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_sell", 1);
        }
        setup();
}

int is_container() { return 1; }

void init()
{
   add_action("do_hold", "kou");
   add_action("do_xiulian", "xiulian");
}

int do_hold(string arg)
{
        string what;

        object ob;
        object obj=this_object();
        object me=this_player();

        if( !arg || me != this_player(1))
                        return notify_fail("�����ʽ: kou <��Ʒ> ��\n");

        ob = present(arg, environment(me));
        if( !ob || !living(ob))
                return notify_fail("����û��������\n");

        if( query("sub", ob) != "xx_job")return notify_fail("�ⶫ����ò�Ҫץ��\n");

        if (this_player()->is_busy()) return notify_fail("����æ���ء�\n");

        if( query_temp("hold", this_player()))return notify_fail("�Ѿ��ж����ˣ������ɡ�");

        if( query("playerid", ob) != query("id", this_player()) )
                return notify_fail("�����ҳ����ģ������˼ץ��:)\n");




        if( query("combat_exp", this_player())<10000 )
        {

        if(this_player()->query_skill("poison",1)*10 > random(this_player()->query_skill("force")*3)) {
                        message_vision(HIG"$N�������е��߹��͵ؽ�"+query("name", ob)+"��ס��Ȼ��С������ؽ��߹޷�������ס��\n"NOR,this_player());
                        set("bug_hold",1);
                        set("count", random(10));
                        set("long","һֻ�ʵؾ�ϸ���߹ޡ�\n����ʢ��һֻ"+query("name", ob)+"��\n");
                        set("xiulian", random(5));
                        set("bug_name",query("name", ob));
                        set_temp("bug_hold", 1, this_player());
                        set_temp("found", 1, this_player());
                        destruct(ob);
         }else message_vision("$N�͵ĳ������߹޿���"+query("name", ob)+",��"+query("name", ob)+"����������ˡ�\n",this_player());

         }




         else
         {
         if(this_player()->query_skill("poison",1) > random(this_player()->query_skill("force")*3)) {
                        message_vision(HIG"$N�������е��߹��͵ؽ�"+query("name", ob)+"��ס��Ȼ��С������ؽ��߹޷�������ס��\n"NOR,this_player());
                        set("bug_hold",1);
                        set("count", random(10));
                        set("long","һֻ�ʵؾ�ϸ���߹ޡ�\n����ʢ��һֻ"+query("name", ob)+"��\n");
                        set("xiulian", random(5));
                        set("bug_name",query("name", ob));
                        set_temp("bug_hold", 1, this_player());
                        set_temp("found", 1, this_player());
                        destruct(ob);
         }else message_vision("$N�͵ĳ������߹޿���"+query("name", ob)+",��"+query("name", ob)+"����������ˡ�\n",this_player());
         }






         addn("neili", -50, this_player());
         this_player()->start_busy(random(1)+1);
         return 1;

}

int do_xiulian()
{
        if(this_player()->is_busy()) return notify_fail("����æ���ء�\n");
        if (query("bug_hold")!=1) return notify_fail("û�ж��棬����Ҫ�ÿ���������\n");
        message_vision(HIR"$N����������סȫ���Ѩ��Ȼ������۾�����ָ�����߹ޡ�\n"NOR, this_player());
        message_vision(HIR+query("bug_name")+"����ҧס$N��������Ѫ����\n"NOR, this_player());
        call_out("do_xiulian2", 10, this_player());
        this_player()->start_busy(10);
        return 1;
}

void do_xiulian2(object me){
        object dan;
        message_vision("$N�˹���ϣ�����һ��������վ��������\n",me);
        if (query("xiulian")<=0){
                dan=new("/d/xingxiu/obj/dudan");
                set("player",query("id",  this_player()), dan);
                message_vision(HIG+query("bug_name")+"��Ѫ���꣬���Ӹ߸�����ž��һ������޵ף������˼��£����ˡ�\n"NOR, this_player());
                message_vision("$N����"+query("bug_name")+"�ó��߹ޣ���������ʿ����ó�һ������Ѫ�ĵ�������\n"NOR, this_player());
                if( query("combat_exp", me)<100000){
                     tell_object(this_player(),HIR"���ж��ˣ�\n"NOR);
                     this_player()->affect_by("huadu_poison",
                              ([ "level" : me->query_skill("force")/3 + random(me->query_skill("force")/3),
                                 "id":query("id", me),
                                 "duration" :5 ]));
                }
                set_temp("found", 1, this_player());
                delete("bug_hold", this_object());
                set("long", "һֻ�ʵؾ�ϸ���߹ޡ�\n");
                dan->move(this_player());
        } else message_vision(HIR+query("bug_name")+"���Ӹ߸�����ž��һ������޵ס�\n"NOR, this_player());
        addn("xiulian",-1);
        if (this_player()->query_skill("poison",1)<420)
                this_player()->improve_skill("poison", this_player()->query_skill("feixing-shu",1));
}
