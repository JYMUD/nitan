#include <ansi.h>
#include <localtime.h>

void do_kaijiang(string type);
void time_go();

object cpb;

void create()
{
        time_go();
}

string record_time(int time)
{
        int t, y, mo, d, h, m, s;
        mixed *ltime;
        string ctime;

        ltime = localtime(time);
        s = ltime[LT_SEC];
        m = ltime[LT_MIN];
        h = ltime[LT_HOUR];
        d = ltime[LT_MDAY];
        mo = ltime[LT_MON]+1;
        ctime = "";
        ctime += chinese_number(mo) + "��";
        ctime += chinese_number(d) + "��";
        ctime += chinese_number(h) + "ʱ";
        ctime += chinese_number(m) + "��";
        ctime += chinese_number(s) + "��";
        return ctime;
}

void time_go()
{
        object *cpbs;
        int i, j;

        i = time();
        cpbs = children("/clone/misc/caipiao_ban");
        cpbs -= ({ find_object("/clone/misc/caipiao_ban") });
        if ( !sizeof(cpbs) )
        {
                cpb = new("/clone/misc/caipiao_ban");
                if ( !objectp(cpb) ) return;
                cpb->move("/d/city/caipiao");
        }
        else if ( sizeof(cpbs) > 1 )
        {
                cpb = cpbs[0];
                for ( j=1; j<sizeof(cpbs); j++ )
                {
                        destruct(cpbs[j]);
                }
        }
        else
                cpb = cpbs[0];

        remove_call_out("time_go");
        call_out("time_go", 1);

        cpb->restore();

        if( query("kaijiang_date", cpb) && (i>query("kaijiang_date", cpb) || i == query("kaijiang_date", cpb)) )
                do_kaijiang("kaijiang");
        else if( query("end_date", cpb) && (i>query("end_date", cpb) || i == query("end_date", cpb)) )
                do_kaijiang("end");
        else if( query("start_date", cpb) && (i == query("start_date", cpb) || i>query("start_date", cpb)) )
                do_kaijiang("start");
        if( !query("start_date", cpb) && !query("kaijiang_date", cpb) )
                do_kaijiang("start");
        i=0;
}

