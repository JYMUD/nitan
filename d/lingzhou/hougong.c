// Room: /d/lingzhou/hougong.c

inherit ROOM;

void create()
{
        set("short", "��");
        set("long", @LONG
�����ǹ�͢�ĺ󹬣������ûʣ���Χ���ŷۺ�ɫ�ĳ�ɴ��һ�߽���
��ıǶ˾�Ʈ��һ��������������㣬����������е���Գ����������
�����ǹ�Ůֵҹ����Ϣ��ƫ�ͨ��ƫ���ȥ��������԰��
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"piandian",
        ]));
        set("objects", ([
                CLASS_D("lingjiu") + "/li" : 1,
        ]));
        set("no_clean_up", 0);

        set("coor/x", -6265);
        set("coor/y", 2995);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}