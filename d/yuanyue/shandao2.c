inherit ROOM;

void create()
{
        set("short", "ɽ��"); 
        set("long", @LONG
������ȥԲ��ɽׯ��ɽ���ϣ�һ̧ͷ���ֿɿ��������������״��
������ӥ״�ķ��ݸ߸߷�������������С�ɽ�����죬�������ƣ���
���о������Եá�������̽ͷ��ȥ���ѿ���Լ����Բ��ɽׯ��ͭ���
�š�
LONG );
        set("outdoors", "wansong");
        set("type","road");
        set("exits",([
                "north":__DIR__"damen",
                "south":__DIR__"shandao1",
        ]) );
        

        set("coor/x",-590);
        set("coor/y",180);
        set("coor/z",60);
        setup();
} 
