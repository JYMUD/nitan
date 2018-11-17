// newsd.c

#include <ansi.h>
#include <mudlib.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// 告搴#define TITLE   0       // 妯
#define TIME    1       // 
#define AUTHOR  2       // 浣
#define MSG     3       // у
#define VIEW    4       // 榛

#define NITAN_VER     CHINESE_MUD_NAME
// 涓姊#define MAX_NEWS_CAPACITY       1000

#include "/adm/etc/database.h"

// 淳存緔int     last_update_day = 0;

nosave mixed snotes = ({ });

// ヨ#ifdef DB_SAVE
string *query_notes()
{
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();

        snotes = DATABASE_D->db_all_query(sprintf("SELECT * from %s", NEWS_TABLE));

        if (! pointerp(snotes) || ! sizeof(snotes))
        {
                tell_object(this_player(), "辨綞茬怠錛í韓害茬琺錛ョ拌n");
                return ({});
        }

        return sort_array(snotes, (: $1[1] - $2[1] :));
}
#endif

void create()
{
        seteuid(ROOT_UID);
        restore();
}


void remove()
{
        save();
}

void mud_shutdown()
{
        save();
}

// 娣誨拌/ 辮嬈℃
#ifdef DB_SAVE
void add_view_time(mixed* news, int i)
{
        string sql;

        sql = sprintf("UPDATE %s SET view = view + %d WHERE time = %d",
                      NEWS_TABLE, i, news[TIME]);
        // tell_object(this_player(), WHT + sql + "\n" NOR);
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        DATABASE_D->db_query(sql);
}
#endif

// ずㄦ
void prompt_user(object me)
{
        int num;
        int total;
        mixed *notes;
        int last_read_time;

        last_read_time=query("last_read_news", me);
        if (! last_read_time)
        {
                tell_object(me, WHT "\n姝¤ㄩ + LOCAL_MUD_NAME() +
                                WHT "錛寰浣跨" HIY " news " NOR WHT
                                "戒護ラ煎俊\n" NOR);
                set("last_read_news", 971000000, me);
                return;
        }
#ifdef DB_SAVE
            notes = query_notes();
#else
        notes = query("notes");
#endif
        if (! arrayp(notes) || ! sizeof(notes))
                return;

        num = sizeof(notes);
        total = 0;
        while (num--)
        {
#ifdef DB_SAVE
                       if (notes[num][TIME] > last_read_time)
#else
                if (notes[num]["time"] > last_read_time)
#endif
                        total++;
                else
                        break;
        }
        if (! total)
                tell_object(me, "\n浣鵑璁\n");
        else
                tell_object(me, sprintf(WHT "\n浣辨 " HIY "%d" NOR
                                        WHT " 姊娌辮錛浣跨("
                                        HIY "news" NOR WHT ")戒護辮n" NOR, total));

        // 瀹
        if (previous_object() == find_object(LOGIN_D))
                me->start_call_out(bind((: call_other, __FILE__, "auto_notice", me :), me),
                                        10 + random(10));
}

// 欏ず欏// raw = 1: ’紺烘璁void show_news(object me, int raw)
{
        mixed *notes;
        int i, last_time_read;
        string msg;

#ifdef DB_SAVE
        notes = query_notes();
#else
        notes = query("notes");
#endif
        if (! pointerp(notes) || ! sizeof(notes))
        {
                tell_object(me, "娌浠諱拌n");
                return;
        }

        msg = "涓娑濡n"
              HIC " HIY " HIC "n" NOR;
        last_time_read=query("last_read_news", me);
        i = sizeof(notes);
        while (i--)
        {
#ifdef DB_SAVE

                if (raw && (notes[i][TIME] <= last_time_read))
                        break;

                msg += sprintf("%s[%3d]" NOR " %-" + (40
#ifndef LONELY_IMPROVED
                                                         + color_len(notes[i][TITLE])
#endif
                                                            ) +
                               "s %16s (%s) [%3d]\n",
                               (notes[i][TIME] > last_time_read ? HIY : ""),
                               i + 1, notes[i][TITLE],
                               // notes[i][AUTHOR], ctime(notes[i][TIME])[0..15], notes[i][VIEW]);
                               NITAN_VER, TIME_D->replace_ctime(notes[i][TIME]), notes[i][VIEW]);
#else
                if (raw && (notes[i]["time"] <= last_time_read))
                        break;

                msg += sprintf("%s[%3d]" NOR " %-" + (40 + color_len(notes[i]["title"])) +
                               "s %16s (%s)\n",
                               (notes[i]["time"] > last_time_read ? HIY : ""),
                               i + 1, notes[i]["title"],
                               // notes[i]["author"], ctime(notes[i]["time"])[0..15]);
                               NITAN_VER, TIME_D->replace_ctime(notes[i]["time"]));
#endif
        }

        if (i == sizeof(notes) - 1)
        {
                tell_object(me, "娌浠諱拌n");
                return;
        }

        msg += HIC " HIY " HIC "n" NOR;

        me->start_more(msg);
}

