inherit ROOM;

void create()
{
        set("short", "��Ϣ��");
        set("long", @LONG
����һ��ҩ�̣�һ��ŨŨ��ҩζ���㼸����Ϣ�����Ǵ�ҩ���ϵ�
���ٸ�С������ɢ�������ġ���ҽƽһָ���ڲ輸�Զ��Ժ��Ų裬��
Ҳ������һ�ۡ�
LONG );
        set("exits",([
                "south" : __DIR__"changlang",
        ]));

        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_steal", 1);

        set("coor/x", -49990);
        set("coor/y", 20030);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}