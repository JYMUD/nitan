// Room: /d/lingzhou/bingku.c

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����ǻʹ��ﴢ��ʳ������ڣ��������㣬������������ž޴��
���顣ƽʱ����������ֻ�������ʱ�����ŷ�����ż����ˡ�
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "north" : __DIR__"yushanfang",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -6265);
        set("coor/y", 2975);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}