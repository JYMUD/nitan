// Room: /d/taishan/zhengqi.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ƿ���̨�ұߵ��������������˷���ʹ��ƽʱ����ɽʱ��
ͨ�����������ﴦ�����ֹ������������з��Űѻ�Ƥ�Σ�����ʹ��
���������濪���������Ҹ������ż�λ������ʿ������ȥɱ����
�ڣ�������Ȼ�������⡣
LONG );
        set("exits", ([
                "east" : __DIR__"fengchan",
        ]));
        set("objects",([
                __DIR__"npc/wei-shi2" : 3,
        ]));
        set("coor/x", 20);
	set("coor/y", 310);
	set("coor/z", 220);
	setup();
        FAE->come_here();
}
void reset()
{
        ::reset();
        FAE->come_here();
}