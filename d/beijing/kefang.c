inherit ROOM;

void create()
{
        set("short", "���ͷ�");
        set("long", @LONG
һ���ţ�ֻ�����������ֳֽ䵶��Χ��һ����Ů��ƴ����ɱ��ֻ
�Ǹ�����Ů��������Ʒ��ס�ˣ��۲��������ǰ���Ů��ͷ����ð
��˿˿��������Ȼ�Ѿ���ȫ������ֻһ���۰���֧����ȥ��������
�ֵС����ϰ߰ߵ�㶼��Ѫ����
LONG );
        set("exits", ([
                "west" : "/d/beijing/kediandayuan",
        ]));
        set("objects", ([
                "/d/beijing/npc/dubi" : 1,
                "/d/beijing/npc/lama" : 6,
        ]));
	set("coor/x", -2800);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}