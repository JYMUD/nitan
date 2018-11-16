// broadcastd.c

#include <ansi.h>

inherit F_SAVE;
inherit F_DBASE;

mapping push_msg = ([]);
string query_save_file() { return DATA_DIR + "broadcastd"; }

/* ��ʱͨ��pushmsg ָ�����͵Ĺ㲥��Ϣ
��ʽ��
push_msg = ([
   "msg���" :  ([
      "�㲥����"       : "xxx",
      "���ʱ��"       : N, // ��λ��
      "ѭ������"       : N, // int
      "�ϴι㲥ʱ�䣺  : TIME,
      "��ѭ������"     : N, // int
   ]),
]);
*/
void create()
{
        seteuid(getuid());
        set("channel_id", "�㲥����");
        CHANNEL_D->do_channel( this_object(), "sys", "�㲥�����Ѿ�������");

        if( !restore() && !mapp(push_msg) )
                push_msg = ([]);

        SCHEDULE_D->set_event(10, 1, this_object(), "broadcast_push_msg");
}

void broadcast_push_msg()
{
        string *key;
        int i;

        if (! sizeof(push_msg))return;

        key = keys(push_msg);

        for (i = 0; i < sizeof(key); i ++)
        {
                if( time() - push_msg[key[i]]["last_broadcast"] < push_msg[key[i]]["delay"] )
                        continue;

                if( push_msg[key[i]]["broadcast_times"] >= push_msg[key[i]]["times"] )
                        continue;

                message_system(HIW + push_msg[key[i]]["msg"] + "\n" NOR);
                push_msg[key[i]]["last_broadcast"] = time();
                push_msg[key[i]]["broadcast_times"] += 1;
        }
        return;
}

public int add_push_msg(string title, string info, int delay, int times)
{
        string *key;

        if (! sizeof(push_msg)) key = ({});
        else
                key = keys(push_msg);

        // �������Ƿ��ظ�
        if (sizeof(key))
        {
                if (member_array(title, key) != -1)
                        return notify_fail("�����ظ���\n");
        }

        if (sizeof(info) > 300)
                return notify_fail("��Ϣ���ȳ���" + sprintf("%d", sizeof(info) - 88) + "���ַ���\n");

        if (delay < 1)
                return notify_fail("���ʱ�䲻�ܵ���1�롣\n");

        if (times < 1)
                return notify_fail("ѭ����������С��1��\n");

        if( !mapp(push_msg) ) push_msg = ([]);
        push_msg += ([
              title : ([
                  "msg"       : info,
                  "delay"     : delay, // ��λ��
                  "times"     : times,
                  "last_broadcast"   : 0,
                  "broadcast_times"  : 0,
              ])
        ]);

        save();
        write("��ӳɹ���ʹ��ָ�� pushmsg list �鿴��ǰ��Ϣ�б�\n");
        return 1;
}

public int show_push_lish()
{
        string *key, msg;
        int i;

        msg = HIC "\n=----------------------------------------=\n" NOR;

        if (! sizeof(push_msg))
                return notify_fail("��ǰû��PUSHMSG��Ϣ��\n");

        key = keys(push_msg);

        for (i = 0; i < sizeof(key); i ++)
        {
                msg += HIY "[" + key[i] + "]    " HIC + "���" + sprintf("%d", push_msg[key[i]]["delay"]) + "��    " +
                       "ѭ��" + sprintf("%d/%d", push_msg[key[i]]["broadcast_times"],push_msg[key[i]]["times"] ) + "\n" NOR;
                msg += HIY "���ݣ�" + HIC + push_msg[key[i]]["msg"] + "\n\n";
        }
        msg += HIC "\n=----------------------------------------=\n" NOR;
        msg += HIR "ָ�� pushmsg del [TITLE] ��ɾ���㲥��\n" NOR;

        write(msg);
        return 1;
}

public int delete_push_msg(string title)
{
        string *key;

        if (! sizeof(push_msg))key = ({});
        else
                key = keys(push_msg);

        // �������Ƿ��ظ�
        if (sizeof(key))
        {
                if (member_array(title, key) == -1)
                        return notify_fail("�޴˱��⣡\n");
        }
        else
                return notify_fail("��ǰ��PUSHMSG��\n");

        map_delete(push_msg, title);

        write(title + " del OK.\n");
        save();
        return 1;
}

void reback_lonely_book()
{
        mixed *file;
        int iCount;
        string *t;
        object book;

        remove_call_out("reback_lonely_book");
        call_out("reback_lonely_book", 3600*24); // 24Сʱ����һ��

        file = get_dir("/clone/lonely/book/", -1);

        message_system(HIW "ϵͳ����Ψһ��Ʒ��\n" NOR);

        for (iCount = 0; iCount < sizeof(file); iCount ++)
        {
                book = find_object("/clone/lonely/book/" + file[iCount][0]);
                if (objectp(book))destruct(book);
        }
        // Ǭ����Ų��
        book = find_object("/clone/book/qiankun_book" );
        if (objectp(book))destruct(book);

        return;
}

int remove()
{
        save();
        return 1;
}

