inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������һ�����Ŀճ����ճ��������ŵ�һ���ľ����д��
һ�����ġ��䡱�֡���������������������ġ�Ʒҩ�ݣ�
һλһ����µ������˱������Ĵ�Ѳ��ָ�㡣
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"fyuan",
]));

        set("objects", ([
                __DIR__"npc/buwawa" : 1,
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
