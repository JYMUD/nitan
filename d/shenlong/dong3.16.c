inherit ROOM;

void create()
{
        set("short", "���涴��");
        set("long",@LONG
�������������涴�⣬��˵���ڳ������ֶ��棬��˵����ס��һ
ֻ������ޣ�����û���˼�����
LONG);

	set("exits", ([
		"enter"   : __DIR__"huodong1",
		"west"   : __DIR__"dong3.15",

	]));

	// δȷ��100%��ȫ��������Ҳ��������
	set("no_die", 1);
	
        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        object env;

	// ����Ƿ��Ѿ���ʼ����ս��
        if (dir == "enter")
        {
                //return notify_fail("�Բ�����ʦ��û������ţ�����ʱ���ܲμӶԿ��������ս����\n");

        	ob = find_living("huo qilin");
        	
        	if (objectp(ob) && environment(ob))
        	{
        		if (base_name(environment(ob)) == "/d/shenlong/huodong1")
        		{
        			write("�Բ��������Ѿ���ʼ�˶Կ��������ս����\n");
        			return 0;
        		}
        	}
        	
        	if (! objectp(env = find_object(__DIR__"huodong1")))
        		env = load_object(__DIR__"huodong1");
        		
        	// �����峡���ܽ���
        	if( query("doing", env) )
       		{
       			write("������BOSS�Ѿ���ս���������ڵȴ��峡�����Ժ����ԣ�\n");
       			return 0;
       		}
        }

        return 1;
}
