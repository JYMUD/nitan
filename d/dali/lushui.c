//Room: /d/dali/lushui.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","��ˮ�ذ�");
        set("long", @LONG
һ����·������ˮ�ݹ�ȵ��ϱ���������ˮ������ȥ����������
��ˢ�Ź��д�أ��������ѩɽ������ĸ���ɽ�Ը��ʱ��ա���·��
ͨ�˹����Ĵ���͵ĵ飬������������С���䡣
LONG );
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/badidian",
            "south"      : "/d/dali/atoubu",
        ]));
	set("coor/x", -19210);
	set("coor/y", -6880);
	set("coor/z", 20);
	setup();
        (CLASS_D("ultra") + "/huang")->come_here();
}

string long()
{
        object ob;
        string msg;

        msg = query("long");
        if (! objectp(ob = present("huang shang", this_object())))
                return sort_string(msg, 60, 4);

        if (! ob->is_fighting())
                msg += "��һ���ؽ������ⲽ��ʱ����ͷڤ˼��ʱ����ͷԶ"
                       "�����ƺ�����ʲôҪ�������⡣";
        else
                msg += "ֻ��һ��������" +
                       (ob->is_fighting(this_player()) ? "��" : "��") +
                       "��ս������֮�䣬�ɾ�������û��һ�㻨�ɡ�";

        return sort_string(msg, 60, 4);
}