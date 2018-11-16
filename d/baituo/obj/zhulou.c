// Code of JHSH
// zhulou.c ��¨
// maco

#include <ansi.h>
inherit ITEM;

int no_limit_amount(){ return 1; }
void create()
{
        set_name("��¨", ({ "zhu lou", "lou", "basket"}) );
        set_weight(1000);
        set_max_encumbrance(100000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ��������ɵ�¨�ӣ���ŷ�����ҵ���ר���������ߵġ�\n");
                set("material", "bamboo");
                set("value", 100);
        }
        setup();
}

void init()
{
        add_action( "do_catch", "catch" );
        add_action( "do_catch", "buzhuo" );
        add_action( "do_free", "free" );
        add_action( "do_free", "fang" );
}

int is_container() {return 1;}

int do_catch(string arg)
{
        object obj = this_object(), me = this_player();
        object snake;

        if (me->is_busy()
         || query_temp("pending/exercising", me) )
                return notify_fail("��������æ���ء�\n");

        if(me->is_fighting())
                return notify_fail("�Ƚ����ǰ�ĵ�����˵�ɡ�\n");

        if ( !arg )
                return notify_fail("��Ҫ��׽ʲô��\n" );

        snake = present(arg, environment(me));

        if( !objectp(snake = present(arg, me)) && !objectp(snake = present(arg, environment(me)))) 
                return notify_fail("��Ҫ��׽ʲô��\n" );

        if( query("race", snake) != "����" )
                return notify_fail("����¨������׽�ߵġ�\n");

        if( query("keeper", obj) != query("id", me) )
                return notify_fail("�ⲻ�������¨�����Ǳ��Ҷ��ĺá�\n");

        if( query("who_breed", snake) )
                return notify_fail("����"+snake->name()+"��ŷ���������������ģ���ʹ׽�ˣ�Ҳ���ܽ������֡�\n");

        if( snake->query_lord() != me && living(snake) 
         && query("caught", snake) != query("id", me) )
                return notify_fail(snake->name()+"��������ѱ����ֱ�Ӷ���׽�൱Σ�ա�\n");

        if( !query("bt_snake", snake) )
                return notify_fail("�ⲻ��ŷ�������߹ȵ�Ʒ�֡�\n");

        if( snake->move(obj) ) 
        {
                message_vision("$N��"+snake->name()+"׽����������β���������Ž���¨��\n", me, snake);
                delete("frightened", snake);
                if( !query("caught", snake) )
                me->improve_skill("training",atoi(query("snake_poison", snake)));

                set("caught",query("id",  me), snake);
        return 1;
        }
        else return 0;
}

int do_free(string arg)
{
        object me, obj, snake, *inv;
        int i;
        me = this_player();
        obj = this_object();

        if( !arg )
                return notify_fail("�����ʲ��ų���¨��\n");

        if( me->is_busy() )
                return notify_fail("����æ���ء�\n");

        if( query("keeper", obj) != query("id", me) )
                return notify_fail("�ⲻ�������¨�����Ǳ��Ҷ��ĺá�\n");

        if(arg=="all") {

                if( me->is_fighting() )
                        return notify_fail("�㻹��ս���У�һ�����ܷ�һ���ߡ�\n");

                inv = all_inventory(obj);
                if( !sizeof(inv) )
                        return notify_fail("������û���κζ�����\n");

                for(i=0; i<sizeof(inv); i++) {
                        if( query("race", inv[i]) != "����")continue;
                        inv[i]->move(environment(me));
                        message_vision("$N��һ��$n�ų���¨��\n"NOR, me, inv[i]);
                }
                write("��¨�����ȫ���ų����ˡ�\n");
                return 1;

        }

        if( !objectp(snake = present(arg, obj)) )
                return notify_fail("��¨��û��������\n");

        if( !snake->is_character() || snake->is_corpse() )
                return notify_fail("�ǲ����ǻ��ֱ�����õľͿ����ˡ�\n");

        message_vision("$N��һ"+query("unit", snake)+"$n�ų���¨��\n"NOR,me,snake);

        snake->move(environment(me));

        if( me->is_fighting() ) me->start_busy(1);

        return 1;
}

int reject(object ob)
{
        if( query("race", ob) == "����"){
                notify_fail("���ò�׽(catch | buzhuo)ָ�\n");
                return 1;
                }

        notify_fail("����¨������׽�ߵġ�\n");
        return 1;
}