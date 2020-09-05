/** @file
 *  @brief Bluetooth Mesh Access Layer APIs.
 */

/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __BT_MESH_ACCESS_H
#define __BT_MESH_ACCESS_H

/**
 * @brief Bluetooth Mesh Access Layer
 * @defgroup bt_mesh_access Bluetooth Mesh Access Layer
 * @ingroup bt_mesh
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#define BT_MESH_ADDR_UNASSIGNED   0x0000
#define BT_MESH_ADDR_ALL_NODES    0xffff
#define BT_MESH_ADDR_PROXIES      0xfffc
#define BT_MESH_ADDR_FRIENDS      0xfffd
#define BT_MESH_ADDR_RELAYS       0xfffe

#define BT_MESH_KEY_UNUSED        0xffff
#define BT_MESH_KEY_DEV           0xfffe

/** Helper to define a mesh element within an array.
 *
 *  In case the element has no SIG or Vendor models the helper
 *  macro BT_MESH_MODEL_NONE can be given instead.
 *
 *  @param _loc       Location Descriptor.
 *  @param _mods      Array of models.
 *  @param _vnd_mods  Array of vendor models.
 */
#define BT_MESH_ELEM(_loc, _mods, _vnd_mods)        \
{                                                   \
	.loc              = (_loc),                 \
	.model_count      = ARRAY_SIZE(_mods),      \
	.models           = (_mods),                \
	.vnd_model_count  = ARRAY_SIZE(_vnd_mods),  \
	.vnd_models       = (_vnd_mods),            \
}

/** Abstraction that describes a Mesh Element */
struct bt_mesh_elem {
	/* Unicast Address. Set at runtime during provisioning. */
	u16_t addr; //单播地址，每个element都有一个，且同一mesh网络中不重复，provisioning时被分配。

	/* Location Descriptor (GATT Bluetooth Namespace Descriptors) */
	const u16_t loc;

	const u8_t model_count; //model数量
	const u8_t vnd_model_count; //vnd model数量。

	struct bt_mesh_model * const models; //指针，指向models结构数组首地址，models被应用程序初始化。
	struct bt_mesh_model * const vnd_models; //指针，指向vnd models结构结构数组首地址，models被应用程序初始化。
};

/* Foundation Models 内建的models，协议栈已实现其消息处理等操作*/
#define BT_MESH_MODEL_ID_CFG_SRV                   0x0000
#define BT_MESH_MODEL_ID_CFG_CLI                   0x0001
#define BT_MESH_MODEL_ID_HEALTH_SRV                0x0002
#define BT_MESH_MODEL_ID_HEALTH_CLI                0x0003

/* Models from the Mesh Model Specification sig基于Mesh Model Specification定义好的的model，它
	们的opcode都定义好了，但opcode对应的功能需用户自已实现。 */
