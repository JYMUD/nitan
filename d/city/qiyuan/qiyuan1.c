//��Է

#include <ansi.h>
inherit  ROOM;

string look_string();

void  create  ()
{
    set  ("short",  "��Է");
        set("long", @LONG
��Է�����ĸ���䣬����̸���ܵĺõط���������ϱ���������
�������һ�����ң���ÿ�����ҵ����ⶼ����[1��33m����������[2��37��0m�����ӣ�
�ڷ�������������ϻ�����һ������ָ��(help)��
LONG );

  set("no_dazuo",1);set("no_kill",1);set("no_fight",1);
         set("no_steal",1);
         set("pingan",1);
         set("no_beg",1);         
    set("item_desc", ([
    "help" : ( : look_string : ),
    ]));

    set("exits",  ([
    "east"  :  __DIR__"qiyuan2",
    "south"  :  __DIR__"qiyuan3",
    "north"  :  __DIR__"qiyuan4",
    "west" : "/d/pingan/nan2",
    ]));

     set("objects",  ([
    __DIR__"cch"  :  1,
    ]));
   setup();
}

string look_string()
{
        string  msg  =  "��ӭ����Է�����壡\n"  +
"
��������������Χ��������壬����������Ĳ��裺
һ�����Һö��֣�Ȼ��ֱ���  sit black  ��  sit white  ������
����ʹ�� new ��ʼһ���µ���֣�new [-5] [-b(numbers)] [-h(numbers)]
    ���� -5  �����������壬��ѡ��Ϊ��Χ�壻
      �� -b  ָ���������̵Ĵ�С��
         -h  ָ�����ӵ���Ŀ��
�������磺
����Χ�� new
    �þ���Χ�壺new -h9
    ʮ���ʮ��������壺new -5 -b15
����ʹ�� play ��������
    ���� play d4 �ȵȡ�
�ġ�ʹ�� refresh �ۿ����̡�
�塢ʹ�� leave �뿪���̡�
����ʹ�� pass �������䡣
�ߡ�ʹ�� undo ���塣Ŀǰֻ�ṩ������Ļ��幦�ܡ�

";
        return  msg;
}

int valid_leave(object me, string dir)
{
        object room;
        mapping exit;

        exit=query("exits", environment(me));

        if ( dir == "south" || dir == "north" || dir == "west" ) {
                if( !( room = find_object(exit[dir])) )
                       room = load_object(exit[dir]);
                if( query_temp("action", room) == 1 )
                       return notify_fail("�Ǽ������Ѿ����˿�ʼ�����ˣ��������\n");
                }

        return ::valid_leave(me, dir);
}