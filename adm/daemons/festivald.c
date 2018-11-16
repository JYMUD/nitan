#include <localtime.h>
#include <ansi.h>

inherit F_DBASE;

mixed festivals = ([]);
mixed now_festivals = ({});
string now_string = "";
void setup();
void check_festival();
void create()
{
        seteuid(getuid());
        set("channel_id", "���ս�������");   
        setup();
        check_festival();
}

void setup()
{
        // /adm/etc/festival
        // Ӣ����:������:��ʼʱ��:����ʱ��:��������:����������:��������:����
        // ����������|����,����|����
        string sen;
        mixed fess;
        mixed tmp,tmp2;
        int i,sz,j,sz2;
        int y,m,d;
        string reward;
        int rewardcount;
        sen = read_file("/adm/etc/festival");
        fess = explode(sen,"\n");
        sz = sizeof(fess);
        for(i=0;i<sz;i++) {
                tmp = explode(fess[i],":");
                //log_file("fes",sprintf("%O\n",tmp));
                festivals[tmp[0]] = ([]);
                festivals[tmp[0]]["cname"] = tmp[1];
                festivals[tmp[0]]["fname"] = tmp[5];
                festivals[tmp[0]]["fdate"] = tmp[4];
                festivals[tmp[0]]["stime"] = tmp[2];
                festivals[tmp[0]]["etime"] = tmp[3];
                festivals[tmp[0]]["type"] = atoi(tmp[6]);//0��ʾ��ȡһ�Σ�1��ʾÿ����ȡ
                festivals[tmp[0]]["explimit"] = atoi(tmp[7]);
                festivals[tmp[0]]["reward"] = ([]);
                tmp2 = explode(tmp[8],",");
                sz2 = sizeof(tmp2);
                for(j=0;j<sz2;j++) {
                        sscanf(tmp2[j],"%s|%d",reward,rewardcount);
                        festivals[tmp[0]]["reward"][reward] = rewardcount;
                }
                sscanf(tmp[2],"%d-%d-%d",y,m,d);
                festivals[tmp[0]]["stimey"] = y;
                festivals[tmp[0]]["stimem"] = m;
                festivals[tmp[0]]["stimed"] = d;
                sscanf(tmp[3],"%d-%d-%d",y,m,d);
                festivals[tmp[0]]["etimey"] = y;
                festivals[tmp[0]]["etimem"] = m;        
                festivals[tmp[0]]["etimed"] = d;        
        }
}

string set_festival_string()
{
        string ret;
        mixed tmp;
        int i,sz,j,sz2;
        if(!(sz=sizeof(now_festivals))) {
                ret = HIY + "��ǰû�����ڽ��еĽ��ջ��\n"+NOR;
        } else {
                ret = HIY+"��ǰ���ڽ����еĽ��ջ�У�\n";
                for(i=0;i<sz;i++) {
                        ret += HIY+"\t����ƣ�"+HIG+festivals[now_festivals[i]]["cname"]+"\n";
                        ret += HIY+"\tӢ�ı�ʶ��"+HIG+now_festivals[i]+"\n";
                        ret += HIY+"\t��ʼʱ�䣺"+HIG+festivals[now_festivals[i]]["stime"]+"\n";
                        ret += HIY+"\t����ʱ�䣺"+HIG+festivals[now_festivals[i]]["etime"]+"\n";
                        ret += HIY+"\t�������ƣ�"+HIG+festivals[now_festivals[i]]["explimit"]+"\n";
                        ret += HIY+"\t�������ݣ�"+HIG;
                        tmp = keys(festivals[now_festivals[i]]["reward"]);
                        sz2 = sizeof(tmp);
                        for(j=0;j<sz2;j++) {
                                switch(tmp[j]) {
                                case "exp":
                                        ret += "����";
                                        break;
                                case "pot":
                                        ret += "Ǳ��";
                                        break;
                                case "mar":
                                        ret += "���";
                                        break;
                                case "neili":
                                        ret += "����";
                                        break;
                                case "jingli":
                                        ret += "����";
                                        break;
                                case "weiwang":
                                        ret += "����";
                                        break;
                                case "score":
                                        ret += "����";
                                        break;
                                case "gongxian":
                                        ret += "����";
                                        break;
                                case "gold":
                                        ret += "�ƽ�";
                                        break;
                                default ://�����ߵļ򵥽ӿ�
                                        ret+=query("name", get_object(tmp[j]));
                                        break;
                                }
                                ret += ":"+festivals[now_festivals[i]]["reward"][tmp[j]]+"��";
                        }
                        ret += "\n";
                        ret += HIY+"\t�������ͣ�"+HIG+((festivals[now_festivals[i]]["type"])?"ÿ����ȡ":"����һ��")+"\n";
                        ret += HIY+"\t�������գ�"+HIG+festivals[now_festivals[i]]["fname"]+"("+festivals[now_festivals[i]]["fdate"]+")\n\n";

                }
        }       
        ret += NOR;
        return ret;
}

