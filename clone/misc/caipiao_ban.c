// ��ƱͶעϵͳ made by Ҷ���(sunyc)@kync 2001/1/26
// remodify by Sunyc@kync 2002/7/24
// remodify By Sunyc@kync.tomud.com 5555 2002/11/24
// �������𣬿����ۼƣ�Ҳ��ֻ��gold��
// ��Ϊ30ѡ7

#include <ansi.h>
#include <localtime.h>
inherit ITEM;
inherit F_SAVE;

mixed *all_biao;
nosave string *touzhu;

int do_read(string);
int do_ya(string);
void enough_rest();
string show_player();
void auto_post(string title, string body);

string query_save_file()
{
        return DATA_DIR + "caipiao";
}

void create()
{
        set_name(HIG "��ƱͶע��" NOR, ({ "touzhu ban", "touzhu", "ban"}) );
        set("long",
                "����ȫ����ҵĲ�ƱͶע�塣\n"
                "��ι����Ʊ��read rules��\n");
        set_weight(900000000);
        seteuid(getuid());
        set("unit", "��");
        set("no_put", 1);
        set("no_get", 1);

        set("times", 1);
        restore();
}

void init()
{
        add_action("do_read", "read");
        add_action("do_ya", "touzhu");
        add_action("do_duijiang", "duijiang");
}

void enough_rest()
{
        delete_temp("busy");
}

int do_ya(int arg)
{
        object me, ob, caipiao;
        mapping biao;
        string str;
        int i;

        me = this_player();
        str = "";

        if( query("balance", me)/10000<10 )
                return notify_fail("Ǯׯ����Ҫ��ʮ���ƽ����Ͷע��\n");

        if( query("end_ya") || query("duijiang") )
                return notify_fail("��ֹʱ���ѹ������´��������......\n");

        if( query_temp("busy") )
                return notify_fail("���Ժ���������...\n");

        if( !intp(arg) || !arg ) {
                tell_object(me, "��ѡ7��30���ڵĺ��룬�ö��Ÿ�����\n");
                tell_object(me,"���磺2,3,4,5,6,7,8\n");
                tell_object(me,"��������-1���л�ѡ��\n");
                tell_object(me,"����������ѡ��");
                input_to("touzhu_1",me);
                return 1;
        } else {
                message_vision("$N��ͶƱ��д�ú��ӽ���ͶƱ�塣����ͻȻ������һ�Ų�Ʊ��$N��æ����������\n",me);
                addn("balance", -100000, me);
                tell_object(me,"Ǯׯ�Ѿ��۳�����ʮ���ƽ�����"+query("kaijiang_cdate")+"���ȴ�����ɣ�\n");
                tell_object(me,HIR"�ǣϣϣġ��̣գã� ף�����ˣ�\n"NOR);
                caipiao=new("/clone/misc/caipiao.c");
                set("kaijiang_date", query("kaijiang_cdate"), caipiao);
                // ���һ�������ַ���
                for(i=0;i<sizeof(query_temp("z_num", me));i++)
                        str+=query_temp("z_num", me)[i]+"";
                set("z_num", str, caipiao);
                set("times", query("times"), caipiao);
                caipiao->move(me);
                set("crypt", oldcrypt(str,0), caipiao);
                biao = ([
                        "id":query("id", me),
                        "name"  :me->name(1),
                        "z_num" :str,
                        "z_num_all":query_temp("z_num",me),
                        "jieguo":"δ����",
                ]);
                delete_temp("z_num", me);
                if( !pointerp(all_biao) ) all_biao = ({biao});
                else all_biao += ({biao});
                save();
                remove_call_out("enough_rest");
                call_out("enough_rest", 1);
                return 1;
        }
        return 1;
}

