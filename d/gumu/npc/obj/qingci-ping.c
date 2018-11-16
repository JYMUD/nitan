// qingci-ping.c ���ƿ������װ�����

#include <ansi.h>

inherit ITEM;

inherit F_LIQUID;

#define RAN 60        // ����Ч���ĸ���

void create()
{
        set_name(CYN "���ƿ" NOR, ({"qingci ping", "ping", "bottle" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "��Ĺ������װ����۵����Сƿ��\n");
                set("unit", "��");
                set("base_unit", "��");
                set("max_liquid", 10);
                set("no_give",0);
        }

        set("liquid", ([
                "type": "mi",
                "name": "�����",
                "remaining": 10,
                "drunk_apply": 1,
        ]));

}

void init()
{
        add_action("do_drink", "he");
        add_action("do_drink", "drink");
        add_action("do_fill", "fill");
        add_action("do_fill", "zhuang");
        add_action("do_add", "add");
}


int do_drink(string arg)
{
        object pl = this_player();
        object ping = this_object();
        object *inv;
        string item;
        int num,i,j;

        if(!arg) return 0;
        if( !living(pl) ) return 0;
        if( pl->is_busy() )
                return notify_fail("����һ��������û����ɡ�\n");
        if( query("water", pl) >= pl->max_water_capacity() )
                return notify_fail("���Ѿ���̫���ˣ���Ҳ�಻��һ��ˮ�ˡ�\n");

        if (sscanf(arg, "%s %d", item, num)==2){
                if( !id(item) ) return 0;
                if(num){
                        inv = all_inventory(pl);
                        j = 0;
                        for(i=0; i<sizeof(inv); i++){
                                if( query("name", inv[i]) == CYN"���ƿ"NOR){
                                        j += 1;
                                        if( j == num ) ping = inv[i];
                                }
                        }
                }
        }
        else if( !id(arg) ) return 0;
        
        if( !query("liquid/remaining", ping) )
                return notify_fail(name()+(query("liquid/name", ping)?"�Ѿ����ȵ�һ��Ҳ��ʣ�ˡ�\n":"�ǿյġ�\n"));

        addn("liquid/remaining", -1, ping);
        message_vision("$N����"+name()+"����һС��"+query("liquid/name", ping)+"��\n",pl);
        addn("water", 5, pl);
        addn("jingli", 5, pl);

        if( query("liquid/name", ping) == "�����"){
                addn("jing", 30, pl);
                if ((int)pl->query_condition("yufengdu")) {
                    pl->apply_condition("yufengdu", (int)pl->query_condition("yufengdu") - 5);
                        tell_object(pl, HIW "��䶾������������һЩ��\n" NOR );
                }
        }
        if( query("liquid/name", ping) == "�����ˮ"){
                addn("jingli", 25, pl);
                if ((int)pl->query_condition("yufengdu")) {
                    pl->apply_condition("yufengdu", (int)pl->query_condition("yufengdu") - 2);
                        tell_object(pl, HIW "��䶾������ֻ������һ��㣡\n" NOR );
                }
        }
        if( query("liquid/name", ping) == "�������"){
                if (pl->query_skill("qufeng",1) > 60
                        && pl->query_skill("yunv-xinfa",1) > 30
                         && query("family/family_name", pl) == "��Ĺ��"){
                        tell_object(pl, HIW "��Ǳ�˹���������������֮�������ھ�����\n" NOR );
                        if ( random(100) < RAN ){
                                if( query("max_jingli", pl)<pl->query_current_jingli_limit() )
                                {
                                        addn("max_jingli", 1, pl);
                                        addn("eff_jingli", 1, pl);
                                }        
                        }
                        else if( query("jingli", pl)<query("max_jingli", pl) )
                                set("jingli",query("max_jingli",  pl), pl);
                        if ((int)pl->query_condition("yufengdu")>=20) 
                                pl->apply_condition("yufengdu", 20);
                        else
                                pl->apply_condition("yufengdu", 
                                        (int)pl->query_condition("yufengdu") + 2);
                }
                else pl->apply_condition("yufengdu", 
                        (int)pl->query_condition("yufengdu") + 20);
        }
        if( query("liquid/name", ping) == "��Ĺ��"){
                if (pl->query_skill("qufeng",1) > 120
                        && pl->query_skill("yunu-xinjing",1) > 90
                         && query("family/family_name", pl) == "��Ĺ��"){
                        tell_object(pl, HIW "��Ǳ����Ů�ľ�����������֮������������ƺ���Щ���á�\n" NOR );
                        if ( random(100) < RAN ){
                                if( query("max_neili", pl)<pl->query_current_neili_limit() )
                                        addn("max_neili", 1, pl);
                        }
                        else if( query("neili", pl)<query("max_neili", pl) )
                                set("neili",query("max_neili",  pl), pl);
                        if ((int)pl->query_condition("yufengdu")>=30) 
                                pl->apply_condition("yufengdu", 30);
                        else
                            pl->apply_condition("yufengdu", 
                                        (int)pl->query_condition("yufengdu") + 3);
                }
                else pl->apply_condition("yufengdu", 
                        (int)pl->query_condition("yufengdu") + 30);
        }
        if( query("liquid/name", ping) == "��Ĺʥ��"){
                if ( pl->query_skill("qufeng",1) > 150
                        && pl->query_skill("yunu-xinjing",1) > 120
                         && query("family/family_name", pl) == "��Ĺ��"){
                        tell_object(pl, HIW "��Ǳ����Ů�ľ�����ʥ������֮�����о�����ͨ����̩��\n" NOR );
                        if ( random(100) < RAN ){
                                if( query("max_neili", pl)<pl->query_current_neili_limit() )
                                        addn("max_neili", 1, pl);
                        }
                        else 
                        if( query("max_jingli", pl)<pl->query_current_jingli_limit()){
                                addn("max_jingli", 1, pl);
                                addn("eff_jingli", 1, pl);
                        }
                        if ((int)pl->query_condition("yufengdu")>=30) 
                                pl->apply_condition("yufengdu", 30);
                        else
                            pl->apply_condition("yufengdu", 
                                        (int)pl->query_condition("yufengdu") + 3);
                }
                else pl->apply_condition("yufengdu", 
                        (int)pl->query_condition("yufengdu") + 30);
        }

//        if( pl->query("jingli") > pl->query("max_jingli")) 
//        this_player()->set("jingli", this_player()->query("max_jingli"));

        if( pl->is_fighting() ) pl->start_busy(2);
        if( !query("liquid/remaining", ping)){
                write("���Ѿ���"+name()+"���"+query("liquid/name", ping )
                        + "�ȵ�һ��Ҳ��ʣ�ˡ�\n");
                if( query("worthless", ping))set("value",0);
        }

        // This allows customization of drinking effect.
        if( query("liquid/drink_func", ping))return 1;

        switch(query("liquid/type", ping)){
                case "alcohol":
                        pl->apply_condition("drunk",
                                (int)pl->query_condition("drunk") 
                                +query("liquid/drunk_apply", ping));
                        break;
        }
        
        return 1;
}

int do_fill(string arg)
{
        object pl = this_player();
        object ping = this_object();
        object *inv;
        string item;
        int num,i,j;

        if(!arg) return 0;
        if( !living(pl) ) return 0;
        if( pl->is_busy() )
                return notify_fail("����һ��������û����ɡ�\n");
        if( !query("resource/water", environment(pl)) )
                return notify_fail("����û�еط�����װˮ��\n");

        if (sscanf(arg, "%s %d", item, num)==2){
                if( !id(item) ) return 0;
                if(num){
                        inv = all_inventory(pl);
                        j = 0;
                        for(i=0; i<sizeof(inv); i++){
                                if( query("name", inv[i]) == CYN"���ƿ"NOR){
                                        j += 1;
                                        if( j == num ) ping = inv[i];
                                }
                        }
                }
        }
        else if( !id(arg) ) return 0;

        if( query("liquid/remaining", ping) == query("max_liquid", ping )
                 && query("liquid/name", ping) == "�����"){
                message_vision("$N��ˮ����ע��" + ping->name() + "�����ҡ�ȡ�\n", pl);
                set("liquid/type", "mi-water", ping);
                set("liquid/name", "�����ˮ", ping);
                set("liquid/remaining", query("max_liquid"), ping);
                set("liquid/drink_func", 0, ping);
        }
        else {
                if( query("liquid/remaining", ping) )
                        message_vision("$N��" + name() + "��ʣ�µ�" + query("liquid/name") + "������\n", pl);
                message_vision("$N��" + name() + "װ����ˮ��\n", pl);

                set("liquid/type", "water", ping);
                set("liquid/name", "��ˮ", ping);
                set("liquid/remaining", query("max_liquid"), ping);//*query_amount());
                set("liquid/drink_func", 0, ping);
        }

        if( pl->is_fighting() ) pl->start_busy(2);

        return 1;
}

int do_addn(string arg)
{
        object me = this_player();
        int i,max,remaining;

        if( !wizardp(me) ) return 0;
        if(!arg) return 0;

        sscanf(arg, "%d", i);
        addn("liquid/remaining", i);
        remaining = query("liquid/remaining");
        max = query("max_liquid");        //*query_amount();
        tell_object(me, "��ƿ"+chinese_number(max)+"������"        + chinese_number(remaining)+"��\n");
        
        return 1;
}