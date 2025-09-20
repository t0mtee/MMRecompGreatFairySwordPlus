#include "global.h"
#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

extern TexturePtr gEquippedItemOutlineTex[];

extern PlayState* bPlayState;
extern bool mGFSEquipped;

bool bKaleidoScope_DrawItemSelect = false;

RECOMP_HOOK("KaleidoScope_DrawItemSelect") void KaleidoScope_DrawItemSelect_Init(PlayState* play) {
    if (mGFSEquipped == true) {
        bKaleidoScope_DrawItemSelect = true;
    }
}
    
RECOMP_HOOK_RETURN("Gfx_SetupDL42_Opa") void Gfx_SetupDL42_Opa_Return() {
    if (bKaleidoScope_DrawItemSelect == true) {
        PauseContext* pauseCtx = &bPlayState->pauseCtx;
        
        Vtx* greatFairySwordBorder = GRAPH_ALLOC(bPlayState->state.gfxCtx, (1 * 4) * sizeof(Vtx));

        greatFairySwordBorder[0].v.ob[0] = greatFairySwordBorder[2].v.ob[0] =
            pauseCtx->itemVtx[64].v.ob[0] + ITEM_GRID_SELECTED_QUAD_MARGIN;
        
        greatFairySwordBorder[1].v.ob[0] = greatFairySwordBorder[3].v.ob[0] =
            greatFairySwordBorder[0].v.ob[0] + ITEM_GRID_SELECTED_QUAD_WIDTH;
        
        greatFairySwordBorder[0].v.ob[1] = greatFairySwordBorder[1].v.ob[1] =
            pauseCtx->itemVtx[64].v.ob[1] - ITEM_GRID_SELECTED_QUAD_MARGIN;
        
        greatFairySwordBorder[2].v.ob[1] = greatFairySwordBorder[3].v.ob[1] =
            greatFairySwordBorder[0].v.ob[1] - ITEM_GRID_SELECTED_QUAD_WIDTH;
        
        greatFairySwordBorder[0].v.ob[2] = greatFairySwordBorder[1].v.ob[2] = greatFairySwordBorder[2].v.ob[2] =
            greatFairySwordBorder[3].v.ob[2] = 0;
        
        greatFairySwordBorder[0].v.flag = greatFairySwordBorder[1].v.flag = greatFairySwordBorder[2].v.flag =
            greatFairySwordBorder[3].v.flag = 0;
        
        greatFairySwordBorder[0].v.tc[0] = greatFairySwordBorder[0].v.tc[1] = greatFairySwordBorder[1].v.tc[1] =
            greatFairySwordBorder[2].v.tc[0] = 0;
        
        greatFairySwordBorder[1].v.tc[0] = greatFairySwordBorder[2].v.tc[1] = greatFairySwordBorder[3].v.tc[0] =
            greatFairySwordBorder[3].v.tc[1] = ITEM_GRID_SELECTED_QUAD_TEX_SIZE * (1 << 5);
        
        greatFairySwordBorder[0].v.cn[0] = greatFairySwordBorder[1].v.cn[0] = greatFairySwordBorder[2].v.cn[0] =
            greatFairySwordBorder[3].v.cn[0] = greatFairySwordBorder[0].v.cn[1] =
                greatFairySwordBorder[1].v.cn[1] = greatFairySwordBorder[2].v.cn[1] =
                    greatFairySwordBorder[3].v.cn[1] = greatFairySwordBorder[0].v.cn[2] =
                        greatFairySwordBorder[1].v.cn[2] = greatFairySwordBorder[2].v.cn[2] =
                            greatFairySwordBorder[3].v.cn[2] = 255;
        
        greatFairySwordBorder[0].v.cn[3] = greatFairySwordBorder[1].v.cn[3] = greatFairySwordBorder[2].v.cn[3] =
            greatFairySwordBorder[3].v.cn[3] = pauseCtx->alpha;
        
        OPEN_DISPS(bPlayState->state.gfxCtx);
        
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 100, 255, 120, pauseCtx->alpha);
        
        gSPVertex(POLY_OPA_DISP++, &greatFairySwordBorder[0], 4, 0);
        POLY_OPA_DISP = Gfx_DrawTexQuadIA8(POLY_OPA_DISP, gEquippedItemOutlineTex, 32, 32, 0);

        CLOSE_DISPS(bPlayState->state.gfxCtx);
    
        bKaleidoScope_DrawItemSelect = false;
    }
}