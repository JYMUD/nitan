inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
���ŷ������������ʣ���ݵ���ʩ��Ȼ��ª��ȴ��һ����
��ȥ����������������̸��˵�أ����������������������
�������£����Գ���������û�¶�����������һ�������ϼ�
��ˮ�̣����ϵر������ġ�
LONG);
        set("resource/water", 1);
        set("exits", ([
                "west" : __DIR__"nandajie2",
        ]));

        set("objects", ([
                __DIR__"npc/chaxiaoer" : 1,
                __DIR__"npc/obj/yantong":1,
        ]));

	set("coor/x", -16830);
	set("coor/y", -7230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}