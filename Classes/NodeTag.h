//
//  Tag.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/23.
//
//

#ifndef Casidra_NodeTag_h
#define Casidra_NodeTag_h

//
// SelectScene
//
namespace NodeTag_SelectScene {
    enum Tag {
        Header     = 10,
        Footer     = 11,
        TitleLabel = 12,
        ButtonNode = 20,
        
        SelectButton = 0,
        HatenaButton = 1,
        ButtonLabel  = 2,
    };
}
//
// Header
//
namespace NodeTag_Header {
    enum Tag {
        Line = 0,
        BackButton = 1,
        NextButton = 2,
        TiteLabel = 3
    };
}
#endif
