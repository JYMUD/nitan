// Room: god2
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"聖殿"NOR);
        set("long", HIC @LONG
你步如到聖殿中。聖殿里的空間顯得格外的大，你抬起頭來，竟看不到頂，
四排三十二根白柱向上伸去，也不知道有多高。仙霧繚繞中，你隱約看見前面一
個平台上有一把金椅，上面似乎坐着個沉思的老人，可你卻看不清他的面容，你
想再走上前去，卻有一股奇異的力量將你擋了回來，這恐怕就是神的力量吧，那
位老人應該就是天帝了吧。
　　在你和天帝中間，有一條長長的翡翠石道，兩旁坐着許多仙子，或歌或舞，
原來那和祥悅耳的音樂就是她們演奏出來的……。在聖殿中，你只覺得幸福和安
詳，天國原來就是這樣的……可是，你卻慢慢覺得這裡過於冷清，不由開始懷念
起那喧囂嘈雜的塵世來……
LONG
NOR   );
        set("no_magic", 1);
        setup();
}