string query_festival_string()
{
        return now_string;
}

int compare_date(mixed a,mixed b)
{
        //С�ڵ�����1
        //������0
        if(a[0]<b[0]) {
                return 1;
        } else if(a[0]>b[0]) {
                return 0;
        } else {
                if(a[1] < b[1]) {
                        return 1;
                } else if(a[1]>b[1]) {
                        return 0;
                } else {
                        if(a[2] < b[2]) {
                                return 1;
                        } else if(a[2]>b[2]) {
                                return 0;
                        } else {
                                return 1;
                        }
                }
        }       
}

int is_festival(string arg)
{
        mixed lc;
        int y,m,d;

        lc = localtime(time());
        y = lc[LT_YEAR];
        m = lc[LT_MON] + 1;
        d = lc[LT_MDAY];

        if(!arg || undefinedp(festivals[arg]))
                return 0;

        if(compare_date(({festivals[arg]["stimey"],festivals[arg]["stimem"],festivals[arg]["stimed"]}),({y,m,d})) && compare_date(({y,m,d}),({festivals[arg]["etimey"],festivals[arg]["etimem"],festivals[arg]["etimed"]})) )
                return 1;
        return 0;
}
void check_festival()
{
        //ʹ�ý��յ��������������ж�
        
        // ���ж��Ƿ��оɵĻ����
        int i,sz;
        mixed tmp_fes;
        mixed feskeys;
        tmp_fes = copy(now_festivals);
        if(sz = sizeof(tmp_fes)) {
                //һ��һ���ж�
                for(i=0;i<sz;i++) {
                        if(!is_festival(tmp_fes[i])) {
                                now_festivals -= ({tmp_fes[i]});
                                CHANNEL_D->channel_broadcast("mess","���վ��飺���ջ "+festivals[tmp_fes[i]]["cname"]+" �����ˡ�");
                        }
                }
        }
        feskeys = keys(festivals);
        sz = sizeof(feskeys);
        for(i=0;i<sz;i++) {
                if(member_array(feskeys[i],now_festivals)>=0)
                        continue;
                if(is_festival(feskeys[i])) {
                        now_festivals += ({feskeys[i]});
                        CHANNEL_D->channel_broadcast("mess", "���վ��飺���ջ "+festivals[feskeys[i]]["cname"]+" ��ʼ�ˡ�");
                }
        }       
        now_string = set_festival_string();
        call_out("check_festival",60);
}

