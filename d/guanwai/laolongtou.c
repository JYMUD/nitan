inherit BUILD_ROOM;

void create()
{
        set("short", "����ͷ");
        set("long", @LONG
����ͷ�����ﳤ����ˡ��κ�¥Ρ��߾��ͷ��¥�ϡ��۽������
���ҾӸ����£�ֱ���󺣡��Գκ�¥����һʯ���𼶶�������󺣣�վ��ʯ
���ն�¥ƽ̨������������һɫ���ޱ��޼ʣ�������ǧ��
LONG );
        set("exits", ([
                "northwest" : __DIR__"shanhaiguan",
                "southwest" : "/d/beijing/road3",
        ]));

        set("outdoors", "guanwai");
        set("coor/x", 3950);
	set("coor/y", 9110);
	set("coor/z", 0);
	setup();
}
