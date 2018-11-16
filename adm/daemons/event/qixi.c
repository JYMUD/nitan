// qixi.c �¼�����Ϧţ��֯Ů�����
// couple/id �����������ӱ�
#include <ansi.h>

void create() { seteuid(getuid()); }

#define STATUS_PROMPT           1
#define STATUS_START            2
#define STATUS_END              3

// ��ʼ�����¼�
void create_event()
{
        // ����7��7��ţ��֯Ů����ᣬ��ǰһ����ʾ
        EVENT_D->at_after(1, -7, -6, -12, STATUS_PROMPT);
}

// ����
private void do_bonus(object room)
{
        object *obs;
        string msg;
        int r;
        int p = 1;
        int i;

        obs = all_inventory(room);
        obs = filter_array(obs, (: playerp($1) && living($1) :));
        if (sizeof(obs) < 1)
                return;

        msg = HIW "\nֻ�����Ⱥ�ǹ�â��ţ�ȵ�����֣�ţ��֯Ů֮�ǹ⻪��ҫ��\n"
                  "�����ȵ��֮�ϣ�ɲ�Ǽ䣬Ⱥ��Χ�ƣ�������ʣ�һ��ʢ��\n"
                  "��������ν��\n" HIY
                  "����    ά���к��������й⡣\n"
                  "        ᪱�֯Ů���������塣\n"
                  "        �������壬���ɱ��¡�\n"
                  "        ����ǣţ�����Ա��䡣\n" HIW
                  "���˱������������й�ʫ�ƣ�\n" HIY
                  "����    ����ǣţ�ǣ���Ӻ�Ů��\n"
                  "        ���˹����֣�����Ū���̣�\n"
                  "        ���ղ����£����������ꡣ\n"
                  "        �Ӻ�����ǳ����ȥ������?\n"
                  "        ӯӯһˮ�ʣ����������\n" NOR;

        message("vision", msg, obs);
        msg = "��˵���³���" + implode(sizeof(obs) > 4 ? obs[0..3]->name(1) : obs->name(1), "��") +
              "����������̨����ţ��֯Ů����ᡣ";

        CHANNEL_D->do_channel(this_object(), "rumor", msg);

        obs=filter_array(obs,(:query("combat_exp", $1) >= 10000:));
        if (sizeof(obs) < 1)
                return;

        msg = HIG "�����ź�嫵�����Լ�ţ������֯Ů�Ƿ���ҫ�۵Ĺ�â���ƺ�������˼��\n" NOR;
        message("vision", msg, obs);

        for( i=0; i<sizeof(obs); i++ )
        {
                // �Ѿ����������ӱ�
                if( stringp(query("couple/id", obs[i])))
                {
                        if (query("combat_exp", obs[i]) < 1000000000)
                                addn("combat_exp", 3000 * p*2, obs[i]);
                        obs[i]->improve_potential(1000 * p*2 + random(1000 * p*2));
                        obs[i]->improve_skill("martial-cognize", 1000 * p*2 + random(1000* p*2), 1);
                        addn("magic_points", 30*p*2+random(21*p*2), obs[i]);
                }
                else
                {
                        if (query("combat_exp", obs[i]) < 1000000000)
                                addn("combat_exp", 3000 * p, obs[i]);
                        obs[i]->improve_potential(1000 * p + random(1000 * p));
                        obs[i]->improve_skill("martial-cognize", 1000 * p + random(1000* p), 1);
                        addn("magic_points", 30*p+random(21*p), obs[i]);
                }
        }
        MAP_D->record_rumor(obs, "����̨��Ϧʢ��", this_object());
}

// �¼�����
void trigger_event(int status)
{
        object room;

        room = find_object("/d/henshan/wangyuetai");

        // Ǯ��������
        switch (status)
        {
        case STATUS_PROMPT:
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "���³�����Ҫ���ˣ���˵������ǰ������̨����ţ��֯Ů����ᡣ");
                // ����18�������
                EVENT_D->at_after(0, 0, 1, -18, STATUS_START);
                break;

        case STATUS_START:
                if (objectp(room))
                        do_bonus(room);
                // һ��Сʱ�Ժ����
                EVENT_D->at_after(0, 0, 0, 1, STATUS_END);
                break;

        case STATUS_END:
                if (objectp(room))
                        message("vision", "����𽥰������������ָ���ƽ���������"
                                          "�·���������˹�����\n", room);
                // ����ִ��default�е�����

        default:
                create_event();
                break;
        }
}

// ����
string query_detail(string topic)
{
        switch (topic)
        {
        case "����̨��Ϧʢ��":
                return "ÿ�����³���ţ������֯Ů����ȵ����ᣬ�ǳ�׼ʱ���ʳ�֮Ϊ��Ϧʢ��ɫ��ÿ���������"
                       "ʱȺ����ҫ��������ˣ���������׳�ۡ�\n";
        }
}

