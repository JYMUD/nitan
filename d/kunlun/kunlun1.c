inherit ROOM;
void create()
{
        set("short", "����ɽ´");
        set("long", @LONG
��һ����ľ������ɽʯ��ᾣ��������ǲ��㣬ɽ�ϻ�ѩ���񣬵�
·��᫣��������Ƿ�����ת������ɽ�£�����һ�������֡���������
�����������������֦�½��ᡣ
LONG );
        set("no_new_clean_up", 0);
        set("outdoors", "kunlun");
        set("exits", ([ /* sizeof() == 2 */
                "southwest" : __DIR__"kunlun2",
                "northeast" : __DIR__"klshanlu",

        ]));

        setup();
        replace_program(ROOM);
}