// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit VRM_SERVER;
string openlock(string lock); // �ⲿ���ÿ�������
varargs void init_data(object s, string arg);   // ��ʼ���������
string get_result(string str1, string str2);

mapping unlock = ([
// ��Ӧ����ɿ�����������A-B-C-D(3412)
        "A" : "123",
        "B" : "23",
        "C" : "134",
        "D" : "12",
]);

void create()
{
        //�Թ��������̳е�����ĵ������ơ�
        set_inherit_room( ROOM );

        //Ψһ����
        set_unique_room( ({
                "/maze/mausoleum/unique_room/jiguan_a",
                "/maze/mausoleum/unique_room/jiguan_b",
                "/maze/mausoleum/unique_room/jiguan_c",
                "/maze/mausoleum/unique_room/jiguan_d",
        }) );

        //���ķ���
        set_center_room("/maze/mausoleum/unique_room/enter");

        //�Թ�������Ĺ��
        set_maze_npcs( ([
                "/maze/mausoleum/npc/jiangling": random(2),
                "/maze/mausoleum/npc/qianrenzhang": random(2),
                "/maze/mausoleum/npc/bairenzhang": 1,
                "/maze/mausoleum/npc/bingshi": 1,
                "/maze/mausoleum/npc/baozi": random(2),
                "/maze/mausoleum/npc/tiger": random(2),
                "/maze/mausoleum/npc/lions": random(2),
                "/maze/mausoleum/npc/ni": 1,
                "/maze/mausoleum/npc/mammoth": random(2),
        ]) );

        set_lonely_create(1);

        //set_maze_boxs(5);

        //set_maze_traps(8);

        set_npcs_rate(40); 

        //�Թ��ĵ��߳�
        set_maze_long(10);

        //��ڷ���(�����ڶ���)
        set_entry_dir("south");

        //��������������ӷ���
        set_link_exit_dir("north");

        //��������������ӵ�����
        set_link_exit_room("/d/luoyang/wenmiao");

        //��ͨ��������
        set_maze_room_short(HIY "�����⹬" NOR);

        set_maze_room_desc(@LONG
�Լ�վ�ڳ����İ���ʯ��֮�ף�ʯ��ֱͨ���Ϸ����������ߡ�ʮ��
����ľ޴�ƽ̨����ͷ��ȥ�������ĺ�ɫ���׺����ǧ��ű�ʯ�����飬
��ʶ�Ŀ�������Ǻӣ������ҹ�գ��������յ�һƬ������������
�����Ķ���·�����Ȼ����һ���εض�������������ΰ���ǡ���Ρ
��׳���ĳ�¥������Ķ��ǵ����ܷ��ߣ������۴��ڰ���ʯ̨�ϣ���
̩ɽѹ�������ȳ�����¥��Ҫ���ư��硢���������ʯ�����ߵĹ㳡�ϣ�
�������龹ȫ���гɷ���ı�ٸ��ͭ�ˡ���ٸ��ʯ�񡭡�������ӣ���
˵Ҳ�м���֮�ڣ�������׳���������ݡ��㳡�ϣ�һ�����������ѽ���
��ҫ����Ŀ�Ĺ��󣬾����ǽ��ӻ㼯��һ�볯����һ���׹�������ˮ��
��ȥ��
LONG);

        //��ڷ��������
        set_entry_short(HIR "�����⹬���" NOR);

        //��ڷ�������
        set_entry_desc(@LONG
�Լ�վ�ڳ����İ���ʯ��֮�ף�ʯ��ֱͨ���Ϸ����������ߡ�ʮ��
����ľ޴�ƽ̨����ͷ��ȥ�������ĺ�ɫ���׺����ǧ��ű�ʯ�����飬
��ʶ�Ŀ�������Ǻӣ������ҹ�գ��������յ�һƬ������������
�����Ķ���·�����Ȼ����һ���εض�������������ΰ���ǡ���Ρ
��׳���ĳ�¥������Ķ��ǵ����ܷ��ߣ������۴��ڰ���ʯ̨�ϣ���
̩ɽѹ�������ȳ�����¥��Ҫ���ư��硢���������ʯ�����ߵĹ㳡�ϣ�
�������龹ȫ���гɷ���ı�ٸ��ͭ�ˡ���ٸ��ʯ�񡭡�������ӣ���
˵Ҳ�м���֮�ڣ�������׳���������ݡ��㳡�ϣ�һ�����������ѽ���
��ҫ����Ŀ�Ĺ��󣬾����ǽ��ӻ㼯��һ�볯����һ���׹�������ˮ��
��ȥ��
LONG);

        //���ڷ��������
        set_exit_short(HIW "�����⹬����" NOR);

        //���ڷ�������
        set_exit_desc(@LONG
�Լ�վ�ڳ����İ���ʯ��֮�ף�ʯ��ֱͨ���Ϸ����������ߡ�ʮ��
����ľ޴�ƽ̨����ͷ��ȥ�������ĺ�ɫ���׺����ǧ��ű�ʯ�����飬
��ʶ�Ŀ�������Ǻӣ������ҹ�գ��������յ�һƬ������������
�����Ķ���·�����Ȼ����һ���εض�������������ΰ���ǡ���Ρ
��׳���ĳ�¥������Ķ��ǵ����ܷ��ߣ������۴��ڰ���ʯ̨�ϣ���
̩ɽѹ�������ȳ�����¥��Ҫ���ư��硢���������ʯ�����ߵĹ㳡�ϣ�
�������龹ȫ���гɷ���ı�ٸ��ͭ�ˡ���ٸ��ʯ�񡭡�������ӣ���
˵Ҳ�м���֮�ڣ�������׳���������ݡ��㳡�ϣ�һ�����������ѽ���
��ҫ����Ŀ�Ĺ��󣬾����ǽ��ӻ㼯��һ�볯����һ���׹�������ˮ��
��ȥ��
LONG);
        init_data();
}

