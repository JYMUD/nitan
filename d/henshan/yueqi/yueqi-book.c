#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "「古樂器篇」" NOR, ({ "yueqi book", "yueqi", "book" }));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", HIW "記載着古代樂器的筆記，你閑着沒事兒"
                            "可以看看(read)。\n" NOR);
                set("value", 50);
                set("material", "paper");
        }
        setup();
}

void init()
{
        add_action("do_read", "read");

}

int do_read(string arg)
{
        if (arg == "yueqi book" || arg == "yueqi" || arg == "book")
                return notify_fail(WHT "\n"
"-----------------------------------------------------\n\n"
"                   中國古樂器介紹\n\n"
"    瑟：瑟，古代彈弦樂器。其歷史久遠。據《儀禮》記載，\n"
"古代鄉飲酒禮、鄉射禮、燕禮中，都用瑟伴奏唱歌。戰國至\n"
"秦漢之際盛行“竽瑟之歌”。魏晉南北朝時期，瑟是伴奏相\n"
"和歌的常用樂器。隋唐時期用於清樂。以後則只用於宮廷雅\n"
"樂和丁祭音樂 \n\n"
"   排簫：吹奏樂器。又名洞簫、雅簫、頌簫 鳳簫、雲簫等。\n"
"早在原始社會，已有用蘆葦編製成的葦龠。排簫管數、長度，\n"
"歷代記載不同，而且形制、大小有別。唐代以前，排簫逕稱\n"
"簫。唐宋以後，由於單管豎吹的簫日漸流行，便稱編管簫為\n"
"排簫，以示區別。元明兩代，排簫改進為精緻的簫。清代\n"
"排簫為雙翼形制的簫。\n\n"
"   鍾：古代打擊樂器。鍾在古代“八音”分類法中屬金部。\n"
"鍾盛行於青銅時代。鍾在古代不僅是樂器，還是地位和權力\n"
"象徵的禮器。王公貴族在朝聘、祭祀等各種儀典、宴饗與日\n"
"常燕樂中，廣泛使用着鍾樂。敲擊鐘的正鼓部和側鼓部可發\n"
"兩個頻率音，這兩個音，一般為大小三度音程。由於青銅鐘\n"
"質料堅實和耐腐蝕，數千年來，給我們留下了古代真實的音\n"
"響、 留下了豐富的古鐘遺產，它們不分朝代地並存於今世，\n"
"集歷代政治、歷史、音樂、民俗、冶煉、宗教等各種文化\n"
"內涵於一身，形成奇特的中華古鐘文化。\n\n"
"   磬： 質料主要是石灰石，其次是青石和玉石。均上作倨\n"
"句形，下作微弧形。大小厚薄各異。磬架用銅鑄成，呈單面\n"
"雙層結構，橫樑為圓管狀。立柱和底座作怪獸狀，龍頭、鶴\n"
"頸、鳥身、鱉足。造型奇特，製作精美而牢固。磬分上下兩\n"
"層懸掛，每層又分為兩組，一組為六件，以四、五度關係排\n"
"列；一組為十件，相鄰兩磬為二、三、四度關係。它們是按\n"
"不同的律（調）組合的。\n\n"
"   笙:  吹奏樂器。早在大約三千多年前的商代已有笙的雛\n"
"形。古代笙用匏做笙斗，在樂器的八音分類法中屬匏類。\n\n"
"   塤:  吹奏樂器。原始社會已出現。塤的起源與先民的勞\n"
"動生產活動有關，隨着社會的進步而被當成單純的樂器。\n\n"
"   鼓： 打擊樂器。甲骨文中有鼓字，傳說最早的鼓，皮面\n"
"用棰敲擊，為祀神之用。懸鼓，懸掛起來敲擊的鼓。虎座鳳\n"
"懸鼓，屬“懸而擊之”的懸鼓。\n\n"
"  骨笛：骨笛，吹管樂器。距今約八千多年左右，為新石器\n"
"時代早期遺物。骨笛由禽骨製作，長約20厘米、直徑約一厘\n"
"米，開管、管側開七個音孔，無吹孔和笛膜孔。吹奏時需將\n"
"骨笛斜持，頂端吹口與嘴保持一定的傾斜度。\n\n" HIG
"                 一脈相承琴器幾千載\n\n"
"                 大浪淘沙古器貌未改\n\n" WHT
"-----------------------------------------------------\n"
"\n\n" NOR);
}