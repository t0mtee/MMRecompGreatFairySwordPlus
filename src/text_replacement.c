#include "eztr_api.h"
#include "recomputils.h"
#include "recompconfig.h"

extern bool mGFSEquipped;

EZTR_MSG_CALLBACK(GFS_change) {
    if (mGFSEquipped) {
        EZTR_MsgSContent_Sprintf(buf->data.content, "Excuse me, but just what do you" EZTR_CC_NEWLINE "think I'm supposed to do with" EZTR_CC_NEWLINE "that?! It doesn't even look like" EZTR_CC_NEWLINE "it's made of metal..." EZTR_CC_EVENT2 "" EZTR_CC_END "");
    } else {
        EZTR_MsgSContent_Sprintf(buf->data.content, "Sorry, but we do only swords and" EZTR_CC_NEWLINE "cutlery." EZTR_CC_EVENT2 "" EZTR_CC_END "");
    }
}

EZTR_ON_INIT void Mod_MessageReplacement() {
    EZTR_Basic_ReplaceText(
        0x0C38,
        EZTR_STANDARD_TEXT_BOX_I,
        48,
        EZTR_ICON_NO_ICON,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        EZTR_NO_VALUE,
        true,
        "Sorry, but we do only swords and" EZTR_CC_NEWLINE "cutlery." EZTR_CC_EVENT2 "" EZTR_CC_END "",
        GFS_change
    );
}