inherit ROOM;

void create()
{
        set("short", "ʦү��");
        set("long", @LONG
һ�߽�ʦү�����ӣ��ͼ�ʦү�����������ǵ�ɢ����һЩ
�Ǻ͹Ϲ�������Ĵ�ǽ������һ�Ŵ�ĸ�ʾ��ʦү���е�����
̫ʦ���ϡ�
LONG);
        set("exits", ([
                "south" : __DIR__"zoulang1",                 
        ]));

        set("coor/x", -9060);
	set("coor/y", -950);
	set("coor/z", 0);
	setup();
}