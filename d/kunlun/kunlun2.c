inherit ROOM;

void create()
{
        set("short", "����ɽ´");
        set("long", @LONG
    ����������ֻ�з紵���Σ�������ɣ����Ӳ��죬ע��Ⱥɽ����
�˲�����Ȼ����˼��֮���飡��ǰ����ֻ��һ�����ң����پ��£���
�¿����ͱ��絶�����ƾ���ӿ������ס�
LONG );
        set("no_new_clean_up", 0);
        set("outdoors", "kunlun");

        set("exits", ([ /* sizeof() == 3 */
                "northeast" : __DIR__"kunlun1",
                "up" : __DIR__"kunlun3",
        ]));

        setup();
        replace_program(ROOM);
}