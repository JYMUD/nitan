inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
   �������ҩ���ȵı����ң�����ı������ǹ�ҩ������ƽʱ
�����õģ�����Ӧ�о��С�
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"tulu2",
]));

        set("objects", ([
        "/d/village/obj/zhujian" : 10,
//      WEAPON_DIR"zhui" : 60,
]));

        setup();
        replace_program(ROOM);
}
