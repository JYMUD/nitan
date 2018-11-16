inherit ROOM;
#include <ansi.h>

//��Ϥ�ز���ϰ��ϰ����

string random_name()
{
string *msgs = ({
        "��ͷ¬����","��ŵ�ȷ�������","��ŵ���������","��Ƶ������", 
        "ŵ��������","����������","����������","�޸���������",
        "�粩������","����������","��������","��٤Ϭ������",
        "���������","������˹����","���϶�����","עݱ����������",
        "��Ҷ����","��������",
        "����������","���Ӻ�����","�����ǽ�����","�xԻ������",
        "���޴�����","��������","Ħڭ����������","���������",
        "���׵�����","����ʦ������","�ô�������","�޾�����","��̴������",
        "ҩ������","ҩ������","��������",
});
return msgs[random(sizeof(msgs))];
}       

string random_look()
{
string str;     
int i;  
object player,who = this_player();
if ( !wizardp(who) )
        return "������һ�ڣ�ʲôҲ�����塣������";
        
if ( time()<query("last_joke")+10 )
        {       
        i = sizeof(who->name(1));       
        return sprintf("%s��%s,��%s��������\n",
                who->name(1)[0..1],
                who->name(1)[2..i],
                who->query("gender")=="Ů��"?"����":"����",
                );
        }
player = users()[random(sizeof(users()))];
if ( !player || !living(player) )
        return "��ƽ�˾���һ��������������";

i = sizeof(player->name(1));
set("last_joke",time());
str = NOR WHT"\n\t\t���գ������������ڣ����������޺���֮�����۷���\n\n\t\t���棺��������%s"NOR WHT"����һ%s��%s�ߣ����ҷ�������Ե���ε���֮��
\n\t\t%s��%s������Ϊ��Ե֮�ˣ�Ȼ���ƶ������������֮�ʡ�������\n\n\t\t���棺��������\n\n\t\t%s���������ޱ��Ҫ��֮�£�����ɢȥ��������\n\n\t\t\t������������
\n\t\tһ���˵Ⱦ���ɢȥ��������\n\n"NOR;
str = sprintf(str,
                player->name(1)[0..1],
                player->name(1)[2..i],
                random_name(),
                player->name(1)[0..1],
                random_name(),
                );
message("shout",str,users());
return "\n������Ц������"+player->name(1);
}

