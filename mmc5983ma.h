

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MMC5983MA_H
#define MMC5983MA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include <stddef.h>
#include <stdint.h>

#define PROPERTY_DISABLE (0U)
#define PROPERTY_ENABLE (1U)

/** REGISTER ADDRES */
#define MMC5983MA_ID 0x30
#define MMC5983MA_WHO_AM_I 0x2f

#define MMC5983MA_XOUT_0 0x00
#define MMC5983MA_XOUT_1 0x01
#define MMC5983MA_YOUT_0 0x02
#define MMC5983MA_YOUT_1 0x03
#define MMC5983MA_ZOUT_0 0x04
#define MMC5983MA_ZOUT_1 0x05
#define MMC5983MA_XYZOUT_2 0x06
#define MMC5983MA_TOUT 0x07
#define MMC5983MA_STATUS 0x08
#define MMC5983MA_INTERNAL_CTRL_0 0x09
#define MMC5983MA_INTERNAL_CTRL_1 0x0A
#define MMC5983MA_INTERNAL_CTRL_2 0x0B
#define MMC5983MA_INTERNAL_CTRL_3 0x0C

typedef struct {
  uint8_t bandwidth : 2;
  uint8_t x_inhibit : 1;
  uint8_t yz_inhibit : 2;
  uint8_t reserved : 2;
  uint8_t sw_reset : 1;
} mmc5983ma_ctrl1_t; // order inverse little endian

typedef struct {
  uint8_t tm_m : 1;
  uint8_t tm_t : 1;
  uint8_t int_meas_done_en : 1;
  uint8_t set : 1;
  uint8_t reset : 1;
  uint8_t auto_sr_en : 1;
  uint8_t otp_read : 1;
  uint8_t reserved : 1;
} mmc5983ma_ctrl0_t; // order inverse little endian

typedef struct {
  uint8_t cm_freq : 3;
  uint8_t cmm_en : 1;
  uint8_t prd_set : 3;
  uint8_t en_prd_set : 1;

} mmc5983ma_ctrl2_t; // order inverse little endian

typedef struct {
  uint8_t reserved_01 : 2;
  uint8_t st_enp : 1;
  uint8_t st_enm : 1;
  uint8_t reserved__02 : 3;
  uint8_t spi_3w : 1;
  uint8_t reserved_03 : 1;
} mmc5983ma_ctrl3_t; // order inverse little endian

typedef enum {

  MMC5983MA_BW_100HZ = 0x00,
  MMC5983MA_BW_200HZ = 0x01,
  MMC5983MA_BW_400HZ = 0x02,
  MMC5983MA_BW_800HZ = 0x03,

} mmc5983ma_bw_t;

typedef enum {

  MMC5983MA_CONTINIOUS_MODE_FREQ_0HZ = 0x00,
  MMC5983MA_CONTINIOUS_MODE_FREQ_1HZ = 0x01,
  MMC5983MA_CONTINIOUS_MODE_FREQ_10HZ = 0x02,
  MMC5983MA_CONTINIOUS_MODE_FREQ_50HZ = 0x03,
  MMC5983MA_CONTINIOUS_MODE_FREQ_100HZ = 0x03,
  MMC5983MA_CONTINIOUS_MODE_FREQ_200HZ = 0x03,
  MMC5983MA_CONTINIOUS_MODE_FREQ_1000HZ = 0x03,

} mmc5983ma_continuous_mode_freq_t;

typedef struct {

  uint8_t Meas_M_Done : 1;
  uint8_t Meas_T_Done : 1;
  uint8_t reserved__01 : 2;
  uint8_t OTP_Rd_Done : 1;
  uint8_t reserved_02 : 3;
} mmc5983ma_status_t;

typedef struct {
  uint8_t internal_control0;
  uint8_t internal_control1;
  uint8_t internal_control2;
  uint8_t internal_control3;
} mmc5983ma_shadow_t;

typedef struct {
  uint8_t xout0;
  uint8_t xout1;
  uint8_t yout0;
  uint8_t yout1;
  uint8_t zout0;
  uint8_t zout1;
  uint8_t xyzout2;
  uint8_t tout;
  uint32_t xraw_1;
  uint32_t yraw_1;
  uint32_t zraw_1;
  uint32_t xraw_2;
  uint32_t yraw_2;
  uint32_t zraw_2;
} mmc5983ma_raw_magneto_data_t;

typedef struct {
  float x;
  float y;
  float z;

} mmc5983ma_magneto_data_t;

typedef int32_t (*memsicdev_write_ptr)(void *, uint8_t, const uint8_t *,
                                       uint16_t);
typedef int32_t (*memsicdev_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);
typedef void (*memsicdev_mdelay_ptr)(uint32_t millisec);

