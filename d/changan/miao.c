//Room: miao.c
#include <ansi.h>

inherit ROOM;

void create ()
{
        set ("short", "������");
        set("long", @LONG
����һ��������ˣ������Ͳ������ھ��Եø�С�ˣ�����С��
���������������ա�û��������������һ�ǣ����Ҹպ�����������
�ĵط��������������ܵ�ɽ��������õġ���Ҳ��֪�Ǳ�����һλ
�������ܵ�������������۾��ɵ�����öͭ�壬���һ����ڷ��⡣
�Ա߻���һ���ƾɵ����ӣ����Ϲ���һ��ľ�ң�bian����
LONG );
        set("exits", ([
                "west"   : "/d/changan/yongtai-dadao4",
        ]));
        set("objects", ([
                "/d/changan/npc/keeper"   : 1,
                __DIR__"obj/table" : 1,
                __DIR__"npc/shensuan" : 1,
        ]));
        set("item_desc", ([
                "bian" : "���е�Ϧ���������в�����ơ�",
        ]));

        set("no_fight",1);
        set("coor/x", -10750);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_knock","knock");
        remove_call_out("stat");
        call_out("stat", 10, this_player());
        remove_call_out("do_sleep");
        call_out("do_sleep",110+random(10));
}
int do_knock(string arg)
{
        object me,ob;
        me = this_player();
        ob = present("shensuan zi",this_object());
        if (ob){
         if(!arg || arg != "table")   return notify_fail("��Ҫ��ʲô��\n");
         if( !query_temp("sleeped", ob) )
            return notify_fail("�������Ѿ����ˣ��������������ˡ�\n");
         delete_temp("sleeped", ob);
         delete("no_get", ob);
         delete("no_get_from", ob);
         ob->enable_player();
         set("long", "������Զ�������������ӡ������ɡ����ܶ��˶�Ľ����������������\n"HIY"���������ƺ�������һЩ�������ܡ�\n"NOR, ob);
         message_vision("$N�������������ӡ�\n",me);
         message_vision("����������˯�����ʵ��۾������˸���������������Ŀ��˿�$N��\n",me);
          set_temp("knock", 1, me);
         remove_call_out("do_sleep");
         call_out("do_sleep",60);
         return 1;
        }else  return notify_fail("��õ������ɻ�����˵��\n");
}

void do_sleep()
{
      object ob;

      remove_call_out("do_sleep");
      ob=present("shensuan zi",this_object());
      if (ob && living(ob)){
      message_vision("$N���˸���Ƿ����˯���ˡ�\n",ob);
      set_temp("sleeped", 1, ob);
      set("no_get", 1, ob);
      set("no_get_from", 1, ob);
      ob->disable_player("<˯����>");
      set("long", "�����������ڰ��ͷſ��������˯������Һһֱ���������ӵ��¡�\n", ob);
      }
      
}
int stat(object me)
{
   object ob;
   
   if (!me || environment(me)!=this_object() ) return 1;   
   
   ob=present("shensuan zi",this_object());
   if( ob && query_temp("sleeped", ob)){
      message_vision("����.....��.........��...............\n",ob);
   }
   remove_call_out("stat");
   call_out("stat",60,me);
}
void reset()
{
   ::reset();
   call_out("do_sleep",0);
}
