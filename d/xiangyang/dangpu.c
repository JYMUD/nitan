// Room: /d/xiangyang/dangpu.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���Ǽ�Զ�������ĵ��̣�����������棬һ��д�š��񺽵��̡�
�ĸ����ֵĺ��ң������߳߸ߵ���̴ľ�Ĺ�̨��ĥ�ù�����ˣ���һ
��ȥ����һ��ѹ�ֺͱ���ĸо�����̨����ϰ���ͷҲ��̧��ֻ��
���������̣���̨�Ϸ�����һ�黨ľ����(paizi) ���ݽַ���˵����
���̸��ļۻ�����������ҴӲ��ʻ������������˻���ʲô���գ�
��������ܲ���
LONG );
        set("item_desc", ([
                "paizi" : "��ƽ����\n
sell        �� 
buy         ��
pawn        ��
expiate     ��
value       ����
",
        ]));

        //set("no_fight", 1);
        set("no_beg", 1);
        set("exits", ([
                "north" : __DIR__"westjie1",
        ]));
        set("objects", ([
                __DIR__"npc/qiuhang" : 1,
        ]));
        set("coor/x", -7830);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
