// Room: /d/guiyun/jiugong.c
// Last Modified by winder on Jul. 9 2001

int do_move(object ob);
void init()
{
        object ob=this_player();
        int i, temp, count;

        if( !query_temp("jiugong", ob) )
        {
                set_temp("jiugong", 1, ob);
                set_temp("jiugong_0", 0, ob);
                count = 45;
                for (i = 1; i <= 5; i++)
                {
                        temp = random(10);
                        set_temp("jiugong_"+i, temp, ob);
                        count -= temp;
                }
                for (; i <= 8; i++)
                {
                        temp = random(count > 9 ? 10 : count);
                        set_temp("jiugong_"+i, temp, ob);
                        count -= temp;
                }
                set_temp("jiugong_9", count, ob);
        }
        temp=query_temp("jiugong_"+HERENO, ob);
        if (temp > 0)
                set("long","����һƬï�ܵ��һ��ԣ���һ�߽�������ʧ�˷��򡣵�����"+chinese_number(query_temp("jiugong_"+HERENO, ob))+"���һ�(taohua)��\n");
        else
                set("long","����һƬï�ܵ��һ��ԣ���һ�߽�������ʧ�˷��򡣵���һ���һ�(taohua)Ҳû�С�\n");
        add_action("do_drop", "drop");
        add_action("do_look", "look");
        add_action("do_get", "get");
        add_action("do_inv", "inventory");
        if( query_temp("step_count", ob)>99 )
        {
                do_move(ob);
                return;
        }
        addn_temp("step_count", 1, ob);
        return;
}

int do_move(object ob)
{
        int i;
        if( !objectp(ob) ) return 1;
        delete_temp("step_count", ob);
        write("���������۵þ�ƣ����������������֧�����˹�ȥ��\n");
        write("���Ժ������ƺ����˰��㱳������\n");
        delete_temp("jiugong", ob);
        for (i = 0; i <= 9; i++)
                delete_temp("jiugong_"+i, ob);
        ob->unconcious();
        if( query_temp("jiugong_dir", ob) == "w" )
                ob->move(__DIR__"road4", 1);
        else 
                ob->move(__DIR__"shiqiao", 1);
        message("vision","ȴ����Ӱ��˸�����Ժ�Ȼ�ֳ�һ��ȱ�ڣ�����ׯ����һ�����Բ��ѵļһ����˳�����\n", environment(ob), ob);
        return 1;
}

int do_look(string arg)
{
        object ob=this_player();
        int temp;

        if (!arg) {
                temp=query_temp("jiugong_"+HERENO, ob);
                if (temp > 0)
                        set("long","����һƬï�ܵ��һ��ԣ���һ�߽�������ʧ�˷��򡣵�����"+chinese_number(query_temp("jiugong_"+HERENO, ob))+"���һ�(taohua)��\n");
                else
                        set("long","����һƬï�ܵ��һ��ԣ���һ�߽�������ʧ�˷��򡣵���һ���һ�(taohua)Ҳû�С�\n");
        }
        else if (arg=="west" || arg=="east" || arg=="north" || arg=="south")
                {
                        write("�㿴�����Ǳߵ������\n");
                        return 1;
                }
        ob->look(arg);
}

string inv_desc(object ob)
{
        return sprintf("%s%s",
                query("equipped", ob)?HIC"��"NOR:"",
                ob->short()
        );
}

int do_inv(string arg)
{
        int temp;
        object *inv;
        object ob = this_player();

        if( arg && arg != query("id", ob))return 0;

        inv = all_inventory(ob);
        temp=query_temp("jiugong_0", ob);
        if (temp > 0)
                printf("�����ϴ���������Щ����(����%d%%)��\n"+chinese_number(query_temp("jiugong_0", ob))+"���һ�(taohua)\n%s\n",ob->query_encumbrance()*100/ob->query_max_encumbrance(),implode(map_array(inv,"inv_desc",this_object()),"\n"));
        else
                printf("�����ϴ���������Щ����(���� %d%%)��\n%s\n", (int)ob->query_encumbrance() * 100 / (int)ob->query_max_encumbrance(), implode(map_array(inv, "inv_desc", this_object()), "\n") );
        return 1;
}

int do_get(string arg)
{
        int amount, herenum;
        string taohua;
        object ob=this_player();

        if (!arg || sscanf(arg, "%d %s", amount, taohua) != 2)
                return 0;
        if (taohua != "taohua") return 0;
        
        herenum=query_temp("jiugong_"+HERENO, ob);
        if (herenum < 1) return notify_fail("�������û���һ���\n");
        if (amount > herenum) return notify_fail("����û����ô�����һ���\n");
        set_temp("jiugong_"+HERENO, herenum-amount, ob);
        addn_temp("jiugong_0", amount, ob);
        write("�����" + chinese_number(amount) + "���һ���\n");
        return 1;
}        

int do_drop(string arg)
{
        int i, amount;
        int *num = ({0,0,0,0,0,0,0,0,0,0});
        string taohua;
        object ob=this_player();

        if (!arg || sscanf(arg, "%d %s", amount, taohua) != 2)
                return 0;
        if (taohua != "taohua") return 0;
        
        for (i = 0; i <= 9; i++)
                num[i]=query_temp("jiugong_"+i, ob);
        if (num[0] < 1) return notify_fail("��ı��������û���һ���\n");
        if (amount>num[0]) return notify_fail("��ı�����û����ô�����һ���\n");
        num[HERENO] += amount;
        num[0] -= amount;
        set_temp("jiugong_"+HERENO, num[HERENO], ob);
        set_temp("jiugong_0", num[0], ob);
        write("�㶪��" + chinese_number(amount) + "���һ���\n");
        if (num[0] == 0)
        {
                if (num[1] + num[2] + num[3] == 15 &&
                        num[4] + num[5] + num[6] == 15 &&
                        num[7] + num[8] + num[9] == 15 &&
                        num[1] + num[4] + num[7] == 15 &&
                        num[2] + num[5] + num[8] == 15 &&
                        num[3] + num[6] + num[9] == 15 &&
                        num[1] + num[5] + num[9] == 15 &&
                        num[3] + num[5] + num[7] == 15)
                {
                        write( "�һ����к�Ȼ����һ��������������������ֳ�һ����·�����æ���˳�ȥ��\n");
                        delete_temp("jiugong", ob);
                        delete_temp("step_count", ob);
                        if( query_temp("jiugong_dir", ob) == "w" )
                        {
                                tell_room(__DIR__"shiqiao","ȴ����Ӱ��˸�����Ժ�Ȼ�ֳ�һ��ȱ�ڣ�" + ob->name() + "���������\n", ({}));
                                ob->move(__DIR__"shiqiao");
                        }
                        else
                        {
                                tell_room(__DIR__"road4","ȴ����Ӱ��˸�����Ժ�Ȼ�ֳ�һ��ȱ�ڣ�" + ob->name() + "���������\n", ({}));
                                ob->move(__DIR__"road4");
                        }
                }
        }
        return 1;
}
