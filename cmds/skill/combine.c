// combine.c
// Updated by Lonely

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

mapping combine_list = ([
        //勳章合成
        ({
          "/clone/medal/xinrui_xunzhang3-1",
          "/clone/medal/xinrui_xunzhang3-2",
        }) :  "/clone/medal/xinrui_xunzhang2",
        ({
          "/clone/medal/xinrui_xunzhang2-1",
          "/clone/medal/xinrui_xunzhang2-2",
        }) :  "/clone/medal/xinrui_xunzhang1",
        ({
          "/clone/medal/xinrui_xunzhang1-1",
          "/clone/medal/xinrui_xunzhang1-2",
        }) :  "/clone/medal/yinghao_xunzhang1",
        ({
          "/clone/medal/yinghao_xunzhang3-1",
          "/clone/medal/yinghao_xunzhang3-2",
        }) :  "/clone/medal/yinghao_xunzhang2",
        ({
          "/clone/medal/yinghao_xunzhang2-1",
          "/clone/medal/yinghao_xunzhang2-2",
        }) :  "/clone/medal/yinghao_xunzhang1",
        ({
          "/clone/medal/yinghao_xunzhang1-1",
          "/clone/medal/yinghao_xunzhang1-2",
        }) :  "/clone/medal/jingying_xunzhang1",        
        ({
          "/clone/medal/jingying_xunzhang3-1",
          "/clone/medal/jingying_xunzhang3-2",
        }) :  "/clone/medal/jingying_xunzhang2",
        ({
          "/clone/medal/jingying_xunzhang2-1",
          "/clone/medal/jingying_xunzhang2-2",
        }) :  "/clone/medal/jingying_xunzhang1",
        ({
          "/clone/medal/jingying_xunzhang1-1",
          "/clone/medal/jingying_xunzhang1-2",
        }) :  "/clone/medal/zhanshen_xunzhang1",
        ({
          "/clone/medal/zhanshen_xunzhang3-1",
          "/clone/medal/zhanshen_xunzhang3-2",
        }) :  "/clone/medal/zhanshen_xunzhang2",
        ({
          "/clone/medal/zhanshen_xunzhang2-1",
          "/clone/medal/zhanshen_xunzhang2-2",
        }) :  "/clone/medal/zhanshen_xunzhang1",
        ({
          "/clone/medal/zhanshen_xunzhang1-1",
          "/clone/medal/zhanshen_xunzhang1-2",
        }) :  "/clone/medal/lunjian_xunzhang1",
        ({
          "/clone/medal/lunjian_xunzhang3-1",
          "/clone/medal/lunjian_xunzhang3-2",
        }) :  "/clone/medal/lunjian_xunzhang2",
        ({
          "/clone/medal/lunjian_xunzhang2-1",
          "/clone/medal/lunjian_xunzhang2-2",
        }) :  "/clone/medal/lunjian_xunzhang1",
        ({
          "/clone/medal/lunjian_xunzhang1-1",
          "/clone/medal/lunjian_xunzhang1-2",
        }) :  "/clone/medal/diamond_xunzhang",
                                
        //寶石合成
        ({
          "/inherit/template/gem/cdiamond-1",
          "/inherit/template/gem/cdiamond-2",
          "/inherit/template/gem/cdiamond-3",
          }) :  "/clone/tessera/diamond",
          ({
          "/inherit/template/gem/diamond-1",
          "/inherit/template/gem/diamond-2",
          "/inherit/template/gem/diamond-3",
          }) :  "/clone/tessera/fdiamond",
          ({
          "/inherit/template/gem/fdiamond-1",
          "/inherit/template/gem/fdiamond-2",
          "/inherit/template/gem/fdiamond-3",
          }) :  "/clone/tessera/mdiamond",
          	         
         ({
          "/inherit/template/gem/cemerald-1",
          "/inherit/template/gem/cemerald-2",
          "/inherit/template/gem/cemerald-3",
          }) :  "/clone/tessera/emerald",
          ({
          "/inherit/template/gem/emerald-1",
          "/inherit/template/gem/emerald-2",
          "/inherit/template/gem/emerald-3",
          }) :  "/clone/tessera/femerald",
          ({
          "/inherit/template/gem/femerald-1",
          "/inherit/template/gem/femerald-2",
          "/inherit/template/gem/femerald-3",
          }) :  "/clone/tessera/memerald",
          	
         ({
          "/inherit/template/gem/csapphire-1",
          "/inherit/template/gem/csapphire-2",
          "/inherit/template/gem/csapphire-3",
          }) :  "/clone/tessera/sapphire",
          ({
          "/inherit/template/gem/sapphire-1",
          "/inherit/template/gem/sapphire-2",
          "/inherit/template/gem/sapphire-3",
          }) :  "/clone/tessera/fsapphire",
          ({
          "/inherit/template/gem/fsapphire-1",
          "/inherit/template/gem/fsapphire-2",
          "/inherit/template/gem/fsapphire-3",
          }) :  "/clone/tessera/msapphire",
          	
           ({
          "/inherit/template/gem/cruby-1",
          "/inherit/template/gem/cruby-2",
          "/inherit/template/gem/cruby-3",
          }) :  "/clone/tessera/ruby",
          ({
          "/inherit/template/gem/ruby-1",
          "/inherit/template/gem/ruby-2",
          "/inherit/template/gem/ruby-3",
          }) :  "/clone/tessera/fruby",
          ({
          "/inherit/template/gem/fruby-1",
          "/inherit/template/gem/fruby-2",
          "/inherit/template/gem/fruby-3",
          }) :  "/clone/tessera/mruby",
          	
         ({
          "/inherit/template/gem/ctopaz-1",
          "/inherit/template/gem/ctopaz-2",
          "/inherit/template/gem/ctopaz-3",
          }) :  "/clone/tessera/topaz",
          ({
          "/inherit/template/gem/topaz-1",
          "/inherit/template/gem/topaz-2",
          "/inherit/template/gem/topaz-3",
          }) :  "/clone/tessera/ftopaz",
          ({
          "/inherit/template/gem/ftopaz-1",
          "/inherit/template/gem/ftopaz-2",
          "/inherit/template/gem/ftopaz-3",
          }) :  "/clone/tessera/mtopaz",

        ({
          "/clone/tessera/cdiamond-1",
          "/clone/tessera/cdiamond-2",
          "/clone/tessera/cdiamond-3",
          }) :  "/clone/tessera/diamond",
          ({
          "/clone/tessera/diamond-1",
          "/clone/tessera/diamond-2",
          "/clone/tessera/diamond-3",
          }) :  "/clone/tessera/fdiamond",
          ({
          "/clone/tessera/fdiamond-1",
          "/clone/tessera/fdiamond-2",
          "/clone/tessera/fdiamond-3",
          }) :  "/clone/tessera/mdiamond",
          	         
         ({
          "/clone/tessera/cemerald-1",
          "/clone/tessera/cemerald-2",
          "/clone/tessera/cemerald-3",
          }) :  "/clone/tessera/emerald",
          ({
          "/clone/tessera/emerald-1",
          "/clone/tessera/emerald-2",
          "/clone/tessera/emerald-3",
          }) :  "/clone/tessera/femerald",
          ({
          "/clone/tessera/femerald-1",
          "/clone/tessera/femerald-2",
          "/clone/tessera/femerald-3",
          }) :  "/clone/tessera/memerald",
          	
         ({
          "/clone/tessera/csapphire-1",
          "/clone/tessera/csapphire-2",
          "/clone/tessera/csapphire-3",
          }) :  "/clone/tessera/sapphire",
          ({
          "/clone/tessera/sapphire-1",
          "/clone/tessera/sapphire-2",
          "/clone/tessera/sapphire-3",
          }) :  "/clone/tessera/fsapphire",
          ({
          "/clone/tessera/fsapphire-1",
          "/clone/tessera/fsapphire-2",
          "/clone/tessera/fsapphire-3",
          }) :  "/clone/tessera/msapphire",
          	
           ({
          "/clone/tessera/cruby-1",
          "/clone/tessera/cruby-2",
          "/clone/tessera/cruby-3",
          }) :  "/clone/tessera/ruby",
          ({
          "/clone/tessera/ruby-1",
          "/clone/tessera/ruby-2",
          "/clone/tessera/ruby-3",
          }) :  "/clone/tessera/fruby",
          ({
          "/clone/tessera/fruby-1",
          "/clone/tessera/fruby-2",
          "/clone/tessera/fruby-3",
          }) :  "/clone/tessera/mruby",
          	
         ({
          "/clone/tessera/ctopaz-1",
          "/clone/tessera/ctopaz-2",
          "/clone/tessera/ctopaz-3",
          }) :  "/clone/tessera/topaz",
          ({
          "/clone/tessera/topaz-1",
          "/clone/tessera/topaz-2",
          "/clone/tessera/topaz-3",
          }) :  "/clone/tessera/ftopaz",
          ({
          "/clone/tessera/ftopaz-1",
          "/clone/tessera/ftopaz-2",
          "/clone/tessera/ftopaz-3",
          }) :  "/clone/tessera/mtopaz",          
        //裝備之魂
        ({
          "/clone/enchase/charm_soul1-1",
          "/clone/enchase/charm_soul1-2",
          "/clone/enchase/charm_soul1-3",
          }) :  "/clone/enchase/charm_soul2",
        ({
          "/clone/enchase/charm_soul2-1",
          "/clone/enchase/charm_soul2-2",
          "/clone/enchase/charm_soul2-3",
          }) :  "/clone/enchase/charm_soul3",
        ({
          "/clone/enchase/charm_soul3-1",
          "/clone/enchase/charm_soul3-2",
          "/clone/enchase/charm_soul3-3",
          }) :  "/clone/enchase/charm_soul4",
        ({
          "/clone/enchase/charm_soul4-1",
          "/clone/enchase/charm_soul4-2",
          "/clone/enchase/charm_soul4-3",
          }) :  "/clone/enchase/charm_soul5",
        ({
          "/clone/enchase/charm_soul5-1",
          "/clone/enchase/charm_soul5-2",
          "/clone/enchase/charm_soul5-3",
          }) :  "/clone/enchase/charm_soul6",
        ({
     	  "/clone/enchase/cloth_soul1-1",
          "/clone/enchase/cloth_soul1-2",
          "/clone/enchase/cloth_soul1-3",
          }) :  "/clone/enchase/cloth_soul2",
        ({
     	  "/clone/enchase/cloth_soul2-1",
          "/clone/enchase/cloth_soul2-2",
          "/clone/enchase/cloth_soul2-3",
          }) :  "/clone/enchase/cloth_soul3",
        ({
     	  "/clone/enchase/cloth_soul3-1",
          "/clone/enchase/cloth_soul3-2",
          "/clone/enchase/cloth_soul3-3",
          }) :  "/clone/enchase/cloth_soul4",
        ({
          "/clone/enchase/cloth_soul4-1",
          "/clone/enchase/cloth_soul4-2",
          "/clone/enchase/cloth_soul4-3",
          }) :  "/clone/enchase/cloth_soul5",
        ({
          "/clone/enchase/cloth_soul5-1",
          "/clone/enchase/cloth_soul5-2",
          "/clone/enchase/cloth_soul5-3",
          }) :  "/clone/enchase/cloth_soul6",
        ({
     	  "/clone/enchase/finger_soul1-1",
          "/clone/enchase/finger_soul1-2",
          "/clone/enchase/finger_soul1-3",
          }) :  "/clone/enchase/finger_soul2",
        ({
          "/clone/enchase/finger_soul2-1",
          "/clone/enchase/finger_soul2-2",
          "/clone/enchase/finger_soul2-3",
          }) :  "/clone/enchase/finger_soul3",
        ({
     	  "/clone/enchase/finger_soul3-1",
          "/clone/enchase/finger_soul3-2",
          "/clone/enchase/finger_soul3-3",
          }) :  "/clone/enchase/finger_soul4",
        ({
     	  "/clone/enchase/finger_soul4-1",
          "/clone/enchase/finger_soul4-2",
          "/clone/enchase/finger_soul4-3",
          }) :  "/clone/enchase/finger_soul5",
        ({
     	  "/clone/enchase/finger_soul5-1",
          "/clone/enchase/finger_soul5-2",
          "/clone/enchase/finger_soul5-3",
          }) :  "/clone/enchase/finger_soul6",
        ({
     	  "/clone/enchase/hands_soul1-1",
          "/clone/enchase/hands_soul1-2",
          "/clone/enchase/hands_soul1-3",
          }) :  "/clone/enchase/hands_soul2",
        ({
     	  "/clone/enchase/hands_soul2-1",
          "/clone/enchase/hands_soul2-2",
          "/clone/enchase/hands_soul2-3",
          }) :  "/clone/enchase/hands_soul3",
        ({
     	  "/clone/enchase/hands_soul3-1",
          "/clone/enchase/hands_soul3-2",
          "/clone/enchase/hands_soul3-3",
          }) :  "/clone/enchase/hands_soul4",
        ({
     	  "/clone/enchase/hands_soul4-1",
          "/clone/enchase/hands_soul4-2",
          "/clone/enchase/hands_soul4-3",
          }) :  "/clone/enchase/hands_soul5",
        ({
          "/clone/enchase/hands_soul5-1",
          "/clone/enchase/hands_soul5-2",
          "/clone/enchase/hands_soul5-3",
          }) :  "/clone/enchase/hands_soul6",
        ({
          "/clone/enchase/neck_soul1-1",
          "/clone/enchase/neck_soul1-2",
          "/clone/enchase/neck_soul1-3",
          }) :  "/clone/enchase/neck_soul2",
        ({
          "/clone/enchase/neck_soul2-1",
          "/clone/enchase/neck_soul2-2",
          "/clone/enchase/neck_soul2-3",
          }) :  "/clone/enchase/neck_soul3",
        ({
     	  "/clone/enchase/neck_soul3-1",
          "/clone/enchase/neck_soul3-2",
          "/clone/enchase/neck_soul3-3",
          }) :  "/clone/enchase/neck_soul4",
        ({
     	  "/clone/enchase/neck_soul4-1",
          "/clone/enchase/neck_soul4-2",
          "/clone/enchase/neck_soul4-3",
          }) :  "/clone/enchase/neck_soul5",
        ({
     	  "/clone/enchase/neck_soul5-1",
          "/clone/enchase/neck_soul5-2",
          "/clone/enchase/neck_soul5-3",
          }) :  "/clone/enchase/neck_soul6",
        ({
     	  "/clone/enchase/rings_soul1-1",
          "/clone/enchase/rings_soul1-2",
          "/clone/enchase/rings_soul1-3",
          }) :  "/clone/enchase/rings_soul2",
        ({
     	  "/clone/enchase/rings_soul2-1",
          "/clone/enchase/rings_soul2-2",
          "/clone/enchase/rings_soul2-3",
          }) :  "/clone/enchase/rings_soul3",
        ({
     	  "/clone/enchase/rings_soul3-1",
          "/clone/enchase/rings_soul3-2",
          "/clone/enchase/rings_soul3-3",
          }) :  "/clone/enchase/rings_soul4",
        ({
     	  "/clone/enchase/rings_soul4-1",
          "/clone/enchase/rings_soul4-2",
          "/clone/enchase/rings_soul4-3",
          }) :  "/clone/enchase/rings_soul5",
        ({
     	  "/clone/enchase/rings_soul5-1",
          "/clone/enchase/rings_soul5-2",
          "/clone/enchase/rings_soul5-3",
          }) :  "/clone/enchase/rings_soul6",
        ({
     	  "/clone/enchase/surcoat_soul1-1",
          "/clone/enchase/surcoat_soul1-2",
          "/clone/enchase/surcoat_soul1-3",
          }) :  "/clone/enchase/surcoat_soul2",
        ({
     	  "/clone/enchase/surcoat_soul2-1",
          "/clone/enchase/surcoat_soul2-2",
          "/clone/enchase/surcoat_soul2-3",
          }) :  "/clone/enchase/surcoat_soul3",
        ({
          "/clone/enchase/surcoat_soul3-1",
          "/clone/enchase/surcoat_soul3-2",
          "/clone/enchase/surcoat_soul3-3",
          }) :  "/clone/enchase/surcoat_soul4",
        ({
     	  "/clone/enchase/surcoat_soul4-1",
          "/clone/enchase/surcoat_soul4-2",
          "/clone/enchase/surcoat_soul4-3",
          }) :  "/clone/enchase/surcoat_soul5",
        ({
     	  "/clone/enchase/surcoat_soul5-1",
          "/clone/enchase/surcoat_soul5-2",
          "/clone/enchase/surcoat_soul5-3",
          }) :  "/clone/enchase/surcoat_soul6",
        ({
          "/clone/enchase/weapon_soul1-1",
          "/clone/enchase/weapon_soul1-2",
          "/clone/enchase/weapon_soul1-3",
          }) :  "/clone/enchase/weapon_soul2",
        ({
     	  "/clone/enchase/weapon_soul2-1",
          "/clone/enchase/weapon_soul2-2",
          "/clone/enchase/weapon_soul2-3",
          }) :  "/clone/enchase/weapon_soul3",
        ({
          "/clone/enchase/weapon_soul3-1",
          "/clone/enchase/weapon_soul3-2",
          "/clone/enchase/weapon_soul3-3",
          }) :  "/clone/enchase/weapon_soul4",
        ({
          "/clone/enchase/weapon_soul4-1",
          "/clone/enchase/weapon_soul4-2",
          "/clone/enchase/weapon_soul4-3",
          }) :  "/clone/enchase/weapon_soul5",
        ({
          "/clone/enchase/weapon_soul5-1",
          "/clone/enchase/weapon_soul5-2",
          "/clone/enchase/weapon_soul5-3",
          }) :  "/clone/enchase/weapon_soul6",
        ({
     	  "/clone/enchase/waist_soul1-1",
          "/clone/enchase/waist_soul1-2",
          "/clone/enchase/waist_soul1-3",
          }) :  "/clone/enchase/waist_soul2",
        ({
          "/clone/enchase/waist_soul2-1",
          "/clone/enchase/waist_soul2-2",
          "/clone/enchase/waist_soul2-3",
          }) :  "/clone/enchase/waist_soul3",
        ({
     	  "/clone/enchase/waist_soul3-1",
          "/clone/enchase/waist_soul3-2",
          "/clone/enchase/waist_soul3-3",
          }) :  "/clone/enchase/waist_soul4",
        ({
     	  "/clone/enchase/waist_soul4-1",
          "/clone/enchase/waist_soul4-2",
          "/clone/enchase/waist_soul4-3",
          }) :  "/clone/enchase/waist_soul5",
        ({
          "/clone/enchase/waist_soul5-1",
          "/clone/enchase/waist_soul5-2",
          "/clone/enchase/waist_soul5-3",
          }) :  "/clone/enchase/waist_soul6",
        ({
     	  "/clone/enchase/armor_soul1-1",
          "/clone/enchase/armor_soul1-2",
          "/clone/enchase/armor_soul1-3",
          }) :  "/clone/enchase/armor_soul2",
        ({
          "/clone/enchase/armor_soul2-1",
          "/clone/enchase/armor_soul2-2",
          "/clone/enchase/armor_soul2-3",
          }) :  "/clone/enchase/armor_soul3",
        ({
          "/clone/enchase/armor_soul3-1",
          "/clone/enchase/armor_soul3-2",
          "/clone/enchase/armor_soul3-3",
          }) :  "/clone/enchase/armor_soul4",
        ({
          "/clone/enchase/armor_soul4-1",
          "/clone/enchase/armor_soul4-2",
          "/clone/enchase/armor_soul4-3",
          }) :  "/clone/enchase/armor_soul5",
        ({
     	  "/clone/enchase/armor_soul5-1",
          "/clone/enchase/armor_soul5-2",
          "/clone/enchase/armor_soul5-3",
          }) :  "/clone/enchase/armor_soul6",
        ({
     	  "/clone/enchase/head_soul1-1",
          "/clone/enchase/head_soul1-2",
          "/clone/enchase/head_soul1-3",
          }) :  "/clone/enchase/head_soul2",
        ({
          "/clone/enchase/head_soul2-1",
          "/clone/enchase/head_soul2-2",
          "/clone/enchase/head_soul2-3",
          }) :  "/clone/enchase/head_soul3",
        ({
          "/clone/enchase/head_soul3-1",
          "/clone/enchase/head_soul3-2",
          "/clone/enchase/head_soul3-3",
          }) :  "/clone/enchase/head_soul4",
        ({
          "/clone/enchase/head_soul4-1",
          "/clone/enchase/head_soul4-2",
          "/clone/enchase/head_soul4-3",
          }) :  "/clone/enchase/head_soul5",
        ({
     	  "/clone/enchase/head_soul5-1",
          "/clone/enchase/head_soul5-2",
          "/clone/enchase/head_soul5-3",
          }) :  "/clone/enchase/head_soul6",  
        ({
     	  "/clone/enchase/wrists_soul1-1",
          "/clone/enchase/wrists_soul1-2",
          "/clone/enchase/wrists_soul1-3",
          }) :  "/clone/enchase/wrists_soul2",
        ({
     	  "/clone/enchase/wrists_soul2-1",
          "/clone/enchase/wrists_soul2-2",
          "/clone/enchase/wrists_soul2-3",
          }) :  "/clone/enchase/wrists_soul3",
        ({
          "/clone/enchase/wrists_soul3-1",
          "/clone/enchase/wrists_soul3-2",
          "/clone/enchase/wrists_soul3-3",
          }) :  "/clone/enchase/wrists_soul4",
        ({
          "/clone/enchase/wrists_soul4-1",
          "/clone/enchase/wrists_soul4-2",
          "/clone/enchase/wrists_soul4-3",
          }) :  "/clone/enchase/wrists_soul5",
        ({
     	  "/clone/enchase/wrists_soul5-1",
          "/clone/enchase/wrists_soul5-2",
          "/clone/enchase/wrists_soul5-3",
          }) :  "/clone/enchase/wrists_soul6",          	
        ({
          "/clone/enchase/boots_soul1-1",
          "/clone/enchase/boots_soul1-2",
          "/clone/enchase/boots_soul1-3",
          }) :  "/clone/enchase/boots_soul2",
        ({
     	  "/clone/enchase/boots_soul2-1",
          "/clone/enchase/boots_soul2-2",
          "/clone/enchase/boots_soul2-3",
          }) :  "/clone/enchase/boots_soul3",
        ({
     	  "/clone/enchase/boots_soul3-1",
          "/clone/enchase/boots_soul3-2",
          "/clone/enchase/boots_soul3-3",
          }) :  "/clone/enchase/boots_soul4",
        ({
          "/clone/enchase/boots_soul4-1",
          "/clone/enchase/boots_soul4-2",
          "/clone/enchase/boots_soul4-3",
          }) :  "/clone/enchase/boots_soul5",
        ({
          "/clone/enchase/boots_soul5-1",
          "/clone/enchase/boots_soul5-2",
          "/clone/enchase/boots_soul5-3",
          }) :  "/clone/enchase/boots_soul6",
        // 帝王符圖...
        ({
          "/clone/tuteng/diwang-suipian1-1",
          "/clone/tuteng/diwang-suipian2-1",
          "/clone/tuteng/diwang-suipian3-1",
          "/clone/tuteng/diwang-suipian4-1",
          "/clone/tuteng/diwang-suipian5-1",
          "/clone/tuteng/diwang-suipian6-1",
          "/clone/tuteng/diwang-suipian7-1",
          })  : "/clone/tuteng/futu1",
        ({
          "/clone/tuteng/diwang-suipian8-1",
          "/clone/tuteng/diwang-suipian9-1",
          "/clone/tuteng/diwang-suipian10-1",
          "/clone/tuteng/diwang-suipian11-1",
          "/clone/tuteng/diwang-suipian12-1",
          "/clone/tuteng/diwang-suipian13-1",
          "/clone/tuteng/diwang-suipian14-1",
          })  : "/clone/tuteng/futu2",
        ({
          "/clone/tuteng/diwang-suipian15-1",
          "/clone/tuteng/diwang-suipian16-1",
          "/clone/tuteng/diwang-suipian17-1",
          "/clone/tuteng/diwang-suipian18-1",
          "/clone/tuteng/diwang-suipian19-1",
          "/clone/tuteng/diwang-suipian20-1",
          "/clone/tuteng/diwang-suipian21-1",
          })  : "/clone/tuteng/futu3",
        ({
          "/clone/tuteng/diwang-suipian22-1",
          "/clone/tuteng/diwang-suipian23-1",
          "/clone/tuteng/diwang-suipian24-1",
          "/clone/tuteng/diwang-suipian25-1",
          "/clone/tuteng/diwang-suipian26-1",
          "/clone/tuteng/diwang-suipian27-1",
          "/clone/tuteng/diwang-suipian28-1",
          })  : "/clone/tuteng/futu4",
        ({
          "/clone/tuteng/diwang-suipian29-1",
          "/clone/tuteng/diwang-suipian30-1",
          "/clone/tuteng/diwang-suipian31-1",
          "/clone/tuteng/diwang-suipian32-1",
          "/clone/tuteng/diwang-suipian33-1",
          "/clone/tuteng/diwang-suipian34-1",
          "/clone/tuteng/diwang-suipian35-1",
          })  : "/clone/tuteng/futu5",
        ({
          "/clone/tuteng/diwang-suipian36-1",
          "/clone/tuteng/diwang-suipian37-1",
          "/clone/tuteng/diwang-suipian38-1",
          "/clone/tuteng/diwang-suipian39-1",
          "/clone/tuteng/diwang-suipian40-1",
          "/clone/tuteng/diwang-suipian41-1",
          "/clone/tuteng/diwang-suipian42-1",
          })  : "/clone/tuteng/futu6",
        ({
          "/clone/tuteng/diwang-suipian43-1",
          "/clone/tuteng/diwang-suipian44-1",
          "/clone/tuteng/diwang-suipian45-1",
          "/clone/tuteng/diwang-suipian46-1",
          "/clone/tuteng/diwang-suipian47-1",
          "/clone/tuteng/diwang-suipian48-1",
          "/clone/tuteng/diwang-suipian49-1",
          })  : "/clone/tuteng/futu7",


        // 符文的合成公式
        ({ "/clone/tessera/rune01-1",
           "/clone/tessera/rune01-2",
           "/clone/tessera/rune01-3", }) : "/clone/tessera/rune02",

        ({ "/clone/tessera/rune02-1",
           "/clone/tessera/rune02-2",
           "/clone/tessera/rune02-3", }) : "/clone/tessera/rune03",

        ({ "/clone/tessera/rune03-1",
           "/clone/tessera/rune03-2",
           "/clone/tessera/rune03-3", }) : "/clone/tessera/rune04",

        ({ "/clone/tessera/rune04-1",
           "/clone/tessera/rune04-2",
           "/clone/tessera/rune04-3", }) : "/clone/tessera/rune05",

        ({ "/clone/tessera/rune05-1",
           "/clone/tessera/rune05-2",
           "/clone/tessera/rune05-3", }) : "/clone/tessera/rune06",

        ({ "/clone/tessera/rune06-1",
           "/clone/tessera/rune06-2",
           "/clone/tessera/rune06-3", }) : "/clone/tessera/rune07",

        ({ "/clone/tessera/rune07-1",
           "/clone/tessera/rune07-2",
           "/clone/tessera/rune07-3", }) : "/clone/tessera/rune08",

        ({ "/clone/tessera/rune08-1",
           "/clone/tessera/rune08-2",
           "/clone/tessera/rune08-3", }) : "/clone/tessera/rune09",

        ({ "/clone/tessera/rune09-1",
           "/clone/tessera/rune09-2",
           "/clone/tessera/rune09-3", }) : "/clone/tessera/rune10",

        ({ "/clone/tessera/rune10-1",
           "/clone/tessera/rune10-2",
           "/clone/tessera/rune10-3", }) : "/clone/tessera/rune11",

        ({ "/clone/tessera/rune11-1",
           "/clone/tessera/rune11-2",
           "/clone/tessera/rune11-3", }) : "/clone/tessera/rune12",

        ({ "/clone/tessera/rune12-1",
           "/clone/tessera/rune12-2",
           "/clone/tessera/rune12-3", }) : "/clone/tessera/rune13",

        ({ "/clone/tessera/rune13-1",
           "/clone/tessera/rune13-2",
           "/clone/tessera/rune13-3", }) : "/clone/tessera/rune14",

        ({ "/clone/tessera/rune14-1",
           "/clone/tessera/rune14-2",
           "/clone/tessera/rune14-3", }) : "/clone/tessera/rune15",

        ({ "/clone/tessera/rune15-1",
           "/clone/tessera/rune15-2",
           "/clone/tessera/rune15-3", }) : "/clone/tessera/rune16",

        ({ "/clone/tessera/rune16-1",
           "/clone/tessera/rune16-2",
           "/clone/tessera/rune16-3", }) : "/clone/tessera/rune17",

        ({ "/clone/tessera/rune17-1",
           "/clone/tessera/rune17-2",
           "/clone/tessera/rune17-3", }) : "/clone/tessera/rune18",

        ({ "/clone/tessera/rune18-1",
           "/clone/tessera/rune18-2",
           "/clone/tessera/rune18-3", }) : "/clone/tessera/rune19",

        ({ "/clone/tessera/rune19-1",
           "/clone/tessera/rune19-2",
           "/clone/tessera/rune19-3", }) : "/clone/tessera/rune20",

        ({ "/clone/tessera/rune20-1",
           "/clone/tessera/rune20-2",
           "/clone/gift/puti-zi-1", }) : "/clone/tessera/rune21",

        ({ "/clone/tessera/rune21-1",
           "/clone/tessera/rune21-2",
           "/clone/gift/jiuzhuan-1", }) : "/clone/tessera/rune22",

        ({ "/clone/tessera/rune22-1",
           "/clone/tessera/rune22-2",
           "/clone/gift/tianxiang-1", }) : "/clone/tessera/rune23",

        ({ "/clone/tessera/rune23-1",
           "/clone/tessera/rune23-2",
           "/clone/gift/xuanhuang-1", }) : "/clone/tessera/rune24",

        ({ "/clone/tessera/rune23-1",
           "/clone/tessera/rune23-2",
           "/clone/fam/max/xuanhuang-1", }) : "/clone/tessera/rune24",

        ({ "/clone/tessera/rune24-1",
           "/clone/tessera/rune24-2",
           "/d/shenlong/obj/hua4-1", }) : "/clone/tessera/rune25",

        ({ "/clone/tessera/rune25-1",
           "/clone/tessera/rune25-2",
           "/clone/fam/etc/prize5-1", }) : "/clone/tessera/rune26",

        ({ "/clone/tessera/rune26-1",
           "/clone/tessera/rune26-2",
           "/inherit/template/gem/ftopaz-1", }) : "/clone/tessera/rune27",

        ({ "/clone/tessera/rune27-1",
           "/clone/tessera/rune27-2",
           "/inherit/template/gem/fruby-1", }) : "/clone/tessera/rune28",

        ({ "/clone/tessera/rune28-1",
           "/clone/tessera/rune28-2",
           "/inherit/template/gem/fsapphire-1", }) : "/clone/tessera/rune29",

        ({ "/clone/tessera/rune29-1",
           "/clone/tessera/rune29-2",
           "/inherit/template/gem/femerald-1", }) : "/clone/tessera/rune30",

        ({ "/clone/tessera/rune30-1",
           "/clone/tessera/rune30-2",
           "/inherit/template/gem/fdiamond-1", }) : "/clone/tessera/rune31",

        ({ "/clone/tessera/rune31-1",
           "/clone/tessera/rune31-2",
           "/inherit/template/gem/mtopaz-1", }) : "/clone/tessera/rune32",

        ({ "/clone/tessera/rune32-1",
           "/clone/tessera/rune32-2",
           "/inherit/template/gem/mruby-1", }) : "/clone/tessera/rune33",

        ({ "/clone/tessera/rune33-1",
           "/clone/tessera/rune33-2",
           "/inherit/template/gem/msapphire-1", }) : "/clone/tessera/rune34",

        ({ "/clone/tessera/rune34-1",
           "/clone/tessera/rune34-2",
           "/inherit/template/gem/memerald-1", }) : "/clone/tessera/rune35",

        ({ "/clone/tessera/rune35-1",
           "/clone/tessera/rune35-2",
           "/inherit/template/gem/mdiamond-1", }) : "/clone/tessera/rune36",                      

       // 佛光寶珠
       ({
       	  "/clone/quarry/item/zhenzhu-1",
       	  "/clone/quarry/item/zhenzhu-2",
       	  "/clone/quarry/item/zhenzhu-3",   })  : "/clone/quarry/item/combine/foguang-baozhu",
       	  
       // 萬年紅
       ({
       	  "/clone/fam/item/bixue-1",
       	  "/clone/fam/item/bless_water-1",
       	  "/clone/fam/pill/neili2-1",   })  : "/clone/fam/item/wannian-hong",

        // 鎮獄驚天丸
        ({ "/clone/fam/max/xuanhuang-1",
           "/clone/fam/max/longjia-1",
           "/clone/fam/item/kunlun-1",
           "/clone/fam/item/baxian-1", }) : "/clone/fam/max/zhenyu",

        // 子午龍甲丹
        ({ "/clone/fam/pill/dimai-1",
           "/clone/fam/pill/renshen4-1",
           "/clone/fam/etc/lv7d-1", }) : "/clone/fam/max/longjia",

        // 玄黃紫箐丹
        ({ "/clone/fam/pill/yulu-1",
           "/clone/fam/pill/lingzhi4-1",
           "/clone/fam/etc/lv7a-1", }) : "/clone/fam/max/xuanhuang",

        // 地脈血泉
        ({ "/clone/fam/pill/puti2-1",
           "/clone/fam/pill/sheli3-1",
           "/clone/fam/etc/lv7b-1", }) : "/clone/fam/pill/dimai",

        // 天香玉露
        ({ "/clone/fam/pill/sheli2-1",
           "/clone/fam/pill/puti3-1",
           "/clone/fam/etc/lv7c-1", }) : "/clone/fam/pill/yulu",

        // 千年參心丹
        ({ "/clone/fam/pill/renshen1-1",
           "/clone/fam/pill/renshen2-1",
           "/clone/fam/etc/lv5c-1", }) : "/clone/fam/pill/renshen4",

        // 千年靈芝丸
        ({ "/clone/fam/pill/lingzhi1-1",
           "/clone/fam/pill/lingzhi2-1",
           "/clone/fam/etc/lv5c-1", }) : "/clone/fam/pill/lingzhi4",

        // 千年雪蓮膏
        ({ "/clone/fam/pill/xuelian1-1",
           "/clone/fam/pill/xuelian2-1",
           "/clone/fam/etc/lv5c-1", }) : "/clone/fam/pill/xuelian4",

        // 百年參心丹
        ({ "/clone/fam/pill/renshen1-1",
           "/clone/fam/etc/lv5e-1", }) : "/clone/fam/pill/renshen3",

        // 百年靈芝丸
        ({ "/clone/fam/pill/lingzhi1-1",
           "/clone/fam/etc/lv5e-1", }) : "/clone/fam/pill/lingzhi3",

        // 百年雪蓮膏
        ({ "/clone/fam/pill/xuelian1-1",
           "/clone/fam/etc/lv5e-1", }) : "/clone/fam/pill/xuelian3",

        // 昊天丹
        ({ "/clone/fam/pill/linghui1-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/linghui2",

        // 火龍果
        ({ "/clone/fam/pill/neili1-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/neili2",

        // 菩提子
        ({ "/clone/fam/pill/puti1-1",
           "/clone/fam/pill/puti2-1",
           "/clone/fam/pill/puti3-1", }) : "/clone/fam/pill/puti4",

        // 聖舍利
        ({ "/clone/fam/pill/sheli1-1",
           "/clone/fam/pill/sheli2-1",
           "/clone/fam/pill/sheli3-1", }) : "/clone/fam/pill/sheli4",

        // 帝者舍利
        ({ "/clone/fam/pill/sheli2-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/sheli3",

        // 冰菩提
        ({ "/clone/fam/pill/puti2-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/puti3",

        // 心菩提
        ({ "/clone/fam/pill/puti1-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/puti2",

        // 佛尊舍利
        ({ "/clone/fam/pill/sheli1-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/sheli2",

        // 忘情天書
        ({ "/clone/fam/etc/lv5a-1",
           "/clone/fam/etc/lv5b-1",
           "/clone/fam/etc/lv5d-1",
           "/clone/fam/etc/lv7d-1",
           "/clone/fam/gift/str3-1", }) : "/clone/fam/max/tianshu1",

        // 忘情天書
        ({ "/clone/fam/etc/lv5a-1",
           "/clone/fam/etc/lv5b-1",
           "/clone/fam/etc/lv5d-1",
           "/clone/fam/etc/lv7d-1",
           "/clone/fam/gift/con3-1", }) : "/clone/fam/max/tianshu1",

        // 忘情天書
        ({ "/clone/fam/etc/lv5a-1",
           "/clone/fam/etc/lv5b-1",
           "/clone/fam/etc/lv5d-1",
           "/clone/fam/etc/lv7d-1",
           "/clone/fam/gift/int3-1", }) : "/clone/fam/max/tianshu1",

        // 忘情天書
        ({ "/clone/fam/etc/lv5a-1",
           "/clone/fam/etc/lv5b-1",
           "/clone/fam/etc/lv5d-1",
           "/clone/fam/etc/lv7d-1",
           "/clone/fam/gift/dex3-1", }) : "/clone/fam/max/tianshu1",
        // 五張九宵紋圖碎片拼湊出完整的九宵紋圖
        ({ "/clone/tattoo/spcs1-1",
           "/clone/tattoo/spcs1-2",
           "/clone/tattoo/spcs1-3",
           "/clone/tattoo/spcs1-4",
           "/clone/tattoo/spcs1-5" }) : "/clone/tattoo/spc1",

        // 五張鳳舞九天圖碎片拼湊出完整的鳳舞九天圖
        ({ "/clone/tattoo/spcs2-1",
           "/clone/tattoo/spcs2-2",
           "/clone/tattoo/spcs2-3",
           "/clone/tattoo/spcs2-4",
           "/clone/tattoo/spcs2-5" }) : "/clone/tattoo/spc2",

        // 五張萬佛朝聖圖碎片拼湊出完整的萬佛朝聖圖
        ({ "/clone/tattoo/spcs3-1",
           "/clone/tattoo/spcs3-2",
           "/clone/tattoo/spcs3-3",
           "/clone/tattoo/spcs3-4",
           "/clone/tattoo/spcs3-5" }) : "/clone/tattoo/spc3",

        // 五張百鬼夜行圖碎片拼湊出完整的百鬼夜行圖
        ({ "/clone/tattoo/spcs4-1",
           "/clone/tattoo/spcs4-2",
           "/clone/tattoo/spcs4-3",
           "/clone/tattoo/spcs4-4",
           "/clone/tattoo/spcs4-5" }) : "/clone/tattoo/spc4",

        // 五張托塔天王圖碎片拼湊出完整的托塔天王圖
        ({ "/clone/tattoo/spcs5-1",
           "/clone/tattoo/spcs5-2",
           "/clone/tattoo/spcs5-3",
           "/clone/tattoo/spcs5-4",
           "/clone/tattoo/spcs5-5" }) : "/clone/tattoo/spc5",

        // 五張千手觀音圖碎片拼湊出完整的千手觀音圖
        ({ "/clone/tattoo/spcs6-1",
           "/clone/tattoo/spcs6-2",
           "/clone/tattoo/spcs6-3",
           "/clone/tattoo/spcs6-4",
           "/clone/tattoo/spcs6-5" }) : "/clone/tattoo/spc6",

        // 五張錦繡山河圖碎片拼湊出完整的錦繡山河圖
        ({ "/clone/tattoo/spcs7-1",
           "/clone/tattoo/spcs7-2",
           "/clone/tattoo/spcs7-3",
           "/clone/tattoo/spcs7-4",
           "/clone/tattoo/spcs7-5" }) : "/clone/tattoo/spc7",

        // 五張后羿射日圖碎片拼湊出完整的后羿射日圖
        ({ "/clone/tattoo/spcs8-1",
           "/clone/tattoo/spcs8-2",
           "/clone/tattoo/spcs8-3",
           "/clone/tattoo/spcs8-4",
           "/clone/tattoo/spcs8-5" }) : "/clone/tattoo/spc8",

        // 五張九儀天尊圖碎片拼湊出完整的九儀天尊圖
        ({ "/clone/tattoo/spcs9-1",
           "/clone/tattoo/spcs9-2",
           "/clone/tattoo/spcs9-3",
           "/clone/tattoo/spcs9-4",
           "/clone/tattoo/spcs9-5" }) : "/clone/tattoo/spc9",

        // 五張冥皇煉獄圖碎片拼湊出完整的冥皇煉獄圖
        ({ "/clone/tattoo/spcs10-1",
           "/clone/tattoo/spcs10-2",
           "/clone/tattoo/spcs10-3",
           "/clone/tattoo/spcs10-4",
           "/clone/tattoo/spcs10-5" }) : "/clone/tattoo/spc10",

        // 三個鑽石碎片合并成為一個鑽石
        ({ "/clone/gift/cdiamond-1",
           "/clone/gift/cdiamond-2",
           "/clone/gift/cdiamond-3" }) : "/clone/gift/diamond",

        // 三個鑽石合并成為一個精美鑽石
        ({ "/clone/gift/diamond-1",
           "/clone/gift/diamond-2",
           "/clone/gift/diamond-3" }) : "/clone/gift/fdiamond",

        // 三個精美鑽石合并成為一個神之鑽石
        ({ "/clone/gift/fdiamond-1",
           "/clone/gift/fdiamond-2",
           "/clone/gift/fdiamond-3" }) : "/clone/gift/mdiamond",

        // 三個瑪瑙碎片合并成為一個瑪瑙
        ({ "/clone/gift/cagate-1",
           "/clone/gift/cagate-2",
           "/clone/gift/cagate-3" }) : "/clone/gift/agate",

        // 三個瑪瑙合并成為一個精美瑪瑙
        ({ "/clone/gift/agate-1",
           "/clone/gift/agate-2",
           "/clone/gift/agate-3" }) : "/clone/gift/fagate",

        // 三個精美瑪瑙合并成為一個神之瑪瑙
        ({ "/clone/gift/fagate-1",
           "/clone/gift/fagate-2",
           "/clone/gift/fagate-3" }) : "/clone/gift/magate",

        // 三個水晶碎片合并成為一個水晶
        ({ "/clone/gift/ccrystal-1",
           "/clone/gift/ccrystal-2",
           "/clone/gift/ccrystal-3" }) : "/clone/gift/crystal",

        // 三個水晶合并成為一個精美水晶
        ({ "/clone/gift/crystal-1",
           "/clone/gift/crystal-2",
           "/clone/gift/crystal-3" }) : "/clone/gift/fcrystal",

        // 三個精美水晶合并成為一個神之水晶
        ({ "/clone/gift/fcrystal-1",
           "/clone/gift/fcrystal-2",
           "/clone/gift/fcrystal-3" }) : "/clone/gift/mcrystal",

        // 三個翡翠碎片合并成為一個翡翠
        ({ "/clone/gift/cjade-1",
           "/clone/gift/cjade-2",
           "/clone/gift/cjade-3" }) : "/clone/gift/jade",

        // 三個翡翠合并成為一個精美翡翠
        ({ "/clone/gift/jade-1",
           "/clone/gift/jade-2",
           "/clone/gift/jade-3" }) : "/clone/gift/fjade",

        // 三個精美翡翠合并成為一個神之翡翠
        ({ "/clone/gift/fjade-1",
           "/clone/gift/fjade-2",
           "/clone/gift/fjade-3" }) : "/clone/gift/mjade",

/*
        // 乾坤聖水
        ({ "/clone/fam/gift/int3-1",
           "/clone/fam/gift/con3-1",
           "/clone/fam/gift/str3-1",
           "/clone/fam/gift/dex3-1" }) : "/clone/fam/item/bless_water",
*/

        // 乾坤聖水
        ({ "/clone/fam/gift/int3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // 乾坤聖水
        ({ "/clone/fam/gift/con3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // 乾坤聖水
        ({ "/clone/fam/gift/dex3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // 乾坤聖水
        ({ "/clone/fam/gift/str3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // 輝石
        ({ "/clone/fam/item/stone3-1",
           "/clone/fam/item/stone1-1",
           }) : "/clone/fam/item/stone4",

        // 皓石
        ({ "/clone/fam/item/stone2-1",
           "/clone/fam/item/stone1-1",
           }) : "/clone/fam/item/stone3",


        // 輝月華石
        ({ "/clone/fam/item/stone1-1",
           "/clone/fam/item/stone4-1",
           "/clone/fam/item/stone3-1",
           "/clone/fam/item/stone2-1",
           }) : "/clone/fam/item/stone5",

        /******************************************
                    鑲嵌之物品--高級
        *******************************************/
        // 碧魄冰晶
        ({ "/clone/fam/etc/lv5f-1",
          "/clone/fam/etc/lv7c-1", // 青龍牙
          "/clone/fam/etc/lv7d-1", // 如意通天钁
          "/clone/fam/etc/lv7a-1", // 五彩玲瓏珠
          "/clone/fam/etc/prize5-1", // 神血清
           }) : "/clone/fam/etc/bipo",

        // 幻石
        ({ "/clone/fam/item/baxian-1",
          "/clone/fam/item/kunlun-1",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/etc/lv7a-1",
          "/clone/fam/etc/prize5-1",
           }) : "/clone/fam/etc/huanshi",

        // 冰火珠
        ({ "/clone/fam/item/leihuo-1",
          "/clone/fam/item/lihuo-1",
          "/clone/fam/etc/lv5d-1", // 幻地神珠
          "/clone/fam/etc/lv7a-1",
          "/clone/fam/etc/prize5-1",
           }) : "/clone/fam/etc/binghuozhu",

        // 雷神珠
        ({ "/clone/fam/item/leihuo-1",
          "/clone/fam/etc/lv7c-1",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/etc/lv7a-1",
          "/clone/fam/etc/prize5-1",
           }) : "/clone/fam/etc/leishenzhu",

        /******************************************
                    鑲嵌之物品--珍品
        *******************************************/
        // 神之寒晶・冰
        ({ "/clone/fam/etc/bipo-1",
          "/clone/fam/item/bless_water-1",
          "/clone/fam/etc/lv5d-1",
          "/clone/fam/etc/prize4-1",
           }) : "/clone/fam/etc/hanjing",

        // 魔之心・魔
        ({ "/clone/fam/etc/huanshi-1",
          "/clone/fam/item/bless_water-1",
          "/clone/fam/etc/lv5d-1",
          "/clone/fam/item/stone5-1",
           }) : "/clone/fam/etc/mozhixin",

        // 火之精靈・火
        ({ "/clone/fam/etc/binghuozhu-1",
          "/clone/fam/item/bless_water-1",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/etc/lv7b-1",
           }) : "/clone/fam/etc/huojingling",

        // 雷神之瞳・電
        ({ "/clone/fam/etc/leishenzhu-1",
          "/clone/fam/item/bless_water-1",
          "/clone/fam/etc/lv5d-1",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/item/zhenlong-1",
           }) : "/clone/fam/etc/leishentong",

        // 白虎・金 = 精金 + 如意通天钁 + 雷神珠   + 輝華月石
        // 青龍・木 = 木靈 + 鎮龍石     + 青龍牙   + 乾坤聖水
        // 玄武・水 = 玄冰 + 碧魄冰晶   + 神血清 + 乾坤聖水
        // 朱雀・火 = 炎晶 + 冰火珠     + 熾石     + 五彩玲瓏珠
        // 麒麟・土 = 玉髓 + 幻石       + 息壤     + 輝華月石
        ({ "/clone/tessera/metal-1",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/etc/leishenzhu-1",
          "/clone/fam/item/stone5-1",
          }) : "/clone/tessera/baihu",

        ({ "/clone/tessera/wood-1",
          "/clone/fam/item/zhenlong-1",
          "/clone/fam/etc/lv7c-1",
          "/clone/fam/item/bless_water-1",
          }) : "/clone/tessera/qinglong",

        ({ "/clone/tessera/water-1",
          "/clone/fam/etc/bipo-1",
          "/clone/fam/etc/prize5-1",
          "/clone/fam/item/bless_water-1",
          }) : "/clone/tessera/xuanwu",

        ({ "/clone/tessera/fire-1",
          "/clone/fam/etc/binghuozhu-1",
          "/clone/fam/item/stone1-1",
          "/clone/fam/etc/lv7a-1",
          }) : "/clone/tessera/zhuque",

        ({ "/clone/tessera/earth-1",
          "/clone/fam/etc/huanshi-1",
          "/clone/fam/etc/lv7b-1",
          "/clone/fam/item/stone5-1",
          }) : "/clone/tessera/qilin",

        ({ "/clone/fam/etc/bipo-1",
          "/d/death/obj/qise-1",
          "/clone/tessera/rune20-1",
          }) : "/clone/goods/tianjing",

/**********************************************************
 特殊裝備或者物品，非常珍貴，只能通過一些特殊途徑獲取或合成
 比如故事等。
**********************************************************/
       // 炎甲
       ({
          "/clone/fam/etc/longlin-1",
          "/clone/fam/etc/longlin-2",
          "/clone/fam/etc/longlin-3",
          "/clone/fam/etc/longlin-4",
          "/clone/fam/etc/longlin-5",
          "/clone/fam/etc/longlin-6",
          "/clone/fam/etc/longlin-7",
          "/clone/fam/etc/longlin-8",
          "/clone/fam/etc/longlin-9",
          "/clone/fam/etc/longlin-10",
          "/clone/fam/etc/longjiao-1",
          "/clone/fam/etc/longjiao-2",
          "/clone/fam/etc/longjin-1",
          "/clone/fam/etc/longxu-1",
          "/clone/fam/etc/longxu-2",
          "/clone/fam/etc/prize3-1",
          "/clone/fam/etc/prize3-2"}) : "/clone/fam/armor/yanlongjia",

       // 紫鮫甲
       ({
          "/clone/fam/etc/jiaopige-1",
          "/clone/fam/etc/jiaopige-2",
          "/clone/fam/etc/jiaojin-1",
          "/clone/fam/etc/jiaoxu-1",
          "/clone/fam/etc/jiaoxu-2",
          "/clone/fam/pill/dimai-1",
          "/clone/fam/pill/dimai-2",
          "/clone/fam/pill/dimai-3",
          "/clone/fam/pill/dimai-4",
          "/clone/fam/pill/dimai-5",
          "/clone/fam/pill/dimai-6"}) : "/clone/fam/armor/zijiaojia",

      // 紫鮫皮革
      ({
          "/clone/fam/etc/jiaopi-1",
          "/clone/fam/etc/jiaopi-2",
          "/clone/fam/etc/jiaopi-3",
          "/clone/fam/etc/jiaopi-4",
          "/clone/fam/etc/jiaopi-5",
          "/clone/fam/etc/jiaopi-6",
          "/clone/fam/etc/jiaopi-7",
          "/clone/fam/etc/jiaopi-8",
          "/clone/fam/etc/jiaopi-9",
          "/clone/fam/etc/jiaopi-10"}) : "/clone/fam/etc/jiaopige",

      //鳳凰羽毛
      ({
          "/clone/fam/etc/yumao-1",
          "/clone/fam/etc/yumao-2",
          "/clone/fam/etc/yumao-3",
          "/clone/fam/etc/yumao-4",
          "/clone/fam/etc/yumao-5" }) : "/clone/fam/etc/yumao2",


       // 鳳凰披風
       ({
          "/clone/fam/etc/yumao2-1",
          "/clone/fam/etc/yumao2-2",
          "/clone/fam/etc/yumao2-3",
          "/clone/fam/etc/yumao2-4",
          "/clone/fam/etc/zhuquejiao-1",
          "/clone/fam/etc/zhuquejiao-2",
          "/clone/fam/etc/zhuquejin-1",
          "/clone/fam/etc/lv7a-1",
          "/clone/fam/etc/lv7a-2"}) : "/clone/fam/armor/fenghuangjia",

       // 白虎皮革
      ({
          "/clone/fam/etc/hupi-1",
          "/clone/fam/etc/hupi-2",
          "/clone/fam/etc/hupi-3",
          "/clone/fam/etc/hupi-4",
          "/clone/fam/etc/hupi-5",
          "/clone/fam/etc/hupi-6",
          "/clone/fam/etc/hupi-7",
          "/clone/fam/etc/hupi-8",
          "/clone/fam/etc/hupi-9",
          "/clone/fam/etc/hupi-10"}) : "/clone/fam/etc/hupige",


       // 鳳凰頭冠
      ({
          "/clone/fam/etc/yumao-1",
          "/clone/fam/etc/yumao-2",
          "/clone/fam/etc/fenghuangjiao-1",
          "/clone/fam/etc/fenghuangjiao-2",
          "/clone/fam/etc/fenghuangjiao-3",
          "/clone/fam/etc/fenghuangjiao-4"}) : "/clone/fam/armor/fenghuanghead",

       // 炎龍神冠
      ({
          "/clone/fam/etc/longlin-1",
          "/clone/fam/etc/longlin-2",
          "/clone/fam/etc/longjiao-1",
          "/clone/fam/etc/longjiao-2",
          "/clone/fam/etc/longjiao-3",
          "/clone/fam/etc/longjiao-4"}) : "/clone/fam/armor/yanlonghead",

       // 紫蛟頭顱
      ({
          "/clone/fam/etc/jiaopi-1",
          "/clone/fam/etc/jiaopi-2",
          "/clone/fam/etc/jiaoxu-1",
          "/clone/fam/etc/jiaoxu-2",
          "/clone/fam/etc/jiaoxu-3",
          "/clone/fam/etc/jiaoxu-4"}) : "/clone/fam/armor/zijiaohead",

       // 白虎護腕
      ({
          "/clone/fam/etc/hugu-1",
          "/clone/fam/etc/hugu-2",
          "/clone/fam/etc/hupi-1",
          "/clone/fam/etc/hupi-2",
          "/clone/fam/etc/hupi-3",
          "/clone/fam/etc/hupi-4"}) : "/clone/fam/armor/baihuwrists",


       // 鳳凰腰帶
      ({
          "/clone/fam/etc/fenghuangjin-1",
          "/clone/fam/etc/fenghuangjin-2",
          "/clone/fam/etc/fenghuangjin-3",
          "/clone/fam/etc/fenghuangjin-4"}) : "/clone/fam/armor/fenghuangyaodai",

       // 神虎腰帶
      ({
          "/clone/fam/etc/hujin-1",
          "/clone/fam/etc/hujin-2",
          "/clone/fam/etc/hujin-3",
          "/clone/fam/etc/hujin-4"}) : "/clone/fam/armor/baihuyaodai",

       // 神虎戰甲
      ({
          "/clone/fam/etc/hupige-1",
          "/clone/fam/etc/hupige-2",
          "/clone/fam/etc/hujin-1",
          "/clone/fam/etc/hugu-1",
          "/clone/fam/etc/hugu-2",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/etc/lv7d-2",
          "/clone/fam/etc/lv7d-3",
          "/clone/fam/etc/lv7d-4"}) : "/clone/fam/armor/shenhujia",

       // 炎龍腰帶
      ({
          "/clone/fam/etc/longjin-1",
          "/clone/fam/etc/longjin-2",
          "/clone/fam/etc/longjin-3",
          "/clone/fam/etc/longjin-4"}) : "/clone/fam/armor/yanlongyaodai",

       // 紫蛟腰帶
      ({
          "/clone/fam/etc/jiaojin-1",
          "/clone/fam/etc/jiaojin-2",
          "/clone/fam/etc/jiaojin-3",
          "/clone/fam/etc/jiaojin-4"}) : "/clone/fam/armor/zijiaoyaodai",

       // 藍寶石
      ({
          "/clone/quarry/item/lan-baoshikuang-1",
          "/clone/quarry/item/lan-baoshikuang-2",
          "/clone/quarry/item/lan-baoshikuang-3",
          "/clone/quarry/item/lan-baoshikuang-4",
	  "/clone/quarry/item/lan-baoshikuang-5",}) : "/clone/fam/enchase/lan-baoshi",

       // 紅寶石
      ({
          "/clone/quarry/item/hong-baoshikuang-1",
          "/clone/quarry/item/hong-baoshikuang-2",
          "/clone/quarry/item/hong-baoshikuang-3",
          "/clone/quarry/item/hong-baoshikuang-4",
          "/clone/quarry/item/hong-baoshikuang-5",}) : "/clone/fam/enchase/hong-baoshi",
          
/*
        // 風洞之眼・風
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/yelgem7-1",
          "/clone/tessera/rune20-1",
           }) : "/clone/item/fengdong.c",

        // 神之寒晶・冰
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/grngem7-1",
          "/clone/tessera/rune21-1",
           }) : "/clone/item/hanjing",

        // 聖魔之心・魔
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/blugem7-1",
          "/clone/tessera/rune22-1",
           }) : "/clone/item/mozhixin",

        // 火之精靈・火
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/redgem7-1",
          "/clone/tessera/rune23-1",
           }) : "/clone/item/huojingling",

        // 雷神之瞳・電
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/maggem7-1",
          "/clone/tessera/rune24-1",
           }) : "/clone/item/leishentong",
*/
]);

int main(object me, string arg)
{
        mapping same;                   // 判斷重複的物品的需要的mapping
        string *item_list, *name_list;  // 合并的物品ID表和匹配的基本名字表
        string bname;                   // 物品對應的文件的基本名字
        object *ob_list;                // 合并的所有物品
        string *per;                    // mapping中記錄的可合并的基本名字表
        object obj;                     // 生成的物品
        int mp, i;

        if (! arg)
                return notify_fail("你要合并什麼物品？\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再做這件事情吧！\n");

        if (me->is_fighting())
                return notify_fail("你現在正在打架，沒時間做這些事情。\n");

        if( query("max_jingli", me)<300 )
                return notify_fail("你現在的精力修為有限，無法合成物品。\n");

        if( query("jingli", me)<300 )
                return notify_fail("你現在精力不濟，無法合成物品。\n");

        item_list = explode(arg, "&");
        ob_list   = allocate(sizeof(item_list));
        name_list = allocate(sizeof(item_list));
        same = allocate_mapping(sizeof(item_list));
        for (i = 0; i < sizeof(item_list); i++)
        {
                bname = item_list[i];
                if (! bname || bname == " ") return notify_fail("格式錯誤。\n");
                while (bname[0] == ' ') bname = bname[1..<0];
                if( sizeof(bname) < 2 ) notify_fail("格式錯誤。\n");
                while (bname[strlen(bname) - 1] == ' ') bname = bname[0..<2];
                ob_list[i] = present(bname, me);

                if (! objectp(ob_list[i]))
                        return notify_fail("你身上沒有 " + bname + " 這種物品啊。\n");

                /*
                if( query("no_identify", ob_list[i]) )
                        return notify_fail("你身上的 " + bname + " 還沒有去鑒定啊。\n");
                */

                if (i > 0 && member_array(ob_list[i], ob_list[0..i - 1]) != -1)
                        return notify_fail("合并物品需要指明不同的物品，不要重複指"
                                           "明一件物品。\n");

                bname = base_name(ob_list[i]);
                /*
                if (strsrch(bname, "/inherit/template/jewel/") >= 0)
                        sscanf(bname, "%s-%*s", bname);
                */
                if (undefinedp(same[bname]))
                        same[bname] = 1;
                else
                        same[bname]++;
                name_list[i] = bname + "-" + (string) same[bname];
        }

        tell_object(me, HIW "\n你雙目微閉，將數樣物品凝於掌中，運轉內勁迫"
                        "使它們交融。\n" NOR);

        me->start_busy(1);
        addn("jingli", -200, me);
        foreach (per in keys(combine_list))
        {
                if (per - name_list == ({ }) && sizeof(per) == sizeof(name_list))
                {
                        // 找到了合適的組合
                        obj = new(combine_list[per]);
                        for (i = 0; i < sizeof(ob_list); i++)
                        {
                                if (ob_list[i]->query_amount())
                                        ob_list[i]->add_amount(-1);
                                else
                                {
                                        /*
                                        if (strsrch(base_name(ob_list[i]), "/data/template/jewel/") >= 0)
                                                rm(base_name(ob_list[i]) + ".c");
                                        */
                                        destruct(ob_list[i]);
                                }
                        }
                        message("vision", HIW "\n霎時間只見" + me->name() + HIW "掌心一道"
                                          "光華閃過，但轉瞬即逝，似乎發生了什麼不同尋常的"
                                          "事情。\n\n" NOR, environment(me), ({me}));

                        tell_object(me, HIW "霎時間只見萬道光華疾閃而過，你急忙攤開手掌，"
                                        "發現掌心\n豁然出現了一"+query("unit", obj)+
                                        obj->name() + HIW "，蘊漾着七色霞光。\n\n" NOR);

                        if( query("value", obj) )
                        {
                                mp=(query("value", obj)/700);
                                mp = 1 + random(mp);
                                if (mp < 1) mp = 1;
                                if (mp > 100) mp = 100;

                                addn("magic_points", mp, me);
                                tell_object(me, HIC "你通過合成"+ obj->name() + HIC "的歷"
                                                "練過程，從而獲得了" + chinese_number(mp) +
                                                "點靈慧。\n" NOR);
                        }
                        addn("max_jingli", -1, me);
                        obj->move(me, 1);
                        MYGIFT_D->check_mygift(me, "newbie_mygift/combine"); 
                        return 1;
                }
        }
        tell_object(me, HIR "可是過了半天，似乎沒有任何變化，你不禁一聲"
                        "長嘆。\n" NOR);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : combine <特殊物品> & <特殊物品> & ……

這個指令可以讓你將某些特殊物品合并成一種新的物品，哪些才能合
並？這就要靠你去發掘了。每次合并都會損失一點精力的上限。如果
要合并的幾個物品名字相同，則需要指明他們的序號，比如有三個鑽
石，如果要合一，則需要輸入：

  combine diamond & diamond 2 & diamond 3

HELP);
        return 1;
}
