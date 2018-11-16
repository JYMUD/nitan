#include <ansi.h>
#define TOTALRATE       1000
inherit COMBINED_ITEM;

int open_baoxiang(object me,object this);
string test(object me,object this);

string extra_long() 
{
        string str;
        mixed key,list;
        object ob;
        int i;
        str = this_object()->name()+"�п��ܿ����Ľ���������\n";
        list = query("BAOXIANG_LIST", this_object());
        if(!list || !mapp(list) ) {
                return str;
        }
        key = keys(list);
        for(i=0;i<sizeof(key);i++) {
                ob = load_object(key[i]);
                if(ob) {
                        str += "\t"+ob->name()+"("+query("id",ob)+")\n";
                }
        }
        return str;


}

int do_test(string arg)
{
        object me,this;
        me = this_player();

        this = this_object();

        if( !arg ) return notify_fail("��Ҫ����ʲô��\n"); 
        if(present(arg,environment()) != this) {
                return 0;
        }

        tell_object(me,test(me,this)+"\n");
        return 1;
}

string test(object me,object this)
{
        mixed list;
        string str;
        mixed keys;
        object ob;
        int totalRate;
        int i;

        str = this->name()+"\n";

        list = query("BAOXIANG_LIST", this);

        if(!list || !mapp(list)) {
                str += "��û��BAOXIANG_LIST���ԣ����߸����Բ���mapping��";
        } else {
                keys = keys(list);
                if(!sizeof(keys)) {
                        str += "BAOXIANG_LIST�б�Ϊ�գ�";
                } else {
                        totalRate = 0;
                        for(i=0;i<sizeof(keys);i++) {
                                totalRate += list[keys[i]];
                                ob = load_object(keys[i]);      
                                if(!ob) {
                                        str += keys[i]+"�����ʣ�"+list[keys[i]]+"������ʧ�ܣ��������ļ����ļ��������\n";
                                } else {
                                        str += keys[i]+"["+ob->name()+"]"+"�����ʣ�"+list[keys[i]]+"��������\n";
                                }
                        }

                        if(totalRate == TOTALRATE) {
                                str += "�ܸ��ʣ�"+totalRate+"������";
                        } else {
                                str += "�ܸ��ʣ�"+totalRate+"��������������";
                        }
                }

        }
        return str;

}

int do_open(string arg)
{
        object me,this;
        me = this_player();
        this = this_object();
        if( !arg ) return notify_fail("��Ҫ��ʲô��\n");
        if(present(arg,environment()) != this) {
                return 0;
        }
        if(this->query_amount()) {
                if(open_baoxiang(me,this)) {
                        this->add_amount(-1);
                        return 1;
                } else {
                        return 0;
                }
        } else {
                return 0;
        }
}

int open_baoxiang(object me,object this)
{
        mixed list;
        object ob;
        mixed keys;
        int totalRate;
        int rand;       
        int i;

        string str;

        list = query("BAOXIANG_LIST", this);
        
        if(!list || !mapp(list)) {
                return 0;
        }
        
        totalRate = 0;
        rand = random(TOTALRATE);       

        keys = keys(list);
        for(i=0;i<sizeof(list);i++) {
                if(rand >= totalRate && rand < totalRate+list[keys[i]]) {
                        ob = new(keys[i]);
                        if(ob && ob->move(me)) {
                                str = "����һ��"+this->name()+"������ߵõ���"+ob->name()+"("+query("id",ob)+")��\n";
                                tell_room(environment(me),me->name()+str,({me}));
                                tell_object(me,"��"+str);
                                return 1;
                        } else {
                                if(ob) {
                                        tell_object(me,"��"+this->name()+"ʧ���ˡ�\n");
                                        destruct(ob);
                                }
                                return 0;
                        }
                } else {
                        totalRate += list[keys[i]];
                }
        }
        return 0;
}