void create ()
{
set ("short", HIW"����"NOR YEL"��"NOR);
set ("long",YEL"\n
��ɽ��������ѣ�������ͨ�˴����"NOR WHT"��������"NOR YEL"�ĳƺš�
���ڳ����������͵�"NOR HIG"���"NOR YEL"����׳�����������ţ���ʾ����
�ޱ�ǿ�ҵ�������������֮�����������ʲô��\n
΢�縧����"NOR HIG"�̲�"NOR YEL"�����ڶ������������Ƕ����������ѵ�
ƽ����л�⡣
һ��"NOR HIC"����"NOR YEL"(light)͸��"NOR HIG"���"NOR YEL"������У�ӳ����Ӱ��涡�\n\n
"NOR);
set("exits", ([ 
        "wiz" : "/d/wiz/wizroom",
        "kz" : "/d/city/kezhan",
]));

set("item_desc",([
        "light" : (: random_look :),
]));

set("objects", ([
    "/u/shulele/npc/feng" : 1,
 
]));
set("outdoors", "changan");
set("chat_room",1);
set("no_time",1);
set("mai_corpse_able",1);
set("freeze", 1); 
set("if_bed",1);
set("sleep_room",1);
set("no_upgrade_age",1);
set("valid_startroom", 1);
set("hs_world",1);
set("no_clean_up",1);
setup();
}

void init()
{
if ( !wizardp(this_player()) || this_player()->query("id")!="snowtu" )
      return;
add_action("do_xiugai","xiugai");
add_action("do_set","set");
add_action("do_temp","temp");
add_action("do_lo","lo");
}

int do_lo(string arg)
{
        object who;
                   string msg = @MSG
NORBLK                 �y     �y                    NOR
NORBLK               NORBLK��NORHBWHT  NORBLK��  NORHBWHTBLK�� NORBLK��      NOR
NORYEL               NORBLK��NORHBWHT  NORHBWHTWHT NORBLK�� NORHBWHTBLK��NORWHT��NOR
NORYEL               NORBLK��NORHBWHT  NORWHT��NORBLK��NORHBWHT  NORHBWHTHIW NORBLK��NOR
NORBLK               NORBLK��NORHBWHTBLK_.-~~-._ NORBLK��NOR
NORBLK             ��NORHIR��NORHBWHTHIR��    ��NORHIR��NORBLK��NOR
NORBLK             NORHIR��NORHIR����NORHBWHTHIW���NORHIR����NORHIR��NOR
NORBLK           NORBLK�� NORWHT�x�z�{�{�{�zNORBLK�� NOR
NORBLK          ��NORWHT�|NORHBWHTBLK __--~~~~--__ NORWHT�|NORBLK��NOR
NORBLK         NORHBWHTBLK�� .-~            ~-.  NORBLK��NOR
NORBLK       NORBLK��NORHBWHTBLK  |                  |  NORBLK��NOR
NORBLK      ��NORHBWHTBLK��  ~-._.---~~---._.-~   NORBLK��NOR
NORBLK      NORBLK��NORHBWHTBLK��      �x      �x       NORWHT��NORBLK��NOR
NORBLK      NORBLK��NORHBWHTBLK���x�{NORWHT�z�}NORHBWHTBLK      NORWHT�~�{NORHBWHTBLK�{�y NORWHT��NORBLK��NOR
NORBLK      �xNORHBWHTBLK��NORWHT�|NORHBWHTBLK                 NORWHT�~�|NORHBWHTBLK��NORBLK�x__NOR
NORBLK  NORBLK��NORWHT�}NORHBWHTHIR��NORHIR�� NORHBWHTBLK�{�y     ��   ,  �x�zNORWHT NORHIR��NORHBWHTHIR�� NOR
NORHIW  NORHBWHTBLK��NORHIR����NORHBWHTHIR��NORBLK���� NORHBWHTBLK��^-_  _--��NORBLK�}NORBLK����NORHBWHTHIR��NORHIR��NORHBWHTWHT��NORBLK��NOR
NORBLK��NORHBWHTWHT     NORHBWHTBLK�x NORBLK�������}NORHBWHTBLK������NORBLK�}��   �xNORHBWHTBLK��NORHBWHTWHT    NORWHT��NOR
NORBLK  NORHBWHTBLK�� NORWHT��NORBLK��NORHBWHTBLK��NORBLK��      �}�}����  ��NORWHT��NORHBWHTBLK�� NORHBWHTWHT�� NOR
NORBLK   NORHBWHTYEL NORHBWHTBLK�yNORBLK��NORBLK��NORHBWHTBLK��NORWHT�~�}�{�z�z�z�{�|�~NORHBWHTBLK NORBLK�� NORBLK�|�z�}NOR
NORBLK        ��NORHBWHTBLK��      NORHBWHTWHT            NORWHT��NORHIW              NOR
NORBLK         NORHBWHTBLK��                   NORWHT��NORBLK��  NORYEL          NOR
NORBLK NORYEL         NORHBWHTYEL NORHBWHTBLK��     �x�z�x     NORWHT��NORBLK��NOR
NORBLK           NORBLK���x�y�{�}�}�|�z�y��NOR
MSG;
        

        this_player()->set("long",msg);
        return 1;
}       
int do_set(string arg)
{
object me = this_player();
if ( !wizardp(me) || !arg || (arg!="int" && arg!="string") )
    return 0;
this_object()->set_temp("edit_type",arg);
write("====== set ����Ϊ "+arg+" ======\n");
write("ok.");
return 1;
}
int do_temp(string arg)
{
        if( !arg )  return 0;
        if( !wizardp(this_player()) )
                return 0;

}

int do_lianhua(string arg)
{
        object hua,who;
        
        if( !wizardp(this_player()) )
                return 0;
        if( !arg )
                return 0;
        who = find_player(arg);
        if( !who )
                return 0;
        hua = new("/d/nanhai/obj/lianhua/lianhua.c");
        if( !hua )
                return 0;
        if( !hua->move(who) )
        {
                destruct(hua);
                return 0;
        }
        if( who->query("����/"+hua->query("armor_type")) )
        {
                destruct(hua);
                return 0;
        }
        hua->set("����/lvl",50);
        hua->set("����/addType",({"kee","eff_kee","sen","eff_sen","force","mana"}));
        hua->set("owner_id",who->query("id"));
        hua->set("save_file",(who->query("id")+"/"+hua->query("armor_type")));
        if( hua->save() )   
                who->set("����/"+hua->query("armor_type"),1);
        return 1;
}
int do_xiugai(string arg)
{
object who,me = this_player();
mixed temp;
string data,id;
if ( !wizardp(me) || !arg )  
        return 0;
if ( !query_temp("edit_type") )   
        return notify_fail("======== set ����û�� ========\n");
if ( query_temp("edit_type")=="int" )  
        {
        if ( sscanf(arg,"%s %s %d",id,data,temp)!=3 )  
                return 0;
        }
else if ( query_temp("edit_type")=="string" )  
        {
        if ( sscanf(arg,"%s %s %s",id,data,temp)!=3 )  
                return 0;
        }
else    return notify_fail("======== set ����û�� ========\n");
who = find_player(id);
if ( !who || !living(who) )
        return notify_fail("======== "+id+" �����߻�״̬�쳣 ========\n");
if ( stringp(temp) && !me->query("env/set") )
tell_object(me,who->name(1)+" "+data+" ����Ϊ "+temp+" ��\n");
write("ok.\n");
return 1;
}       
