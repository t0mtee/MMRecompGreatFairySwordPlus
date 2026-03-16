#include "global.h"
#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"

bool mFixApplied = false;

void Mod_InitFix() {
    if (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_SWORD_GREAT_FAIRY)
    {
        BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_DEKU_NUT;
        mFixApplied = true;
    }
}

void Mod_ReturnFix() {
    if (mFixApplied)
    {
        BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_SWORD_GREAT_FAIRY;
        mFixApplied = false;
    }
}

RECOMP_HOOK("Interface_SetBButtonPlayerDoAction") void Interface_SetBButtonPlayerDoAction_Init(PlayState* play, s16 bButtonDoAction) {
    Mod_InitFix();
}

RECOMP_HOOK_RETURN("Interface_SetBButtonPlayerDoAction") void Interface_SetBButtonPlayerDoAction_Return() {
    Mod_ReturnFix();
}

RECOMP_HOOK("Interface_DrawBButtonIcons") void Interface_DrawBButtonIcons_Init(PlayState* play) {
    Mod_InitFix();
}

RECOMP_HOOK_RETURN("Interface_DrawBButtonIcons") void Interface_DrawBButtonIcons_Return() {
    Mod_ReturnFix();
}