#include "global.h"
#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"

extern u8 gPlayerFormItemRestrictions[PLAYER_FORM_MAX][114];

extern bool mGFSEquipped;

PlayState* bPlayState;

RECOMP_CALLBACK("*", recomp_after_play_init) void after_play_init(PlayState* this) {
    // Save PlayState to be used throughout the mod.
    bPlayState = this;
    
    // Compatibility with Forms Use More Items - disable GFS for all forms except humans (who wants to use GFS as Deku anyways?)
    for (PlayerTransformation i = PLAYER_FORM_FIERCE_DEITY; i < PLAYER_FORM_HUMAN; i++) {
        gPlayerFormItemRestrictions[i][ITEM_SWORD_GREAT_FAIRY] = false;
    }
}

// Keep GFS equipped if B button item is changed back to normal sword contextually e.g. dismounting Epona.
// Does this by checking if the item at the beginning of the function is different to the item at the end and
// whether the item at the end is a sword. 
u8 bBButtonItemEquip;

RECOMP_HOOK("Interface_UpdateButtonsPart2") void Interface_UpdateButtonsPart2_Init(PlayState* play) {
    bBButtonItemEquip = BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B);
}

RECOMP_HOOK_RETURN("Interface_UpdateButtonsPart2") void Interface_UpdateButtonsPart2_Return() {
    if (mGFSEquipped && BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) != bBButtonItemEquip &&
        ((ITEM_SWORD_KOKIRI <= BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) && BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) <= ITEM_SWORD_DEITY) ||
        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) == ITEM_NONE)) {
            BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_SWORD_GREAT_FAIRY;
            Interface_LoadItemIconImpl(bPlayState, EQUIP_SLOT_B);
        }
}

// Keep GFS equipped after unlocking a new sword.
// Mark mGiveSword as true if unlocking a new sword, and before the B button item icon is loaded, set it back to GFS.
bool mGiveSword = false;

RECOMP_HOOK("Item_Give") void Item_Give_Init(PlayState* play, u8 item) {
    if (ITEM_SWORD_KOKIRI <= item && item <= ITEM_SWORD_GILDED && mGFSEquipped == true) {
        mGiveSword = true;
    }
}

RECOMP_HOOK("Interface_LoadItemIconImpl") void Interface_LoadItemIconImpl_Init(PlayState* play, u8 btn) {
    if (mGiveSword == true) {
        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_SWORD_GREAT_FAIRY;
        mGiveSword = false;
    }
}