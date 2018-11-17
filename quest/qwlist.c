//qwlist.c
//Last Modified by firefly    2004/3/31

// /d/底下的東西都加進去了
/*除注釋中去掉的東東外，還去掉了：
柴 清茶 熊膽 仙丹 雪蓮 帛書 人蔘
白綢裙 粗布袍 白絲衣 神仙倒 老山參 水晶鞋
白色藥粉 紅色藥粉 黑色藥粉 黃色藥粉 綠色藥粉 胡籮卜干 烤山雞腿 雪參玉蟾丹 
草藥 拿不起來   
續命八丸 給了不要  */

inherit SKILL;
#include <ansi.h>;
mapping *quest = ({

//book (去掉"帛卷"、"道德經"、"三字經"、"百家姓"、"千字文"、"九章算術"、"論語"、"鐵掌掌譜")
//     (去掉"一陽指訣"、"一陽指法譜"、"六脈神劍譜"、"雲龍鞭法"、"「金蛇秘芨」"三冊、"毒經下篇")
//     (去掉"冰雪心法")
        ([        "quest":        "薄絹"]),                             
        ([        "quest":        "石板"]),
        ([        "quest":        "棋譜"]),
        ([        "quest":        "羊皮"]),
        ([        "quest":        "舊竹片"]),
        ([        "quest":        "羊皮書"]),
        ([        "quest":        "黃石譜"]),
        ([        "quest":        "血棋衣"]),
        ([        "quest":        "十八木偶"]),                      
        ([        "quest":        "十八泥偶"]),
        ([        "quest":        "辟邪劍譜"]),
        ([        "quest":        "唐詩劍譜"]),
        ([        "quest":        "意形步法"]),
        ([        "quest":        "拳譜總訣"]),
        ([        "quest":        "鞭法總訣"]),
        ([        "quest":        "掌法總譜"]),
        ([        "quest":        "手法精要"]),
        ([        "quest":        "杖法通解"]),
        ([        "quest":        "棍法通解"]),
        ([        "quest":        "棒法入門"]),
        ([        "quest":        "華山劍譜"]),
        ([        "quest":        "岳家槍法"]),
        ([        "quest":        "段家斧法"]),
        ([        "quest":        "玉女劍譜"]),
        ([        "quest":        "嵩山劍譜"]),
        ([        "quest":        "太極拳經"]),
        ([        "quest":        "密宗心經"]),
        ([        "quest":        "崑崙心法"]),
        ([        "quest":        "兩儀劍心得"]),
        ([        "quest":        "太極十三勢"]),
        ([        "quest":        "神龍八式手法"]),
        ([        "quest":        "易筋經文學篇"]),
        ([        "quest":        "胡家刀譜殘篇"]),
        ([        "quest":        "[33m洗髓經[2;37;0m"]),
        ([        "quest":        "[1;36m長石片[2;37;0m"]),

        ([        "quest":        "群星璀璨圖"]),
        ([        "quest":        "[1;36m金雁圖譜[2;37;0m"]),
        ([        "quest":        "[1;37m天長掌法譜[2;37;0m"]),
        ([        "quest":        "[1;33m昊天掌法譜[2;37;0m"]),

        ([        "quest":        "拆招秘術"]),
        ([        "quest":        "五毒真經"]),
        ([        "quest":        "毒經上篇"]),
        ([        "quest":        "毒經中篇"]),

        ([        "quest":        "青字九打"]),
        ([        "quest":        "城字十八破"]),        

        ([        "quest":        "[1;36m飛雪掌譜[2;37;0m"]),
        ([        "quest":        "[1;37m雪山劍譜[2;37;0m"]),
        ([        "quest":        "[1;33m金烏刀譜[2;37;0m"]),

        ([        "quest":        "毒經"]),
        ([        "quest":        "蛇經"]),
        ([        "quest":        "易經"]),
        ([        "quest":        "藥理經"]),
        ([        "quest":        "草藥經"]),
        
        ([        "quest":        "雲龍經"]),
        ([        "quest":        "雲龍劍譜"]),
        ([        "quest":        "雲龍經「上卷」"]),
        ([        "quest":        "雲龍經「下卷」"]),

        ([        "quest":        "華嚴經"]),
        ([        "quest":        "般若經"]),
        ([        "quest":        "金剛經"]),
        ([        "quest":        "阿含經"]),
        ([        "quest":        "維摩經"]),
        ([        "quest":        "法華經"]),
        ([        "quest":        "無量壽經"]),
        ([        "quest":        "大般涅磐經"]),                     
        ([        "quest":        "波羅蜜多心經"]), 

        ([        "quest":        "萬壽道藏"]),
        ([        "quest":        "道德經「上卷」"]),
        ([        "quest":        "道德經「下卷」"]),
        ([        "quest":        "道德經「第一章」"]),
        ([        "quest":        "道德經「第二章」"]),
        ([        "quest":        "道德經「第八章」"]),
        ([        "quest":        "道德經「第十三章」"]),
        ([        "quest":        "道德經「第十六章」"]),
        ([        "quest":        "道德經「第十八章」"]),

        ([        "quest":        "「九陰真經」上冊"]),
        ([        "quest":        "「九陰真經」下冊"]),
        ([        "quest":        "「九陽真經」第一卷"]),
        ([        "quest":        "「九陽真經」第二卷"]),
        ([        "quest":        "「九陽真經」第三卷"]),
        ([        "quest":        "「九陽真經」第四卷"]),
        ([        "quest":        "[1;33m《九陰真經》[2;37;0m"]),

        ([        "quest":        "『星宿毒經〖上冊〗』"]),
        ([        "quest":        "『星宿毒經〖下冊〗』"]),

        ([        "quest":        "[1;35m玉女心經上冊[2;37;0m"]),
        ([        "quest":        "[1;35m玉女心經下冊[2;37;0m"]),

        ([        "quest":        "九宮八卦圖譜"]),
        ([        "quest":        "旋風掃葉腿法"]),
        ([        "quest":        "[1;36m「河圖」[2;37;0m"]),
        ([        "quest":        "[1;36m「洛書」[2;37;0m"]),
        ([        "quest":        "[1;33m「易經序卦篇」[2;37;0m"]),
        ([        "quest":        "[1;33m「易經說卦篇」[2;37;0m"]),
        ([        "quest":        "[1;33m「易經雜卦篇」[2;37;0m"]),
        ([        "quest":        "[1;33m「易經繫辭篇」[2;37;0m"]),

        ([        "quest":        "[1;33m黃帝內經[2;37;0m"]),
        ([        "quest":        "[1;33m華佗內昭圖[2;37;0m"]),
        ([        "quest":        "[1;33m王叔和脈經[2;37;0m"]),
        ([        "quest":        "[1;33m子午針灸經[2;37;0m"]),
        ([        "quest":        "[1;33m孫思邈千金方[2;37;0m"]),
        ([        "quest":        "[1;36m胡青牛醫經[2;37;0m"]),
        ([        "quest":        "[1;36m王難姑毒經[2;37;0m"]),

/*        ([        "quest":        "散花掌法"]),
        ([        "quest":        "羅漢拳法"]),
        ([        "quest":        "般若掌法"]),
        ([        "quest":        "韋陀掌法"]),
        ([        "quest":        "龍爪功法"]),
        ([        "quest":        "寂滅爪法"]),
        ([        "quest":        "摩訶指法"]),
        ([        "quest":        "一指禪功"]),
        ([        "quest":        "修羅刀法"]),
        ([        "quest":        "韋陀棍法"]),
        ([        "quest":        "普渡杖法"]),
        ([        "quest":        "伏魔劍法"]),
        ([        "quest":        "彈腿腿法"]),
        ([        "quest":        "醉棍棍法"]),
        ([        "quest":        "風雲手手法"]),
        ([        "quest":        "大金剛拳法"]),
        ([        "quest":        "如來千葉手手法"]),
        ([        "quest":        "如影隨形腿腿法"]),*/

        ([        "quest":        "天羽奇劍劍譜"]),
        ([        "quest":        "天山六陽掌法圖上冊"]),
        ([        "quest":        "天山六陽掌法圖下冊"]),
        ([        "quest":        "天山折梅手法圖上卷"]),
        ([        "quest":        "天山折梅手法圖下卷"]),

        ([        "quest":        "[1;31m正氣吟[2;37;0m"]),
        ([        "quest":        "[35m紫霞密芨[2;37;0m"]),
        ([        "quest":        "[1;35m紫氳正譜[2;37;0m"]),
        ([        "quest":        "[1;35m紫氳次譜[2;37;0m"]),
        ([        "quest":        "[1;35m紫氳外譜[2;37;0m"]),
                  
        
//jiasha (袈裟)                         
        ([        "quest":        "黃布袈裟"]),
        ([        "quest":        "護法袈裟"]),
        ([        "quest":        "灰布鑲邊袈裟"]),                  
        ([        "quest":        "白布黑邊袈裟"]),
        ([        "quest":        "青布鑲邊袈裟"]),
        ([        "quest":        "金邊黑布袈裟"]),
        ([        "quest":        "[30m黑色袈裟[2;37;0m"]),    //xueshan                  
        ([        "quest":        "[35m紫色袈裟[2;37;0m"]),    //xueshan
        ([        "quest":        "[1;36m青色袈裟[2;37;0m"]),  //xueshan        
        ([        "quest":        "[1;31m紅色袈裟[2;37;0m"]),  //xueshan
        ([        "quest":        "[1;33m黃色袈裟[2;37;0m"]),  //xueshan

//baituo (去掉"海口大碗"、"蛇鞭"、"青色絲袍" )

        ([        "quest":        "鑰匙"]),
        ([        "quest":        "豆漿"]),
        ([        "quest":        "蛋糕"]),                               
        ([        "quest":        "草莓"]),
        ([        "quest":        "蛇皮"]),
        ([        "quest":        "蛇杖"]),
        ([        "quest":        "柴刀"]),
        ([        "quest":        "木柴"]),
        ([        "quest":        "貂裘"]),         
        ([        "quest":        "蛇膽粉"]),        
        ([        "quest":        "金蛇膽"]),
        ([        "quest":        "青蛇膽"]),
        ([        "quest":        "蛇膽膏"]),
        ([        "quest":        "繡花鞋"]),        
        ([        "quest":        "引路神蛇"]),
        ([        "quest":        "白色長袍"]),                        

//beijing (去掉"暗門鑰匙"(不能給)、"小馬甲")

        ([        "quest":        "腰帶"]),        
        ([        "quest":        "貂皮"]),
        ([        "quest":        "錦緞"]),
        ([        "quest":        "金葉"]), 
        ([        "quest":        "拂塵"]),
        ([        "quest":        "禪杖"]),
        ([        "quest":        "魚翅"]),
        ([        "quest":        "女兒紅"]),
        ([        "quest":        "金鑰匙"]),
        ([        "quest":        "青布僧衣"]), 
        ([        "quest":        "明史輯略"]),        

//changan (去掉"馬褂"、"綢袍"、"粗布衣"、"輕紗長裙"、"[33m繡花小鞋[2;37;0m"、還有那些桌子椅子)
                                                                           
        ([        "quest":        "[36m秦磚[2;37;0m"]),        
        ([        "quest":        "[1;36m漢瓦[2;37;0m"]),        
        ([        "quest":        "[1;33m陶俑[2;37;0m"]),  

//city (去掉"橄欖核船")

        ([        "quest":        "軍服"]),                               
        ([        "quest":        "藥粉"]),
        ([        "quest":        "狗皮"]),
        ([        "quest":        "叫化雞"]),
        ([        "quest":        "衙役服"]),
        ([        "quest":        "黑龍鞭"]),
        ([        "quest":        "大珍珠"]),
        ([        "quest":        "金項鏈"]), 
        ([        "quest":        "金戒指"]), 
        ([        "quest":        "漆沙硯"]),        
        ([        "quest":        "繡花小鞋"]),        
        ([        "quest":        "粉紅綢衫"]),
        ([        "quest":        "牢房鑰匙"]),        
        ([        "quest":        "[32m大樹枝[2;37;0m"]),
        ([        "quest":        "[1;36m鵝卵石[2;37;0m"]),
        ([        "quest":        "[1;37m大石頭[2;37;0m"]),  
        ([        "quest":        "[1;36m蛇形杖[2;37;0m"]),
        
//dali

        ([        "quest":        "虎皮"]),                               
        ([        "quest":        "蠻刀"]),
        ([        "quest":        "紫袍"]),
        ([        "quest":        "筒裙"]),
        ([        "quest":        "毛毯"]),
        ([        "quest":        "砍刀"]),
        ([        "quest":        "白衣"]),
        ([        "quest":        "瑤琴"]),
        ([        "quest":        "白綢衫"]),
        ([        "quest":        "紡紗機"]),
        ([        "quest":        "大理雪梨"]),
        ([        "quest":        "擺夷短裙"]),
        ([        "quest":        "青色道袍"]),
        ([        "quest":        "錦衣軍服"]),
        ([        "quest":        "黃衣軍服"]),
        ([        "quest":        "台夷短裙"]),
        ([        "quest":        "台夷頭巾"]),
        ([        "quest":        "烏夷長裙"]),
        ([        "quest":        "烏夷大麾"]),
        ([        "quest":        "圓領小襖"]),
        ([        "quest":        "貝殼項鏈"]),
        ([        "quest":        "[1;37m滿月[2;37;0m"]),                
        ([        "quest":        "[1;31m山茶花[2;37;0m"]),
        ([        "quest":        "[1;31m七仙女[2;37;0m"]),
        ([        "quest":        "[1;32m八寶妝[2;37;0m"]),
        ([        "quest":        "[1;34m八仙過海[2;37;0m"]),
        ([        "quest":        "[1;33m落第秀才[2;37;0m"]), 
        ([        "quest":        "[1;32m十三太保[2;37;0m"]),
        ([        "quest":        "[1;31m十八學士[2;37;0m"]),
        ([        "quest":        "[1;31m二[37m喬[2;37;0m"]),
        ([        "quest":        "[1;34m眼[1;37m兒媚[2;37;0m"]),
        ([        "quest":        "[1;31m紅妝[1;37m素裹[2;37;0m"]),
        ([        "quest":        "[35m風[37m塵三[1;31m俠[2;37;0m"]),
        ([        "quest":        "[1;37m倚[1;32m欄[1;31m嬌[2;37;0m"]),
        ([        "quest":        "[1;37m抓破[1;32m美[2;37;0m人[1;31m臉[2;37;0m"]),

//emei (去掉 "中藥"、"硫磺"、"霹靂彈"、"天香斷續膏"、)

        ([        "quest":        "軟劍"]),                   
        ([        "quest":        "粉條"]),       //恆山
        ([        "quest":        "淡黃衫"]),                 
        ([        "quest":        "菠菜粉條"]),                          
        ([        "quest":        "琉璃茄子"]),
        ([        "quest":        "麻辣豆腐"]),
        ([        "quest":        "珊瑚白菜"]),
        ([        "quest":        "清水葫蘆"]),
        ([        "quest":        "紅燒茄子"]),        //恆山        
        ([        "quest":        "醋溜白菜"]),   //恆山
        ([        "quest":        "芙蓉花菇"]),   //少林
        ([        "quest":        "夾心荸薺"]),   //少林
        ([        "quest":        "密汁甜藕"]),   //少林
        ([        "quest":        "拔絲山藥"]),   //少林
        ([        "quest":        "[37m灰色道袍[2;37;0m"]),
        ([        "quest":        "[1;36m天香斷續膏[2;37;0m"]),

//foshan

        ([        "quest":        "菜刀"]),                               
        ([        "quest":        "紫袍"]), 
        ([        "quest":        "[1;37m石塊[2;37;0m"]),
        ([        "quest":        "[32m小樹枝[2;37;0m"]),
        ([        "quest":        "[1;37m白合花[2;37;0m"]),              
        ([        "quest":        "[1;31m莎欏花[2;37;0m"]),
        ([        "quest":        "[1;34m蕙蘭花[2;37;0m"]),
        
//fuzhou (去掉"袈裟")        

//guanwai
        
        ([        "quest":        "闖王寶刀"]),                           
        ([        "quest":        "[1;36m鐵琵琶[2;37;0m"]),
        ([        "quest":        "[1;33m獨腳銅人[2;37;0m"]),

//guiyun

        ([        "quest":        "書信"]), 
        ([        "quest":        "桿秤"]),                                
        ([        "quest":        "砍柴斧"]),                              
        ([        "quest":        "熟鐵扁擔"]),
        ([        "quest":        "油紙摺扇"]),
        ([        "quest":        "[1;32m青布衣[2;37;0m"]),
        ([        "quest":        "[1;31m紅綾襖[2;37;0m"]),

//gumu

              ([        "quest":        "玉蜂漿"]),                               
        ([        "quest":        "玉蜂蜜"]),
        ([        "quest":        "蜂漿瓶"]),  
        ([        "quest":        "[1;37m銀索[2;37;0m"]),

//hangzhou

        ([        "quest":        "[1;32m凝碧劍[2;37;0m"]),              

//hanzhong

        ([        "quest":        "[31m血竭[2;37;0m"]),                 
        ([        "quest":        "[1;37m龜苓膏[2;37;0m"]),
        ([        "quest":        "[1;34m烏龜甲[2;37;0m"]),

//heimuya (去掉"葵花針"、"上等煙草")

        ([        "quest":        "紫金錘"]),                            
        ([        "quest":        "雷震擋"]),
        ([        "quest":        "熟銅棍"]),
        ([        "quest":        "紫綢衫"]),
        ([        "quest":        "地牢鑰匙"]),
        ([        "quest":        "風雷堂令牌"]),
        ([        "quest":        "白虎堂令牌"]),
        ([        "quest":        "青龍堂令牌"]),
        ([        "quest":        "棗紅緞麵皮袍"]),   

//heizhao

        ([        "quest":        "夜行布衣"]),                            
        ([        "quest":        "[1;31m紅布[2;37;0m"]),                
        ([        "quest":        "[1;37m白布[2;37;0m"]),
        ([        "quest":        "[1;31m紅布小囊[2;37;0m"]),
        ([        "quest":        "[1;37m白布小囊[2;37;0m"]),
        ([        "quest":        "[1;33m黃布小囊[2;37;0m"]),

//henshan (包括衡陽一帶)

        ([        "quest":        "手帕"]), 
        ([        "quest":        "黑色布衣"]),                           
        ([        "quest":        "熟羅長袍"]),                                  
        ([        "quest":        "[1;32m手鐲[2;37;0m"]),
        ([        "quest":        "[1;36m玉佩[2;37;0m"]),        
                                                                   
//huanghe (包括黃河一帶)
                
              ([        "quest":        "大斧頭"]),
        ([        "quest":        "分水刺"]),
        ([        "quest":        "三股叉"]),        
        ([        "quest":        "喪門斧"]),        
        ([        "quest":        "青布袍"]),                                 //梅超風
        ([        "quest":        "夜行水靠"]),
        ([        "quest":        "葛布長袍"]),
        ([        "quest":        "[1;36m判官筆[2;37;0m"]),
                         
//huashan

        ([        "quest":        "手信"]),
        ([        "quest":        "信紙"]),                                
        ([        "quest":        "游龍劍"]),
        ([        "quest":        "[35m湯碗[2;37;0m"]),
        ([        "quest":        "[33m黃米飯[2;37;0m"]),
        ([        "quest":        "[36m龍泉劍[2;37;0m"]), 
        ([        "quest":        "[1;32m碧水劍[2;37;0m"]),

//huijiang

        ([        "quest":        "香茶"]),                                   
        ([        "quest":        "點心"]),
        ([        "quest":        "飛刀"]),        
        ([        "quest":        "鐵槳"]),                 
        ([        "quest":        "金牛角"]),
        ([        "quest":        "[1;32m翠羽[2;37;0m"]),                 
        ([        "quest":        "[1;33m黃衫[2;37;0m"]),
        ([        "quest":        "[1;36m短劍[2;37;0m"]),

//jiangling

        ([        "quest":        "烏蠶衣"]),
        ([        "quest":        "[1;33m嫩黃衫[2;37;0m"]),
        ([        "quest":        "[32m綠玉如意[2;37;0m"]),
        ([        "quest":        "[33m唐詩選輯[2;37;0m"]),
        ([        "quest":        "[1;33m金波旬花[2;37;0m"]),
        ([        "quest":        "[1;32m春水碧波[2;37;0m"]),                

//jianzhong (去掉"玄鐵重劍")

        ([        "quest":        "怪蛇之膽"]),                           

//jiaxing (包括嘉興一帶)

        ([        "quest":        "夜明珠"]),
        ([        "quest":        "[1;36m冰魄銀針[2;37;0m"]),                 

//jinshe

        ([        "quest":        "骸骨"]),                               
        ([        "quest":        "小鐵盒"]),
        ([        "quest":        "大鐵盒"]),
        ([        "quest":        "[33m金蛇劍[2;37;0m"]),                
        ([        "quest":        "[33m金蛇錐[2;37;0m"]),  

//kunlun

        ([        "quest":        "綢袍"]),                                     
        ([        "quest":        "小籠包"]),        
        ([        "quest":        "[30m黑貂裘[2;37;0m"]),
        ([        "quest":        "[1;33m金項鏈[2;37;0m"]),
        ([        "quest":        "[1;33m大石頭[2;37;0m"]),
        ([        "quest":        "[1;37m白弧裘[2;37;0m"]),
        ([        "quest":        "[1;33m大樹榦[2;37;0m"]),                                                
        ([        "quest":        "[1;32m青陀羅花[2;37;0m"]),
        ([        "quest":        "[1;33m淡黃色緞袍[2;37;0m"]),
        ([        "quest":        "[37m黑邊白色長袍[2;37;0m"]),
        ([        "quest":        "[34m白邊藍色長袍[2;37;0m"]),
        ([        "quest":        "[33m白邊黃色長袍[2;37;0m"]),
        ([        "quest":        "[1;36m白邊青色長袍[2;37;0m"]),

//lanzhou

        ([        "quest":        "鐵鍬"]),                               
        ([        "quest":        "[33m酥油[2;37;0m"]), 
        ([        "quest":        "[32m扁擔[2;37;0m"]), 

//lingjiu

        ([        "quest":        "青衣"]),                               
        ([        "quest":        "酸梅湯"]),
        ([        "quest":        "白雲熊膽丸"]),
        ([        "quest":        "冰雪翡翠糕"]),         

//lingxiao

        ([        "quest":        "白袍"]),
        ([        "quest":        "[1;37m寒玉牌[2;37;0m"]),                       
        ([        "quest":        "[1;31m怪蛇血[2;37;0m"]),
        ([        "quest":        "[1;37m冰魄玉精[2;37;0m"]),

//lingzhou

        ([        "quest":        "烤羊腿"]),  

//luoyang

        ([        "quest":        "破竹刀"]),                             

//meizhuang (去掉"紅綢"、"朱果"、"梯子"、"綠玉洞簫")

         ([        "quest":        "無憂紅花"]),                         
        ([        "quest":        "梅花令牌"]),
        ([        "quest":        "黑色長衫"]), 
        ([        "quest":        "綉梅青衣"]),
        ([        "quest":        "鑌鐵判官筆"]),
        ([        "quest":        "[30m黑木令[2;37;0m"]),
        ([        "quest":        "[1;37m白玉瑤琴[2;37;0m"]),
        ([        "quest":        "[1;31m紅玉鑰匙[2;37;0m"]),        

//mingjiao

        ([        "quest":        "屍骨"]),                               
        ([        "quest":        "葫蘆"]),
        ([        "quest":        "木鏜"]),
        ([        "quest":        "油布包"]),
        ([        "quest":        "狼牙棒"]),
        ([        "quest":        "倚天劍"]),
//        ([        "quest":        "鐵焰令"]),
        ([        "quest":        "大白魚"]), 
        ([        "quest":        "白布長袍"]),        
        ([        "quest":        "陽頂天遺骨"]),
        ([        "quest":        "陽夫人遺骨"]),
        ([        "quest":        "陽教主遺信"]),
        ([        "quest":        "[1;36m僧鞋[2;37;0m"]),        
        ([        "quest":        "[1;33m奪命金花[2;37;0m"]),

//mobei

        ([        "quest":        "骷髏頭骨"]),                           
        ([        "quest":        "[33m金刀[2;37;0m"]),

//nanyang

        ([        "quest":        "[33m黃酒罈子[2;37;0m"]),                     

//qilian

        ([        "quest":        "[1;34m鐵石[2;37;0m"]),                         

//qingcheng
                            
        ([        "quest":        "茶水碗"]), 
        ([        "quest":        "賴湯圓"]), 
        ([        "quest":        "青蜂釘"]), 
        ([        "quest":        "青布長衫"]),
        ([        "quest":        "[1;36m鐵錐[2;37;0m"]),                
        ([        "quest":        "[1;36m雷公轟[2;37;0m"]), 

//quanzhen

        ([        "quest":        "重陽令"]),                             
        ([        "quest":        "白色道袍"]),                            

//quanzhou

        ([        "quest":        "[33m茯苓[2;37;0m"]),                 
        ([        "quest":        "[1;37m沒藥[2;37;0m"]),
        ([        "quest":        "[1;33m田七[2;37;0m"]),

//shaolin (去掉"素雞"、"素鴨")

        ([        "quest":        "黑索"]),                              
        ([        "quest":        "菩提子"]), 
        ([        "quest":        "木魚槌"]), 
        ([        "quest":        "金剛罩"]),          
        
//shenlong (去掉"腹蛇膽"、"斷腸花"、"百花腹蛇膏")

        ([        "quest":        "無名花"]),        
        ([        "quest":        "[1;36m翡翠蘭[2;37;0m"]),
        ([        "quest":        "[1;32m百香花[2;37;0m"]),         
        
//shiliang (去掉"情書"、"掃把"、"金蛇劍譜")        
        
//suzhou

        ([        "quest":        "[1;33m小樹枝[2;37;0m"]),                       

//taiwan

        ([        "quest":        "頭巾"]),                                
        ([        "quest":        "鋤頭"]),
        ([        "quest":        "長矛"]), 
        ([        "quest":        "倭刀"]), 
        ([        "quest":        "荷蘭火槍"]),
        
//taohua

        ([        "quest":        "玉蕭"]),                                 
        ([        "quest":        "明珠"]),
        ([        "quest":        "豬肉"]),
        ([        "quest":        "米飯"]),
        ([        "quest":        "石子"]),
        ([        "quest":        "桃木劍"]),
        ([        "quest":        "布陣箱"]),
        ([        "quest":        "桃花糕"]),
        ([        "quest":        "醉仙茶"]),
        ([        "quest":        "茉莉花茶"]),                
        ([        "quest":        "束髮金帶"]),
        ([        "quest":        "[35m紫玉簫[2;37;0m"]),
      
//taohuacun (去掉"木床")

        ([        "quest":        "花瓶"]),                               

//tianlongsi

        ([        "quest":        "香"]),                                 
        ([        "quest":        "錦盒"]),

//tiezhang

        ([        "quest":        "大米飯"]),                           
        ([        "quest":        "紅燒牛肉"]),
        ([        "quest":        "[30m黑衣[2;37;0m"]),
        ([        "quest":        "[1;36m灰衣[2;37;0m"]),        
        ([        "quest":        "[1;34m麻衣[2;37;0m"]),
        ([        "quest":        "[1;33m片皮乳豬[2;37;0m"]),

//village

        ([        "quest":        "燒紅的鐵錘"]),                          

//wanjiegu (去掉"藥草"、"細鐵杆")
                                 
        ([        "quest":        "絕情花"]),          
        ([        "quest":        "木魚錘"]),        
        ([        "quest":        "繡花鞋"]),
        ([        "quest":        "陰陽合和散"]),
        ([        "quest":        "[1;36m青衫[2;37;0m"]),  
        ([        "quest":        "[33m羊皮靴[2;37;0m"]),
        ([        "quest":        "[1;33m軟金束帶[2;37;0m"]), 
        ([        "quest":        "[1;36m淺藍色馬褂[2;37;0m"]),                        

//wudang (去掉"女兒香"、"破桌子")

        ([        "quest":        "香茶"]),                              
        ([        "quest":        "八卦服"]),
        ([        "quest":        "五行服"]),
        ([        "quest":        "水蜜桃"]),
        ([        "quest":        "粗磁大碗"]),                             
        ([        "quest":        "灰色道袍"]),
        ([        "quest":        "白色道袍"]),                           

//wudujiao (去掉"鐵哨"、"土豆"、"柿餅"、"銅牌"、"金鉤"、"解毒丹"、"金蛇毒液")

        ([        "quest":        "竹簍"]),                               
        ([        "quest":        "乾柴"]),
        ([        "quest":        "鋼鉤"]),
        ([        "quest":        "錦衣"]),
        ([        "quest":        "五毒剪"]),
        ([        "quest":        "千日醉"]),
        ([        "quest":        "蛇信子"]),
        ([        "quest":        "狍子肉"]),
        ([        "quest":        "野豬腿"]),
        ([        "quest":        "穿心蓮"]),
        ([        "quest":        "旱煙袋"]),
        ([        "quest":        "金蛇錘"]),
        ([        "quest":        "蛇毒囊"]),
        ([        "quest":        "蠍子毒囊"]),
        ([        "quest":        "蜘蛛毒囊"]),
        ([        "quest":        "蜈蚣毒囊"]),
        ([        "quest":        "蟾蜍毒囊"]), 
        ([        "quest":        "無形之毒"]),
        ([        "quest":        "含沙射影"]),
        ([        "quest":        "胡籮卜干"]),
        ([        "quest":        "諸葛行軍散"]),
        ([        "quest":        "缺口的青花瓷碗"]),
        ([        "quest":        "[1;36m龍涎香[2;37;0m"]),             
        ([        "quest":        "[1;31m天蠶絲裙[2;37;0m"]),           

//wuliang (包括無量山一帶) (去掉"莽牯朱蛤")

        ([        "quest":        "葯鋤"]),                                
        ([        "quest":        "小蒲團"]),
        ([        "quest":        "[1;32m通天草[2;37;0m"]),
                                                          
//xiakedao (去掉"死豬"、"鳥肉"、"椰子"、"芒果"、"腐心草"、"賞善銅牌"、"罰惡銅牌"、"賞善罰惡令")

        ([        "quest":        "石塊"]),                                
        ([        "quest":        "豬頭"]),
        ([        "quest":        "黃衫"]),        
        ([        "quest":        "青衫"]),        
        ([        "quest":        "烤豬腿"]),                          
        ([        "quest":        "白虹劍"]),
        ([        "quest":        "賞善罰惡簿"]),
        ([        "quest":        "[1;36m玄鐵令[2;37;0m"]),
        ([        "quest":        "[1;36m玄冰碧火酒[2;37;0m"]),          

//xiangyang
        
        ([        "quest":        "鐵背心"]),                             
        ([        "quest":        "蒙古彎刀"]),
        ([        "quest":        "[1;31m高粱米飯[2;37;0m"]),
        ([        "quest":        "[1;32m野菜湯碗[2;37;0m"]),
                                
//xiaoyao

        ([        "quest":        "水碗"]),                               
        ([        "quest":        "米飯"]),        
        ([        "quest":        "[1;31m步步生蓮[2;37;0m"]),         
        ([        "quest":        "[1;32m羽衣霓裳[2;37;0m"]),
        
//xingxiu (包括星宿海一帶)

        ([        "quest":        "銅鈸"]),                                
        ([        "quest":        "銅鼓"]),
        ([        "quest":        "銅號"]),
        ([        "quest":        "羊鞭"]), 
        ([        "quest":        "長鞭"]),
        ([        "quest":        "長袍"]),        
        ([        "quest":        "黃衫"]),
        ([        "quest":        "蒙汗藥"]), 
        ([        "quest":        "清心散"]),
        ([        "quest":        "小毛驢"]),
        ([        "quest":        "伊犁馬"]), 
        ([        "quest":        "哈密瓜"]),
        ([        "quest":        "馬奶酒壺"]), 
        ([        "quest":        "天山雪蓮"]),
        ([        "quest":        "波斯長袍"]),
        ([        "quest":        "阿拉伯彎刀"]),
        ([        "quest":        "三笑逍遙散"]),
        ([        "quest":        "維吾爾族長袍"]),
        ([        "quest":        "[1;37m白狐裘[2;37;0m"]),
        ([        "quest":        "[1;32m青葫蘆[2;37;0m"]),
        ([        "quest":        "[1;32m煉心彈[2;37;0m"]),
        ([        "quest":        "[1;32m碧磷針[2;37;0m"]),         
        ([        "quest":        "[32m天山器法[2;37;0m"]),

//xuedao 
        ([        "quest":        "鳥羽大氅"]),
        
//xueshan                
        ([        "quest":        "法輪"]),                               
        ([        "quest":        "木棍"]),        
        ([        "quest":        "僧棍"]),
        ([        "quest":        "[1;37m銀輪[2;37;0m"]),
        ([        "quest":        "[1;31m僧帽[2;37;0m"]),
        ([        "quest":        "[1;31m血刀[2;37;0m"]),
        ([        "quest":        "[1;33m金輪[2;37;0m"]),

//yanziwu(去掉"黑玉斷續膏"、"翠綠綢衫")

        ([        "quest":        "碧螺春"]),                             
        ([        "quest":        "四色點心"]),
        ([        "quest":        "[1;37m粉侯[2;37;0m"]),
        ([        "quest":        "[1;37m雪塔[2;37;0m"]),
        ([        "quest":        "[1;31m玫瑰花露[2;37;0m"]),
        ([        "quest":        "[1;37m茉莉花露[2;37;0m"]),
        ([        "quest":        "[1;33m寒梅花露[2;37;0m"]),

//yueyang

        ([        "quest":        "[31m洞庭魚[2;37;0m"]),
        ([        "quest":        "[1;32m洞庭春茶[2;37;0m"]),
        ([        "quest":        "[33m汨羅粽子[2;37;0m"]),

//others
                                                                                            
        ([        "quest":        "[32m清湯[2;37;0m"]),
        ([        "quest":        "[1;33m米飯[2;37;0m"]),
});

mapping query_quest()
{
        return quest[random(sizeof(quest))];
}
