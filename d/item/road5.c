// road5.c С��

inherit ROOM;

void create()
{
        object ob;

        set("short", "С��");
        set("long", @LONG
����һ�����ѵ�С������������ͨ��ɽ�·����һ��Сש������Ͳ
����ʱ��ʱð��һ�ɹɺ��̣���������Щ���ܣ���һʱ�̲�ס���������
�硣�����洫��������ô����������������Ǹ������Ǵ���˵�����ͷ��
�����̡�
LONG );

        set("exits", ([
                "west"  : __DIR__"road4",
                "enter" : __DIR__"xiaowu",
        ]));
        set("outdoors", "suzhou");
        set("coor/x", 900);
        set("coor/y", -1060);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}