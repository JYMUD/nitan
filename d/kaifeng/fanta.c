inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�������ڷ�̨֮�ϣ�����һ�����ǾŲ㣬��ʮ���׸ߵľ��ͷ�����
��Ϊ׳�ۡ���ʫԻ��̨�ߵ��ĳ����죬�����ʶ�ʮ�ﴺ����������ʮ
���ף���ש����ש���о����ķ��񣬹���һ������֣���ǧ������
�ڴ���һ����ʮ�˿�𾭱��̡�
LONG );
        set("outdoors", "kaifeng");
        set("exits", ([
                "east" : __DIR__"zhulin",
                "west" : __DIR__"jiedao2",
        ]));

        set("no_clean_up", 0);
	set("coor/x", -5030);
	set("coor/y", 2140);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}