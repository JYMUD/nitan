inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������һ�����Ĺ���������ש�̾͵ĵ���ǳ����࣬����
�Ǻ�����ĵ����ˣ�����Ļ���ÿ����������һ�����˴��
�������������ԣ�������������书�����ǵ���֮���������ڴˣ�
���˸о���Ī����ѹ�������治Զ��һ���ש�����ſڻ�������
���ڰ��ء�
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "northeast" : __DIR__"gd6",
  "west" : __DIR__"shufang",
]));

        set("outdoors", "yaowang");
        setup();
}

int valid_leave(object ob,string dir)
{
        if( !wizardp(ob)
        && (dir == "west")
         && (query("family/family_name", ob) != "ҩ����") )
                return notify_fail("��������ҩͯ��ס�����ȥ·��\n");

        return ::valid_leave(ob,dir);
}
