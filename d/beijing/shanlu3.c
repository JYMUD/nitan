inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
������ɽ�е�һƬ���֣���ľ�м�����һЩҰ�������ߴ����ľ
��ס�����⡣һ��޴��ʯͷ�������ԡ�
LONG );
        set("exits", ([
                "eastdown" : "/d/beijing/shanlu2",
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7630);
	set("coor/z", 30);
	setup();
        (CLASS_D("ultra") + "/kuihua")->come_here();
}

string long()
{
        object ob;
        string msg;

        msg = query("long");
        if (! objectp(ob = present("kuihua taijian", this_object())))
                return sort_string(msg, 70, 4);

        if (! ob->is_fighting())
                msg += "��һ�������˿���ʯ�ϣ��ճյ�����Զ����һ������"
                       "�ģ�Ҳ��֪���������﾿�����˶�á�";
        else
                msg += "ֻ��һ���������ι��أ����˼������磬������" +
                       (ob->is_fighting(this_player()) ? "��" : "��") +
                       "��ս��";

        return sort_string(msg, 70, 4);
}