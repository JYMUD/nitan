inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
���˻��ԣ���ǰ��һ��С������������Խ��Խ�࣬�򻨻�ס����
���ϣ��������衣����Ҳ��η�ˣ��ɽ�ʱ������ͷ�ϡ����ϡ�����ͣ����
�е����磬ֻ��һ����Ϫ�Խ����ߡ��˼�é�ݣ�é��֮ǰ�Ǽ��黨�ԣ�
��������㻨�ݡ�é��֮���Ǻô��һƬ��԰��ֻ�ǿ�����һ���ư���
���롺����ҽ�ɡ�����ͷ�ⲻ��ơ�
LONG
	);
       set("outdoors", "mingjiao");
       set("no_fight",1);
       set("no_steal",1);
       set("no_beg",1);

	set("exits", 
	([
		"southeast" : "/d/mingjiao/diecong1",
          	"south" : __DIR__"huapu",
          	"north" : __DIR__"guoyuan",

	]));
        set("objects", 
	([
		__DIR__"huqingniu" : 1,
	]));
    
	setup();
}
