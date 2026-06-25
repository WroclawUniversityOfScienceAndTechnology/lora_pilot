#ifndef _ESP_OTA_OPS_H
#define _ESP_OTA_OPS_H

#include "esp_partition.h"
#include <stdint.h>
#include <cassert>
#include <cstdint>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct {
        char version[32];
        char project_name[32];
        char time[32];
        char date[32];
        char idf_ver[32];
    } esp_app_desc_t;

    const esp_app_desc_t* esp_app_get_description(void);

    typedef int esp_err_t;

/* Definitions for error constants. */
#define ESP_OK 0    /*!< esp_err_t value indicating success (no error) */
#define ESP_FAIL -1 /*!< Generic esp_err_t code indicating failure */

#define ESP_ERR_NO_MEM 0x101           /*!< Out of memory */
#define ESP_ERR_INVALID_ARG 0x102      /*!< Invalid argument */
#define ESP_ERR_INVALID_STATE 0x103    /*!< Invalid state */
#define ESP_ERR_INVALID_SIZE 0x104     /*!< Invalid size */
#define ESP_ERR_NOT_FOUND 0x105        /*!< Requested resource not found */
#define ESP_ERR_NOT_SUPPORTED 0x106    /*!< Operation or feature not supported */
#define ESP_ERR_TIMEOUT 0x107          /*!< Operation timed out */
#define ESP_ERR_INVALID_RESPONSE 0x108 /*!< Received response was invalid */
#define ESP_ERR_INVALID_CRC 0x109      /*!< CRC or checksum was invalid */
#define ESP_ERR_INVALID_VERSION 0x10A  /*!< Version was invalid */
#define ESP_ERR_INVALID_MAC 0x10B      /*!< MAC address was invalid */
#define ESP_ERR_NOT_FINISHED 0x10C     /*!< There are items remained to retrieve */

#define ESP_ERR_WIFI_BASE 0x3000      /*!< Starting number of WiFi error codes */
#define ESP_ERR_MESH_BASE 0x4000      /*!< Starting number of MESH error codes */
#define ESP_ERR_FLASH_BASE 0x6000     /*!< Starting number of flash error codes */
#define ESP_ERR_HW_CRYPTO_BASE 0xc000 /*!< Starting number of HW cryptography module error codes */
#define ESP_ERR_MEMPROT_BASE 0xd000   /*!< Starting number of Memory Protection API error codes */

#define OTA_SIZE_UNKNOWN 0xffffffff /*!< Used for esp_ota_begin() if new image size is unknown */
#define OTA_WITH_SEQUENTIAL_WRITES                                                                                     \
    0xfffffffe /*!< Used for esp_ota_begin() if new image size is unknown and erase can be done in incremental manner  \
                  (assuming write operation is in continuous sequence) */

#define ESP_ERR_OTA_BASE 0x1500 /*!< Base error code for ota_ops api */
#define ESP_ERR_OTA_PARTITION_CONFLICT                                                                                 \
    (ESP_ERR_OTA_BASE + 0x01) /*!< Error if request was to write or erase the current running partition */
#define ESP_ERR_OTA_SELECT_INFO_INVALID                                                                                \
    (ESP_ERR_OTA_BASE + 0x02) /*!< Error if OTA data partition contains invalid content */
#define ESP_ERR_OTA_VALIDATE_FAILED (ESP_ERR_OTA_BASE + 0x03) /*!< Error if OTA app image is invalid */
#define ESP_ERR_OTA_SMALL_SEC_VER                                                                                      \
    (ESP_ERR_OTA_BASE + 0x04) /*!< Error if the firmware has a secure version less than the running firmware. */
#define ESP_ERR_OTA_ROLLBACK_FAILED                                                                                    \
    (ESP_ERR_OTA_BASE +                                                                                                \
     0x05) /*!< Error if flash does not have valid firmware in passive partition and hence rollback is not possible */
#define ESP_ERR_OTA_ROLLBACK_INVALID_STATE                                                                             \
    (ESP_ERR_OTA_BASE + 0x06) /*!< Error if current active firmware is still marked in pending validation state        \
                                 (ESP_OTA_IMG_PENDING_VERIFY), essentially first boot of firmware image post upgrade   \
                                 and hence firmware upgrade is not possible */

    typedef uint32_t esp_ota_handle_t;

    const esp_partition_t* esp_ota_get_next_update_partition(const esp_partition_t* start_from);
    esp_err_t esp_ota_begin(const esp_partition_t* partition, size_t image_size, esp_ota_handle_t* out_handle);
    esp_err_t esp_ota_abort(esp_ota_handle_t handle);
    esp_err_t esp_ota_write(esp_ota_handle_t handle, const void* data, size_t size);
    esp_err_t esp_ota_end(esp_ota_handle_t handle);
    esp_err_t esp_ota_set_boot_partition(const esp_partition_t* partition);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_OTA_OPS_H */
