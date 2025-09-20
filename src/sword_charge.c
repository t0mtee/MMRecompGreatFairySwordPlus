#include "global.h"
#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "overlays/actors/ovl_En_M_Thunder/z_en_m_thunder.h"

EnMThunder* bThis = NULL;

RECOMP_HOOK("EnMThunder_Draw") void EnMThunder_Draw_Init(Actor* thisx, PlayState* play2) {
    bThis = (EnMThunder*)thisx;
}

RECOMP_HOOK("Matrix_RotateXS") void Matrix_RotateXS_Init(s16 x, MatrixMode mode) {
    if (bThis != NULL && bThis->type == ENMTHUNDER_TYPE_GREAT_FAIRYS_SWORD) {
        if (bThis->type == ENMTHUNDER_TYPE_GILDED_SWORD) {
            Matrix_Scale(1.5833f, 1.375f, 1.5f, MTXMODE_APPLY);
        } else {
            Matrix_Scale(2.7143f, 1.8333f, 2.25f, MTXMODE_APPLY);
        }
        bThis = NULL;
    }
}