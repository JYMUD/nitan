#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "���ξ���" NOR);
        set("long", CYN @LONG
�������ξ�����о������Ժ����ģ���ʶ�ܲ�������
�Ĵ����ǰ�ããһƬ����ʲô�������С�
LONG NOR );
 /*       set("exits", ([
                "enter" : __DIR__"sky1",
]));*/
        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_magic", 1);
        set("objects", ([
                "/adm/npc/buddha2": 1,
        ]));

        setup();
}

void init()
{    
    object me = this_player();
    if ( !userp(me) ) return;

    add_action("do_wake", "wake");
    set_temp("apply/name", ({"������"}), me);
    set_temp("apply/short", ({"������(dreamwalker)"}), me);
    set_temp("apply/long", ({"������(dreamwalker)\n"}), me);
}

int do_wake()
{
   object room, me = this_player();

   message_vision("$N��Ȼ��ƮƮ�ط���������һ�¾ͷ����ˡ�\n", me);
  
   delete_temp("apply/name", me);
   delete_temp("apply/short", me);
   delete_temp("apply/long", me);
   if( query_temp("dream_place", me) )
   {     
      me->move(query_temp("dream_place", me));
      delete_temp("dream_place", me);
   } else
   me->move("/d/city/kedian");
   message_vision("$N���������˯�ۣ������˹�����\n", me); 
  return 1;
}