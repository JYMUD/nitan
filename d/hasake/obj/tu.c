#include <ansi.h>

inherit ITEM;

mapping *long_desc = ({
 ([ "name":HIW"赤壁图"NOR,
    "long": "\n
                    《赤壁图》
此图写东坡赤壁泛舟景，笔意圆硬，如钢针镌铁。画山穷其凹凸，
写水状其盘涡，古画中面目之特立者。原为项元汴所藏，题为“北
宋朱锐画赤壁图，赵闲闲追和坡仙词真迹”，后人从之。考元遗山
集中，有题赵闲闲书赤壁词，末云：“赤壁图，武元直所绘。”故
此图实为武元直作。\n",]),

([ "name":YEL"虎溪三笑图"NOR,
   "long": "\n
                   《虎溪三笑图》 
虎溪三笑故事，庐山记云：“远法师居庐阜三十余年，影不出山，
迹不入俗，送客过虎溪，虎辄鸣号。昔陶元亮居栗里，山南陆修静
亦有道之士。远师尝送此二人，与语道合，不觉过之，因相与大笑。\n",]),

([ "name":GRN"溪山行旅图"NOR,
   "long": "\n
                   《溪山行旅图》
郁郁峨峨，其厚重浑沦，直似真山压面；邱陵寺宇，林麓森森，栈
桥高架于危流，驮队安行陌上。构景之妙，可云独至。全幅多用逆
笔，故老辣浑成，如钝刀刮铁，是传世范(宽)画极精之品。\n",]),

([ "name":HIY"文姬归汉图"NOR,
   "long": "\n
                   《文姬归汉图》
李唐所绘画册，本幅均绢本，均设色画。是册写《胡茄十八拍》诗
意，此页为第十三拍，幅上配原诗。\n",]),

([ "name":CYN"宫乐图"NOR,
   "long": "\n
                     《宫乐图》
本幅无作者名款，画女乐十二人。十人围案而坐，中四人正吹奏笙、
箫、古筝与琵琶诸乐器；侍立二人中，一人持拍相和；其余众人坐
听，状至闲适。此图石渠宝笈原标名元人画，然审其人物体态丰腴，
开脸留三白，发髻衣饰，设色画法皆系晚唐作风。\n",]),

([ "name":MAG"枇杷猿戏图"NOR,
   "long": "\n
                   《枇杷猿戏图》
枇杷一株，树干横斜自右而上，一枝左垂下挂，觉老树盘空，纸外
有画，布局新意别出。一猿挂枝下坠，如人之嬉戏秋千；一猿距干
注目，如人之旁观袖手，真能得物之情。至于用墨之精，用笔之稳，
用色之雅，尤有过人处，是宋无款画大幅中之精品。\n",]),

([ "name":YEL"明皇幸蜀图"NOR,
   "long": "\n
                   《明皇幸蜀图》
天宝十四年（七五五），安禄山举兵反，陷长安，明皇幸蜀避之。
画中著朱衣者即明皇。骑三骥照夜白，出栈道飞仙岭下，乍见小桥，
马惊不进。笔法精劲工细，青绿设色，绚灿华丽。\n",]),

([ "name":GRN"秋庭婴戏图"NOR,
   "long": "\n
                   《秋庭婴戏图》
本幅画童婴二人，拨枣为戏，精神专注，态貌如生，庭石芙蓉，秋光
满纸；另一圆凳上列玩具，地上双钹，一俯一仰，无一物不工。有言
苏画婴儿“着色鲜润，体度如生，熟玩之，不啻相语言笑者，可为神
矣！”本轴虽无款，但确系苏(汉臣)作。传世多幅题为苏汉臣婴戏图
中，以此画为最佳。除各局部精描细绘，造型姿态掌握得宜外，更令
人叹服的是传神的技巧与意境的呈现。\n",]),

});

void create()
{        
         mapping i = long_desc[random(sizeof(long_desc))];

         set_name(i["name"], ({ "tu juan", "tu", "juan"}));
         set("long", i["long"]);

        if (clonep())
                set_default_object(__FILE__);
        else {               
//                set("value", 1);
                set("unit", "张");
                set("weight", 100);
                set("material", "paper");
                }
        setup();
}