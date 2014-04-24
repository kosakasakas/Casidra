//
//  Text.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/20.
//
//

#ifndef Casidra_Params_h
#define Casidra_Params_h

//
// Text
//

// Opening
namespace Text_Opening {
}
// SelectScene
namespace Text_SelectScene {
    static const char* title_rouletteType = "タイプ選択";
    static const char* title_betMethod    = "手法選択";
    static const char* title_minBet       = "最低ベット";
    static const char* title_betZone      = "ベット領域";
    static const char* desc_rouretteType = "ルーレットタイプを選んで下さい。";
    static const char* desc_betMethod    = "運用方法を選択して下さい。";
    static const char* desc_minBet       = "最低ベット額を入力して下さい。";
    static const char* desc_betZone      = "ベットするゾーンを選んで下さい。";
}
// ListText
namespace Text_List {
    static const char* rouletteType[] = {"アメリカン", "ヨーロピアン"};
    static const char* rouletteTypeDesc[] = {"アメリカンは0と00があるやつ", "ヨーロピアンは0のみ"};
    static const char* method[] = {"モンテカルロ法", "ウィナーズ投資法", ""};
    static const char* methodDesc[] = {"モンテカルロ法ってのは。。", "ウィナーズ投資法ってのは。。", ""};
    static const char* zone[] = {"赤", "黒", "ハイ", "ロー", "奇数", "偶数", "1~12", "13~24",
        "25~36", "列1", "列2", "列3"};
}
// EditBox
namespace Text_EditBox {
    static const char* spriteFileName = "editBox.png";
    static const char* placeHolder_MinBet = "最低ベット額：";
    static const char* placeHolder_ResultNum = "結果：";
}

//
// Types
//

// BetZone
namespace Type {
    enum BetZone {
        Red,
        Black,
        Hight,
        Low,
        Odd,
        Even,
        Dozen1,
        Dozen2,
        Dozen3,
        Column1,
        Column2,
        Column3,
        NoZone,
        ZoneNum
    };
    // RouletteType
    enum RouletteType {
        American,
        European,
        RouletteTypeNum
    };
    // Method
    enum Method {
        MonteCarlo,
        Winners,
        MethodNum
    };
    // SelectScenePage
    enum SelectScenePage {
        SelectRouletteTypePage,
        SelectMethodPage,
        SelectZonePage,
        SelectMinBetPage,
        NonePage,
        PageNum
    };
}
#endif
