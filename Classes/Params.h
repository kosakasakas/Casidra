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
    static const char* title_editBet      = "ベット額";
    static const char* desc_rouretteType = "ルーレットタイプを選んで下さい。";
    static const char* desc_betMethod    = "運用方法を選択して下さい。";
    static const char* desc_minBet       = "最低ベット額を入力して下さい。";
    static const char* desc_betZone      = "ベットするゾーンを選んで下さい。";
    static const char* desc_editBet      = "ベット額を入力して下さい。";
}
// ListText
namespace Text_List {
    static const char* rouletteType[] = {"アメリカン", "ヨーロピアン"};
    static const char* rouletteTypeDesc[] = {"アメリカンは0と00があるやつ", "ヨーロピアンは0のみ"};
    static const char* method[] = {"モンテカルロ法", "ウィナーズ投資法", "未設定"};
    static const char* methodDesc[] = {"モンテカルロ法ってのは。。", "ウィナーズ投資法ってのは。。", ""};
    static const char* zone[] = {"赤", "黒", "ハイ", "ロー", "奇数", "偶数", "1~12", "13~24",
        "25~36", "列1", "列2", "列3", "未設定"};
}
// EditBox
namespace Text_EditBox {
    static const char* spriteFileName = "editBox.png";
    static const char* placeHolder_MinBet = "最低ベット額：";
    static const char* placeHolder_ResultNum = "結果：";
    static const char* placeHolder_editBet = "おすすめ額：";
    static const char* submit = "確定";
    static const char* errorTitle = "入力エラー";
    static const char* errorDescNotDecimal = "数値を入力して下さい。";
}
// config
namespace Text_Config {
    static const char* notInitialized = "未設定";
}
// BetScene
namespace Text_BetScene {
    static const char* errorNotInitializedMethodTitle = "手法が未設定";
    static const char* errorNotInitializedMethodDesc = "設定からメソッドを設定して下さい。";
}

//
// Types
//

// BetZone
namespace Type {
    enum BetZoneType {
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
    enum MethodType {
        MonteCarlo,
        Winners,
        NoneMethod,
        MethodNum
    };
    // SelectScenePage
    enum SelectScenePageType {
        SelectRouletteTypePage,
        SelectMethodPage,
        SelectZonePage,
        SelectMinBetPage,
        SelectEditBetPage,
        SelectEditMethodPage,
        MainPage,
        NonePage,
        PageNum
    };
}
#endif