// 姝ゅ哥╁寰F_EDIT 涓法杓煎
#ifdef DB_SAVE
void done_post(object me, mixed *note, int n, string text)
#else
void done_post(object me, mapping note, int n, string text)
#endif
{
        int i;
        int pl;
        string sign;
        string pure;
        mapping *notes;
#ifdef DB_SAVE
        int t;
        string sql;
#endif

        if( !n)n=query("env/default_sign", me);
        if (! stringp(sign = query(sprintf("env/sign%d", n), me)))
        {
                // 告絎絀虹敖                for (i = 1; i <= 4; i++)
                {
                        sign = query(sprintf("env/sign%d", i), me);
                        if (stringp(sign)) break;
                }
        }

        if (stringp(sign))
        {
                sign = replace_string(sign, "~", "\""); 
                sign = replace_string(sign, "", "\\"); 
                sign = replace_string(sign, "\\n", "\n");
                sign = trans_color(sign, 3);
                pure = filter_color(sign);
                if (strlen(pure) >= 1 &&
                    pure[strlen(pure) - 1] != '\n')
                        sign += "\n";

                pure = filter_color(text);
                pl = strlen(pure);
                if (pl >= 1 && pure[pl - 1] != '\n')
                        text += "\n\n" + sign;
                else
                if (pl >= 2 && pure[pl - 2] != '\n')
                        text += "\n" + sign;
                else
                        text += sign;
        }

        text = color_filter(text) + NOR;
        text = replace_string(text, "\"", "");
#ifdef DB_SAVE
        note[MSG] = text;
        t = sizeof(note);
        sql = "";

        for (i = 0; i < t; i++)
        {
                if (stringp(note[i]))
                        sql += sprintf("\"%s\"", note[i]);
                else if (intp(note[i]))
                        sql += sprintf("%d", note[i]);
                else sql += sprintf("%O", note[i]);

                if (i != t - 1)
                        sql += ",";
        }
        // write(sql);
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        DATABASE_D->db_query(sprintf("INSERT INTO %s VALUES (%s)",
                                     NEWS_TABLE, sql));
#else
        note["msg"] = text;
        notes = query("notes");
        if (! pointerp(notes) || ! sizeof(notes))
                notes = ({ note });
        else
        {
                i = sizeof(notes) - 1;
                if (note["time"] <= notes[i]["time"])
                        note["time"] = notes[i]["time"] + 1;
                notes += ({ note });
        }

        // Truncate the notes if maximum capacity exceeded.
        if (sizeof(notes) > MAX_NEWS_CAPACITY)
                notes = notes[MAX_NEWS_CAPACITY / 4 .. MAX_NEWS_CAPACITY];

        set("notes", notes);
#endif
        tell_object(me, "拌煎瀹n");
        message("system", BLINK HIW "\n簿拌錛浣瀹惰news ョn\n" NOR,
                users());
        save();
}

