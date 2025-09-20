#include "global.h"
#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"

u8 bSwordEquipValue;

RECOMP_HOOK("func_80C10B0C") void func_80C10B0C_Init() {
    bSwordEquipValue = GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD);
}

extern PlayState* bPlayState;
extern bool mGFSEquipped;
extern void Mod_UnequipGFS();

// If bird steals the GFS, we need to unequip it from the B button as well.
RECOMP_HOOK("Inventory_DeleteItem") void Inventory_DeleteItem_Init(s16 item, s16 slot) {
    if (item == ITEM_SWORD_GREAT_FAIRY && mGFSEquipped == true) {
        Mod_UnequipGFS();
    }
}

// If bird steals the player's normal sword (detected if GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) has changed),
// we need to keep the GFS equipped to the B button.
RECOMP_HOOK_RETURN("func_80C10B0C") void func_80C10B0C_Return() {
    if (mGFSEquipped == true && bSwordEquipValue != GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD)) {
        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_SWORD_GREAT_FAIRY;
    }
}