inherit ROOM;

void create()
{
        set("short", "ˮ��");
        set("long", @LONG
������һƬ����Ĳݵأ�����ϡϡ����ĳ��ż������񣬲�
��������һ�ھ������ߵ�����Ϲ���һֻ��ˮ(fill)��ľͰ����
�ֵ��Ǿ�̨�ĵ�ʯͷ�ϲ�֪����˭Ū���˺���������ɫ��
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"xiaoyuan",
]));

        set("outdoors", "yaowang");

        set("resource", ([
        "water" : 1,            // ��ˮ���
        "condition" : "scorpion_poison",   // ˮ���ж�

        "count" : 12,           // ����ʱ��
        "time" : -1,            // ˮ�ж�����Чʱ�䣬-1 ������Զ��Ч
]));

        setup();
        replace_program(ROOM);
}
