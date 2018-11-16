// This program is a part of NT MudLIB
// Х�ƻ�̳

#include <ansi.h>
inherit ROOM;

string long_desc();
int do_withdraw(string arg);
int do_plant(string arg);

void create()
{
        set("short", HIW"Х�ƻ�̳"NOR);
        set("long", (: long_desc :));

        set("exits", ([
                "north" : __DIR__"etower5",
                "down"  : __DIR__"eting",
        ]));

        set("outdoors", "battle");
        setup();
}


void init()
{
        add_action("do_withdraw", "ba");
        add_action("do_withdraw", "withdraw");
        add_action("do_plant", "plant");
}


string long_desc()
{
        string desc,temp;
        int nRank,i,j;

        if( query("flag") >0 )
                desc  = HIY"

                           /I______________I\\               "+HIC"|"+HIW"=====|"+HIY"
                         //||||||||||||||||||\\\\             "+HIC"|"+HIW" ��   |"+HIY"
                     T\\//IIIIIIIIIIIIIIIIIIIIII\\\\/T         "+HIC"|"+HIW"=====|"+HIY"
                     ^^^^"+HIG"||"NOR+HIY"^^^"+HIW"��Х�ƻ�̳��"NOR+HIY"^^^"+HIG"||"+HIY"^^^^         "+HIC"|"+HIY"
                         "+HIG"||"NOR+HIY"__________________"+HIG"||"NOR+HIY"             "+HIC"|"+HIY"
                        /||||||||||||||||||||||\\            "+HIC"|"+HIY"
                    T\\//IIIIIIIIIIIIIIIIIIIIIIII\\\\/T        "+HIC"|"+HIY"
                    ^^^^"+HIG"||"+HIY"^^^^^^^^^^^^^^^^^^^^"+HIG"||"+HIY"^^^^        "+HIC"|"+HIG"
                        ||                    ||            "+HIC"|"+HIW"
          []___[]___[]__|[]___[]___||___[]___[]|__[]___[]___[]
          |__________________|_|________|_|__________________|"+HIW"
             ||                                          ||
\n"NOR;
        else
                desc  = HIY"

                           /I______________I\\
                         //||||||||||||||||||\\\\
                     T\\//IIIIIIIIIIIIIIIIIIIIII\\\\/T
                     ^^^^"+HIG"||"NOR+HIY"^^^"+HIW"��Х�ƻ�̳��"NOR+HIY"^^^"+HIG"||"+HIY"^^^^
                         "+HIG"||"NOR+HIY"__________________"+HIG"||"NOR+HIY"
                        /||||||||||||||||||||||\\
                    T\\//IIIIIIIIIIIIIIIIIIIIIIII\\\\/T
                    ^^^^"+HIG"||"+HIY"^^^^^^^^^^^^^^^^^^^^"+HIG"||"+HIY"^^^^
                        ||                    ||
          []___[]___[]__|[]___[]___||___[]___[]|__[]___[]___[]
          |__________________|_|________|_|__________________|"+HIW"
             ||                                          ||
\n"NOR;

        return desc;
}

int do_withdraw(string arg)
{
        object flag, me=this_player(), *obj;
        int i, bGuarded = 0;

        if( !arg || arg != "flag" && arg != "qi" )
                return notify_fail("����Ҫ��ʲô��\n");

        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( query("flag") <= 0 )
                return notify_fail("û��ɰΡ�\n");

        if( query_temp("battle/team_name", me) == query("team_name") )
                return notify_fail("͵�Լ����죿\n");

        message_vision(HIY"$N�����Ծ����һ�Ѱ������ӡ�\n"NOR, me);

        obj = all_inventory(environment(me));
        for( i=0; i<sizeof(obj); i++ ) {
                if( living(obj[i])
                 && query_temp("battle/team_name", obj[i]) != query_temp("battle/team_name", me )
                &&  obj[i]->visible(me) )
                {
                        obj[i]->kill_ob(me);
                        message_vision(HIR"$N����$n�ȵ�����$n����͵�죬���У���\n"NOR, obj[i],me,me);
                        me->kill_ob(obj[i]);
                        bGuarded = 1;
                }
        }

        if( !bGuarded )
        {
                flag = new(__DIR__"obj/flag");
                flag->set_name(query("team_name")+"����", ({ "flag" }) );
                if( flag->move(me) ) {
                        message_vision(HIG"$Nһ�ѳ����˴��죬�߸߾���\n"NOR, me);
                        set("flag",0);
                } else {
                        destruct(flag);
                }
                CHANNEL_D->do_channel(this_object(), "war",
                        "��˵"+me->name()+"������"+query("team_name")+HIR"�Ĵ��죡"NOR );
        }
        return 1;
}

int do_plant(string arg)
{
        object flag, me = this_player();

        if( !BATTLEFIELD_D->in_battle(me) )
                return notify_fail("����û�б�����\n");

        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg || arg != "flag" && arg != "qi" )
                return notify_fail("����Ҫ��ʲô��\n");

        if( query("flag") > 0 )
                return notify_fail("������������ˡ�\n");

        if( query_temp("battle/team_name", me) != query("team_name") )
                return notify_fail("��ɲ�����Ĵ�Ӫ��\n");

        flag = present("flag", me);
        if( !flag ) return notify_fail("������û����Բ塣\n");

        if( query("name", flag) != query("team_name")+"����" )
                return notify_fail("�Լ��Ĵ�Ӫ��ô�ܲ��˼ҵ��죿\n");

        message_vision(HIY "$N�Ѵ��컩����չ������������ˡ�\n" NOR, me);

        destruct(flag);

        set("flag", 1);

        CHANNEL_D->do_channel(this_object(), "war",
                "��˵"+me->name()+"���������˴�Ӫ��" );

        BATTLEFIELD_D->add_bonus_score(me, 20);
        return 1;
}

