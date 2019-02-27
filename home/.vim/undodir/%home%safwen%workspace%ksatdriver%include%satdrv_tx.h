Vim�UnDo� ��H�e��G�� �����j"���
�g6�)��   �                                  [�x.    _�                            ����                                                                                                                                                                                                                                                                                                                                                             [�j�    �         �      #include "ksatdriver_mbd.h"5�_�                     &        ����                                                                                                                                                                                                                                                                                                                                                             [�x-     �               �   #ifndef __SATDRV_TX_H__   #define __SATDRV_TX_H__       #include <linux/types.h>   #include <linux/skbuff.h>       !#include "ksatdriver_mbd_burst.h"   #include "ksatdriver_types.h"   #include "ksatdriver_rle.h"   #include "satdrv.h"           struct satdev_tx ;       struct satfilter_tx_cb {   	satfilter_tx_t  process;   	const void      *ctxt;   };       enum satdrv_tx_type {   	SATDRV_TX_DVB_RCS,   	SATDRV_TX_NB   } ;       Jint satdrv_tx_init(struct satdev_tx **tx_dev, enum satdrv_tx_type tx_type,   &                   void * client_dev);       1void satdev_tx_release(struct satdev_tx *tx_dev);   1int satdev_tx_add_queue(struct satdev_tx *tx_dev,   			u8 queue_id,   (			const struct queue_params_t *params);   1int satdev_tx_del_queue(struct satdev_tx *tx_dev,   			u8 queue_id);       7void satdev_tx_clear_queues(struct satdev_tx * tx_dev);       Cint satdev_tx_perform_mbd_group_insertion(struct satdev_tx *tx_dev,   (				    struct mbd_group *sig_mbd_group,   				    u32 sig_mbd_len,   ,				    struct mbd_group **filled_mbd_group,   				    u32 * filled_mbd_len);   Pint satdev_tx_packet(struct satdev_tx *tx_dev, struct sk_buff *skb, int *ndrop);   =int satdev_tx_set_disable_insertion(struct satdev_tx *tx_dev,   				    u8 state);   =int satdev_tx_get_disable_insertion(struct satdev_tx *tx_dev,   				    u8 * state);   8int satdev_tx_get_queue_params(struct satdev_tx *tx_dev,   			       u8 queue_id,   )			       struct queue_params_t *params);   7int satdev_tx_get_queue_infos(struct satdev_tx *tx_dev,   			      u8 queue_id,   &			      struct queue_infos_t *infos);       3void satdev_tx_set_filter(struct satdev_tx *tx_dev,   6                          satfilter_tx_t satfilter_tx,   9                          const void *satfilter_ctxt_tx);       /**   % * @brief Reset queue_infos statistic   ' * @param[in] tx_dev TX module context.   / * @param[in] queue_id Index of queue to reset.    */   Gint satdev_tx_reset_queue_infos(struct satdev_tx *tx_dev, u8 queue_id);       /**   5 * @brief Set the RLE configuration for transmission.    *    * @ingroup BC    *   F * @param[in] tx_dev The tx context (previously provided by the "probe    * callback" to the client).   J * @param[in]  buffer  The configuration (Frame Payload Format Descriptor)    *   ( * @returns <b>0</b> if everything is OK   D * @returns a value defined in <b>asm-generic/errno-base.h</b> if an    * error occured    */   6int satdev_tx_set_rle_config(struct satdev_tx *tx_dev,   D                             const struct rle_config_buffer buffer);       /**   $ * @brief Reset the RLE transmitter.    *    * @ingroup BC    *   F * @param[in] tx_dev The tx context (previously provided by the "probe    * callback" to the client).   L * @param[in] value  The value written. If value is 0, nothing is done, else   0 *                   the transmitter is reseted.    *   ( * @returns <b>0</b> if everything is OK   D * @returns a value defined in <b>asm-generic/errno-base.h</b> if an    * error occured    */   =int satdev_tx_reset_rle_transmitter(struct satdev_tx *tx_dev,   5                                    const int value);       /**   : * @brief Set the RLE payload label for control et trafic.    *    * @ingroup BC    *   F * @param[in] tx_dev The tx context (previously provided by the "probe    * callback" to the client).   % * @param[out]  pl  le payload label.    *   ( * @returns <b>0</b> if everything is OK   D * @returns a value defined in <b>asm-generic/errno-base.h</b> if an    * error occured    */   5int satdev_tx_set_rle_control_traffic_burst_payload (   !        struct satdev_tx *tx_dev,   ;        const struct rle_control_traffic_burst_payload pl);       /**   B * @brief Get the RLE configuration parameters flags transmission.    *    * @ingroup BC    *   C * @param[in] tx_dev The tx context containing the flags set during    * configuration.   @ * @param[out]  context  The configuration parameters structure.    *   ( * @returns <b>0</b> if everything is OK   D * @returns a value defined in <b>asm-generic/errno-base.h</b> if an    * error occured    */   int satdev_tx_get_rle_config (   !        struct satdev_tx *tx_dev,   %        struct rle_context *context);   /**   ? * @brief Retrieve the RLE logon overhead from the RLE library.    *    * @ingroup BC    *   F * @param[in] tx_dev The tx context (previously provided by the "probe    * callback" to the client).   K * @param[out]  rle_logon_overhead  The retrieved RLE logon overhead value.    *   ( * @returns <b>0</b> if everything is OK   D * @returns a value defined in <b>asm-generic/errno-base.h</b> if an    * error occured    */   >int satdev_tx_get_rle_logon_overhead(struct satdev_tx *tx_dev,   >                                     u32 *rle_logon_overhead);       /**   A * @brief Retrieve the RLE control overhead from the RLE library.    *    * @ingroup BC    *   F * @param[in] tx_dev The tx context (previously provided by the "probe    * callback" to the client).   O * @param[out]  rle_control_overhead  The retrieved RLE control overhead value.    *   ( * @returns <b>0</b> if everything is OK   D * @returns a value defined in <b>asm-generic/errno-base.h</b> if an    * error occured    */   @int satdev_tx_get_rle_control_overhead(struct satdev_tx *tx_dev,   B                                       u32 *rle_control_overhead);       /**   I * @brief Retrieve the RLE traffic control overhead from the RLE library.    *    * @ingroup BC    *   F * @param[in] tx_dev The tx context (previously provided by the "probe    * callback" to the client).   O * @param[out]  rle_traffic_control_overhead  The retrieved RLE traffic control   = *                                            overhead value.    *   ( * @returns <b>0</b> if everything is OK   D * @returns a value defined in <b>asm-generic/errno-base.h</b> if an    * error occured    */   /int satdev_tx_get_rle_traffic_control_overhead(   E        struct satdev_tx *tx_dev, u32 *rle_traffic_control_overhead);       #endif5��