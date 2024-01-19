/*
 * sm_security.h
 *
 *  Created on: Jul 18, 2023
 *      Author: Admin
 */

#ifndef COMMON_SECURITY_SM_SECURITY_H_
#define COMMON_SECURITY_SM_SECURITY_H_

typedef struct sm_security sm_security_t;

typedef struct
{
    int32_t (*encode)(sm_security_t *_this, uint8_t *_src, uint32_t _len_src, uint8_t *_dest, uint32_t *_len_dest);
    int32_t (*decode)(sm_security_t *_this, uint8_t *_src, uint32_t _len_src, uint8_t *_dest, uint32_t *_len_dest);
    int32_t (*gen_key)(sm_security_t *_this);
} sm_security_func_t;

struct sm_security
{
    char key[128];
    sm_security_func_t *func;
};

/**
 * @brief
 * @param _this
 * @param _src
 * @param _len_src
 * @param _dest
 * @param _len_dest
 * @return  0: success | -1 : false
 */
static inline int32_t sm_security_encode(sm_security_t *_this, uint8_t *_src, uint32_t _len_src, uint8_t *_dest,
        uint32_t *_len_dest)
{
    return _this->func->encode (_this, _src, _len_src, _dest, _len_dest);
}

/**
 * @brief
 * @param _this
 * @param _src
 * @param _len_src
 * @param _dest
 * @param _len_dest
 * @return  0: success | -1 : false
 */
static inline int32_t sm_security_decode(sm_security_t *_this, uint8_t *_src, uint32_t _len_src, uint8_t *_dest,
        uint32_t *_len_dest)
{
    return _this->func->decode (_this, _src, _len_src, _dest, _len_dest);
}
/**
 * @brief
 * @param _this
 * @return  0: success | -1 : false
 */
static inline int32_t sm_security_gen_key(sm_security_t *_this)
{
    return _this->func->gen_key (_this);
}

#endif /* COMMON_SECURITY_SM_SECURITY_H_ */
