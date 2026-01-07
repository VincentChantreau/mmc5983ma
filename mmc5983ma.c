#include "mmc5983ma.h"
#include <stdint.h>

// Shadow register as the device does not allow read modify write
static mmc5983ma_shadow_t mmc_shadow = {.internal_control0 = 0,
                                        .internal_control1 = 0,
                                        .internal_control2 = 0,
                                        .internal_control3 = 0};

/**
 * @brief  Read generic device register
 *
 * @param  ctx   read / write interface definitions(ptr)
 * @param  reg   register to read
 * @param  data  pointer to buffer that store the data read(ptr)
 * @param  len   number of consecutive register to read
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mmc5983ma_read_reg(const memsicdev_ctx_t *ctx, uint8_t reg,
                           uint8_t *data, uint16_t len) {
  int32_t ret;

  if (ctx == NULL)
    return -1;

  ret = ctx->read_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
 * @brief  Write generic device register
 *
 * @param  ctx   read / write interface definitions(ptr)
 * @param  reg   register to write
 * @param  data  pointer to data to write in register reg(ptr)
 * @param  len   number of consecutive register to write
 * @retval          interface status (MANDATORY: return 0 -> no Error)
 *
 */
int32_t mmc5983ma_write_reg(const memsicdev_ctx_t *ctx, uint8_t reg,
                            uint8_t *data, uint16_t len) {
  int32_t ret;

  if (ctx == NULL)
    return -1;

  ret = ctx->write_reg(ctx->handle, reg, data, len);

  return ret;
}

int32_t mmc5983ma_device_id_get(const memsicdev_ctx_t *ctx, uint8_t *val) {
  int32_t ret;

  ret = mmc5983ma_read_reg(ctx, MMC5983MA_WHO_AM_I, val, 1);

  return ret;
}

int32_t mmc5983ma_status_get(const memsicdev_ctx_t *ctx,
                             mmc5983ma_status_t *val) {
  int32_t ret;

  ret = mmc5983ma_read_reg(ctx, MMC5983MA_STATUS, (uint8_t *)val, 1);

  return ret;
}

/** RESET */
int32_t mmc5983ma_reset(const memsicdev_ctx_t *ctx) {
  int32_t ret;
  mmc5983ma_ctrl1_t reg;

  reg = *(mmc5983ma_ctrl1_t *)&mmc_shadow.internal_control1;

  reg.sw_reset = 1U;

  mmc_shadow.internal_control1 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_1,
                            (uint8_t *)&mmc_shadow.internal_control1, 1);
  if (ret != 0) {
    return ret;
  }

  if (reg.sw_reset == 1) {
    reg.sw_reset = 0;
    mmc_shadow.internal_control1 = *(uint8_t *)&reg;

    ctx->mdelay(15);
  }
  return ret;
}

int32_t mmc5983ma_bandwith_set(const memsicdev_ctx_t *ctx, mmc5983ma_bw_t val) {
  int32_t ret;
  mmc5983ma_ctrl1_t reg;

  reg = *(mmc5983ma_ctrl1_t *)&mmc_shadow.internal_control1;

  reg.bandwidth = (uint8_t)val & 0x03U;

  mmc_shadow.internal_control1 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_1,
                            (uint8_t *)&mmc_shadow.internal_control1, 1);

  return ret;
}

int32_t mmc5983ma_bandwith_get(const memsicdev_ctx_t *ctx,
                               mmc5983ma_bw_t *val) {
  if (val == NULL) {
    return -1;
  }
  mmc5983ma_ctrl1_t reg;

  reg = *(mmc5983ma_ctrl1_t *)&mmc_shadow.internal_control1;

  *val = reg.bandwidth;

  return 0;
}

int32_t mmc5983ma_x_inhibit_set(const memsicdev_ctx_t *ctx, uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl1_t reg;

  reg = *(mmc5983ma_ctrl1_t *)&mmc_shadow.internal_control1;

  reg.x_inhibit = (uint8_t)val & 0x03U;

  mmc_shadow.internal_control1 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_1,
                            (uint8_t *)&mmc_shadow.internal_control1, 1);

  return ret;
}
int32_t mmc5983ma_x_inhibit_get(const memsicdev_ctx_t *ctx, uint8_t *val) {
  if (val == NULL) {
    return -1;
  }
  mmc5983ma_ctrl1_t reg;

  reg = *(mmc5983ma_ctrl1_t *)&mmc_shadow.internal_control1;

  *val = reg.x_inhibit;

  return 0;
}

