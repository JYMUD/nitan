//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{

        set ("short", "Ԫ���");
        set ("long", @LONG
����ԭ������ۣ������ƿ�Ԫ��䣬ԭ���ھ��ݳ���������Ǩ���ˡ�
Ϊ�ܿ����ʵ�����֮���䣬����������Ϊ��Ԫ������ǰһ���Ľ��ܼⶥ
������¥������ʸ󣬺������������ڳ�̨֮�ϣ��������£�Ρ��
ׯ�ϡ�
LONG);
        set("exits", ([ 
                "north" : __DIR__"xxend",
        ]));
  
        set("no_clean_up", 0);
        set("coor/x", -7080);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}