string give_festival_reward(object usr,string arg)
{
        string ret;
        mixed tmp;
        int i,j,sz2;
        object ob;
        ret = "���ڽ��ջ��"+festivals[arg]["cname"]+"("+arg+")�л�������½�����\n";
        tmp = keys(festivals[arg]["reward"]);
                        sz2 = sizeof(tmp);
                        for(j=0;j<sz2;j++) {
                                switch(tmp[j]) {
                                case "exp":
                                        addn("combat_exp", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "����";
                                        break;
                                case "pot":
                                        addn("potential", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "Ǳ��";
                                        break;
                                case "mar":
                                        addn("experience", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "���";
                                        break;
                                case "neili":
                                        addn("max_neili", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "����";
                                        break;
                                case "jingli":
                                        addn("max_jingli", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "����";
                                        break;
                                case "weiwang":
                                        addn("weiwang", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "����";
                                        break;
                                case "score":
                                        addn("score", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "����";
                                        break;
                                case "gongxian":
                                        addn("family/gongji", festivals[arg]["reward"][tmp[j]], usr);
                                        ret += "����";
                                        break;
                                case "gold":
                                        ob = new("/clone/money/gold");
                                        ob->set_amount(festivals[arg]["reward"][tmp[j]]);
                                        ob->move(usr);
                                        ret += "�ƽ�";
                                        break;
                                default ://�����ߵļ򵥽ӿ�
                                        for(i=0;i<festivals[arg]["reward"][tmp[j]];i++)  {
                                                ob = new(tmp[j]);
                                                ob->move(usr);
                                        }
                                        ret+=query("name", get_object(tmp[j]));
                                        break;
                                }
                                ret += ":"+festivals[arg]["reward"][tmp[j]]+"��";
                        }

                        ret += "\n";
        return ret;
}

string get_reward(object usr)
{
        int i,sz;
        mixed fes_record;
        string today,ret;
        int y,m,d,ty,tm,td;
        mixed lc;

        if(!(sz=sizeof(now_festivals)))
                return "Ŀǰû�����ڽ����еĽ��գ����û�п�����ȡ�Ľ�����";    
        ret = "";       
        lc = localtime(time());
        ty = lc[LT_YEAR];
        tm = lc[LT_MON] + 1;
        td = lc[LT_MDAY];

        today = lc[LT_YEAR]+"-"+sprintf("%.2d",lc[LT_MON] + 1)+"-"+sprintf("%.2d",lc[LT_MDAY]);
        fes_record=query("festival_record", usr);
        if(!mapp(fes_record))
                fes_record = ([]);
        for(i=0;i<sz;i++) {
                //ÿ��fes���ж��ͽ�����������
                if(undefinedp(fes_record[now_festivals[i]])) { //�޼�¼�����콱
                        //������
                        if( query("combat_exp", usr)<festivals[now_festivals[i]]["explimit"]){
                                ret += festivals[now_festivals[i]]["cname"]+"("+now_festivals[i]+")Ҫ��������Ϊ"+festivals[now_festivals[i]]["explimit"]+"������ǰ���鲻�㣬�޷���ȡ������\n";
                        } else {
                                ret += give_festival_reward(usr,now_festivals[i]);
                                //��record
                                fes_record[now_festivals[i]] = today;
                        }
                } else {//�м�¼
                        sscanf(fes_record[now_festivals[i]],"%d-%d-%d",y,m,d);
                        if(compare_date(({festivals[now_festivals[i]]["stimey"],festivals[now_festivals[i]]["stimem"],festivals[now_festivals[i]]["stimed"]}),({y,m,d}))==0) {//������¼�ȿ������磬˵�����ϴν��ջ�ã����콱(����ʱ����ڽ�����¼ 0)
                                //������
                                if( query("combat_exp", usr)<festivals[now_festivals[i]]["explimit"]){
                                         ret += festivals[now_festivals[i]]["cname"]+"("+now_festivals[i]+")Ҫ��������Ϊ"+festivals[now_festivals[i]]["explimit"]+"������ǰ���鲻�㣬�޷���ȡ������\n";
                                } else {
                                        ret += give_festival_reward(usr,now_festivals[i]);
                                        //��record
                                        fes_record[now_festivals[i]] = today;
                                }
                        } else { //���������ˡ�����
                                if(festivals[now_festivals[i]]["type"]==0) { //����������һ�Σ���������
                                        ret += festivals[now_festivals[i]]["cname"]+"("+now_festivals[i]+")ֻ����ȡһ�ν���������"+fes_record[now_festivals[i]]+"����ȡ���������ٴ���ȡ��\n";
                                } else { //ÿ����ȡ��
                                        if(compare_date(({ty,tm,td}),({y,m,d}))==0) { //������¼�Ƚ����磬����ȡ(���� ���� ������¼ 0)
                                                if( query("combat_exp", usr)<festivals[now_festivals[i]]["explimit"]){
                                                        ret += festivals[now_festivals[i]]["cname"]+"("+now_festivals[i]+")Ҫ��������Ϊ"+festivals[now_festivals[i]]["explimit"]+"������ǰ���鲻�㣬�޷���ȡ������\n";
                                                } else {
                                                        //������
                                                        ret += give_festival_reward(usr,now_festivals[i]);
                                                        //��record
                                                        fes_record[now_festivals[i]] = today;
                                                }       
                                        } else { //�������죬����
                                                ret += festivals[now_festivals[i]]["cname"]+"("+now_festivals[i]+")�ڻ�ڼ��ÿ����ȡ����һ�Σ������죨"+today+"���Ѿ���ȡ�������������ٴ���ȡ��\n";
                                        }
                                }
                        }
                }
        }
        set("festival_record", fes_record, usr);
        return ret;
}