// 煎拌
void do_post(object me, string arg)
{
        int n;
#ifdef DB_SAVE
        mixed *note;
#else
        mapping note;
#endif
        /*
        if (! VERSION_D->is_release_server())
        {
                tell_object(me, "ㄧ甯絝煎拌n");
                return;
        }
        */

        if (! wizardp(me) || ! interactive(me))
        {
                tell_object(me, "宸斧煎拌n");
                return;
        }

        if (! arg)
        {
                tell_object(me, "煎拌璜瀹欏\n");
                return;
        }

        if (sscanf(arg, "%s with %d", arg, n) != 2)
                n = 0;

        if (replace_string(arg, " ", "") == "")
                arg = "℃欏;
        else
                arg = trans_color(arg, 3) + NOR;
#ifdef DB_SAVE
        note = allocate(5);
        note[TITLE] = arg;
        note[AUTHOR]=me->name(1)+"-"+query("id", me);
        note[TIME] = time();
        note[VIEW] = 0;
#else
        note = allocate_mapping(4);
        note["title"] = arg;
        note["author"]=me->name(1)+"-"+query("id", me);
        note["time"] = time();
#endif
        me->edit(bind((: call_other, __FILE__, "done_post", me, note, n :), me));
}

// 辮拌
void do_read(object me, string arg)
{
        int num;
        mixed *notes;
        int last_read_time;

        last_read_time=query("last_read_news", me);
#ifdef DB_SAVE
        notes = query_notes();
#else
        notes = query("notes");
#endif
        if (! pointerp(notes) || ! sizeof(notes))
        {
                tell_object(me, "娌浠諱拌n");
                return;
        }

        if (! arg)
        {
                tell_object(me, "浣璁涓拌錛n");
                return;
        }

        if (arg == "new" || arg == "next")
        {
                if (! last_read_time)
                        num = 1;
                else
                        for (num = 1; num <= sizeof(notes); num++)
#ifdef DB_SAVE
                                if (notes[num - 1][TIME] > last_read_time)
#else
                                if (notes[num - 1]["time"] > last_read_time)
#endif
                                        break;
        } else
        if (! sscanf(arg, "%d", num))
        {
                tell_object(me, "浣璁騫炬拌錛n");
                return;
        }

        if (num < 1 || num > sizeof(notes))
        {
                tell_object(me, "娌拌n");
                return;
        }
        num--;
#ifdef DB_SAVE
        me->start_more(sprintf(HIC " HIY ""
                               " HIC "n"
                               NOR "[%3d] %-" + (40
#ifndef LONELY_IMPROVED
                                                    + color_len(notes[num][TITLE])
#endif
                                                      ) +
                               "s %16s (%s)\n" HIC " HIY ""
                               " HIC "n" NOR,
                               // num + 1, notes[num][TITLE], notes[num][AUTHOR],
                               num + 1, notes[num][TITLE], NITAN_VER,
                               TIME_D->replace_ctime(notes[num][TIME])) + notes[num][MSG]);
        // 娣誨榛 / 辮嬈℃
        add_view_time(notes[num], 1);
        // 璦╁涓辮拌        if (notes[num][TIME] > (int)last_read_time)
                set("last_read_news", notes[num][TIME], me);
#else
        me->start_more(sprintf(HIC " HIY ""
                               " HIC "n"
                               NOR " [%3d] %-" + (40 + color_len(notes[num]["title"])) +
                               "s %16s (%s)\n" HIC " HIY ""
                               " HIC "n\n" NOR,
                               // num + 1, notes[num]["title"], notes[num]["author"],
                               num + 1, notes[num]["title"], NITAN_VER,
                               TIME_D->replace_ctime(notes[num]["time"])) + notes[num]["msg"]);

        // Keep track which post we were reading last time.
        if (notes[num]["time"] > (int)last_read_time)
                set("last_read_news", notes[num]["time"], me);
#endif
}

