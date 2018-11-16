// quest.c

#include <ansi.h>
 
inherit F_CLEAN_UP;
string time_period(int timep);

int main(object me, string arg)
{
        object ob,env;
        mapping q,quest;
        string master,msg,*place;
        int tag_fam = 0;
        int flag_zs = 0;
        int flag_bh = 0;
        int i;

        while (arg)
        {
                if (arg == "cancel")
                {
                        if( !stringp(master=query("quest/master_id", me)) )
                                return notify_fail("������������������\n");

                        if (! objectp(ob = present(master, environment(me))))
                                return notify_fail("������������Ǹ������ڲ�������ɣ�\n");
                } else
                if (! objectp(ob = present(arg, environment(me))))
                        return notify_fail("����û������ˣ�����ô������\n");

                if (! living(ob))
                        return notify_fail("�㻹�ǵ�" + ob->name() +
                                           "������˵�ɣ�\n");

                if (me->is_fighting())
                        return notify_fail("ר�Ĵ���ļܣ�\n");

                if (me->is_busy())
                        return notify_fail("�㻹���п����ٺ�" + ob->name() +
                                           "̸��Щ����ɣ�\n");

                if (ob->is_fighting())
                        return notify_fail("�㻹�ǵ�" + ob->name() +
                                           "�������˵�ɣ�\n");

                if (ob->is_busy())
                        return notify_fail(ob->name() +
                                           "��æ���أ�û�������㡣\n");

                notify_fail(ob->name() + "������Ǻǵ�ɵЦ��\n");
                return (arg == "cancel" ? ob->cancel_quest(me)
                                        : ob->ask_quest(me));
        }
        write(HIR + "�������ϵͳ��\n" + NOR);
        if( query_temp("finish_bunch_times", me) )
                write(sprintf("ͷ����������������Ѿ���������� %d ����\n",
                       query_temp("finish_bunch_times", me)));

        msg = "";
             if( mapp(quest=query("bunch_quest", me)) )
         {
                flag_bh = 1;
                msg = quest["type"] + "��" + quest["msg"];
                write("��ղ��������\n"+msg+"\n");
                if (quest["id"] == "xc")
                {
                        place = ({});
                        place = quest["place"];
                        if (sizeof(place))
                        {
                                msg = "�㻹��ҪѲ����Щ�ط���";
                                for (i = 0;i < sizeof(place);i++)
                                {
                                        env = get_object(place[i]);
                                        msg += env->short() + " ";
                                }
                                write(msg + "\n");
                        } else write("����Ի�ȥ�����ˣ�\n");
                }
         }

        if (!flag_bh) write("��Ŀǰû�дӰ�����������\n");

        write(HIR + "\n��������ϵͳ��\n" + NOR);
        if( query("quest_count", me) )
                write(sprintf("ʦ����������������Ѿ���������� %d ����\n",
                       query("quest_count", me)));
 
        if( mapp(q=query("quest", me)) )
        {
                 switch (q["type"])
                { 
                  case "kill":
                        write(q["master_name"] + "�Ը�����" + CHINESE_D->chinese_monthday(q["limit"]) +
                      "֮ǰ����" HIR + q["name"] + NOR "����ͷ����" + q["family"] + "���\n" +
                      "��˵����ǰ����������" + q["place"] + "��û��\n");
                      tag_fam = 1;
                      break;
                case "letter":
                      write(q["master_name"] + "�Ը�����" + CHINESE_D->chinese_monthday(q["limit"]) +
                      "֮ǰ���ż��͵�" HIC + q["name"] + NOR "���У�ȡ��ִ���\n" +
                      "���Ų���ǰ����������" + q["place"] + "��\n");
                      tag_fam = 1;
                      break;
                }
        }
        if (!tag_fam) write("������û�����κ���������\n");
        
        write(HIR + "\n��ʦ����ϵͳ��\n" + NOR);

        if( query("questdg_times", me) )
                     write("������ܽ���������������������"+query("questdg_times", me)+"���ˡ�\n");
        if( query("questkh_times", me) )
                     write("����̫�ཻ��������������������"+query("questkh_times", me)+"���ˡ�\n");
        if( query("questsn_times", me) )
                     write("�Ϻ����ύ��������������������"+query("questsn_times", me)+"���ˡ�\n");;
        if( query("quesths_times", me) )
                 write("���ѽ���������������������"+query("quesths_times", me)+"���ˡ�\n");

        msg = "";
        // �������
         if( mapp(quest=query("quest_dg", me)) )
         {
                flag_zs = 1;
                msg = quest["dgmsg"];
                write("��ղ��������\n"+msg+"\n");
         }

         msg = "";
        // ��������
        if( mapp(quest=query("quest_kh", me)) )
         {
                flag_zs = 1;
                        msg = quest["khmsg"];
                if (quest["desc"] == "��")
                           if(quest["time"] < time())
                                     msg += "\n���Ѿ������˹涨ʱ���ˣ�";
                             else
                                            msg += "\n�㻹��"+time_period(quest["time"]-time())+"��ʱ�䡣";
                write("��ղ��������\n"+msg+"\n");
         }

        msg = "";
        // ����
         if( mapp(quest=query("quest_hs", me)) )
         {
                flag_zs = 1;
                msg = quest["msg"];
                if (quest["type"] == "��")
                {
                                     msg += "\n���Ѿ������" + quest["ok"] + "����";
                                            msg += "\n�㻹��Ҫ��" + (quest["want"] - quest["ok"]) + "����";
                }
                write("��ղ��������\n"+msg+"\n");
         }

        msg = "";
        // �Ϻ�����
         if( mapp(quest=query("quest_sn", me)) )
         {
                flag_zs = 1;
                msg = quest["msg"];
                if (quest["type"] == "��")
                {
                                     msg += "\n���Ѿ������" + quest["ok"] + "����";
                                            msg += "\n�㻹��Ҫ��" + (quest["want"] - quest["ok"]) + "����";
                }
                write("��ղ��������\n"+msg+"\n");
         }

        if (!flag_zs) write("��Ŀǰû�д��κ���ʦ���������\n");
        return 1;
}

string time_period(int timep)
{
   int t, d, h, m, s;
   string time;
   t = timep;
   s = t % 60;             t /= 60;
   m = t % 60;             t /= 60;
   h = t % 24;             t /= 24;
   d = t;
 
   if(d) time = chinese_number(d) + "��";
   else time = "";
 
   if(h) time += chinese_number(h) + "Сʱ";
   if(m) time += chinese_number(m) + "��";
   time += chinese_number(s) + "��";
   return time;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : quest  ���ָ�����������������ɵ����Ż����ҳ���
��ȡ������������κβ�������ʾ���㵱ǰ������

����ʦ������ȡ����ֻ��Ҫ����ʦ���ڵط�����quest������Ҫ���κ�
������

HELP );
        return 1;
}