void touzhu_1(string num,object me)
{
    int i,z,j=0;
    int h,k,p=0;
    int *jieguo=({});
    string str,*tmp=({});
    if(!num || num=="")
    {
        tell_object(me,"��ѡ7��1-30�еĺ��룬�ö��Ÿ�����\n");
        tell_object(me,"���磺2,3,4,5,6,7,8\n");
        tell_object(me,"��������-1���л�ѡ��\n");
        tell_object(me,"����������ѡ��");
        input_to("touzhu_1", me);
        return;
    }
    if(atoi(num)==-1)
    {
        i=0;
        z=0;
        str="";
        while(p!=7)
        {
            i=random(30)+1;
            if(member_array(i,jieguo)!=-1) continue;
            else
            {
                jieguo+=({i});
                p++;
                continue;
            }
        }
        for(i=0;i<sizeof(jieguo);i++)
            str+=jieguo[i]+" ";
        set_temp("z_num", jieguo, me);
        write("\n����Ͷע����Ϊ"HIR+str+NOR"����ȷ��ô?[y/n]��");
        input_to("yn",me);
        return;
    }
    touzhu=explode(num,",");
    str="";
    for(i=0;i<sizeof(touzhu);i++)
    {
        if(!intp(z=atoi(touzhu[i])) || z<1 || z>30 || sizeof(touzhu)!=7) {j=1;break;}
        if(member_array(z,tmp)==-1)
            tmp+=({z});
        str+=" "+z;
    }
    if(sizeof(tmp)!=7) j=1;
    if(j)
    {
        tell_object(me,"��ѡ7��1-30�еĺ��룬�ö��Ÿ�����\n");
        tell_object(me,"���磺2,3,4,5,6,7,8\n");
        tell_object(me,"��������-1���л�ѡ��\n");
        tell_object(me,"����������ѡ��");
        input_to("touzhu_1", me);
        return;
    }
    set_temp("z_num", touzhu, me);
    write("\n����Ͷע����Ϊ"HIR+str+NOR"����ȷ��ô?[y/n]��");
    input_to("yn",me);
    return;
}
void yn(string yn,object me)
{
    if( (yn[0]!='y' && yn[0]!='Y') ) {
        delete_temp("z_num", me);
        write("\n�ðɣ�������Ͷע��");
        tell_object(me,"��ѡ7��1-30�еĺ��룬�ö��Ÿ�����\n");
        tell_object(me,"���磺2,3,4,5,6,7,8\n");
        tell_object(me,"����������ѡ��");
        input_to("touzhu_1", me);
        return;
    }
    else {
        write("\n����������...\n");
        do_ya(1);
        return;
    }
}

//void check(string yn,object me)
void check(object me)
{
    int money=0;
    int i;
 /*query_temp("check", if( oldcrypt(me),yn) != yn){
        write("�Բ����������У�������󣬲��ܸ���������\n");
        delete_temp("check", me);
        return;
    }
    else {   */
        write("\n��ϲ�����˱��ڴ�...\n");
        delete_temp("check", me);
        write("ok...��ʼ����\n");
        switch (all_biao[query_temp("num",me)]["jieguo"])
        {
        case "�صȽ�":money=query("last_gold");
            break;
        case "һ�Ƚ�":money=query("last_gold")/5;
            break;
        case "���Ƚ�":money=query("last_gold")/10;
            break;
        case "���Ƚ�":money=query("last_gold")/100;
            break;
        case "�ĵȽ�":money=query("last_gold")/1000;
            break;
        }
        for(i=0;i<money;i++)
        {
            addn("money", 10000, me);
        }
        write(HIR"������"+chinese_number(money)+"���ƽ�,�Ѿ���������˻���\n");
        message("system",HIW"����̶���ʡ���"+HIC" "+query("name",me)+HIW" ����"+HIY" "+chinese_number(money)+HIW" ���ƽ��Ѿ������ʻ���\n"NOR,users());
        all_biao[query_temp("num",me)]["jieguo"]="�Ѷҽ�";
        //all_biao-=({query_temp("num", all_biao[me)]});
        save();//����
        restore();
        delete_temp("num", me);
        delete_temp("check", me);
        remove_call_out("enough_rest");
        call_out("enough_rest", 1);
        return;
 //   }
}

