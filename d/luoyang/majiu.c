#include <room.h>
inherit TRANS_ROOM;

void create()
{
mapping map_short = ([
         "nanyang"     : "����",
         "wugong"      : "�书��",
         "yangzhou"    : "����",
         "kaifeng"     : "����",
         "changan"     : "����",
         "beijing"     : "����",
         "zhongzhou"   : "����",
         "xiangyang"   : "����",
]);

mapping trans_pay = ([
         "nanyang"     : 120,
         "wugong"      : 80,
         "yangzhou"    : 160,
         "kaifeng"     : 140,
         "changan"     : 100,
         "beijing"     : 160,
         "zhongzhou"   : 120,
         "xiangyang"   : 100,
]);

        set("short","���");
        set("long",@LONG
���ǿ͵�����ǣ����깩Ӧ���ʲ��ϡ����������¹ų�
��ʷ�ƾá���紾�ӣ�����ǻ����ǣ����Ǻ����տ�������
��ι�����㣬��ϴˢ�ø�Ǭ��������������µ���ľ���϶���
����ľ�� (paizi)������жѷ������Ѳ��ϡ�
LONG);
        set("outdoors", "luoyang");
        set("no_fight", 1);
        set("objects", ([
              "/clone/horse/zaohongma": 1,
              "/clone/horse/huangbiaoma": 1,
              "/clone/horse/ziliuma": 1,
              "/clone/npc/mafu": 1,
        ]));
        set("exits",([
                "west" : __DIR__"kezhan",
                "up"   : "/clone/shop/luoyang_shop",
        ]));
        set("trans", map_short);
        set("trans_money", trans_pay);

	set("coor/x", -6970);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}