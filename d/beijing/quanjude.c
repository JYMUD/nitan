inherit ROOM;

void create()
{
        set("short", "ȫ�۵¾�¥");
        set("long", @LONG
������Ǿ�������Ϊ������ȫ�۵¾�¥����Բ������������ȫ��
�¾�¥�Ŀ�Ѽ����˵�����˲�֪�����˲�����¥������˽ǣ���ľ��
�أ����������������ϻ����ż�����������װ��������Ż�������
С������һ�������ľ�ǻ������к��ſ��ˡ���¥��ǽ����һ��¥�ݣ�
ͨ��ȫ�۵¾�¥��¥��������
LONG );
        set("exits", ([
                "south" : "/d/beijing/wang_10",
                "up"   : "/d/beijing/quanjudeup",
        ]));
        set("objects", ([
                "/d/beijing/npc/xiaoer1" : 1,
        ]));

	set("coor/x", -2770);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}