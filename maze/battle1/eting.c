// This program is a part of NT MudLIB
// eting.c
// ������


#include <ansi.h>
inherit ROOM;

string long_desc();
int do_withdraw(string arg);
int do_plant(string arg);


void create()
{
        set("short", HIW"������"NOR);
        set("long", (: long_desc :));

        set("exits", ([
                "west" : __DIR__"etower2",
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

        if( !query("flag") )
                desc  = HIW"
                   /I____________I\\
                 //||||||||||||||||\\\\
             T\\//IIIIIIIIIIIIIIIIIIII\\\\/T
            ^^^^"+HIG"||"NOR+HIY"^^^"+HIW"[ ������ ]"NOR+HIY"^^^"+HIG"||"+HIY"^^^^         "+HIY"
                "+HIG"||"NOR+HIY"________________"+HIG"||"NOR+HIY"             "+HIC"
         []__|[]___[]___||___[]___[]|__[]___[]
         |_________|_|________|_|____________|"+HIB"
               ||                  ||
               ||                  ||
               ||                  ||
               ||                  ||
               ||                  ||
               ||__________________||\n
               "+HIC"��ǰ������һ�ű�����\n"NOR;
        else
                desc  = HIW"
                   /I____________I\\         "+HIR"��"+HIW"
                 //||||||||||||||||\\\\       "+HIY"||"+HIR"~~~~~~~~/"+HIW"
             T\\//IIIIIIIIIIIIIIIIIIII\\\\/T   "+HIY"||   ��   "+HIR"{"+HIW"
            ^^^^"+HIG"||"NOR+HIY"^^^"+HIW"[ ������ ]"NOR+HIY"^^^"+HIG"||"+HIY"^^^^    "+HIY"||         "+HIR"\\"+HIY"
                "+HIG"||"NOR+HIY"________________"+HIG"||"NOR+HIY"        ||"+HIR"~~~~~~~~~~~"+HIC"
         []__|[]___[]___||___[]___[]|__[]___[]
         |_________|_|________|_|____________|"+HIB"
               ||                  ||
               ||                  ||
               ||                  ||
               ||                  ||
               ||                  ||
               ||__________________||\n
               "+HIC"��ǰ������һ�ű�����\n"NOR;

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
                if( living(obj[i]) &&
                    query_temp("battle/team_name", obj[i]) != query_temp("battle/team_name", me) && 
                    obj[i]->visible(me) ) {
                        obj[i]->kill_ob(me);
                        message_vision(HIR"$N����$n�ȵ�����$n����͵�죬���У���\n"NOR, obj[i],me,me);
                        me->kill_ob(obj[i]);
                        bGuarded = 1;
                }
        }

        if( !bGuarded )
        {
                flag = new(__DIR__"obj/flag");
                flag->set_name(query("flag_name"), ({ "flag" }) );
                if( flag->move(me) ) {
                        message_vision(HIG"$Nһ�ѳ����˴��죬�߸߾���\n"NOR, me);
                        set("flag",0);
                } else {
                        destruct(flag);
                }
                CHANNEL_D->do_channel(this_object(), "war",
                        "��˵"+me->name()+"������"+query("flag_name")+HIR"��"NOR );
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

        if( query_temp("battle/team_name", me) == query("team_name") )
                return notify_fail("��ɲ�����ĵ��̡�\n");

        flag = present("flag",me );
        if( !flag ) return notify_fail("������û����Բ塣\n");

        if( query("name", flag) == query("team_name")+"����" )
                return notify_fail("�Լ��Ķ���Ӧ�ò��ڴ�Ӫ���ǡ�\n");

        message_vision(HIY"$N�Ѵ��컩����չ������������ˡ�\n"NOR, me);

        set("flag",1);

        CHANNEL_D->do_channel(this_object(), "war",
                "��˵"+me->name()+"��"+query("name", flag)+HIR"�嵽����������"NOR);
        set("flag_name",query("name", flag));

        destruct(flag);

        BATTLEFIELD_D->add_bonus_score(me, 20);
        BATTLEFIELD_D->win_battle(query_temp("battle/team_name", me)); 
        return 1;
}
