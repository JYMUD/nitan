inherit ROOM;
void create()
{
        set("short", "����յ�");
        set("long", @LONG
���ǳ���Ŀյأ�һЩ�ɹű��ļ�ϸ�ͼ��ֳ��������߮����Ѱ
�����Ǹ���Ȥ�������ʱ�м�ö�����ͷ��ವطɹ������˷���ʤ
����
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);
        set("step",2);
        set("no_fly",1);     
        set("exits", ([
               "east" : __DIR__"east_out5", 
               "west" : __DIR__"east_out3", 
        ]));
        set("coor/x", -7820);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
}