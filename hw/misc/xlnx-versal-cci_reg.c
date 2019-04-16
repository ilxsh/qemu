/*
 * QEMU model of the CCI_REG Cache Coherent Interconnect Configuration
 * and Event registers
 *
 * Copyright (c) 2019 Xilinx Inc.
 *
 * Autogenerated by xregqemu.py 2019-04-16.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "qemu/osdep.h"
#include "hw/sysbus.h"
#include "hw/register.h"
#include "qemu/bitops.h"
#include "qemu/log.h"

#ifndef XILINX_CCI_REG_ERR_DEBUG
#define XILINX_CCI_REG_ERR_DEBUG 0
#endif

#define TYPE_XILINX_CCI_REG "xlnx.cci_reg"

#define XILINX_CCI_REG(obj) \
     OBJECT_CHECK(CCI_REG, (obj), TYPE_XILINX_CCI_REG)

REG32(MISC_CTRL, 0x0)
    FIELD(MISC_CTRL, SLVERR_ENABLE, 0, 1)
REG32(ISR_0, 0x10)
    FIELD(ISR_0, ADDR_DECODE_ERR, 31, 1)
    FIELD(ISR_0, EC7_OFLW, 8, 1)
    FIELD(ISR_0, EC6_OFLW, 7, 1)
    FIELD(ISR_0, EC5_OFLW, 6, 1)
    FIELD(ISR_0, EC4_OFLW, 5, 1)
    FIELD(ISR_0, EC3_OFLW, 4, 1)
    FIELD(ISR_0, EC2_OFLW, 3, 1)
    FIELD(ISR_0, EC1_OFLW, 2, 1)
    FIELD(ISR_0, EC0_OFLW, 1, 1)
    FIELD(ISR_0, ERRORIRQ, 0, 1)
REG32(IMR_0, 0x14)
    FIELD(IMR_0, ADDR_DECODE_ERR, 31, 1)
    FIELD(IMR_0, EC7_OFLW, 8, 1)
    FIELD(IMR_0, EC6_OFLW, 7, 1)
    FIELD(IMR_0, EC5_OFLW, 6, 1)
    FIELD(IMR_0, EC4_OFLW, 5, 1)
    FIELD(IMR_0, EC3_OFLW, 4, 1)
    FIELD(IMR_0, EC2_OFLW, 3, 1)
    FIELD(IMR_0, EC1_OFLW, 2, 1)
    FIELD(IMR_0, EC0_OFLW, 1, 1)
    FIELD(IMR_0, ERRORIRQ, 0, 1)
REG32(IER_0, 0x18)
    FIELD(IER_0, ADDR_DECODE_ERR, 31, 1)
    FIELD(IER_0, EC7_OFLW, 8, 1)
    FIELD(IER_0, EC6_OFLW, 7, 1)
    FIELD(IER_0, EC5_OFLW, 6, 1)
    FIELD(IER_0, EC4_OFLW, 5, 1)
    FIELD(IER_0, EC3_OFLW, 4, 1)
    FIELD(IER_0, EC2_OFLW, 3, 1)
    FIELD(IER_0, EC1_OFLW, 2, 1)
    FIELD(IER_0, EC0_OFLW, 1, 1)
    FIELD(IER_0, ERRORIRQ, 0, 1)
REG32(IDR_0, 0x1c)
    FIELD(IDR_0, ADDR_DECODE_ERR, 31, 1)
    FIELD(IDR_0, EC7_OFLW, 8, 1)
    FIELD(IDR_0, EC6_OFLW, 7, 1)
    FIELD(IDR_0, EC5_OFLW, 6, 1)
    FIELD(IDR_0, EC4_OFLW, 5, 1)
    FIELD(IDR_0, EC3_OFLW, 4, 1)
    FIELD(IDR_0, EC2_OFLW, 3, 1)
    FIELD(IDR_0, EC1_OFLW, 2, 1)
    FIELD(IDR_0, EC0_OFLW, 1, 1)
    FIELD(IDR_0, ERRORIRQ, 0, 1)
REG32(CCI_MISC_CTRL, 0x40)
    FIELD(CCI_MISC_CTRL, SPIDEN, 3, 1)
    FIELD(CCI_MISC_CTRL, DBGEN, 2, 1)
    FIELD(CCI_MISC_CTRL, SPNIDEN, 1, 1)
    FIELD(CCI_MISC_CTRL, NIDEN, 0, 1)

#define CCI_REG_R_MAX (R_CCI_MISC_CTRL + 1)

typedef struct CCI_REG {
    SysBusDevice parent_obj;
    MemoryRegion iomem;
    qemu_irq irq_imr_0;

    uint32_t regs[CCI_REG_R_MAX];
    RegisterInfo regs_info[CCI_REG_R_MAX];
} CCI_REG;

static void imr_0_update_irq(CCI_REG *s)
{
    bool pending = s->regs[R_ISR_0] & ~s->regs[R_IMR_0];
    qemu_set_irq(s->irq_imr_0, pending);
}

static void isr_0_postw(RegisterInfo *reg, uint64_t val64)
{
    CCI_REG *s = XILINX_CCI_REG(reg->opaque);
    imr_0_update_irq(s);
}

static uint64_t ier_0_prew(RegisterInfo *reg, uint64_t val64)
{
    CCI_REG *s = XILINX_CCI_REG(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IMR_0] &= ~val;
    imr_0_update_irq(s);
    return 0;
}

static uint64_t idr_0_prew(RegisterInfo *reg, uint64_t val64)
{
    CCI_REG *s = XILINX_CCI_REG(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IMR_0] |= val;
    imr_0_update_irq(s);
    return 0;
}

static const RegisterAccessInfo cci_reg_regs_info[] = {
    {   .name = "MISC_CTRL",  .addr = A_MISC_CTRL,
    },{ .name = "ISR_0",  .addr = A_ISR_0,
        .rsvd = 0x7ffffe00,
        .ro = 0x7ffffe00,
        .w1c = 0x800001ff,
        .post_write = isr_0_postw,
    },{ .name = "IMR_0",  .addr = A_IMR_0,
        .reset = 0x800001ff,
        .rsvd = 0x7ffffe00,
        .ro = 0xffffffff,
    },{ .name = "IER_0",  .addr = A_IER_0,
        .rsvd = 0x7ffffe00,
        .ro = 0x7ffffe00,
        .pre_write = ier_0_prew,
    },{ .name = "IDR_0",  .addr = A_IDR_0,
        .rsvd = 0x7ffffe00,
        .ro = 0x7ffffe00,
        .pre_write = idr_0_prew,
    },{ .name = "CCI_MISC_CTRL",  .addr = A_CCI_MISC_CTRL,
        .rsvd = 0xfffffff0,
    }
};

static void cci_reg_reset(DeviceState *dev)
{
    CCI_REG *s = XILINX_CCI_REG(dev);
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(s->regs_info); ++i) {
        register_reset(&s->regs_info[i]);
    }

    imr_0_update_irq(s);
}

static const MemoryRegionOps cci_reg_ops = {
    .read = register_read_memory,
    .write = register_write_memory,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4,
    },
};

static void cci_reg_realize(DeviceState *dev, Error **errp)
{
    /* Delete this if you don't need it */
}

