#include <room.h>
inherit TRANS_ROOM;

void create()
{
mapping map_short = ([
         "chengdu"     : "�ɶ�",
         "dali"        : "����",
         "jingzhou"    : "����",
         "emei"        : "����ɽ",
         "xiangyang"   : "����",
]);

mapping trans_pay = ([
         "chengdu"     : 120,
         "dali"        : 150,
         "jingzhou"    : 140,
         "emei"        : 120,
         "xiangyang"   : 500,
]);

              set("short","���");
              set("long",@LONG
����Ԫ�˿�ջ�����ǣ����깩Ӧ���ʲ��ϡ�������紾
�ӣ�����ǻ����ǣ����Ǻ����տ���������ι�����㣬��ϴ
ˢ�ø�Ǭ������һֱ�ź򵽿�����·����������µ���ľ����
����һ����ľ�� (paizi)������жѷ������Ѳ��ϣ�������һ
����ۡ�
LONG);
        set("outdoors", "kunming");
        set("no_fight", 1);
        set("objects", ([
                      "/clone/horse/zaohongma": 1,
                      "/clone/horse/huangbiaoma": 1,
                      "/clone/horse/ziliuma": 1,
                      "/clone/npc/mafu": 1,
              ]));
              set("exits",([
                      "east"      : __DIR__"kedian",
              ]));
        set("trans", map_short);
        set("trans_money", trans_pay);

	set("coor/x", -16860);
	set("coor/y", -7230);
	set("coor/z", 0);
	setup();
              replace_program(TRANS_ROOM);
}