int32_t mmc5983ma_yz_inhibit_set(const memsicdev_ctx_t *ctx, uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl1_t reg;

  reg = *(mmc5983ma_ctrl1_t *)&mmc_shadow.internal_control1;

  reg.yz_inhibit = (uint8_t)val & 0x03U;

  mmc_shadow.internal_control1 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_1,
                            (uint8_t *)&mmc_shadow.internal_control1, 1);

  return ret;
}

int32_t mmc5983ma_yz_inhibit_get(const memsicdev_ctx_t *ctx, uint8_t *val) {
  if (val == NULL) {
    return -1;
  }
  mmc5983ma_ctrl1_t reg;

  reg = *(mmc5983ma_ctrl1_t *)&mmc_shadow.internal_control1;

  *val = reg.yz_inhibit;

  return 0;
}

int32_t mmc5983ma_meas_done_int_set(const memsicdev_ctx_t *ctx, uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl0_t reg;

  reg = *(mmc5983ma_ctrl0_t *)&mmc_shadow.internal_control0;

  reg.int_meas_done_en = (uint8_t)val & 0x01U;

  mmc_shadow.internal_control0 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_0,
                            (uint8_t *)&mmc_shadow.internal_control0, 1);

  return ret;
}

int32_t mmc5983ma_meas_done_int_get(const memsicdev_ctx_t *ctx, uint8_t *val) {
  if (val == NULL) {
    return -1;
  }
  mmc5983ma_ctrl0_t reg;

  reg = *(mmc5983ma_ctrl0_t *)&mmc_shadow.internal_control0;

  *val = reg.int_meas_done_en;

  return 0;
}

int32_t
mmc5983ma_take_magnetic_field_measurement_set(const memsicdev_ctx_t *ctx,
                                              uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl0_t reg;

  reg = *(mmc5983ma_ctrl0_t *)&mmc_shadow.internal_control0;

  reg.tm_m = (uint8_t)val & 0x01U;

  mmc_shadow.internal_control0 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_0,
                            (uint8_t *)&mmc_shadow.internal_control0, 1);

  if (reg.tm_m == 1) {
    reg.tm_m = 0;
    mmc_shadow.internal_control0 = *(uint8_t *)&reg;
  }
  return ret;
}

int32_t mmc5983ma_take_temperature_measurement_set(const memsicdev_ctx_t *ctx,
                                                   uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl0_t reg;

  reg = *(mmc5983ma_ctrl0_t *)&mmc_shadow.internal_control0;

  reg.tm_t = (uint8_t)val & 0x01U;

  mmc_shadow.internal_control0 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_0,
                            (uint8_t *)&mmc_shadow.internal_control0, 1);

  if (reg.tm_t == 1) {
    reg.tm_t = 0;
    mmc_shadow.internal_control0 = *(uint8_t *)&reg;
  }
  return ret;
}

int32_t mmc5983ma_auto_sr_set(const memsicdev_ctx_t *ctx, uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl0_t reg;

  reg = *(mmc5983ma_ctrl0_t *)&mmc_shadow.internal_control0;

  reg.auto_sr_en = (uint8_t)val & 0x01U;

  mmc_shadow.internal_control0 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_0,
                            (uint8_t *)&mmc_shadow.internal_control0, 1);

  return ret;
}
int32_t mmc5983ma_auto_sr_get(const memsicdev_ctx_t *ctx, uint8_t *val) {
  if (val == NULL) {
    return -1;
  }
  mmc5983ma_ctrl0_t reg;

  reg = *(mmc5983ma_ctrl0_t *)&mmc_shadow.internal_control0;

  *val = reg.auto_sr_en;

  return 0;
}