static void cci_reg_init(Object *obj)
{
    CCI_REG *s = XILINX_CCI_REG(obj);
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    RegisterInfoArray *reg_array;

    memory_region_init(&s->iomem, obj, TYPE_XILINX_CCI_REG, CCI_REG_R_MAX * 4);
    reg_array =
        register_init_block32(DEVICE(obj), cci_reg_regs_info,
                              ARRAY_SIZE(cci_reg_regs_info),
                              s->regs_info, s->regs,
                              &cci_reg_ops,
                              XILINX_CCI_REG_ERR_DEBUG,
                              CCI_REG_R_MAX * 4);
    memory_region_add_subregion(&s->iomem,
                                0x0,
                                &reg_array->mem);
    sysbus_init_mmio(sbd, &s->iomem);
    sysbus_init_irq(sbd, &s->irq_imr_0);
}

static const VMStateDescription vmstate_cci_reg = {
    .name = TYPE_XILINX_CCI_REG,
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32_ARRAY(regs, CCI_REG, CCI_REG_R_MAX),
        VMSTATE_END_OF_LIST(),
    }
};

static void cci_reg_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = cci_reg_reset;
    dc->realize = cci_reg_realize;
    dc->vmsd = &vmstate_cci_reg;
}

static const TypeInfo cci_reg_info = {
    .name          = TYPE_XILINX_CCI_REG,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(CCI_REG),
    .class_init    = cci_reg_class_init,
    .instance_init = cci_reg_init,
};

static void cci_reg_register_types(void)
{
    type_register_static(&cci_reg_info);
}

type_init(cci_reg_register_types)
