inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
��������ʯ���̳ɵ�ʯ���ϡ�������Ǵ�˵�����صİ���ɽ��Զ
Զ��ȥ��������ɳ�ѻ��γɵ�ɽ�����һֻ���յļ�����һ��ɽ����
�������ǰ��
LONG );
        set("exits", ([
                "east"      : __DIR__"caoping",
                "northup"   : __DIR__"damen",
                "southdown" : __DIR__"guangchang" ,
        ]));
        set("outdoors", "baituo");
        set("coor/x", -49980);
        set("coor/y", 19990);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}