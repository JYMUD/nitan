#include <room.h>
inherit TRANS_ROOM;

void create()
{
mapping map_short = ([
         "nanyang"       : "����",
         "suzhou"        : "����",
         "luoyang"       : "����",
         "beijing"       : "����",
         "xiangyang"     : "����",
         "kaifeng"       : "����",
         "changan"       : "����",
         "yangzhou"      : "����",
]);

mapping trans_pay = ([
         "nanyang"       : 120,
         "suzhou"        : 80,
         "luoyang"       : 120,
         "beijing"       : 150,
         "xiangyang"     : 80,
         "kaifeng"       : 100,
         "changan"       : 100,
         "yangzhou"      : 80,
]);

      set("short", "���");
      set("long", @LONG
���������ݳ�Ӣ����¥�����ǣ����깩Ӧ���ʲ��ϡ���
�ݳ��Թ��˾���Ҫ�أ���紾�ӣ�����ǻ����ǣ����Ǻ���
�տ���������ι�����㣬��ϴˢ�ø�Ǭ������һֱ�ź򵽿���
��·����������µ���ľ���϶���һ����ľ�� (paizi)�����
�жѷ������Ѳ��ϣ�������һ����ۡ�
LONG);
      set("outdoors", "zhongzhou");
      set("no_fight", 1);
      set("objects", ([
              "/clone/horse/zaohongma": 1,
              "/clone/horse/huangbiaoma": 1,
              "/clone/horse/ziliuma": 1,
              "/clone/npc/mafu": 1,
      ]));
      set("exits",([
              "west" : __DIR__"yinghao",
              "up"   : "/clone/shop/zhongzhou_shop",
      ]));
        set("trans", map_short);
        set("trans_money", trans_pay);
        set("coor/x", -9020);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
      replace_program(TRANS_ROOM);
}