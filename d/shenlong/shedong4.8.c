inherit ROOM;

void create()
{
        set("short", "�߾�����");
        set("long",@LONG
�����߾����⣬����ǰ�߾�Ҫ�����߾����ˣ���˵����û�����ܻ���
�߳��߾�����
LONG);


	set("exits", ([
		"north"  : __DIR__"shedong4.7",		
		"enter"   : __DIR__"shejingdong",
	]));

	// Ϊȷ��100%��ȫ������Ҳ��������
	set("no_die", 1);
	
        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        object env;

	// ����Ƿ��Ѿ���ʼ�߾�ս��
        if (dir == "enter")
        {
                //return notify_fail("�Բ�����ʦ��û������ţ�����ʱ���ܲμӶԿ��߾���ս����\n");
        	
        	ob = find_living("jiutou shejing");
        	
        	if (objectp(ob) && environment(ob))
        	{
        		if (base_name(environment(ob)) == "/d/shenlong/shejingdong")
        		{
        			write("�Բ��������Ѿ���ʼ�˶Կ��߾���ս����\n");
        			return 0;
        		}
        	}
        	
        	if (! objectp(env = find_object(__DIR__"shejingdong")))
        		env = load_object(__DIR__"shejingdong");
        		
        	// �����峡���ܽ���
        	if( query("doing", env) )
       		{
       			write("�߾�BOSS�Ѿ���ս���������ڵȴ��峡�����Ժ����ԣ�\n");
       			return 0;
       		}
        	
        }

        return 1;
}
