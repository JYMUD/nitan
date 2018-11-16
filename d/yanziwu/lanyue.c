//ROOM: /d/yanziwu/lanyue.c

inherit ROOM;
#include <ansi.h>

int check_pass(object me);
int end_whisper(object me);

void create()
{
        set("short", "���¾�");
        set("long", @LONG
����Ľ�ݹ��ӵ����ң����г�����ͨ����ʰ����Ϊ���࣬�ݽ�һ
��ï���辰(penjing)���ú�����ʢ�������¹�Ӵ����������������
�⣬���������һ��������
LONG );
        set("exits", ([
            "west": __DIR__"shuwu",
        ]));

        set("item_desc", ([
            "penjing" : HIW "���辰�ƺ���ƽ��������������ر�⻬��\n" NOR,
        ]));

        setup();
}

void init()
{
        add_action("do_knock","knock");
        add_action("do_say","whisper");
}

int do_knock(string arg)
{
        object me;
        me=this_player();

        if (!arg || (arg!="penjing" ) )
                 return  notify_fail("��Ҫ��ʲô��\n");

        if( query_temp("marks/pen", me) )
                 return notify_fail("�����ˣ�\n");

        set_temp("marks/pen", 1, me);
        write(HIC "�����辰�����˼���...\n" NOR, me);
        remove_call_out("check_pass");
        call_out("check_pass", 4, me);

        return 1;
}

int check_pass(object me)
{
       write(HIC "��һ�����ֻ����Զ����Լ����һ��˵�����������������\n" NOR);
       write(HIY "�������룬��������һ�䰵������ش�(whisper)���ֲ�֪��˵Щʲô��\n" NOR);
       set_temp("can_whisper", 1, me);
       remove_call_out("end_whisper");
       call_out("end_whisper", 9, me);
       return 1;
}

int end_whisper(object me)
{
      if (! me) return 0;
      write(HIM "�������ã�ֻ����һ���ͷ������������������ˣ�û�±����������ҡ���\n" NOR);
      delete_temp("marks/pen", me);
      delete_temp("can_whisper", me);
      return 1;
}

int do_say(string arg)
{
     object me = this_player();
     
     if( !arg || !query_temp("can_whisper", me) )
              return notify_fail("���������ﲻ֪����˵ʲô��\n");

     if(arg != "�⸴����")
     {
              write(HIG "�����ĵ�˵������" + arg + "����ȴûʲô��Ӧ��\n");
              return 1;
     }
 
     write(HIG "�����ĵ�˵�������⸴���ࡱ����\n" NOR);
     write(HIC "�������Ц��Ц˵��������Ȼ�����˵ķԸ�������ͽ����ɣ���\n");
     write(HIY "��Ȼ����伸�����󣬻����¶��һ��·�������æ˳��������ȥ����\n");
     me->move(__DIR__"huanshi");
     delete_temp("can_whisper", me);
     return 1;

}


