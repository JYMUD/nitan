inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
����һ������ʵ���ʯ���̳��ľ���С·��·�����������
�ݣ�·�����Ը���һ��С��̳�����濪�������Ļ��䡣������һ
��С���ţ�������һ����ճ���
LONG
        );
        set("exits", ([
  "east" : __DIR__"myuan",
  "out" : __DIR__"hqdoor",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