// 拌
void do_discard(object me, string arg)
{
        mixed *notes;
        int num;
        string author, aid;
#ifdef DB_SAVE
        string sql;
#endif

        if (! arg || sscanf(arg, "%d", num) != 1)
        {
                tell_object(me, "浣繪誇姊\n");
                return;
        }
#ifdef DB_SAVE
        notes = query_notes();
#else
        notes = query("notes");
#endif
        if (! arrayp(notes) || num < 1 || num > sizeof(notes))
        {
                tell_object(me, "娌拌n");
                return;
        }

        num--;
#ifdef DB_SAVE
        if ((! stringp(author = notes[num][AUTHOR]) ||
             sscanf(author, "%*s-%s", aid) != 2 ||
             aid != query("id", me)) && !is_root(me) )
            //(string)SECURITY_D->get_status(me) != "(admin)")
        {
                tell_object(me, "澶╃繪浠漢煎\n");
                return;
        }
        sql = sprintf("DELETE FROM %s WHERE title = \"%s\" AND time = %d AND author = \"%s\" AND msg = \"%s\"",
                      NEWS_TABLE, notes[num][TITLE], notes[num][TIME], notes[num][AUTHOR], notes[num][MSG]);
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        DATABASE_D->db_query(sql);
#else
        if ((! stringp(author = notes[num]["author"]) ||
             sscanf(author, "%*s-%s", aid) != 2 ||
             aid != query("id", me)) && 
            (string)SECURITY_D->get_status(me) != "(admin)")
        {
                tell_object(me, "澶╃繪浠漢煎\n");
                return;
        }

        notes = notes[0..num - 1] + notes[num + 1..sizeof(notes) - 1];
        set("notes", notes);
        save();
#endif
        tell_object(me, "絎" + (num + 1) + " 姊...Okn");
}

