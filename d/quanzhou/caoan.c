// Room: /d/quanzhou/caoan.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������������Ħ��ʯ��������Բ����ü��¡��ɢ�����磬����
����ɮ�£�˫��������������ϥ�ϣ���̬ׯ�ϣ���߷�ɡ���ǰԼ����
������ʯ�������п��������Ȱ����徻�����������ǻۣ�������
�棬Ħ���𡻡�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out"   : __DIR__"shangu",
        ]));
	set("coor/x", -931);
	set("coor/y", -7741);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}