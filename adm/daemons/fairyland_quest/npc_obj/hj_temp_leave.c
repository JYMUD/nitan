// ��� qxd ʹ�ã������ʱ�뿪ʱ���Ա������ɫ�İ�ȫ(Я�������)
// naihe 05-9-4 13:48
// naihe 05-9-12 9:22 ����BUG����ָ�� quit ʱ���� quit.

#include <ansi.h>
inherit ITEM;

void create()
{
    set_name( "�þ��������ʱ�뿪ʱ��", ({ "hj temp leave obj" }) );
    set_weight(1);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "���Я��ʱ����ֹ��һ��ָ�\n");
        set("unit", "��");
        set("value", 0);
    }
    set("hj_game/obj","hj leave obj");
    setup();
}
void init()
{
    object env, me = this_player();
    if( (env=environment(this_object()))
      && env == me
    )
    {
        mapping find_name = ([
            "feng" : HIW"��֮����"NOR,
            "yu"   : HIM"��֮����"NOR,
            "lei"  : HIC"��֮����"NOR,
            "dian" : HIG"��֮����"NOR,
        ]);
        set_temp( "apply/short", ({ sprintf( HIR"<��ʱ�뿪��Ϸ> "NOR"%s %s(%s)"NOR,
            find_name[ query_temp( "hj_game_find", me) ],
            query("name", me), capitalize(query("id", me)) ), }), me
        );
        set_temp("hj_apply_short", 1, me);
        message_vision( "\n$N��ʱ�뿪�˻þ���Ϸ��ϵͳ������$N�Ľ�ɫ��ȫ��\n\n", me );
        tell_object( me, "\n\n                  ������Ϸ������ \"back\" \n\n\n" );
        // add_action( "filter_cmds", "", 1 );
        add_action( "filter_cmds", "");
    }
}
int filter_cmds(string arg)
{
    object me = this_player();
        if (! this_player()) return 1;
    if( query_verb() == "quit" )
    {
        return 0;
    }
    if( query_verb() == "back" )
    {
        mapping find_name = ([
            "feng" : HIW"��֮����"NOR,
            "yu"   : HIM"��֮����"NOR,
            "lei"  : HIC"��֮����"NOR,
            "dian" : HIG"��֮����"NOR,
        ]);
        set_temp( "apply/short", ({ sprintf( "%s %s(%s)"NOR,
            find_name[ query_temp( "hj_game_find", me) ],
            query("name", me), capitalize(query("id", me)) ), }), me
        );
        set_temp("hj_apply_short", 1, me);
        message_vision( "\n$N�����˻þ���Ϸ��\n\n", me );
        destruct( this_object() );
        return 1;
    }
    tell_object( me, "��������ʱ�뿪�þ���Ϸ�����践����Ϸ�������� \"back\" \n" );
    return 1;
}