#define BT_MESH_MODEL_ID_GEN_ONOFF_SRV             0x1000
#define BT_MESH_MODEL_ID_GEN_ONOFF_CLI             0x1001
#define BT_MESH_MODEL_ID_GEN_LEVEL_SRV             0x1002
#define BT_MESH_MODEL_ID_GEN_LEVEL_CLI             0x1003
#define BT_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_SRV    0x1004
#define BT_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_CLI    0x1005
#define BT_MESH_MODEL_ID_GEN_POWER_ONOFF_SRV       0x1006
#define BT_MESH_MODEL_ID_GEN_POWER_ONOFF_SETUP_SRV 0x1007
#define BT_MESH_MODEL_ID_GEN_POWER_ONOFF_CLI       0x1008
#define BT_MESH_MODEL_ID_GEN_POWER_LEVEL_SRV       0x1009
#define BT_MESH_MODEL_ID_GEN_POWER_LEVEL_SETUP_SRV 0x100a
#define BT_MESH_MODEL_ID_GEN_POWER_LEVEL_CLI       0x100b
#define BT_MESH_MODEL_ID_GEN_BATTERY_SRV           0x100c
#define BT_MESH_MODEL_ID_GEN_BATTERY_CLI           0x100d
#define BT_MESH_MODEL_ID_GEN_LOCATION_SRV          0x100e
#define BT_MESH_MODEL_ID_GEN_LOCATION_SETUPSRV     0x100f
#define BT_MESH_MODEL_ID_GEN_LOCATION_CLI          0x1010
#define BT_MESH_MODEL_ID_GEN_ADMIN_PROP_SRV        0x1011
#define BT_MESH_MODEL_ID_GEN_MANUFACTURER_PROP_SRV 0x1012
#define BT_MESH_MODEL_ID_GEN_USER_PROP_SRV         0x1013
#define BT_MESH_MODEL_ID_GEN_CLIENT_PROP_SRV       0x1014
#define BT_MESH_MODEL_ID_GEN_PROP_CLI              0x1015
#define BT_MESH_MODEL_ID_SENSOR_SRV                0x1100
#define BT_MESH_MODEL_ID_SENSOR_SETUP_SRV          0x1101
#define BT_MESH_MODEL_ID_SENSOR_CLI                0x1102
#define BT_MESH_MODEL_ID_TIME_SRV                  0x1200
#define BT_MESH_MODEL_ID_TIME_SETUP_SRV            0x1201
#define BT_MESH_MODEL_ID_TIME_CLI                  0x1202
#define BT_MESH_MODEL_ID_SCENE_SRV                 0x1203
#define BT_MESH_MODEL_ID_SCENE_SETUP_SRV           0x1204
#define BT_MESH_MODEL_ID_SCENE_CLI                 0x1205
#define BT_MESH_MODEL_ID_SCHEDULER_SRV             0x1206
#define BT_MESH_MODEL_ID_SCHEDULER_SETUP_SRV       0x1207
#define BT_MESH_MODEL_ID_SCHEDULER_CLI             0x1208
#define BT_MESH_MODEL_ID_LIGHT_LIGHTNESS_SRV       0x1300
#define BT_MESH_MODEL_ID_LIGHT_LIGHTNESS_SETUP_SRV 0x1301
#define BT_MESH_MODEL_ID_LIGHT_LIGHTNESS_CLI       0x1302
#define BT_MESH_MODEL_ID_LIGHT_CTL_SRV             0x1303
#define BT_MESH_MODEL_ID_LIGHT_CTL_SETUP_SRV       0x1304
#define BT_MESH_MODEL_ID_LIGHT_CTL_CLI             0x1305
#define BT_MESH_MODEL_ID_LIGHT_CTL_TEMP_SRV        0x1306
#define BT_MESH_MODEL_ID_LIGHT_HSL_SRV             0x1307
#define BT_MESH_MODEL_ID_LIGHT_HSL_SETUP_SRV       0x1308
#define BT_MESH_MODEL_ID_LIGHT_HSL_CLI             0x1309
#define BT_MESH_MODEL_ID_LIGHT_HSL_HUE_SRV         0x130a
#define BT_MESH_MODEL_ID_LIGHT_HSL_SAT_SRV         0x130b
#define BT_MESH_MODEL_ID_LIGHT_XYL_SRV             0x130c
#define BT_MESH_MODEL_ID_LIGHT_XYL_SETUP_SRV       0x130d
#define BT_MESH_MODEL_ID_LIGHT_XYL_CLI             0x130e
#define BT_MESH_MODEL_ID_LIGHT_LC_SRV              0x130f
#define BT_MESH_MODEL_ID_LIGHT_LC_SETUPSRV         0x1310
#define BT_MESH_MODEL_ID_LIGHT_LC_CLI              0x1311

/** Message sending context.消息发送内容 */
struct bt_mesh_msg_ctx {
	/** NetKey Index of the subnet to send the message on.要发送消息的子网的netkey index */
	u16_t net_idx; //因为有多个net key，需用net_idx选择。每个net_key对应一个子网?

	/** AppKey Index to encrypt the message with. */
	u16_t app_idx; //因为有多个app key，需用app_idx选择。

