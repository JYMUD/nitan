inherit ROOM;

void create()
{
        set("short", "��ŢС·");
        set("long", @LONG
����һ����С��·��������������¹���һ����Ţ��������
��һЩ���õĿ�֦��Ҷ������Ѭ�졣
LONG
        );
        set("exits", ([
  "southwest" : __DIR__"lcd02",
  "northeast" : "/d/foshan/nanling",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
