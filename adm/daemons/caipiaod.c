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
        ctime += chinese_number(mo) + "月";
        ctime += chinese_number(d) + "日";
        ctime += chinese_number(h) + "时";
        ctime += chinese_number(m) + "分";
        ctime += chinese_number(s) + "秒";
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
                message("sendto_alluser",HIW"〖泥潭福彩〗：下面将开出本期彩票大奖！\n"NOR,users());
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

                message("system",HIW"〖泥潭福彩〗：第"+chinese_number(query("times", cpb))+"期兑奖号码为"+BLINK+HIR+str+"！\n"NOR,users());
                message("system",HIW"〖泥潭福彩〗：可以去扬州赌场彩票投注中心read biao来查看得奖名单。\n"NOR,users());

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

                message("system",HIW"〖泥潭福彩〗：下期彩票将于"+query("start_cdate", cpb)+"开始发行，欢迎购买。\n"NOR,users());
                message("system",HIW"〖泥潭福彩〗：第"+chinese_number(query("times", cpb))+"期预计奖金"+chinese_number(query("all_gold", cpb))+"两黄金。\n"NOR,users());
                cpb->auto_post(
                        sprintf(HIR"〖泥潭福彩〗：本期彩票开奖号码为"+str+"！"NOR),
                        sprintf("中奖名单如下：%s",cpb->show_player()),
                );
                rm("/data/caipiao/call");
                write_file("/data/caipiao/call",sprintf(
                        "〖赌场消息〗：本期彩票大奖已开出，兑奖号码为"+str+"\n" +
                        "〖赌场消息〗：下期彩票将于"+query("start_cdate", cpb)+"开始发行，欢迎购买。\n"+
                        "〖赌场消息〗：下期彩票预计奖金"+chinese_number(query("all_gold", cpb))+"两黄金。\n"));
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
                message("system",HIW"〖泥潭福彩〗：本期彩票停止购买，请关注开奖结果！\n"NOR,users());
                message("system",HIW"〖泥潭福彩〗：本期彩票将于"+query("kaijiang_cdate", cpb)+"开奖！\n"NOR,users());
                rm("/data/caipiao/call");
                write_file("/data/caipiao/call",sprintf(
                        "〖赌场消息〗：本期彩票已停止购买，请关注开奖结果！\n" +
                        "〖赌场消息〗：本期彩票将于"+query("kaijiang_cdate", cpb)+"开奖！\n"));
                return;
        }
        else if(type=="start")
        {
                cpb->restore();
                cpb->clean_data();

                if (!query("all_gold", cpb))
                        set("all_gold",500000,cpb);

                message("system",HIW"〖泥潭福彩〗：第"+chinese_number(query("times", cpb))+"期彩票开始发行，欢迎大家前来购买。\n"NOR,users());
                message("system",HIW"〖泥潭福彩〗：第"+chinese_number(query("times", cpb))+"期预计奖金"+chinese_number(query("all_gold", cpb))+"两黄金。\n"NOR,users());

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

                message("system",HIW"〖泥潭福彩〗：第"+chinese_number(query("times",cpb))+"期彩票将于"+query("end_cdate", cpb)+"停止发行。\n"NOR,users());
                rm("/data/caipiao/call");
                write_file("/data/caipiao/call",sprintf(
                        "〖赌场消息〗：第"+chinese_number(query("times", cpb))+"期彩票已经发行，欢迎大家前来购买。\n" +
                        "〖赌场消息〗：第"+chinese_number(query("times", cpb))+"期累计奖金"+chinese_number(query("all_gold", cpb))+"两黄金。\n" +
                        "〖赌场消息〗：第"+chinese_number(query("times", cpb))+"期彩票将于"+query("end_cdate", cpb)+"停止发行。\n"));
                return;
        }
        return;
}