int do_read(string arg)
{
    int i,j,k;
    object me;
    string name,str,str1,str2;
    mapping biao;

    me = this_player();

    if(arg == "rules")
    {
        write("����Ʊϵͳ�Ѿ���ͨ����ӭ���ǰ�����ʡ�\n");
        write("Ͷע����touzhu\n");
        write("��ѯ����read biao\n");
        write("��ѯ��������read duijiang\n");
        write("��ʹ��duijiangָ���Ľ����Զ��������ʻ���\n");
        return 1;
    }
    if(arg == "biao")
    {
        restore();
        /*if( !pointerp(all_biao) || !sizeof(all_biao) )
        {
            write("\n��û���˿�ʼͶע��\n");
            return 1;
        }*/
        write(show_player());
        return 1;
    }
    if(arg == "duijiang")
    {
        write("�ҽ�ϸ��\n");
        write("�صȽ����߸�����ȫ���Ǻϡ�      ����ȫ���ۼƽ���.\n");
        write("һ�Ƚ����������������Ǻϡ�      ����ȫ���ۼƽ���/5.\n");
        write("���Ƚ���������������Ǻ�        ����ȫ���ۼƽ���/50.\n");
        write("���Ƚ��������ĸ������Ǻ�        ����ȫ���ۼƽ���/100.\n");
        write("�ĵȽ����������������Ǻ�        ����ȫ���ۼƽ���/1000.\n");
        write("ף�����ʹ��!\n");
        return 1;
    }
    else        write("��Ҫ��ʲô�����������read rules�����������read biao,�ҽ�������read duijiang��\n");
    return 1;
}
string show_player()
{
    int z,j,k,i,h, m;
    string str="";
    int *str_te,*str_1,*str_2,*str_3,*str_4,*str_5,*list, *str_old;
    mapping name;
    restore();
    i=0;
    if(!query("duijiang"))
    {
        h=sizeof(all_biao);
        str+=HIW"���ڲ�Ʊ���� "HIG+chinese_number(sizeof(all_biao))+HIW" λ���Ͷע��Ͷע״�����£�\n"NOR;
        str+="���������������ש����������������������ש�������\n";
        while (i<h)
        {
            name=all_biao[i];
            /*if (strlen(name["name"])==6)
                str+= sprintf("��%-28s��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);//ɾ��name["jieguo"]ǰ(int)name["t_num"]  by wenwu
            else if(strlen(name["name"])==4)
                str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+" "NOR,(int)name["z_num"],name["jieguo"],);
            else if(strlen(name["name"])==8)
                str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
           else if(strlen(name["name"])==1)
                str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
           else if(strlen(name["name"])==3)
                str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
           else if(strlen(name["name"])==5)
                str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
           else if(strlen(name["name"])==7)
                str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
           else if(strlen(name["name"])==9)
                str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
            else if(strlen(name["name"])==10)
                str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
            else if(strlen(name["name"])==2)
                str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);*/
                        str+= sprintf("��%-12s��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
                        i++;
        }
        str+="���������������ߩ����������������������ߩ�������\n"NOR;
        if (query("end_cdate")) str+=HIW"����Ͷע��ֹʱ�䣺"HIY+query("end_cdate")+HIW"\n���ڲ�Ʊ����ʱ�䣺"HIM+query("kaijiang_cdate")+"\n"NOR;
        else str+=HIR"���ڲ�Ʊ�Ѿ���ֹ����,"HIW"����ʱ�䣺"HIG+query("kaijiang_cdate")+HIW"��\n"NOR;
        str+=HIW"���ڲ�Ʊ�ۼƽ���"HIY+query("all_gold")+HIG" ���ƽ�\n"NOR;
        return "/feature/more.c"->start_more(str);
    }
    str_te=str_1=str_2=str_3=str_4=str_5=list=str_old=({});
    str=HIW"�� "HIY+chinese_number(query("times")-1)+ HIW" �ڲ�Ʊ���ѿ�����"+HIR+query("last_z_num_str")+NOR+"\n";
    str+=HIW"���� "HIG+chinese_number(sizeof(all_biao))+HIW" �����Ͷע���н�������£�\n"NOR;
    i=0;
    h=sizeof(all_biao);
    for(i=0;i<h;i++)
    {
        k=0;
        for(z=0;z<sizeof(query("last_z_num"));z++)
        {
            j=all_biao[i]["z_num_all"][z];
            if(member_array(z,query("last_z_num"))!=-1) k++;
        }

                if ( all_biao[i]["jieguo"] == "�Ѷҽ�")
                        str_old+=({i});
                else
                {
        switch (k){
        case 7:
            str_te+=({i});
            all_biao[i]["jieguo"]="�صȽ�";
            break;
        case 6:
            str_1+=({i});
            all_biao[i]["jieguo"]="һ�Ƚ�";
            break;
        case 5:
            str_2+=({i});
            all_biao[i]["jieguo"]="���Ƚ�";
            break;
        case 4:
            str_3+=({i});
            all_biao[i]["jieguo"]="���Ƚ�";
            break;
        case 3:
            str_4+=({i});
            all_biao[i]["jieguo"]="�ĵȽ�";
            break;
        default:
            str_5+=({i});
            all_biao[i]["jieguo"]="�޽�";
            break;
        }
                }
    }
    save();
    list+=str_te+str_1+str_2+str_3+str_4+str_old;
    str_te=str_1=str_2=str_3=str_4=str_5=str_old=({});
    str+="���������������ש����������������������ש�������\n";
    str+= sprintf("��%-12s��%-22s��%-6s��\n","�����","  Ͷ   ע   ��   ��   ","���н�");
    str+="�ǩ������������贈���������������������贈������\n";
    z=0;
    h=sizeof(list);
    set("zhongjiang_num",h);
        m = 0;
    while (z<h)
    {
        i=list[z];
        name=all_biao[i];
        /*if (strlen(name["name"])==6)
            str+= sprintf("��%-28s��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==4)
            str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+" "NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==8)
            str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==1)
            str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==2)
            str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==3)
            str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==5)
            str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==7)
            str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==9)
            str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
        else if(strlen(name["name"])==10)
            str+= sprintf("��%-27s ��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);*/
                str+= sprintf("��%-12s��%22s��%-6s��\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
                if ( name["jieguo"] != "�Ѷҽ�" )
                        m++;
        z++;
    }
    list=({});
    str+="���������������ߩ����������������������ߩ�������\n"NOR;
        str+=HIW"������δ�ҽ�ע����"HIM+chinese_number(m)+HIW"\n"NOR;
    str+=HIW"���ڲ�Ʊ����ʱ�䣺"HIG+query("start_cdate")+HIW"\n"NOR;
    str+=HIW"���ڲ�ƱԤ�ƽ���"HIY+query("all_gold")+HIW" ���ƽ�\n"NOR;
    return "/feature/more.c"->start_more(str);
}
int do_duijiang()//�ҽ�ָ��
{
    int i,j,k,m,n,money;
    object me;
    me = this_player();
    restore();
    if(!query("duijiang"))
        return notify_fail("��δ���ҽ�ʱ�䣡\n");
    if (query_temp("busy"))
        return notify_fail("�Ժ�........\n");
    set_temp("busy",1);
    j=sizeof(all_biao);
    k=0;
        i=0;
        m = 0;
        n = 0;
    while ( i < j )
    {
        if( all_biao[i]["id"] == query("id", me) && all_biao[i]["name"] == query("name", me) )
        {
                        n = 1;
                        if ( all_biao[i]["jieguo"] != "�Ѷҽ�" && all_biao[i]["jieguo"] != "�޽�" )
                        {
                                k = i + 1;
                                break;
                        }
                        else if ( all_biao[i]["jieguo"] == "�Ѷҽ�" )
                                m = 1;
                        else if ( all_biao[i]["jieguo"] == "�޽�" )
                                m = 2;
        }
        i++;
    }
    delete_temp("busy");
    if ( !n || n == 0 ) return notify_fail("�㲢û�����Ʊѽ��\n");
    else if ( k )
    {
        set_temp("check", all_biao[k-1]["z_num"]+""+all_biao[k-1]["t_num"], me);
        set_temp("num", k-1, me);
        write("�����н�������"+query_temp("check", me)+"��\n");
     //   write("����������У����:");
        //input_to("check",me);
                check(me);
        return 1;
    }
        else if( m == 1 ) return notify_fail("���Ѿ��ҹ����ˣ�\n");
    else if( m == 2 ) return notify_fail("�����û�н������Ҹ�ƨ��\n");
}

void auto_post(string title,string body)
{
    mapping note;
    note = allocate_mapping(4);
    note["title"] = title;
    note["author"] ="��Ʊ��";
   // "/cmds/std/news.c"->done_post(this_object(),note,body);��ע�͵����������콱 by wenwu
    return;
}
void clean_data()
{
    all_biao=({});
    save();
    restore();
}