void do_kaijiang(string type)
{
        int i,z,p=0;
        int *jieguo=({});
        string str="";

        if (type=="kaijiang")
        {
                cpb->restore();
                message("sendto_alluser",HIW"����̶���ʡ������潫�������ڲ�Ʊ�󽱣�\n"NOR,users());
                i=0;
                z=0;
                while(p!=7)
                {
                        i=random(30)+1;
                        if(member_array(i,jieguo)!=-1) continue;
                        else
                        {
                                jieguo+=({i});
                                p++;
                        }
                }
                for(i=0;i<sizeof(jieguo);i++)
                        str+=jieguo[i]+" ";

                message("system",HIW"����̶���ʡ�����"+chinese_number(query("times", cpb))+"�ڶҽ�����Ϊ"+BLINK+HIR+str+"��\n"NOR,users());
                message("system",HIW"����̶���ʡ�������ȥ���ݶĳ���ƱͶע����read biao���鿴�ý�������\n"NOR,users());

                set("last_z_num", jieguo, cpb);
                set("last_z_num_str", str, cpb);
                set("duijiang", 1, cpb);
                delete("kaijiang_date", cpb);
                delete("kaijiang_cdate", cpb);
                delete("end_date", cpb);
                delete("end_cdate", cpb);
                addn("times", 1, cpb);
                set("start_date", (time()+2*60*60*24)/60*60, cpb);
                set("start_cdate", record_time((time()+2*60*60*24)/60*60), cpb);
                cpb->save();
                cpb->show_player();
                set("last_gold",query("all_gold",  cpb), cpb);
                if (!query("zhongjiang_num", cpb)) addn("all_gold",50000,cpb);
                else set("all_gold",500000, cpb);
                cpb->save();

                message("system",HIW"����̶���ʡ������ڲ�Ʊ����"+query("start_cdate", cpb)+"��ʼ���У���ӭ����\n"NOR,users());
                message("system",HIW"����̶���ʡ�����"+chinese_number(query("times", cpb))+"��Ԥ�ƽ���"+chinese_number(query("all_gold", cpb))+"���ƽ�\n"NOR,users());
                cpb->auto_post(
                        sprintf(HIR"����̶���ʡ������ڲ�Ʊ��������Ϊ"+str+"��"NOR),
                        sprintf("�н��������£�%s",cpb->show_player()),
                );
                rm("/data/caipiao/call");
                write_file("/data/caipiao/call",sprintf(
                        "���ĳ���Ϣ�������ڲ�Ʊ���ѿ������ҽ�����Ϊ"+str+"\n" +
                        "���ĳ���Ϣ�������ڲ�Ʊ����"+query("start_cdate", cpb)+"��ʼ���У���ӭ����\n"+
                        "���ĳ���Ϣ�������ڲ�ƱԤ�ƽ���"+chinese_number(query("all_gold", cpb))+"���ƽ�\n"));
                return;
        }
        else if(type=="end" )
        {
                cpb->restore();
                set("end_ya", 1, cpb);
                delete("start_date", cpb);
                delete("start_cdate", cpb);
                delete("end_date", cpb);
                delete("end_cdate", cpb);
                cpb->save();
                message("system",HIW"����̶���ʡ������ڲ�Ʊֹͣ�������ע���������\n"NOR,users());
                message("system",HIW"����̶���ʡ������ڲ�Ʊ����"+query("kaijiang_cdate", cpb)+"������\n"NOR,users());
                rm("/data/caipiao/call");
                write_file("/data/caipiao/call",sprintf(
                        "���ĳ���Ϣ�������ڲ�Ʊ��ֹͣ�������ע���������\n" +
                        "���ĳ���Ϣ�������ڲ�Ʊ����"+query("kaijiang_cdate", cpb)+"������\n"));
                return;
        }
        else if(type=="start")
        {
                cpb->restore();
                cpb->clean_data();

                if (!query("all_gold", cpb))
                        set("all_gold",500000,cpb);

                message("system",HIW"����̶���ʡ�����"+chinese_number(query("times", cpb))+"�ڲ�Ʊ��ʼ���У���ӭ���ǰ������\n"NOR,users());
                message("system",HIW"����̶���ʡ�����"+chinese_number(query("times", cpb))+"��Ԥ�ƽ���"+chinese_number(query("all_gold", cpb))+"���ƽ�\n"NOR,users());

                delete("end_ya", cpb);
                delete("duijiang", cpb);
                delete("last_z_num", cpb);
                delete("last_z_num_str", cpb);
                delete("start_date", cpb);
                delete("start_cdate", cpb);
                set("kaijiang_cdate", record_time((time()+3*60*60*24)/60*60), cpb);
                set("kaijiang_date", (time()+3*60*60*24)/60*60, cpb);
                set("end_cdate", record_time((time()+70*60*60)/60*60), cpb);
                set("end_date", (time()+7*60*60*10)/60*60, cpb);
                cpb->save();
                cpb->restore();

                message("system",HIW"����̶���ʡ�����"+chinese_number(query("times",cpb))+"�ڲ�Ʊ����"+query("end_cdate", cpb)+"ֹͣ���С�\n"NOR,users());
                rm("/data/caipiao/call");
                write_file("/data/caipiao/call",sprintf(
                        "���ĳ���Ϣ������"+chinese_number(query("times", cpb))+"�ڲ�Ʊ�Ѿ����У���ӭ���ǰ������\n" +
                        "���ĳ���Ϣ������"+chinese_number(query("times", cpb))+"���ۼƽ���"+chinese_number(query("all_gold", cpb))+"���ƽ�\n" +
                        "���ĳ���Ϣ������"+chinese_number(query("times", cpb))+"�ڲ�Ʊ����"+query("end_cdate", cpb)+"ֹͣ���С�\n"));
                return;
        }
        return;
}
