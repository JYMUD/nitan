// demonroom.c

// ������������
// n_time    ����ˢ��ʱ��
// n_npc     ����ˢ������
// n_max_npc ����������������������һ�����ˢ�¶��ٸ�����
// s_npc     �������࣬�ļ�·��
// n_av_refresh ƽ��ˢ������
// һ������ֻ�ܶ���һ�ֹ���

#include <ansi.h>

inherit ROOM;

// ����ˢ�����ʵļ��ʱ��
// ÿ��һ��ʱ��ͨ��һ���㷨����ˢ������
#define COUNT_REFRESH_TIME         45

void start_heart_beat()
{
        // Ĭ��Ϊ����1
        set_heart_beat(1);
}

void setup()
{
        mapping product;
        string mine;
        int count;

        //set("no_clean_up", 1);
                set("no_roar", 1);
                //set("no_flyto", 1); // ���������MISS������Ѿ���horse.c������

                // ���÷����������
                if (! query("n_time"))set("n_time", 60);                                // Ĭ�Ϲ���45��ˢ��һ��
                if (! query("n_npc"))set("n_npc", 1);                                        // Ĭ�Ϲ���ÿ��ˢ��һ��
                if (! query("n_max_npc"))set("n_max_npc", 1);                                //Ĭ��Ϊ1������������������������һ�����ˢ�¶��ٸ�����
                if (! query("s_npc"))set("s_npc", "/clone/quarry/zhu");                 // Ĭ�Ϲ���ΪҰ�ޡ���

                set("n_die", 0);                    // ��λʱ���ڹ�����������
                if (query("last_refresh_time"))     // �ϴ�ˢ��ʱ��
                        set("last_refresh_time", query("last_refresh_time"));

                if (query("last_count_refresh_time"))     // �ϴμ���ˢ�����ʵ�ʱ��
                        set("last_count_refresh_time", query("last_count_refresh_time"));

                ::setup();

        start_heart_beat();
}

void init()
{
                if (random(2))this_player()->start_busy(1);
}

// ÿ������ִ�еĲ���
// ˢ��ʱ�䵽��ˢ�¹���������´�ˢ��ʱ�估��������

void heart_beat()
{
                object ob_npc;
                object env;
                object *inv, *obs;
                int n_left_npc; // ��ǰ����������������ɹ������Ĳ�
                int n_npc; // ���ù��������
                int i;  // ��������
                int refresh_total; // ʱ�������ܹ�ˢ�µĹ�������
                int new_n_time;  // �����µ�ˢ��ʱ��
                int new_n_npc; // ���ù���ˢ������

                //object me;

                //me = find_player("rcwiz");

                env = this_object();

                if (new_n_time <= 0)new_n_time = env->query("n_time");
                if (new_n_npc <= 0)new_n_time = env->query("n_npc");

                // ���Ϊ�����������ж��������Ƿ񿪷�
                if (env->query("penglai") && ! GIFT_D->is_open_pld())return;

                inv = all_inventory(env);

                obs = filter_array(inv, (: base_name($1) == query("s_npc") :)); // ���˵��Ǳ��������������ļ�

                // ʱ�䵽����ˢ�¹���
                n_left_npc = query("n_max_npc") - sizeof(obs);
                if (n_left_npc > 0 && time() - query("last_refresh_time") >= query("n_time"))
                {
                        n_npc = n_left_npc >= query("n_npc") ? query("n_npc") : n_left_npc;

                        for (i = 0; i < n_npc; i ++ )
                        {
                                ob_npc = new(query("s_npc"));
                                if (! objectp(ob_npc))
                                {
                                        log_file("mroom", "�޷��ҵ�npc�ļ� " + query("s_npc") + "\n");
                                        return;
                                }

                                ob_npc->move(env);
                        }

                        set("last_refresh_time", time());
                }

                       // ����ˢ�����ʵ��㷨
                // ÿ���COUNT_REFRESH_TIME�����һ�Σ�Ȼ����ݼ�������������
                // ����ˢ��ʱ�������
                if (time() - query("last_count_refresh_time") >= COUNT_REFRESH_TIME)
                {
                        // �㷨����
                        // ͨ��ͳ�Ƶ�λʱ���ڹ�����������
                        // �ж�ˢ���ٶȣ�ֻ���������ٻ򲻱�����������������ӵ�����

                        // ʱ�������ܹ�ˢ�µĹ�������
                        refresh_total = COUNT_REFRESH_TIME / query("n_time") * query("n_npc");

                        if (refresh_total < 1)refresh_total = 1;

                        // ����ˢ��ʱ�䰴�ձ�������
                        new_n_time = query("n_time") * query("n_die") / refresh_total;

                        // ��ˢ����ˢ�����ٹֶ�ȫ��ɱ������ˢ��
                        if (new_n_time >= query("n_time"))
                        {
                                new_n_time = new_n_time - new_n_time / 3;
                                new_n_npc = query("n_npc") + 1;
                        }
                        // ɱ�����ﳬ��ˢ����һ������ˢ��
                        else if (new_n_time >= query("n_time") / 2)
                        {
                                new_n_time = new_n_time - new_n_time / 5;
                                new_n_npc = query("n_npc") + 1;
                        }
                        else // δ����һ��ˢ���ٶ��򽵵�ˢ���ٶ�
                        {
                                new_n_time = new_n_time + new_n_time / 2;
                                new_n_npc = query("n_npc") / 2;
                        }

                        // ����ж�
                        if (new_n_time > query("n_time"))new_n_time = query("n_time");
                        if (new_n_time <= 0)new_n_time = query("n_time"); // n_die == 0
                        if (new_n_time < 15)new_n_time = 15;
                        if (new_n_npc < 1)new_n_npc = 1;
                        if (new_n_npc > query("n_max_npc"))new_n_npc = query("n_max_npc");

                        set("n_time", new_n_time);
                        set("n_npc", new_n_npc);

                        // ������0
                        set("n_die", 0);

                        // ��¼���μ����ʱ��
                        set("last_count_refresh_time", time());

                }

}

// ��������ʱ֪ͨ�÷����ۼƹ��������������Ա����ˢ������
void npc_die(object ob)
{
        add("n_die", 1);
}