int32_t mmc5983ma_set_operation_set(const memsicdev_ctx_t *ctx, uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl0_t reg;

  reg = *(mmc5983ma_ctrl0_t *)&mmc_shadow.internal_control0;

  reg.set = (uint8_t)val & 0x01U;

  mmc_shadow.internal_control0 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_0,
                            (uint8_t *)&mmc_shadow.internal_control0, 1);

  if (reg.set == 1) {
    reg.set = 0;
    mmc_shadow.internal_control0 = *(uint8_t *)&reg;
  }
  return ret;
}
int32_t mmc5983ma_reset_operation_set(const memsicdev_ctx_t *ctx, uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl0_t reg;

  reg = *(mmc5983ma_ctrl0_t *)&mmc_shadow.internal_control0;

  reg.reset = (uint8_t)val & 0x01U;

  mmc_shadow.internal_control0 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_0,
                            (uint8_t *)&mmc_shadow.internal_control0, 1);

  if (reg.reset == 1) {
    reg.reset = 0;
    mmc_shadow.internal_control0 = *(uint8_t *)&reg;
  }
  return ret;
}

int32_t mmc5983ma_cm_freq_set(const memsicdev_ctx_t *ctx,
                              mmc5983ma_continuous_mode_freq_t val) {
  int32_t ret;
  mmc5983ma_ctrl2_t reg;

  reg = *(mmc5983ma_ctrl2_t *)&mmc_shadow.internal_control2;

  reg.cm_freq = (uint8_t)val & 0x06U;

  mmc_shadow.internal_control2 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_2,
                            (uint8_t *)&mmc_shadow.internal_control2, 1);

  return ret;
}
int32_t mmc5983ma_cm_freq_get(const memsicdev_ctx_t *ctx,
                              mmc5983ma_continuous_mode_freq_t *val) {
  if (val == NULL) {
    return -1;
  }
  mmc5983ma_ctrl2_t reg;

  reg = *(mmc5983ma_ctrl2_t *)&mmc_shadow.internal_control1;

  *val = reg.cm_freq;

  return 0;
}

int32_t mmc5983ma_cmm_en_set(const memsicdev_ctx_t *ctx, uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl2_t reg;

  reg = *(mmc5983ma_ctrl2_t *)&mmc_shadow.internal_control2;

  reg.cmm_en = (uint8_t)val & 0x01U;

  mmc_shadow.internal_control2 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_2,
                            (uint8_t *)&mmc_shadow.internal_control2, 1);

  return ret;
}

int32_t mmc5983ma_cmm_en_get(const memsicdev_ctx_t *ctx, uint8_t *val) {
  if (val == NULL) {
    return -1;
  }
  mmc5983ma_ctrl2_t reg;

  reg = *(mmc5983ma_ctrl2_t *)&mmc_shadow.internal_control2;

  *val = reg.cmm_en;

  return 0;
}

int32_t mmc5983ma_prd_set_set(const memsicdev_ctx_t *ctx, uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl2_t reg;

  reg = *(mmc5983ma_ctrl2_t *)&mmc_shadow.internal_control2;

  reg.prd_set = (uint8_t)val & 0x06U;

  mmc_shadow.internal_control2 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_2,
                            (uint8_t *)&mmc_shadow.internal_control2, 1);

  return ret;
}

int32_t mmc5983ma_prd_set_get(const memsicdev_ctx_t *ctx, uint8_t *val) {
  if (val == NULL) {
    return -1;
  }
  mmc5983ma_ctrl2_t reg;

  reg = *(mmc5983ma_ctrl2_t *)&mmc_shadow.internal_control2;

  *val = reg.prd_set;

  return 0;
}

int32_t mmc5983ma_en_prd_set_set(const memsicdev_ctx_t *ctx, uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl2_t reg;

  reg = *(mmc5983ma_ctrl2_t *)&mmc_shadow.internal_control2;

  reg.en_prd_set = (uint8_t)val & 0x01U;

  mmc_shadow.internal_control2 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_2,
                            (uint8_t *)&mmc_shadow.internal_control2, 1);

  return ret;
}

int32_t mmc5983ma_en_prd_set_get(const memsicdev_ctx_t *ctx, uint8_t *val) {
  if (val == NULL) {
    return -1;
  }
  mmc5983ma_ctrl2_t reg;

  reg = *(mmc5983ma_ctrl2_t *)&mmc_shadow.internal_control2;

  *val = reg.en_prd_set;

  return 0;
}