	/** Remote address. */
	u16_t addr; //消息发送目标地址

	/** Destination address of a received message. Not used for sending. */
	u16_t recv_dst; //收到的消息定义的目标地址，这不会用来用于本消息发送

	/** Received TTL value. Not used for sending. */
	u8_t  recv_ttl:7;

	/** Force sending reliably by using segment acknowledgement */
	u8_t  send_rel:1;

	/** TTL, or BT_MESH_TTL_DEFAULT for default TTL. */
	u8_t  send_ttl;
};

struct bt_mesh_model_op {
	/* OpCode encoded using the BT_MESH_MODEL_OP_* macros */
	const u32_t  opcode; //操作码，指示消息接收方要实现的操作，每个操作码都对应一个操作函数，用于实现应用程序期望的操作

	/* Minimum required message length */
	const size_t min_len; //需要的最小的消息长度

	/* Message handler for the opcode 操作码对应的操作函数，需应用程序实现*/
	void (*const func)(struct bt_mesh_model *model,
			   struct bt_mesh_msg_ctx *ctx,
			   struct os_mbuf *buf);
};

#define BT_MESH_MODEL_OP_1(b0) (b0)
#define BT_MESH_MODEL_OP_2(b0, b1) (((b0) << 8) | (b1))
#define BT_MESH_MODEL_OP_3(b0, cid) ((((b0) << 16) | 0xc00000) | (cid))

#define BT_MESH_MODEL_OP_END { 0, 0, NULL }
#define BT_MESH_MODEL_NO_OPS ((struct bt_mesh_model_op []) \
			      { BT_MESH_MODEL_OP_END })

/** Helper to define an empty model array */
#define BT_MESH_MODEL_NONE ((struct bt_mesh_model []){})

#define BT_MESH_MODEL(_id, _op, _pub, _user_data)                            \
{                                                                            \
	.id = (_id),                                                         \
	.op = _op,                                                           \
	.keys = { [0 ... (CONFIG_BT_MESH_MODEL_KEY_COUNT - 1)] =             \
			BT_MESH_KEY_UNUSED },                                \
	.pub = _pub,                                                         \
	.groups = { [0 ... (CONFIG_BT_MESH_MODEL_GROUP_COUNT - 1)] =         \
			BT_MESH_ADDR_UNASSIGNED },                           \
	.user_data = _user_data,                                             \
}

#define BT_MESH_MODEL_VND(_company, _id, _op, _pub, _user_data)              \
{                                                                            \
	.vnd.company = (_company),                                           \
	.vnd.id = (_id),                                                     \
	.op = _op,                                                           \
	.pub = _pub,                                                         \
	.keys = { [0 ... (CONFIG_BT_MESH_MODEL_KEY_COUNT - 1)] =             \
			BT_MESH_KEY_UNUSED },                                \
	.groups = { [0 ... (CONFIG_BT_MESH_MODEL_GROUP_COUNT - 1)] =         \
			BT_MESH_ADDR_UNASSIGNED },                           \
	.user_data = _user_data,                                             \
}

/** @def BT_MESH_TRANSMIT
 *
 *  @brief Encode transmission count & interval steps.
 *
 *  @param count   Number of retransmissions (first transmission is excluded).
 *  @param int_ms  Interval steps in milliseconds. Must be greater than 0,
 *                 less than or equal to 320, and a multiple of 10.
 *
 *  @return Mesh transmit value that can be used e.g. for the default
 *          values of the configuration model data.
 */
#define BT_MESH_TRANSMIT(count, int_ms) ((count) | (((int_ms / 10) - 1) << 3))

/** @def BT_MESH_TRANSMIT_COUNT
 *
 *  @brief Decode transmit count from a transmit value.
 *
 *  @param transmit Encoded transmit count & interval value.
 *
 *  @return Transmission count (actual transmissions is N + 1).
 */
#define BT_MESH_TRANSMIT_COUNT(transmit) (((transmit) & (u8_t)BIT_MASK(3)))

