// Room: /d/taishan/wanxianlou.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "����¥");
        set("long", @LONG
����¥Ϊ�����¥ʽ��������������ĸ���������ɣ�������Ԫ����
��ǽ������������ɽ���㱮��ʮ���顣�Ŷ����������涴��Ϊ��ʱ����
���������Ŷ�����顰л�����������ŵ�����ɽʱ���ط���Ա�ͼ�����
��л�顣��ƾ�ʱ��͵�᷻ع�����������ߵлԪ������֮����
LONG );
        set("exits", ([
                "north" : __DIR__"taohua",
                "south" : __DIR__"sanyibai",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 70);
	set("coor/y", 110);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}