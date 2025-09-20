#include "global.h"
#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"

extern PlayState* bPlayState;

bool mGFSEquipped = false;

void Mod_UnequipGFS() {
    if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) == EQUIP_VALUE_SWORD_NONE) {
        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_NONE;
    } else {
        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_SWORD_KOKIRI - 1 + GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD);
    }
    mGFSEquipped = false;
    Interface_LoadItemIconImpl(bPlayState, EQUIP_SLOT_B);
}

// Allow GFS to be equipped if player presses button a mask is being worn on.
// Value of 255 means that Player_GetCurMaskItemId isn't being called in KaleidoScope_UpdateItemCursor.
// Value of PLAYER_MASK_MAX means that it is.
u8 bCurrentMask = 255;
// Allow GFS to be equipped if player presses button a transformative mask is being worn on.
u8 bCurrentForm = PLAYER_FORM_MAX;

RECOMP_HOOK("KaleidoScope_UpdateItemCursor") void KaleidoScope_UpdateItemCursor_Init(PlayState* play) {
    bCurrentMask = PLAYER_MASK_MAX;
    
    bCurrentForm = GET_PLAYER_FORM;
    gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
}

RECOMP_HOOK("Player_GetCurMaskItemId") void Player_GetCurMaskItemId_Init(PlayState* play) {
    if (bCurrentMask == PLAYER_MASK_MAX && (&play->pauseCtx)->cursorItem[PAUSE_ITEM] == ITEM_SWORD_GREAT_FAIRY) {
        Player* player = GET_PLAYER(play);
        
        bCurrentMask = player->currentMask;
        player->currentMask = PLAYER_MASK_NONE;
    }
}

RECOMP_HOOK_RETURN("Player_GetCurMaskItemId") void Player_GetCurMaskItemId_Return() {
    if (bCurrentMask != 255 && (&bPlayState->pauseCtx)->cursorItem[PAUSE_ITEM] == ITEM_SWORD_GREAT_FAIRY) {
        Player* player = GET_PLAYER(bPlayState);
        
        player->currentMask = bCurrentMask;
        bCurrentMask = PLAYER_MASK_MAX;
    }
}

RECOMP_HOOK_RETURN("KaleidoScope_UpdateItemCursor") void KaleidoScope_UpdateItemCursor_Return() {
    PauseContext* pauseCtx = &bPlayState->pauseCtx;
    
    // Main equip logic.
    if (pauseCtx->mainState == PAUSE_MAIN_STATE_EQUIP_ITEM && pauseCtx->equipTargetItem == ITEM_SWORD_GREAT_FAIRY) {
        pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
        
        if (BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) != ITEM_SWORD_GREAT_FAIRY) {
            BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_B) = ITEM_SWORD_GREAT_FAIRY;
            mGFSEquipped = true;
            Interface_LoadItemIconImpl(bPlayState, EQUIP_SLOT_B);
        } else {
            Mod_UnequipGFS();
        }
    }

    gSaveContext.save.playerForm = bCurrentForm;
    bCurrentMask = 255;
}