inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
���ﳤ���˸ߴ����ľ��������ڰ�ִ����ľ��
����ľ����ӳ�£�����Ҳ�谵����������С��������
��������ȥ��ʹ��������˲���������
LONG);
        set("exits", ([
                "west" : __DIR__"zhulin",
                "north" : __DIR__"beishulin",
        ]));

        set("xinshoucun", 1);
            set("outdoors", "newbie");

           set("objects", ([
                "/clone/quarry/tu" : 40 + random(30),
           ]));
        setup();

        replace_program(ROOM);
}