/** @def BT_MESH_TRANSMIT_INT
 *
 *  @brief Decode transmit interval from a transmit value.
 *
 *  @param transmit Encoded transmit count & interval value.
 *
 *  @return Transmission interval in milliseconds.
 */
#define BT_MESH_TRANSMIT_INT(transmit) ((((transmit) >> 3) + 1) * 10)

/** @def BT_MESH_PUB_TRANSMIT
 *
 *  @brief Encode Publish Retransmit count & interval steps.
 *
 *  @param count   Number of retransmissions (first transmission is excluded).
 *  @param int_ms  Interval steps in milliseconds. Must be greater than 0
 *                 and a multiple of 50.
 *
 *  @return Mesh transmit value that can be used e.g. for the default
 *          values of the configuration model data.
 */
#define BT_MESH_PUB_TRANSMIT(count, int_ms) BT_MESH_TRANSMIT(count,           \
							     (int_ms) / 5)

/** @def BT_MESH_PUB_TRANSMIT_COUNT
 *
 *  @brief Decode Pubhlish Retransmit count from a given value.
 *
 *  @param transmit Encoded Publish Retransmit count & interval value.
 *
 *  @return Retransmission count (actual transmissions is N + 1).
 */
#define BT_MESH_PUB_TRANSMIT_COUNT(transmit) BT_MESH_TRANSMIT_COUNT(transmit)

/** @def BT_MESH_PUB_TRANSMIT_INT
 *
 *  @brief Decode Publish Retransmit interval from a given value.
 *
 *  @param transmit Encoded Publish Retransmit count & interval value.
 *
 *  @return Transmission interval in milliseconds.
 */
#define BT_MESH_PUB_TRANSMIT_INT(transmit) ((((transmit) >> 3) + 1) * 50)

/** Model publication context. */
struct bt_mesh_model_pub {
	/** The model the context belongs to. Initialized by the stack. */
	struct bt_mesh_model *mod; //本结构所属model。

	u16_t addr;         /**< Publish Address. 发布地址 */
	u16_t key;          /**< Publish AppKey Index. */

	u8_t  ttl;          /**< Publish Time to Live. 消息存活时间 */
	u8_t  retransmit;   /**< Retransmit Count & Interval Steps. 重传次数*/
	u8_t  period;       /**< Publish Period. 发布周期 */
	u8_t  period_div:4, /**< Divisor for the Period. */
	      cred:1,       /**< Friendship Credentials Flag. 友元证书标记 */
	      count:3;      /**< Retransmissions left. 剩余重传次数 */

	u32_t period_start; /**< Start of the current period. */

	/** @brief Publication buffer, containing the publication message.
	 *
	 *  The application is expected to initialize this with
	 *  a valid net_buf_simple pointer, with the help of e.g.
	 *  the NET_BUF_SIMPLE() macro. The publication buffer must
	 *  contain a valid publication message before calling the
	 *  bt_mesh_model_publish() API or after the publication's
	 *  @ref bt_mesh_model_pub.update callback has been called
	 *  and returned success. The buffer must be created outside
	 *  of function context, i.e. it must not be on the stack.
	 *  This is most conveniently acheived by creating it inline
	 *  when declaring the publication context:
	 *
	 *      static struct bt_mesh_model_pub my_pub = {
	 *              .msg = NET_BUF_SIMPLE(size),
	 *      };
	 */
	struct os_mbuf *msg;

	/** @brief Callback for updating the publication buffer.
	 *
	 *  When set to NULL, the model is assumed not to support
	 *  periodic publishing. When set to non-NULL the callback
	 *  will be called periodically and is expected to update
	 *  @ref bt_mesh_model_pub.msg with a valid publication
	 *  message.
	 *
	 *  @param mod The Model the Publication Context belogs to.
	 *
	 *  @return Zero on success or (negative) error code otherwise.
	 */
	int (*update)(struct bt_mesh_model *mod);

	/** Publish Period Timer. Only for stack-internal use. */
	struct k_delayed_work timer;
};