typedef struct {
  /** Component mandatory fields **/
  memsicdev_write_ptr write_reg;
  memsicdev_read_ptr read_reg;
  /** Component optional fields **/
  memsicdev_mdelay_ptr mdelay;
  /** Customizable optional pointer **/
  void *handle;

  /** private data **/
  void *priv_data;
} memsicdev_ctx_t;

int32_t mmc5983ma_read_reg(const memsicdev_ctx_t *ctx, uint8_t reg,
                           uint8_t *data, uint16_t len);
int32_t mmc5983ma_write_reg(const memsicdev_ctx_t *ctx, uint8_t reg,
                            uint8_t *data, uint16_t len);

int32_t mmc5983ma_device_id_get(const memsicdev_ctx_t *ctx, uint8_t *val);

int32_t mmc5983ma_status_get(const memsicdev_ctx_t *ctx,
                             mmc5983ma_status_t *val);

// internal 0
int32_t mmc5983ma_meas_done_int_set(const memsicdev_ctx_t *ctx, uint8_t val);
int32_t mmc5983ma_meas_done_int_get(const memsicdev_ctx_t *ctx, uint8_t *val);

int32_t
mmc5983ma_take_magnetic_field_measurement_set(const memsicdev_ctx_t *ctx,
                                              uint8_t val);

int32_t mmc5983ma_take_temperature_measurement_set(const memsicdev_ctx_t *ctx,
                                                   uint8_t val);

int32_t mmc5983ma_auto_sr_set(const memsicdev_ctx_t *ctx, uint8_t val);
int32_t mmc5983ma_auto_sr_get(const memsicdev_ctx_t *ctx, uint8_t *val);

int32_t mmc5983ma_set_operation_set(const memsicdev_ctx_t *ctx, uint8_t val);
int32_t mmc5983ma_reset_operation_set(const memsicdev_ctx_t *ctx, uint8_t val);

// internal 1
int32_t mmc5983ma_bandwith_set(const memsicdev_ctx_t *ctx, mmc5983ma_bw_t val);
int32_t mmc5983ma_bandwith_get(const memsicdev_ctx_t *ctx, mmc5983ma_bw_t *val);

int32_t mmc5983ma_x_inhibit_set(const memsicdev_ctx_t *ctx, uint8_t val);
int32_t mmc5983ma_x_inhibit_get(const memsicdev_ctx_t *ctx, uint8_t *val);

int32_t mmc5983ma_yz_inhibit_set(const memsicdev_ctx_t *ctx, uint8_t val);
int32_t mmc5983ma_yz_inhibit_get(const memsicdev_ctx_t *ctx, uint8_t *val);

int32_t mmc5983ma_reset(const memsicdev_ctx_t *ctx);

// internal 2
int32_t mmc5983ma_cm_freq_set(const memsicdev_ctx_t *ctx,
                              mmc5983ma_continuous_mode_freq_t val);
int32_t mmc5983ma_cm_freq_get(const memsicdev_ctx_t *ctx,
                              mmc5983ma_continuous_mode_freq_t *val);

int32_t mmc5983ma_cmm_en_set(const memsicdev_ctx_t *ctx, uint8_t val);
int32_t mmc5983ma_cmm_en_get(const memsicdev_ctx_t *ctx, uint8_t *val);

int32_t mmc5983ma_prd_set_set(const memsicdev_ctx_t *ctx, uint8_t val);
int32_t mmc5983ma_prd_set_get(const memsicdev_ctx_t *ctx, uint8_t *val);

int32_t mmc5983ma_en_prd_set_set(const memsicdev_ctx_t *ctx, uint8_t val);
int32_t mmc5983ma_en_prd_set_get(const memsicdev_ctx_t *ctx, uint8_t *val);

// internal 3

int32_t mmc5983ma_set_enp_set(const memsicdev_ctx_t *ctx, uint8_t val);
int32_t mmc5983ma_set_enp_get(const memsicdev_ctx_t *ctx, uint8_t *val);

int32_t mmc5983ma_set_enm_set(const memsicdev_ctx_t *ctx, uint8_t val);
int32_t mmc5983ma_set_enm_get(const memsicdev_ctx_t *ctx, uint8_t *val);

int32_t mmc5983ma_spi_3w_set(const memsicdev_ctx_t *ctx, uint8_t val);
int32_t mmc5983ma_spi_3w_get(const memsicdev_ctx_t *ctx, uint8_t *val);

// data register

int32_t
mmc5983ma_raw_magnetic_field_measurement_get(const memsicdev_ctx_t *ctx,
                                             mmc5983ma_raw_magneto_data_t *raw);
int32_t
mmc5983ma_magnetic_field_measurement_get(const memsicdev_ctx_t *ctx,
                                         mmc5983ma_raw_magneto_data_t *raw,
                                         mmc5983ma_magneto_data_t *val);
#ifdef __cplusplus
}
#endif

#endif
