inherit ROOM;

void create()
{
        set("short", "��ŢС·");
        set("long", @LONG
����һ����С��·��������������¹���һ����Ţ��������
��һЩ���õĿ�֦��Ҷ������Ѭ�졣
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "northeast" : __DIR__"lcd01",
  "southwest" : __DIR__"lcd03",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
