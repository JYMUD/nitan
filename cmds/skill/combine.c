// combine.c
// Updated by Lonely

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

mapping combine_list = ([
        //ѫ�ºϳ�
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
                                
        //��ʯ�ϳ�
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
        //װ��֮��
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
        // ������ͼ...
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


        // ���ĵĺϳɹ�ʽ
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

       // ��ⱦ��
       ({
       	  "/clone/quarry/item/zhenzhu-1",
       	  "/clone/quarry/item/zhenzhu-2",
       	  "/clone/quarry/item/zhenzhu-3",   })  : "/clone/quarry/item/combine/foguang-baozhu",
       	  
       // �����
       ({
       	  "/clone/fam/item/bixue-1",
       	  "/clone/fam/item/bless_water-1",
       	  "/clone/fam/pill/neili2-1",   })  : "/clone/fam/item/wannian-hong",

        // ����������
        ({ "/clone/fam/max/xuanhuang-1",
           "/clone/fam/max/longjia-1",
           "/clone/fam/item/kunlun-1",
           "/clone/fam/item/baxian-1", }) : "/clone/fam/max/zhenyu",

        // �������׵�
        ({ "/clone/fam/pill/dimai-1",
           "/clone/fam/pill/renshen4-1",
           "/clone/fam/etc/lv7d-1", }) : "/clone/fam/max/longjia",

        // �������䵤
        ({ "/clone/fam/pill/yulu-1",
           "/clone/fam/pill/lingzhi4-1",
           "/clone/fam/etc/lv7a-1", }) : "/clone/fam/max/xuanhuang",

        // ����ѪȪ
        ({ "/clone/fam/pill/puti2-1",
           "/clone/fam/pill/sheli3-1",
           "/clone/fam/etc/lv7b-1", }) : "/clone/fam/pill/dimai",

        // ������¶
        ({ "/clone/fam/pill/sheli2-1",
           "/clone/fam/pill/puti3-1",
           "/clone/fam/etc/lv7c-1", }) : "/clone/fam/pill/yulu",

        // ǧ����ĵ�
        ({ "/clone/fam/pill/renshen1-1",
           "/clone/fam/pill/renshen2-1",
           "/clone/fam/etc/lv5c-1", }) : "/clone/fam/pill/renshen4",

        // ǧ����֥��
        ({ "/clone/fam/pill/lingzhi1-1",
           "/clone/fam/pill/lingzhi2-1",
           "/clone/fam/etc/lv5c-1", }) : "/clone/fam/pill/lingzhi4",

        // ǧ��ѩ����
        ({ "/clone/fam/pill/xuelian1-1",
           "/clone/fam/pill/xuelian2-1",
           "/clone/fam/etc/lv5c-1", }) : "/clone/fam/pill/xuelian4",

        // ������ĵ�
        ({ "/clone/fam/pill/renshen1-1",
           "/clone/fam/etc/lv5e-1", }) : "/clone/fam/pill/renshen3",

        // ������֥��
        ({ "/clone/fam/pill/lingzhi1-1",
           "/clone/fam/etc/lv5e-1", }) : "/clone/fam/pill/lingzhi3",

        // ����ѩ����
        ({ "/clone/fam/pill/xuelian1-1",
           "/clone/fam/etc/lv5e-1", }) : "/clone/fam/pill/xuelian3",

        // ��쵤
        ({ "/clone/fam/pill/linghui1-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/linghui2",

        // ������
        ({ "/clone/fam/pill/neili1-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/neili2",

        // ������
        ({ "/clone/fam/pill/puti1-1",
           "/clone/fam/pill/puti2-1",
           "/clone/fam/pill/puti3-1", }) : "/clone/fam/pill/puti4",

        // ʥ����
        ({ "/clone/fam/pill/sheli1-1",
           "/clone/fam/pill/sheli2-1",
           "/clone/fam/pill/sheli3-1", }) : "/clone/fam/pill/sheli4",

        // ��������
        ({ "/clone/fam/pill/sheli2-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/sheli3",

        // ������
        ({ "/clone/fam/pill/puti2-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/puti3",

        // ������
        ({ "/clone/fam/pill/puti1-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/puti2",

        // ��������
        ({ "/clone/fam/pill/sheli1-1",
           "/clone/fam/pill/full1-1", }) : "/clone/fam/pill/sheli2",

        // ��������
        ({ "/clone/fam/etc/lv5a-1",
           "/clone/fam/etc/lv5b-1",
           "/clone/fam/etc/lv5d-1",
           "/clone/fam/etc/lv7d-1",
           "/clone/fam/gift/str3-1", }) : "/clone/fam/max/tianshu1",

        // ��������
        ({ "/clone/fam/etc/lv5a-1",
           "/clone/fam/etc/lv5b-1",
           "/clone/fam/etc/lv5d-1",
           "/clone/fam/etc/lv7d-1",
           "/clone/fam/gift/con3-1", }) : "/clone/fam/max/tianshu1",

        // ��������
        ({ "/clone/fam/etc/lv5a-1",
           "/clone/fam/etc/lv5b-1",
           "/clone/fam/etc/lv5d-1",
           "/clone/fam/etc/lv7d-1",
           "/clone/fam/gift/int3-1", }) : "/clone/fam/max/tianshu1",

        // ��������
        ({ "/clone/fam/etc/lv5a-1",
           "/clone/fam/etc/lv5b-1",
           "/clone/fam/etc/lv5d-1",
           "/clone/fam/etc/lv7d-1",
           "/clone/fam/gift/dex3-1", }) : "/clone/fam/max/tianshu1",
        // ���ž�������ͼ��Ƭƴ�ճ������ľ�������ͼ
        ({ "/clone/tattoo/spcs1-1",
           "/clone/tattoo/spcs1-2",
           "/clone/tattoo/spcs1-3",
           "/clone/tattoo/spcs1-4",
           "/clone/tattoo/spcs1-5" }) : "/clone/tattoo/spc1",

        // ���ŷ������ͼ��Ƭƴ�ճ������ķ������ͼ
        ({ "/clone/tattoo/spcs2-1",
           "/clone/tattoo/spcs2-2",
           "/clone/tattoo/spcs2-3",
           "/clone/tattoo/spcs2-4",
           "/clone/tattoo/spcs2-5" }) : "/clone/tattoo/spc2",

        // �������ʥͼ��Ƭƴ�ճ����������ʥͼ
        ({ "/clone/tattoo/spcs3-1",
           "/clone/tattoo/spcs3-2",
           "/clone/tattoo/spcs3-3",
           "/clone/tattoo/spcs3-4",
           "/clone/tattoo/spcs3-5" }) : "/clone/tattoo/spc3",

        // ���Űٹ�ҹ��ͼ��Ƭƴ�ճ������İٹ�ҹ��ͼ
        ({ "/clone/tattoo/spcs4-1",
           "/clone/tattoo/spcs4-2",
           "/clone/tattoo/spcs4-3",
           "/clone/tattoo/spcs4-4",
           "/clone/tattoo/spcs4-5" }) : "/clone/tattoo/spc4",

        // ������������ͼ��Ƭƴ�ճ���������������ͼ
        ({ "/clone/tattoo/spcs5-1",
           "/clone/tattoo/spcs5-2",
           "/clone/tattoo/spcs5-3",
           "/clone/tattoo/spcs5-4",
           "/clone/tattoo/spcs5-5" }) : "/clone/tattoo/spc5",

        // ����ǧ�ֹ���ͼ��Ƭƴ�ճ�������ǧ�ֹ���ͼ
        ({ "/clone/tattoo/spcs6-1",
           "/clone/tattoo/spcs6-2",
           "/clone/tattoo/spcs6-3",
           "/clone/tattoo/spcs6-4",
           "/clone/tattoo/spcs6-5" }) : "/clone/tattoo/spc6",

        // ���Ž���ɽ��ͼ��Ƭƴ�ճ������Ľ���ɽ��ͼ
        ({ "/clone/tattoo/spcs7-1",
           "/clone/tattoo/spcs7-2",
           "/clone/tattoo/spcs7-3",
           "/clone/tattoo/spcs7-4",
           "/clone/tattoo/spcs7-5" }) : "/clone/tattoo/spc7",

        // ���ź�������ͼ��Ƭƴ�ճ������ĺ�������ͼ
        ({ "/clone/tattoo/spcs8-1",
           "/clone/tattoo/spcs8-2",
           "/clone/tattoo/spcs8-3",
           "/clone/tattoo/spcs8-4",
           "/clone/tattoo/spcs8-5" }) : "/clone/tattoo/spc8",

        // ���ž�������ͼ��Ƭƴ�ճ������ľ�������ͼ
        ({ "/clone/tattoo/spcs9-1",
           "/clone/tattoo/spcs9-2",
           "/clone/tattoo/spcs9-3",
           "/clone/tattoo/spcs9-4",
           "/clone/tattoo/spcs9-5" }) : "/clone/tattoo/spc9",

        // ����ڤ������ͼ��Ƭƴ�ճ�������ڤ������ͼ
        ({ "/clone/tattoo/spcs10-1",
           "/clone/tattoo/spcs10-2",
           "/clone/tattoo/spcs10-3",
           "/clone/tattoo/spcs10-4",
           "/clone/tattoo/spcs10-5" }) : "/clone/tattoo/spc10",

        // ������ʯ��Ƭ�ϲ���Ϊһ����ʯ
        ({ "/clone/gift/cdiamond-1",
           "/clone/gift/cdiamond-2",
           "/clone/gift/cdiamond-3" }) : "/clone/gift/diamond",

        // ������ʯ�ϲ���Ϊһ��������ʯ
        ({ "/clone/gift/diamond-1",
           "/clone/gift/diamond-2",
           "/clone/gift/diamond-3" }) : "/clone/gift/fdiamond",

        // ����������ʯ�ϲ���Ϊһ����֮��ʯ
        ({ "/clone/gift/fdiamond-1",
           "/clone/gift/fdiamond-2",
           "/clone/gift/fdiamond-3" }) : "/clone/gift/mdiamond",

        // ���������Ƭ�ϲ���Ϊһ�����
        ({ "/clone/gift/cagate-1",
           "/clone/gift/cagate-2",
           "/clone/gift/cagate-3" }) : "/clone/gift/agate",

        // ������觺ϲ���Ϊһ���������
        ({ "/clone/gift/agate-1",
           "/clone/gift/agate-2",
           "/clone/gift/agate-3" }) : "/clone/gift/fagate",

        // ����������觺ϲ���Ϊһ����֮���
        ({ "/clone/gift/fagate-1",
           "/clone/gift/fagate-2",
           "/clone/gift/fagate-3" }) : "/clone/gift/magate",

        // ����ˮ����Ƭ�ϲ���Ϊһ��ˮ��
        ({ "/clone/gift/ccrystal-1",
           "/clone/gift/ccrystal-2",
           "/clone/gift/ccrystal-3" }) : "/clone/gift/crystal",

        // ����ˮ���ϲ���Ϊһ������ˮ��
        ({ "/clone/gift/crystal-1",
           "/clone/gift/crystal-2",
           "/clone/gift/crystal-3" }) : "/clone/gift/fcrystal",

        // ��������ˮ���ϲ���Ϊһ����֮ˮ��
        ({ "/clone/gift/fcrystal-1",
           "/clone/gift/fcrystal-2",
           "/clone/gift/fcrystal-3" }) : "/clone/gift/mcrystal",

        // ���������Ƭ�ϲ���Ϊһ�����
        ({ "/clone/gift/cjade-1",
           "/clone/gift/cjade-2",
           "/clone/gift/cjade-3" }) : "/clone/gift/jade",

        // �������ϲ���Ϊһ���������
        ({ "/clone/gift/jade-1",
           "/clone/gift/jade-2",
           "/clone/gift/jade-3" }) : "/clone/gift/fjade",

        // �����������ϲ���Ϊһ����֮���
        ({ "/clone/gift/fjade-1",
           "/clone/gift/fjade-2",
           "/clone/gift/fjade-3" }) : "/clone/gift/mjade",

/*
        // Ǭ��ʥˮ
        ({ "/clone/fam/gift/int3-1",
           "/clone/fam/gift/con3-1",
           "/clone/fam/gift/str3-1",
           "/clone/fam/gift/dex3-1" }) : "/clone/fam/item/bless_water",
*/

        // Ǭ��ʥˮ
        ({ "/clone/fam/gift/int3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // Ǭ��ʥˮ
        ({ "/clone/fam/gift/con3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // Ǭ��ʥˮ
        ({ "/clone/fam/gift/dex3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // Ǭ��ʥˮ
        ({ "/clone/fam/gift/str3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // ��ʯ
        ({ "/clone/fam/item/stone3-1",
           "/clone/fam/item/stone1-1",
           }) : "/clone/fam/item/stone4",

        // �ʯ
        ({ "/clone/fam/item/stone2-1",
           "/clone/fam/item/stone1-1",
           }) : "/clone/fam/item/stone3",


        // ���»�ʯ
        ({ "/clone/fam/item/stone1-1",
           "/clone/fam/item/stone4-1",
           "/clone/fam/item/stone3-1",
           "/clone/fam/item/stone2-1",
           }) : "/clone/fam/item/stone5",

        /******************************************
                    ��Ƕ֮��Ʒ--�߼�
        *******************************************/
        // ���Ǳ���
        ({ "/clone/fam/etc/lv5f-1",
          "/clone/fam/etc/lv7c-1", // ������
          "/clone/fam/etc/lv7d-1", // ����ͨ����
          "/clone/fam/etc/lv7a-1", // ���������
          "/clone/fam/etc/prize5-1", // ���}Ѫ��
           }) : "/clone/fam/etc/bipo",

        // ��ʯ
        ({ "/clone/fam/item/baxian-1",
          "/clone/fam/item/kunlun-1",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/etc/lv7a-1",
          "/clone/fam/etc/prize5-1",
           }) : "/clone/fam/etc/huanshi",

        // ������
        ({ "/clone/fam/item/leihuo-1",
          "/clone/fam/item/lihuo-1",
          "/clone/fam/etc/lv5d-1", // �õ�����
          "/clone/fam/etc/lv7a-1",
          "/clone/fam/etc/prize5-1",
           }) : "/clone/fam/etc/binghuozhu",

        // ������
        ({ "/clone/fam/item/leihuo-1",
          "/clone/fam/etc/lv7c-1",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/etc/lv7a-1",
          "/clone/fam/etc/prize5-1",
           }) : "/clone/fam/etc/leishenzhu",

        /******************************************
                    ��Ƕ֮��Ʒ--��Ʒ
        *******************************************/
        // ��֮��������
        ({ "/clone/fam/etc/bipo-1",
          "/clone/fam/item/bless_water-1",
          "/clone/fam/etc/lv5d-1",
          "/clone/fam/etc/prize4-1",
           }) : "/clone/fam/etc/hanjing",

        // ħ֮�ġ�ħ
        ({ "/clone/fam/etc/huanshi-1",
          "/clone/fam/item/bless_water-1",
          "/clone/fam/etc/lv5d-1",
          "/clone/fam/item/stone5-1",
           }) : "/clone/fam/etc/mozhixin",

        // ��֮���顤��
        ({ "/clone/fam/etc/binghuozhu-1",
          "/clone/fam/item/bless_water-1",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/etc/lv7b-1",
           }) : "/clone/fam/etc/huojingling",

        // ����֮ͫ����
        ({ "/clone/fam/etc/leishenzhu-1",
          "/clone/fam/item/bless_water-1",
          "/clone/fam/etc/lv5d-1",
          "/clone/fam/etc/lv7d-1",
          "/clone/fam/item/zhenlong-1",
           }) : "/clone/fam/etc/leishentong",

        // �׻����� = ���� + ����ͨ���� + ������   + �Ի���ʯ
        // ������ľ = ľ�� + ����ʯ     + ������   + Ǭ��ʥˮ
        // ���䡤ˮ = ���� + ���Ǳ���   + ���}Ѫ�� + Ǭ��ʥˮ
        // ��ȸ���� = �׾� + ������     + ��ʯ     + ���������
        // ���롤�� = ���� + ��ʯ       + Ϣ��     + �Ի���ʯ
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
 ����װ��������Ʒ���ǳ����ֻ��ͨ��һЩ����;����ȡ��ϳ�
 ������µȡ�
**********************************************************/
       // �����}��
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

       // ���޼�
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

      // ����Ƥ��
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

      //�����ë
      ({
          "/clone/fam/etc/yumao-1",
          "/clone/fam/etc/yumao-2",
          "/clone/fam/etc/yumao-3",
          "/clone/fam/etc/yumao-4",
          "/clone/fam/etc/yumao-5" }) : "/clone/fam/etc/yumao2",


       // �������
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

       // �׻�Ƥ��
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


       // ���ͷ��
      ({
          "/clone/fam/etc/yumao-1",
          "/clone/fam/etc/yumao-2",
          "/clone/fam/etc/fenghuangjiao-1",
          "/clone/fam/etc/fenghuangjiao-2",
          "/clone/fam/etc/fenghuangjiao-3",
          "/clone/fam/etc/fenghuangjiao-4"}) : "/clone/fam/armor/fenghuanghead",

       // �������
      ({
          "/clone/fam/etc/longlin-1",
          "/clone/fam/etc/longlin-2",
          "/clone/fam/etc/longjiao-1",
          "/clone/fam/etc/longjiao-2",
          "/clone/fam/etc/longjiao-3",
          "/clone/fam/etc/longjiao-4"}) : "/clone/fam/armor/yanlonghead",

       // ����ͷ­
      ({
          "/clone/fam/etc/jiaopi-1",
          "/clone/fam/etc/jiaopi-2",
          "/clone/fam/etc/jiaoxu-1",
          "/clone/fam/etc/jiaoxu-2",
          "/clone/fam/etc/jiaoxu-3",
          "/clone/fam/etc/jiaoxu-4"}) : "/clone/fam/armor/zijiaohead",

       // �׻�����
      ({
          "/clone/fam/etc/hugu-1",
          "/clone/fam/etc/hugu-2",
          "/clone/fam/etc/hupi-1",
          "/clone/fam/etc/hupi-2",
          "/clone/fam/etc/hupi-3",
          "/clone/fam/etc/hupi-4"}) : "/clone/fam/armor/baihuwrists",


       // �������
      ({
          "/clone/fam/etc/fenghuangjin-1",
          "/clone/fam/etc/fenghuangjin-2",
          "/clone/fam/etc/fenghuangjin-3",
          "/clone/fam/etc/fenghuangjin-4"}) : "/clone/fam/armor/fenghuangyaodai",

       // ������
      ({
          "/clone/fam/etc/hujin-1",
          "/clone/fam/etc/hujin-2",
          "/clone/fam/etc/hujin-3",
          "/clone/fam/etc/hujin-4"}) : "/clone/fam/armor/baihuyaodai",

       // ��ս��
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

       // ��������
      ({
          "/clone/fam/etc/longjin-1",
          "/clone/fam/etc/longjin-2",
          "/clone/fam/etc/longjin-3",
          "/clone/fam/etc/longjin-4"}) : "/clone/fam/armor/yanlongyaodai",

       // ��������
      ({
          "/clone/fam/etc/jiaojin-1",
          "/clone/fam/etc/jiaojin-2",
          "/clone/fam/etc/jiaojin-3",
          "/clone/fam/etc/jiaojin-4"}) : "/clone/fam/armor/zijiaoyaodai",

       // ����ʯ
      ({
          "/clone/quarry/item/lan-baoshikuang-1",
          "/clone/quarry/item/lan-baoshikuang-2",
          "/clone/quarry/item/lan-baoshikuang-3",
          "/clone/quarry/item/lan-baoshikuang-4",
	  "/clone/quarry/item/lan-baoshikuang-5",}) : "/clone/fam/enchase/lan-baoshi",

       // �챦ʯ
      ({
          "/clone/quarry/item/hong-baoshikuang-1",
          "/clone/quarry/item/hong-baoshikuang-2",
          "/clone/quarry/item/hong-baoshikuang-3",
          "/clone/quarry/item/hong-baoshikuang-4",
          "/clone/quarry/item/hong-baoshikuang-5",}) : "/clone/fam/enchase/hong-baoshi",
          
/*
        // �綴֮�ۡ���
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/yelgem7-1",
          "/clone/tessera/rune20-1",
           }) : "/clone/item/fengdong.c",

        // ��֮��������
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/grngem7-1",
          "/clone/tessera/rune21-1",
           }) : "/clone/item/hanjing",

        // ʥħ֮�ġ�ħ
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/blugem7-1",
          "/clone/tessera/rune22-1",
           }) : "/clone/item/mozhixin",

        // ��֮���顤��
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/redgem7-1",
          "/clone/tessera/rune23-1",
           }) : "/clone/item/huojingling",

        // ����֮ͫ����
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/maggem7-1",
          "/clone/tessera/rune24-1",
           }) : "/clone/item/leishentong",
*/
]);

int main(object me, string arg)
{
        mapping same;                   // �ж��ظ�����Ʒ����Ҫ��mapping
        string *item_list, *name_list;  // �ϲ�����ƷID���ƥ��Ļ������ֱ�
        string bname;                   // ��Ʒ��Ӧ���ļ��Ļ�������
        object *ob_list;                // �ϲ���������Ʒ
        string *per;                    // mapping�м�¼�Ŀɺϲ��Ļ������ֱ�
        object obj;                     // ���ɵ���Ʒ
        int mp, i;

        if (! arg)
                return notify_fail("��Ҫ�ϲ�ʲô��Ʒ��\n");

        if (me->is_busy())
                return notify_fail("��æ����������������������ɣ�\n");

        if (me->is_fighting())
                return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

        if( query("max_jingli", me)<300 )
                return notify_fail("�����ڵľ�����Ϊ���ޣ��޷��ϳ���Ʒ��\n");

        if( query("jingli", me)<300 )
                return notify_fail("�����ھ������ã��޷��ϳ���Ʒ��\n");

        item_list = explode(arg, "&");
        ob_list   = allocate(sizeof(item_list));
        name_list = allocate(sizeof(item_list));
        same = allocate_mapping(sizeof(item_list));
        for (i = 0; i < sizeof(item_list); i++)
        {
                bname = item_list[i];
                if (! bname || bname == " ") return notify_fail("��ʽ����\n");
                while (bname[0] == ' ') bname = bname[1..<0];
                if( sizeof(bname) < 2 ) notify_fail("��ʽ����\n");
                while (bname[strlen(bname) - 1] == ' ') bname = bname[0..<2];
                ob_list[i] = present(bname, me);

                if (! objectp(ob_list[i]))
                        return notify_fail("������û�� " + bname + " ������Ʒ����\n");

                /*
                if( query("no_identify", ob_list[i]) )
                        return notify_fail("�����ϵ� " + bname + " ��û��ȥ��������\n");
                */

                if (i > 0 && member_array(ob_list[i], ob_list[0..i - 1]) != -1)
                        return notify_fail("�ϲ���Ʒ��Ҫָ����ͬ����Ʒ����Ҫ�ظ�ָ"
                                           "��һ����Ʒ��\n");

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

        tell_object(me, HIW "\n��˫Ŀ΢�գ���������Ʒ�������У���ת�ھ���"
                        "ʹ���ǽ��ڡ�\n" NOR);

        me->start_busy(1);
        addn("jingli", -200, me);
        foreach (per in keys(combine_list))
        {
                if (per - name_list == ({ }) && sizeof(per) == sizeof(name_list))
                {
                        // �ҵ��˺��ʵ����
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
                        message("vision", HIW "\n��ʱ��ֻ��" + me->name() + HIW "����һ��"
                                          "�⻪��������ת˲���ţ��ƺ�������ʲô��ͬѰ����"
                                          "���顣\n\n" NOR, environment(me), ({me}));

                        tell_object(me, HIW "��ʱ��ֻ������⻪�����������㼱æ̯�����ƣ�"
                                        "��������\n��Ȼ������һ"+query("unit", obj)+
                                        obj->name() + HIW "����������ɫϼ�⡣\n\n" NOR);

                        if( query("value", obj) )
                        {
                                mp=(query("value", obj)/700);
                                mp = 1 + random(mp);
                                if (mp < 1) mp = 1;
                                if (mp > 100) mp = 100;

                                addn("magic_points", mp, me);
                                tell_object(me, HIC "��ͨ���ϳ�"+ obj->name() + HIC "����"
                                                "�����̣��Ӷ������" + chinese_number(mp) +
                                                "����ۡ�\n" NOR);
                        }
                        addn("max_jingli", -1, me);
                        obj->move(me, 1);
                        MYGIFT_D->check_mygift(me, "newbie_mygift/combine"); 
                        return 1;
                }
        }
        tell_object(me, HIR "���ǹ��˰��죬�ƺ�û���κα仯���㲻��һ��"
                        "��̾��\n" NOR);

        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : combine <������Ʒ> & <������Ʒ> & ����

���ָ��������㽫ĳЩ������Ʒ�ϲ���һ���µ���Ʒ����Щ���ܺ�
�������Ҫ����ȥ�����ˡ�ÿ�κϲ�������ʧһ�㾫�������ޡ����
Ҫ�ϲ��ļ�����Ʒ������ͬ������Ҫָ�����ǵ���ţ�������������
ʯ�����Ҫ��һ������Ҫ���룺

  combine diamond & diamond 2 & diamond 3

HELP);
        return 1;
}