int32_t mmc5983ma_set_enp_set(const memsicdev_ctx_t *ctx, uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl3_t reg;

  reg = *(mmc5983ma_ctrl3_t *)&mmc_shadow.internal_control3;

  reg.st_enp = (uint8_t)val & 0x01U;

  mmc_shadow.internal_control3 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_3,
                            (uint8_t *)&mmc_shadow.internal_control3, 1);

  return ret;
}

int32_t mmc5983ma_set_enp_get(const memsicdev_ctx_t *ctx, uint8_t *val) {
  if (val == NULL) {
    return -1;
  }
  mmc5983ma_ctrl3_t reg;

  reg = *(mmc5983ma_ctrl3_t *)&mmc_shadow.internal_control2;

  *val = reg.st_enp;

  return 0;
}

int32_t mmc5983ma_set_enm_set(const memsicdev_ctx_t *ctx, uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl3_t reg;

  reg = *(mmc5983ma_ctrl3_t *)&mmc_shadow.internal_control3;

  reg.st_enm = (uint8_t)val & 0x01U;

  mmc_shadow.internal_control3 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_3,
                            (uint8_t *)&mmc_shadow.internal_control3, 1);

  return ret;
}
int32_t mmc5983ma_set_enm_get(const memsicdev_ctx_t *ctx, uint8_t *val) {
  if (val == NULL) {
    return -1;
  }
  mmc5983ma_ctrl3_t reg;

  reg = *(mmc5983ma_ctrl3_t *)&mmc_shadow.internal_control2;

  *val = reg.st_enm;

  return 0;
}

int32_t mmc5983ma_spi_3w_set(const memsicdev_ctx_t *ctx, uint8_t val) {
  int32_t ret;
  mmc5983ma_ctrl3_t reg;

  reg = *(mmc5983ma_ctrl3_t *)&mmc_shadow.internal_control3;

  reg.spi_3w = (uint8_t)val & 0x01U;

  mmc_shadow.internal_control3 = *(uint8_t *)&reg;

  ret = mmc5983ma_write_reg(ctx, MMC5983MA_INTERNAL_CTRL_3,
                            (uint8_t *)&mmc_shadow.internal_control3, 1);

  return ret;
}
int32_t mmc5983ma_spi_3w_get(const memsicdev_ctx_t *ctx, uint8_t *val) {
  if (val == NULL) {
    return -1;
  }
  mmc5983ma_ctrl3_t reg;

  reg = *(mmc5983ma_ctrl3_t *)&mmc_shadow.internal_control2;

  *val = reg.spi_3w;

  return 0;
}

int32_t mmc5983ma_raw_magnetic_field_measurement_get(
    const memsicdev_ctx_t *ctx, mmc5983ma_raw_magneto_data_t *val) {

  int32_t ret;

  ret = mmc5983ma_read_reg(ctx, MMC5983MA_XOUT_0, (uint8_t *)val,
                           sizeof(mmc5983ma_raw_magneto_data_t));

  val->xraw_1 = (val->xout0 << 10) | (val->xout1 << 2) |
                ((val->xyzout2 & 0b11000000) >> 6);
  val->yraw_1 = (val->yout0 << 10) | (val->yout1 << 2) |
                ((val->xyzout2 & 0b00110000) >> 4);
  val->zraw_1 = (val->zout0 << 10) | (val->zout1 << 2) |
                ((val->xyzout2 & 0b00001100) >> 2);

  return ret;
}

int32_t
mmc5983ma_magnetic_field_measurement_get(const memsicdev_ctx_t *ctx,
                                         mmc5983ma_raw_magneto_data_t *raw,
                                         mmc5983ma_magneto_data_t *val) {

  val->x = -8.f + ((float)(raw->xraw_1) * 0.0625f) / 1e3f;
  val->y = -8.f + ((float)(raw->yraw_1) * 0.0625f) / 1e3f;
  val->z = -8.f + ((float)(raw->zraw_1) * 0.0625f) / 1e3f;

  return 0;
}