// ╁
void auto_notice(object me)
{
        int num;
        mixed *notes;
        string msg;
        int last_read_time;

        if (! objectp(me))
                return;

        last_read_time=query("last_read_news", me);
#ifdef DB_SAVE
        notes = query_notes();
#else
        notes = query("notes");
#endif

        if (! pointerp(notes) || ! sizeof(notes))
                return;

        num = sizeof(notes) - 1;
#ifdef DB_SAVE
        if (notes[num][TIME] <= last_read_time)
#else
        if (notes[num]["time"] <= last_read_time)
#endif
                return;

        // 涓拌寰錛濮call_out
        me->start_call_out(bind((: call_other, __FILE__, "auto_notice", me :), me), 30 + random(30));

        if( !living(me) || query_temp("block_msg/all", me) )
                return;

        while (num-- > 0)
        {
#ifdef DB_SAVE
                if (notes[num][TIME] <= last_read_time)
#else
                if (notes[num]["time"] <= last_read_time)
#endif
                {
                        num++;
                        break;
                }

                // 綣肩ユ涓        }

        if (num < 0) num = 0;

        switch (random(5))
        {
        case 0:
                msg = HIM "涓錛簿懼浣㈠錛瑁
                      "涓嫉寸灝瀹ｈ璧蜂n" NOR;
                break;
        case 1:
                msg = HIM "頒紿涓瑁斧錛轟楝肩紲
                      "簿灝浣氨涓搗渚\n" NOR;
                break;
        case 2:
                msg = HIM "浣拷惰瑕浜哄浣浣
                      "綺鵑婊塊澶ф浜渚\n" NOR;
                break;
        case 3:
                msg = HIM "浣涓錛拷跺㈠轟＄э
                      "諱互寰瑕簿媧錛涓康蹇墊瑭\n" NOR;
                break;
        default:
                msg = HIM "涓錛簿戒頒錛
                      "浣蹇浠璧楓\n" NOR;
                break;
        }

        msg += HIG "拌綺鵑ù浣娑錛n" NOR;
        tell_object(me, msg);
#ifdef DB_SAVE
        me->start_more(sprintf(HIC " HIY ""
                               " HIC "n"
                               NOR "[%3d] %-" + (40 + color_len(notes[num][TITLE])) + "s %16s (%s)\n"
                               HIC " HIY ""
                               " HIC "n" NOR,
                               // num + 1, notes[num][TITLE], notes[num][AUTHOR],
                               num + 1, notes[num][TITLE], NITAN_VER,
                               TIME_D->replace_ctime(notes[num][TIME])) + notes[num][MSG]);
        // 娣誨榛 / 辮嬈℃
        add_view_time(notes[num], 1);

        // 璦╁涓辮拌        if (notes[num][TIME] > (int)last_read_time)
                set("last_read_news", notes[num][TIME], me);
#else
        me->start_more(sprintf(HIC " HIY ""
                               " HIC "n"
                               NOR "[%3d] %-" + (40 + color_len(notes[num]["title"])) + "s %16s (%s)\n"
                               HIC " HIY ""
                               " HIC "n" NOR,
                               // num + 1, notes[num]["title"], notes[num]["author"],
                               num + 1, notes[num]["title"], NITAN_VER,
                               TIME_D->replace_ctime(notes[num]["time"])) + notes[num]["msg"]);

        // Keep track which post we were reading last time.
        if (notes[num]["time"] > (int)last_read_time)
                set("last_read_news", notes[num]["time"], me);
#endif
        tell_object(me, HIM "拌綺鵑瑾寰娑けㄤｇт涓\n" NOR);
}

void do_search(object me, string arg)
{
        mixed *notes;
        int i, last_time_read, j;
        string msg, topic, theway;

#ifdef DB_SAVE
        notes = query_notes();;
#else
        notes = query("notes");
#endif
        if (! arrayp(notes) || ! sizeof(notes))
        {
                tell_object(me, "娌浠諱拌n");
                return;
        }

        if (! arg)
        {
                tell_object(me, "浣儲ｄ姊\n");
                return;
        }

        if (sscanf(arg, "%s %s", topic, arg) != 2)
        {
                tell_object(me, "浣芥緔㈡欏title)author)瀹document)n");
                return;
        } else
        {
                if (topic == "title")
                        theway = "妯";
                else
                if (topic == "author")
                        theway = "浣";
                else
                if (topic == "document")
                        theway = "у";
                else
                {
                        tell_object(me, "浣芥緔㈡欏title)author)瀹document)n");
                        return;
                }
        }

        last_time_read=query("last_read_news", me);

        msg = sprintf("規 " HIY "%s" NOR " 儲 " HIY "%s" NOR " 寰濡絎姊歡拌錛n"
                      HIC " HIY " HIC "n" NOR,
                      arg, theway);

        i = sizeof(notes);
        j = 0;
        while (i--)
        {
                if (topic == "document")
                {
#ifdef DB_SAVE
                        if (strsrch(notes[i][MSG], arg) == -1)
#else
                        if (strsrch(notes[i]["msg"], arg) == -1)
#endif
                                continue;
                } else
                {
#ifdef DB_SAVE
                        if (topic == "title")
                        {
                                if (strsrch(notes[i][TITLE], arg) == -1)
                                        continue;
                        }  else
                        if (topic == "author")
                        {
                                if (strsrch(notes[i][AUTHOR], arg) == -1)
                                        continue;
                        }
#else
                        if (strsrch(notes[i][topic], arg) == -1)
                                continue;
#endif
                }

                j++;
#ifdef DB_SAVE
                msg += sprintf("%s[%3d]" NOR " %-" + (40 + color_len(notes[i][TITLE])) +
                               "s %16s (%s)\n",
                               (notes[i][TIME] > last_time_read ? HIY : ""),
                               i + 1, notes[i][TITLE],
                               notes[i][AUTHOR], TIME_D->replace_ctime(notes[i][TIME]));
#else
                msg += sprintf("%s[%3d]" NOR " %-" + (40 + color_len(notes[i]["title"])) +
                               "s %16s (%s)\n",
                               (notes[i]["time"] > last_time_read ? HIY : ""),
                               i + 1, notes[i]["title"],
                               notes[i]["author"], TIME_D->replace_ctime(notes[i]["time"]));
#endif
                if (j > 99)
                {
                        msg += HIW "\n辨儲扮緄澶錛姝ゅ欏ず涓姊璜嬌ㄦ⒑靛|瑭\n" NOR;
                        break;
                }
        }

        if (j == 0)
        {
                tell_object(me, "規 " HIY + arg + NOR " 儲 " HIY + theway + NOR " 娌懼絎瑕\n");
                return;
        }

        msg += HIC " HIY " HIC "n" NOR;

        me->start_more(msg);
}

string query_save_file() { return DATA_DIR "newsd"; }
