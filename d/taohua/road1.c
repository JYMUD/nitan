inherit ROOM;
 
void create()
{
        set("short", "С·");
        set("long", @LONG
����һ��С��������������Զ�����졣С��������ֲ��һЩ�һ�����
��ֻһƳ�ͷ��֣���Щ�һ�ȫ�ǰ�ɫ�ġ�
LONG );
        set("exits", ([
                "east"  : __DIR__"road2",
                "south" : __DIR__"mudi",
        ]));
        
        set("outdoors", "taohua");
 
        set("coor/x", 8970);
        set("coor/y", -2940);
        set("coor/z", 0);
        setup();
}