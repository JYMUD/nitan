// Room: /d/taishan/xiayi.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ƿ���̨��ߵ�������������������ʹ��ƽʱ����ɽʱ��
ͨ������������������ֹ������������з��Ű�̫ʦ�Σ�����ʹ��
���������濪���������Ҹ������ż�λ������ʿ������ȥ������
�ݣ�����һ��ׯ������
LONG );
        set("exits", ([
                "west" : __DIR__"fengchan",
        ]));
        set("objects",([
                __DIR__"npc/wei-shi2" : 3,
        ]));
        set("coor/x", 40);
	set("coor/y", 310);
	set("coor/z", 220);
	setup();
        SHANGSHAN->come_here();
}

void reset()
{
        ::reset();
        SHANGSHAN->come_here();
}