// �ⲿ���ô˺������ݲ���lockΪ: "A"-"D"
string openlock(object me, string lock)
{
        string opened, str_want_open;
        mixed result;
        int i;
        object s;
        string file;

        if( !stringp(query("lock/opened")) || query("lock/opened") == "" ) {
              set("lock/opened", unlock[lock]);
              return unlock[lock];
        }

        str_want_open = unlock[lock];
        opened = query("lock/opened");

        if (! stringp(opened))
              return "erros: opened is not a string.\n";

        result = get_result(opened, str_want_open);
        if( sizeof(result) == 4 && result == "3412" ) {
                file = FUBEN_D->query_maze_dir(me);
                set("lock/unlocked", 1);
                set("lock/opened", result);
                switch( TIME_D->realtime_digital_clock()[0..3] )
                {
                case "����" :
                case "����" :
                        if( !s = find_object(file + "southgate"))
                                s = load_object(file + "southgate");

                        set("exits/north", file+"maze2/entry", s);
                        break;
                case "����" :
                        if( !s = find_object(file + "westgate"))
                                s = load_object(file + "westgate");

                        set("exits/east", file+"maze3/entry", s);
                        break;
                case "����" :
                        if( !s = find_object(file + "northgate"))
                                s = load_object(file + "northgate");

                        set("exits/south", file+"maze4/entry", s);
                        break;
                case "�賿" :
                        if( !s = find_object(file + "eastgate"))
                                s = load_object(file + "eastgate");

                        set("exits/west", file+"maze1/entry", s);
                        break;
                default :
                        break;
                }

                tell_room(s, HIG "ֻ���ú�¡¡������ʯ����������£�¶����ɽ������ڡ�\n" NOR);
                call_out("init_data", 180 + random(10), s, "enter"); // �����Ӻ����³�ʼ����������
                return "UNLOCKED";
        }
        set("lock/opened", result);

        remove_call_out("init_data");

        return query("lock/opened");

}

varargs void init_data(object s, string arg)
{
        string* rn = ({ "A", "B", "C", "D" });
        int ran_num;

        // ������䷿�������ÿ�ν���������˳�򶼲�һ��
        // ���Ի����������ݣ�������������ͳһ���������������ͳһ
        // �����˽��Ե��Ѷ�
        ran_num = random(4);
        set("number/lockroom1", rn[ran_num]);

        rn -= ({ rn[ran_num] });
        ran_num = random(3);
        set("number/lockroom2", rn[ran_num]);

        rn -= ({ rn[ran_num] });
        ran_num = random(2);
        set("number/lockroom3", rn[ran_num]);

        rn -= ({ rn[ran_num] });
        set("number/lockroom4", rn[0]);

        set("lock/unlocked", 0); // �������Ƿ�⿪
        set("lock/opened", "");  // �Ѿ��򿪵�������

        if( objectp(s) && arg == "enter" ) {
                tell_room(s, HIG "ֻ���ú�¡¡������ʯ������ɽ����ס�ˡ�\n" NOR);
                delete("exits/west", s);
                delete("exits/east", s);
                delete("exits/south", s);
                delete("exits/north", s);
        }

        return;

}

string get_result(string str1, string str2)
{
        int n1, n2;
        string temp;

        if( !strcmp(str1, str2) ) return "";

        temp = "";

        for( n1=0; n1<sizeof(str1); n1++ ) {
                for( n2=0; n2<sizeof(str2); n2++ ) {
                      if( str2[n2..n2] == str1[n1..n1] )
                              temp += str2[n2..n2];
                }
        }

        if( temp == "" ) return str1 + str2;

        for( n1=0; n1<sizeof(temp); n1++ )
        {
                str1 = replace_string(str1, temp[n1..n1], "");
                str2 = replace_string(str2, temp[n1..n1], "");
        }

        return str1 + str2;
}