/** Abstraction that describes a Mesh Model instance */
struct bt_mesh_model {
	/* model id。sig定义了一系列model，并对它们做了编号，注意，模型区分srv和cli两种不同的角色。*/
	union {
		const u16_t id;
		struct {
			u16_t company;
			u16_t id;
		} vnd;
	};

	/* Internal information, mainly for persistent storage */
	u8_t  elem_idx;   /* Belongs to Nth element 属于第n个element */
	u8_t  mod_idx;    /* Is the Nth model in the element element的第n个model */
	u16_t flags;      /* Information about what has changed 一些标记，用来记录一些改变 */

	/* Model Publication */
	struct bt_mesh_model_pub * const pub;

	/* AppKey List */
	u16_t keys[CONFIG_BT_MESH_MODEL_KEY_COUNT]; //可由分配器配置，或应用程序写好。

	/* Subscription List (group or virtual addresses) */
	u16_t groups[CONFIG_BT_MESH_MODEL_GROUP_COUNT]; //可由分配器配置，或应用程序写好。

	const struct bt_mesh_model_op * const op; //模型的操作码数组，定义了model能实现的功能。

	/* Model-specific user data */
	void *user_data; //模型的用户数据，应用程序定义。
};

/* 定义消息发送回调函数数 */
struct bt_mesh_send_cb {
	void (*start)(u16_t duration, int err, void *cb_data); //发送开始
	void (*end)(int err, void *cb_data); //结束
};

void bt_mesh_model_msg_init(struct os_mbuf *msg, u32_t opcode);

/** Special TTL value to request using configured default TTL */
#define BT_MESH_TTL_DEFAULT 0xff

/** Maximum allowed TTL value */
#define BT_MESH_TTL_MAX     0x7f

/**
 * @brief Send an Access Layer message.
 *
 * @param model     Mesh (client) Model that the message belongs to.
 * @param ctx       Message context, includes keys, TTL, etc.
 * @param msg       Access Layer payload (the actual message to be sent).
 * @param cb        Optional "message sent" callback.
 * @param cb_data   User data to be passed to the callback.
 *
 * @return 0 on success, or (negative) error code on failure.
 */
int bt_mesh_model_send(struct bt_mesh_model *model,
		       struct bt_mesh_msg_ctx *ctx,
		       struct os_mbuf *msg,
		       const struct bt_mesh_send_cb *cb,
		       void *cb_data);

/**
 * @brief Send a model publication message.
 *
 * Before calling this function, the user needs to ensure that the model
 * publication message (@ref bt_mesh_model_pub.msg) contains a valid
 * message to be sent. Note that this API is only to be used for
 * non-period publishing. For periodic publishing the app only needs
 * to make sure that @ref bt_mesh_model_pub.msg contains a valid message
 * whenever the @ref bt_mesh_model_pub.update callback is called.
 * 在调用这个函数以前，用户需确保准备好要发送的消息（bt_mesh_model_pub.msg中有内容）
 * 此函数只用于非周期性发布。对于周期性发布，用户确保bt_mesh_model_pub.update被调用时，
 * bt_mesh_model_pub.msg有消息，
 *
 * @param model  Mesh (client) Model that's publishing the message.
 *
 * @return 0 on success, or (negative) error code on failure.
 */
int bt_mesh_model_publish(struct bt_mesh_model *model);

/**
 * @brief Get the element that a model belongs to.
 *
 * @param mod  Mesh model.
 *
 * @return Pointer to the element that the given model belongs to.
 */
struct bt_mesh_elem *bt_mesh_model_elem(struct bt_mesh_model *mod);

/** Node Composition node结构，此结构描述了一个node，设备没加入mesh网络前叫device,加入后叫node */
struct bt_mesh_comp {
	u16_t cid;
	u16_t pid;
	u16_t vid;

	size_t elem_count;   //element数量，最少要一个
	struct bt_mesh_elem *elem;
};

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __BT_MESH_ACCESS_H */
